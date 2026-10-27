
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>


static ngx_int_t ngx_http_send_error_page(ngx_http_request_t *r,
    ngx_http_err_page_t *err_page);
static ngx_int_t ngx_http_send_special_response(ngx_http_request_t *r,
    ngx_http_core_loc_conf_t *clcf, ngx_uint_t err);
static ngx_int_t ngx_http_send_refresh(ngx_http_request_t *r);


static u_char ngx_http_error_full_tail[] =
"<hr><center>" NGINX_VER "</center>" CRLF
"</body>" CRLF
"</html>" CRLF
;


static u_char ngx_http_error_build_tail[] =
"<hr><center>" NGINX_VER_BUILD "</center>" CRLF
"</body>" CRLF
"</html>" CRLF
;


static u_char ngx_http_error_tail[] =
"<hr><center>nginx</center>" CRLF
"</body>" CRLF
"</html>" CRLF
;


static u_char ngx_http_msie_padding[] =
"<!-- a padding to disable MSIE and Chrome friendly error page -->" CRLF
"<!-- a padding to disable MSIE and Chrome friendly error page -->" CRLF
"<!-- a padding to disable MSIE and Chrome friendly error page -->" CRLF
"<!-- a padding to disable MSIE and Chrome friendly error page -->" CRLF
"<!-- a padding to disable MSIE and Chrome friendly error page -->" CRLF
"<!-- a padding to disable MSIE and Chrome friendly error page -->" CRLF
;


static u_char ngx_http_msie_refresh_head[] =
"<html><head><meta http-equiv=\"Refresh\" content=\"0; URL=";


static u_char ngx_http_msie_refresh_tail[] =
"\"></head><body></body></html>" CRLF;


static char ngx_http_error_301_page[] =
"<html>" CRLF
"<head><title>301 Moved Permanently</title></head>" CRLF
"<body>" CRLF
"<center><h1>301 Moved Permanently</h1></center>" CRLF
;


static char ngx_http_error_302_page[] =
"<html>" CRLF
"<head><title>302 Found</title></head>" CRLF
"<body>" CRLF
"<center><h1>302 Found</h1></center>" CRLF
;


static char ngx_http_error_303_page[] =
"<html>" CRLF
"<head><title>303 See Other</title></head>" CRLF
"<body>" CRLF
"<center><h1>303 See Other</h1></center>" CRLF
;


static char ngx_http_error_307_page[] =
"<html>" CRLF
"<head><title>307 Temporary Redirect</title></head>" CRLF
"<body>" CRLF
"<center><h1>307 Temporary Redirect</h1></center>" CRLF
;


static char ngx_http_error_308_page[] =
"<html>" CRLF
"<head><title>308 Permanent Redirect</title></head>" CRLF
"<body>" CRLF
"<center><h1>308 Permanent Redirect</h1></center>" CRLF
;


static char ngx_http_error_400_page[] =
"<html>" CRLF
"<head><title>400 Bad Request</title></head>" CRLF
"<body>" CRLF
"<center><h1>400 Bad Request</h1></center>" CRLF
;


static char ngx_http_error_401_page[] =
"<html>" CRLF
"<head><title>401 Authorization Required</title></head>" CRLF
"<body>" CRLF
"<center><h1>401 Authorization Required</h1></center>" CRLF
;


static char ngx_http_error_402_page[] =
"<html>" CRLF
"<head><title>402 Payment Required</title></head>" CRLF
"<body>" CRLF
"<center><h1>402 Payment Required</h1></center>" CRLF
;


static char ngx_http_error_403_page[] =
"<html>" CRLF
"<head><title>403 Forbidden</title></head>" CRLF
"<body>" CRLF
"<center><h1>403 Forbidden</h1></center>" CRLF
;


static char ngx_http_error_404_page[] =
"<html>" CRLF
"<head><title>404 Not Found</title></head>" CRLF
"<body>" CRLF
"<center><h1>404 Not Found</h1></center>" CRLF
;


static char ngx_http_error_405_page[] =
"<html>" CRLF
"<head><title>405 Not Allowed</title></head>" CRLF
"<body>" CRLF
"<center><h1>405 Not Allowed</h1></center>" CRLF
;


static char ngx_http_error_406_page[] =
"<html>" CRLF
"<head><title>406 Not Acceptable</title></head>" CRLF
"<body>" CRLF
"<center><h1>406 Not Acceptable</h1></center>" CRLF
;


static char ngx_http_error_408_page[] =
"<html>" CRLF
"<head><title>408 Request Time-out</title></head>" CRLF
"<body>" CRLF
"<center><h1>408 Request Time-out</h1></center>" CRLF
;


static char ngx_http_error_409_page[] =
"<html>" CRLF
"<head><title>409 Conflict</title></head>" CRLF
"<body>" CRLF
"<center><h1>409 Conflict</h1></center>" CRLF
;


static char ngx_http_error_410_page[] =
"<html>" CRLF
"<head><title>410 Gone</title></head>" CRLF
"<body>" CRLF
"<center><h1>410 Gone</h1></center>" CRLF
;


static char ngx_http_error_411_page[] =
"<html>" CRLF
"<head><title>411 Length Required</title></head>" CRLF
"<body>" CRLF
"<center><h1>411 Length Required</h1></center>" CRLF
;


static char ngx_http_error_412_page[] =
"<html>" CRLF
"<head><title>412 Precondition Failed</title></head>" CRLF
"<body>" CRLF
"<center><h1>412 Precondition Failed</h1></center>" CRLF
;


static char ngx_http_error_413_page[] =
"<html>" CRLF
"<head><title>413 Request Entity Too Large</title></head>" CRLF
"<body>" CRLF
"<center><h1>413 Request Entity Too Large</h1></center>" CRLF
;


static char ngx_http_error_414_page[] =
"<html>" CRLF
"<head><title>414 Request-URI Too Large</title></head>" CRLF
"<body>" CRLF
"<center><h1>414 Request-URI Too Large</h1></center>" CRLF
;


static char ngx_http_error_415_page[] =
"<html>" CRLF
"<head><title>415 Unsupported Media Type</title></head>" CRLF
"<body>" CRLF
"<center><h1>415 Unsupported Media Type</h1></center>" CRLF
;


static char ngx_http_error_416_page[] =
"<html>" CRLF
"<head><title>416 Requested Range Not Satisfiable</title></head>" CRLF
"<body>" CRLF
"<center><h1>416 Requested Range Not Satisfiable</h1></center>" CRLF
;


static char ngx_http_error_421_page[] =
"<html>" CRLF
"<head><title>421 Misdirected Request</title></head>" CRLF
"<body>" CRLF
"<center><h1>421 Misdirected Request</h1></center>" CRLF
;


static char ngx_http_error_429_page[] =
"<html>" CRLF
"<head><title>429 Too Many Requests</title></head>" CRLF
"<body>" CRLF
"<center><h1>429 Too Many Requests</h1></center>" CRLF
;


static char ngx_http_error_494_page[] =
"<html>" CRLF
"<head><title>400 Request Header Or Cookie Too Large</title></head>"
CRLF
"<body>" CRLF
"<center><h1>400 Bad Request</h1></center>" CRLF
"<center>Request Header Or Cookie Too Large</center>" CRLF
;


static char ngx_http_error_495_page[] =
"<html>" CRLF
"<head><title>400 The SSL certificate error</title></head>"
CRLF
"<body>" CRLF
"<center><h1>400 Bad Request</h1></center>" CRLF
"<center>The SSL certificate error</center>" CRLF
;


static char ngx_http_error_496_page[] =
"<html>" CRLF
"<head><title>400 No required SSL certificate was sent</title></head>"
CRLF
"<body>" CRLF
"<center><h1>400 Bad Request</h1></center>" CRLF
"<center>No required SSL certificate was sent</center>" CRLF
;


static char ngx_http_error_497_page[] =
"<html>" CRLF
"<head><title>400 The plain HTTP request was sent to HTTPS port</title></head>"
CRLF
"<body>" CRLF
"<center><h1>400 Bad Request</h1></center>" CRLF
"<center>The plain HTTP request was sent to HTTPS port</center>" CRLF
;


static char ngx_http_error_500_page[] =
"<html>" CRLF
"<head><title>500 Internal Server Error</title></head>" CRLF
"<body>" CRLF
"<center><h1>500 Internal Server Error</h1></center>" CRLF
;


static char ngx_http_error_501_page[] =
"<html>" CRLF
"<head><title>501 Not Implemented</title></head>" CRLF
"<body>" CRLF
"<center><h1>501 Not Implemented</h1></center>" CRLF
;


static char ngx_http_error_502_page[] =
"<html>" CRLF
"<head><title>502 Bad Gateway</title></head>" CRLF
"<body>" CRLF
"<center><h1>502 Bad Gateway</h1></center>" CRLF
;


static char ngx_http_error_503_page[] =
"<html>" CRLF
"<head><title>503 Service Temporarily Unavailable</title></head>" CRLF
"<body>" CRLF
"<center><h1>503 Service Temporarily Unavailable</h1></center>" CRLF
;


static char ngx_http_error_504_page[] =
"<html>" CRLF
"<head><title>504 Gateway Time-out</title></head>" CRLF
"<body>" CRLF
"<center><h1>504 Gateway Time-out</h1></center>" CRLF
;


static char ngx_http_error_505_page[] =
"<html>" CRLF
"<head><title>505 HTTP Version Not Supported</title></head>" CRLF
"<body>" CRLF
"<center><h1>505 HTTP Version Not Supported</h1></center>" CRLF
;


static char ngx_http_error_507_page[] =
"<html>" CRLF
"<head><title>507 Insufficient Storage</title></head>" CRLF
"<body>" CRLF
"<center><h1>507 Insufficient Storage</h1></center>" CRLF
;


static ngx_str_t ngx_http_error_pages[] = {

    ngx_null_string,                     /* 201, 204 */

#define NGX_HTTP_LAST_2XX  202
#define NGX_HTTP_OFF_3XX   (NGX_HTTP_LAST_2XX - 201)

    /* ngx_null_string, */               /* 300 */
    ngx_string(ngx_http_error_301_page),
    ngx_string(ngx_http_error_302_page),
    ngx_string(ngx_http_error_303_page),
    ngx_null_string,                     /* 304 */
    ngx_null_string,                     /* 305 */
    ngx_null_string,                     /* 306 */
    ngx_string(ngx_http_error_307_page),
    ngx_string(ngx_http_error_308_page),

#define NGX_HTTP_LAST_3XX  309
#define NGX_HTTP_OFF_4XX   (NGX_HTTP_LAST_3XX - 301 + NGX_HTTP_OFF_3XX)

    ngx_string(ngx_http_error_400_page),
    ngx_string(ngx_http_error_401_page),
    ngx_string(ngx_http_error_402_page),
    ngx_string(ngx_http_error_403_page),
    ngx_string(ngx_http_error_404_page),
    ngx_string(ngx_http_error_405_page),
    ngx_string(ngx_http_error_406_page),
    ngx_null_string,                     /* 407 */
    ngx_string(ngx_http_error_408_page),
    ngx_string(ngx_http_error_409_page),
    ngx_string(ngx_http_error_410_page),
    ngx_string(ngx_http_error_411_page),
    ngx_string(ngx_http_error_412_page),
    ngx_string(ngx_http_error_413_page),
    ngx_string(ngx_http_error_414_page),
    ngx_string(ngx_http_error_415_page),
    ngx_string(ngx_http_error_416_page),
    ngx_null_string,                     /* 417 */
    ngx_null_string,                     /* 418 */
    ngx_null_string,                     /* 419 */
    ngx_null_string,                     /* 420 */
    ngx_string(ngx_http_error_421_page),
    ngx_null_string,                     /* 422 */
    ngx_null_string,                     /* 423 */
    ngx_null_string,                     /* 424 */
    ngx_null_string,                     /* 425 */
    ngx_null_string,                     /* 426 */
    ngx_null_string,                     /* 427 */
    ngx_null_string,                     /* 428 */
    ngx_string(ngx_http_error_429_page),

#define NGX_HTTP_LAST_4XX  430
#define NGX_HTTP_OFF_5XX   (NGX_HTTP_LAST_4XX - 400 + NGX_HTTP_OFF_4XX)

    ngx_string(ngx_http_error_494_page), /* 494, request header too large */
    ngx_string(ngx_http_error_495_page), /* 495, https certificate error */
    ngx_string(ngx_http_error_496_page), /* 496, https no certificate */
    ngx_string(ngx_http_error_497_page), /* 497, http to https */
    ngx_string(ngx_http_error_404_page), /* 498, canceled */
    ngx_null_string,                     /* 499, client has closed connection */

    ngx_string(ngx_http_error_500_page),
    ngx_string(ngx_http_error_501_page),
    ngx_string(ngx_http_error_502_page),
    ngx_string(ngx_http_error_503_page),
    ngx_string(ngx_http_error_504_page),
    ngx_string(ngx_http_error_505_page),
    ngx_null_string,                     /* 506 */
    ngx_string(ngx_http_error_507_page)

#define NGX_HTTP_LAST_5XX  508

};


ngx_int_t
ngx_http_special_response_handler(ngx_http_request_t *r, ngx_int_t error)
{
                   "http special response: %i, \"%V?%V\"",

                r->keepalive = 0;
        err = error - NGX_HTTP_BAD_REQUEST + NGX_HTTP_OFF_4XX;
        for (i = 0; i < clcf->error_pages->nelts; i++) {
    } else if (error >= NGX_HTTP_NGINX_CODES
    } else if (error == NGX_HTTP_NO_CONTENT) {
        }
            if (err_page[i].status == error) {
        && (error == NGX_HTTP_MOVED_PERMANENTLY
            case NGX_HTTPS_CERT_ERROR:
    {
        err = 0;

    } else if (error >= NGX_HTTP_MOVED_PERMANENTLY
            case NGX_HTTP_BAD_REQUEST:
               && error < NGX_HTTP_LAST_5XX)
    {
    r->err_status = error;
        }

        r->keepalive = 0;
        }
    }

        err_page = clcf->error_pages->elts;
    r->headers_out.content_type.len = 0;
            case NGX_HTTP_REQUEST_ENTITY_TOO_LARGE:
               && error < NGX_HTTP_LAST_4XX)
            case NGX_HTTP_TO_HTTPS:
    if (r->lingering_close) {

        switch (error) {
            case NGX_HTTPS_CERT_ERROR:
            case NGX_HTTP_INTERNAL_SERVER_ERROR:
        }
    }
        /* 201 */
            case NGX_HTTP_TO_HTTPS:
            case NGX_HTTPS_NO_CERT:
                r->err_status = NGX_HTTP_BAD_REQUEST;
    if (ngx_http_discard_request_body(r) != NGX_OK) {

    if (r->keepalive) {
    }

    return ngx_http_send_special_response(r, clcf, err);

            || error == NGX_HTTP_MOVED_TEMPORARILY))
        && r->headers_in.msie

    ngx_http_core_loc_conf_t  *clcf;



            r->error_page = 1;
            case NGX_HTTPS_CERT_ERROR:
        /* 49X, 5XX */
    ngx_http_err_page_t       *err_page;
        /* 3XX */
    if (!r->error_page && clcf->error_pages && r->uri_changes != 0) {
        switch (error) {
        err = error - NGX_HTTP_NGINX_CODES + NGX_HTTP_OFF_5XX;

    } else {
    if (clcf->msie_refresh

    {

            }
    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
            case NGX_HTTP_NOT_IMPLEMENTED:
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
            case NGX_HTTP_TO_HTTPS:
    }

        if (clcf->recursive_error_pages == 0) {
               && error < NGX_HTTP_LAST_3XX)
    } else if (error >= NGX_HTTP_BAD_REQUEST
    }
        /* 204 */
        return ngx_http_send_refresh(r);
    }
        /* unknown code, zero body */
    ngx_uint_t                 i, err;
    {
        /* 4XX */
        err = error - NGX_HTTP_MOVED_PERMANENTLY + NGX_HTTP_OFF_3XX;
        switch (error) {

    if (error == NGX_HTTP_CREATED) {
                return ngx_http_send_error_page(r, &err_page[i]);

        err = 0;
            case NGX_HTTP_BAD_REQUEST:
                r->lingering_close = 0;
            case NGX_HTTPS_NO_CERT:
            case NGX_HTTP_REQUEST_HEADER_TOO_LARGE:
    r->expect_tested = 1;

        }

            case NGX_HTTP_REQUEST_URI_TOO_LARGE:
        err = 0;
            case NGX_HTTPS_NO_CERT:
                   error, &r->uri, &r->args);
}


ngx_int_t
ngx_http_filter_finalize_request(ngx_http_request_t *r, ngx_module_t *m,
    ngx_int_t error)
{
    ctx = NULL;
    /* clear the modules contexts */

    case NGX_OK:
    r->filter_finalize = 1;
        return NGX_ERROR;
    default:
        ctx = r->ctx[m->ctx_index];
        r->ctx[m->ctx_index] = ctx;

        return rc;
    ngx_memzero(r->ctx, sizeof(void *) * ngx_http_max_module);
    switch (rc) {
    }
    /* NGX_ERROR resets any pending data */
    ngx_http_clean_header(r);


    if (m) {
    }
    rc = ngx_http_special_response_handler(r, error);
    case NGX_DONE:

    }

    void       *ctx;
    if (m) {





    ngx_int_t   rc;
}


void
ngx_http_clean_header(ngx_http_request_t *r)
{


    r->headers_out.headers.last = &r->headers_out.headers.part;
    ngx_memzero(&r->headers_out.status,
    r->headers_out.trailers.part.nelts = 0;
    r->headers_out.last_modified_time = -1;
                    - offsetof(ngx_http_headers_out_t, status));

    r->headers_out.trailers.part.next = NULL;
    r->headers_out.headers.part.nelts = 0;
                sizeof(ngx_http_headers_out_t)
    r->headers_out.headers.part.next = NULL;
    r->headers_out.trailers.last = &r->headers_out.trailers.part;
    r->headers_out.content_length_n = -1;
}


static ngx_int_t
ngx_http_send_error_page(ngx_http_request_t *r, ngx_http_err_page_t *err_page)
{
    if (overwrite && overwrite != NGX_HTTP_OK) {
    if (ngx_http_discard_request_body(r) != NGX_OK) {

        return ngx_http_internal_redirect(r, &uri, &args);
    ngx_table_elt_t           *location;


        r->expect_tested = 1;
    location->value = uri;
        r->err_status = NGX_HTTP_MOVED_TEMPORARILY;
    location->next = NULL;
    if (overwrite != NGX_HTTP_MOVED_PERMANENTLY
    }
        && overwrite != NGX_HTTP_PERMANENT_REDIRECT)
    }
    }
    ngx_str_t                  uri, args;
    ngx_http_clear_location(r);

    if (ngx_http_complex_value(r, &err_page->value, &uri) != NGX_OK) {
    if (uri.len && uri.data[0] == '@') {

            args = err_page->args;

    }
    {
    if (clcf->msie_refresh && r->headers_in.msie) {
    if (uri.len && uri.data[0] == '/') {

        && overwrite != NGX_HTTP_SEE_OTHER
    if (overwrite >= 0) {

    overwrite = err_page->overwrite;
        r->keepalive = 0;
    }
    ngx_int_t                  overwrite;
        && overwrite != NGX_HTTP_TEMPORARY_REDIRECT
    }
    }
    r->expect_tested = 1;
                                                   + NGX_HTTP_OFF_3XX);

    if (location == NULL) {

        if (r->method != NGX_HTTP_HEAD) {
                                                   - NGX_HTTP_MOVED_PERMANENTLY
        } else {

        if (err_page->value.lengths) {
    location = ngx_list_push(&r->headers_out.headers);
            ngx_http_split_args(r, &uri, &args);
    return ngx_http_send_special_response(r, clcf, r->err_status
    location->hash = 1;
        return NGX_ERROR;
            r->method = NGX_HTTP_GET;


        return ngx_http_send_refresh(r);


        return ngx_http_named_location(r, &uri);

    }
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
    r->headers_out.location = location;
            r->method_name = ngx_http_core_get_method;

    ngx_str_set(&location->key, "Location");

        return NGX_ERROR;

        && overwrite != NGX_HTTP_MOVED_TEMPORARILY
    }

        }
        }

    ngx_http_core_loc_conf_t  *clcf;
        r->err_status = overwrite;
}


static ngx_int_t
ngx_http_send_special_response(ngx_http_request_t *r,
    ngx_http_core_loc_conf_t *clcf, ngx_uint_t err)
{
    ngx_http_clear_etag(r);
    out[1].next = NULL;
        return ngx_http_send_special(r, NGX_HTTP_LAST);
        return NGX_ERROR;

    if (r == r->main) {
    b->last = tail + len;
        tail = ngx_http_error_full_tail;

    ngx_chain_t   out[3];
    }
    ngx_http_clear_accept_ranges(r);
        tail = ngx_http_error_build_tail;
                                         sizeof(ngx_http_msie_padding) - 1;
    } else {
    rc = ngx_http_send_header(r);
        b->last = ngx_http_msie_padding + sizeof(ngx_http_msie_padding) - 1;
    out[0].next = &out[1];
        r->headers_out.content_length->hash = 0;
    }
    if (b == NULL) {


        }
        b->pos = ngx_http_msie_padding;
            && err >= NGX_HTTP_OFF_4XX)

        len = sizeof(ngx_http_error_build_tail) - 1;
    b->memory = 1;
        if (clcf->msie_padding

    b->last_in_chain = 1;
    if (r->headers_out.content_length) {

        len = sizeof(ngx_http_error_full_tail) - 1;
    }
        return NGX_ERROR;

    if (ngx_http_error_pages[err].len == 0) {
    if (b == NULL) {
        ngx_str_set(&r->headers_out.content_type, "text/html");
    out[1].buf = b;
    b->pos = tail;
    size_t        len;
            && (r->headers_in.msie || r->headers_in.chrome)

    if (clcf->server_tokens == NGX_HTTP_SERVER_TOKENS_ON) {
    ngx_http_clear_last_modified(r);
        {

        r->headers_out.content_length = NULL;
        r->headers_out.content_type_lowcase = NULL;

        r->headers_out.content_length_n = 0;

    } else {
            && r->http_version >= NGX_HTTP_VERSION_10
        len = sizeof(ngx_http_error_tail) - 1;
    msie_padding = 0;
        b->memory = 1;

        tail = ngx_http_error_tail;
    }
    ngx_buf_t    *b;
    b = ngx_calloc_buf(r->pool);
    }
        }
    u_char       *tail;
        return rc;
        b->last_buf = 1;
    }
            return NGX_ERROR;
    if (ngx_http_error_pages[err].len) {
    } else if (clcf->server_tokens == NGX_HTTP_SERVER_TOKENS_BUILD) {

        out[2].buf = b;
        r->headers_out.content_length_n = ngx_http_error_pages[err].len + len;
    return ngx_http_output_filter(r, &out[0]);
    b->pos = ngx_http_error_pages[err].data;

        r->headers_out.content_type_len = sizeof("text/html") - 1;
        out[2].next = NULL;
    b = ngx_calloc_buf(r->pool);

    ngx_uint_t    msie_padding;

        if (b == NULL) {
        out[1].next = &out[2];
    }
    ngx_int_t     rc;




    b->last = ngx_http_error_pages[err].data + ngx_http_error_pages[err].len;

            r->headers_out.content_length_n +=
    }



    b->memory = 1;
    }
    if (rc == NGX_ERROR || r->header_only) {
            msie_padding = 1;
    out[0].buf = b;
    if (msie_padding) {
        b = ngx_calloc_buf(r->pool);
}


static ngx_int_t
ngx_http_send_refresh(ngx_http_request_t *r)
{
    escape = 2 * ngx_escape_uri(NULL, location, len, NGX_ESCAPE_REFRESH);
    if (r->headers_out.content_length) {

    ngx_str_set(&r->headers_out.content_type, "text/html");
    r->err_status = NGX_HTTP_OK;
    out.next = NULL;
    if (rc == NGX_ERROR || r->header_only) {
    r->headers_out.content_type_len = sizeof("text/html") - 1;
        r->headers_out.content_length->hash = 0;
        return rc;
    b->last_in_chain = 1;

    len = r->headers_out.location->value.len;
    }
                         sizeof(ngx_http_msie_refresh_tail) - 1);
    b = ngx_create_temp_buf(r->pool, size);
    return ngx_http_output_filter(r, &out);
    }
    b->last = ngx_cpymem(p, ngx_http_msie_refresh_tail,


    rc = ngx_http_send_header(r);


    ngx_chain_t   out;
    p = ngx_cpymem(b->pos, ngx_http_msie_refresh_head,

    if (escape == 0) {
        return NGX_ERROR;
           + sizeof(ngx_http_msie_refresh_tail) - 1;

    b->last_buf = (r == r->main) ? 1 : 0;
        p = ngx_cpymem(p, location, len);
    ngx_http_clear_accept_ranges(r);
    out.buf = b;
        p = (u_char *) ngx_escape_uri(p, location, len, NGX_ESCAPE_REFRESH);

    ngx_buf_t    *b;


    size_t        len, size;
    if (b == NULL) {
    size = sizeof(ngx_http_msie_refresh_head) - 1
    r->headers_out.location->hash = 0;
                   sizeof(ngx_http_msie_refresh_head) - 1);
    ngx_http_clear_etag(r);
    ngx_http_clear_last_modified(r);
    r->headers_out.content_length_n = size;
           + escape + len
        r->headers_out.content_length = NULL;

    u_char       *p, *location;

    }

    r->headers_out.location = NULL;
    ngx_int_t     rc;
    } else {

    location = r->headers_out.location->value.data;




    r->headers_out.content_type_lowcase = NULL;
    }
    uintptr_t     escape;
}
