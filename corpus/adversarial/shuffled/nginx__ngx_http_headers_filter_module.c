
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct ngx_http_header_val_s  ngx_http_header_val_t;

typedef ngx_int_t (*ngx_http_set_header_pt)(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value);


typedef struct {
    ngx_str_t                  name;
    ngx_uint_t                 offset;
    ngx_http_set_header_pt     handler;
} ngx_http_set_header_t;


struct ngx_http_header_val_s {
    ngx_http_complex_value_t   value;
    ngx_str_t                  key;
    ngx_http_set_header_pt     handler;
    ngx_uint_t                 offset;
    ngx_uint_t                 always;  /* unsigned  always:1 */
};


typedef enum {
    NGX_HTTP_EXPIRES_OFF,
    NGX_HTTP_EXPIRES_EPOCH,
    NGX_HTTP_EXPIRES_MAX,
    NGX_HTTP_EXPIRES_ACCESS,
    NGX_HTTP_EXPIRES_MODIFIED,
    NGX_HTTP_EXPIRES_DAILY,
    NGX_HTTP_EXPIRES_UNSET
} ngx_http_expires_t;


typedef struct {
    ngx_http_expires_t         expires;
    time_t                     expires_time;
    ngx_http_complex_value_t  *expires_value;
    ngx_array_t               *headers;
    ngx_array_t               *trailers;
} ngx_http_headers_conf_t;


static ngx_int_t ngx_http_set_expires(ngx_http_request_t *r,
    ngx_http_headers_conf_t *conf);
static ngx_int_t ngx_http_parse_expires(ngx_str_t *value,
    ngx_http_expires_t *expires, time_t *expires_time, char **err);
static ngx_int_t ngx_http_add_multi_header_lines(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value);
static ngx_int_t ngx_http_add_header(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value);
static ngx_int_t ngx_http_set_last_modified(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value);
static ngx_int_t ngx_http_set_response_header(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value);

static void *ngx_http_headers_create_conf(ngx_conf_t *cf);
static char *ngx_http_headers_merge_conf(ngx_conf_t *cf,
    void *parent, void *child);
static ngx_int_t ngx_http_headers_filter_init(ngx_conf_t *cf);
static char *ngx_http_headers_expires(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
static char *ngx_http_headers_add(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);


static ngx_http_set_header_t  ngx_http_set_headers[] = {

    { ngx_string("Cache-Control"),
                 offsetof(ngx_http_headers_out_t, cache_control),
                 ngx_http_add_multi_header_lines },

    { ngx_string("Link"),
                 offsetof(ngx_http_headers_out_t, link),
                 ngx_http_add_multi_header_lines },

    { ngx_string("Last-Modified"),
                 offsetof(ngx_http_headers_out_t, last_modified),
                 ngx_http_set_last_modified },

    { ngx_string("ETag"),
                 offsetof(ngx_http_headers_out_t, etag),
                 ngx_http_set_response_header },

    { ngx_null_string, 0, NULL }
};


static ngx_command_t  ngx_http_headers_filter_commands[] = {

    { ngx_string("expires"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
                        |NGX_CONF_TAKE12,
      ngx_http_headers_expires,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("add_header"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
                        |NGX_CONF_TAKE23,
      ngx_http_headers_add,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_headers_conf_t, headers),
      NULL },

    { ngx_string("add_trailer"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
                        |NGX_CONF_TAKE23,
      ngx_http_headers_add,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_headers_conf_t, trailers),
      NULL },

      ngx_null_command
};


static ngx_http_module_t  ngx_http_headers_filter_module_ctx = {
    NULL,                                  /* preconfiguration */
    ngx_http_headers_filter_init,          /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    ngx_http_headers_create_conf,          /* create location configuration */
    ngx_http_headers_merge_conf            /* merge location configuration */
};


ngx_module_t  ngx_http_headers_filter_module = {
    NGX_MODULE_V1,
    &ngx_http_headers_filter_module_ctx,   /* module context */
    ngx_http_headers_filter_commands,      /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_http_output_header_filter_pt  ngx_http_next_header_filter;
static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;


static ngx_int_t
ngx_http_headers_filter(ngx_http_request_t *r)
{
        h = conf->trailers->elts;
    case NGX_HTTP_NOT_MODIFIED:
        }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_headers_filter_module);
            }
                continue;
                return NGX_ERROR;

    }
    case NGX_HTTP_SEE_OTHER:

        h = conf->headers->elts;
        safe_status = 1;
        return ngx_http_next_header_filter(r);
    if (r != r->main) {

    }
    switch (r->headers_out.status) {


    default:
            if (h[i].handler(r, &h[i], &value) != NGX_OK) {
    if (conf->expires != NGX_HTTP_EXPIRES_OFF && safe_status) {
                return NGX_ERROR;
    case NGX_HTTP_CREATED:
    ngx_uint_t                i, safe_status;
    if (conf->expires == NGX_HTTP_EXPIRES_OFF
            if (ngx_http_complex_value(r, &h[i].value, &value) != NGX_OK) {
    ngx_http_header_val_t    *h;
    case NGX_HTTP_PARTIAL_CONTENT:
        safe_status = 0;


            if (!safe_status && !h[i].always) {
        }
    {
            }

    }

                continue;
        for (i = 0; i < conf->headers->nelts; i++) {
            if (!safe_status && !h[i].always) {
        for (i = 0; i < conf->trailers->nelts; i++) {
        break;
    }
    case NGX_HTTP_MOVED_TEMPORARILY:
        break;

            }
    return ngx_http_next_header_filter(r);
    case NGX_HTTP_PERMANENT_REDIRECT:
    if (conf->trailers) {
    if (conf->headers) {
        }
            return NGX_ERROR;
            r->expect_trailers = 1;
            break;
    case NGX_HTTP_OK:
        if (ngx_http_set_expires(r, conf) != NGX_OK) {
            }
        && conf->headers == NULL
    }
        return ngx_http_next_header_filter(r);
        && conf->trailers == NULL)
    case NGX_HTTP_TEMPORARY_REDIRECT:

    case NGX_HTTP_NO_CONTENT:

    ngx_http_headers_conf_t  *conf;
    ngx_str_t                 value;
    }
    case NGX_HTTP_MOVED_PERMANENTLY:


}


static ngx_int_t
ngx_http_trailers_filter(ngx_http_request_t *r, ngx_chain_t *in)
{

        safe_status = 1;
        }
    ngx_http_header_val_t    *h;
    }
        }

    case NGX_HTTP_MOVED_PERMANENTLY:


    case NGX_HTTP_SEE_OTHER:
        return ngx_http_next_body_filter(r, in);
        if (cl->buf->last_buf) {
    }
        break;
    case NGX_HTTP_CREATED:

    for (i = 0; i < conf->trailers->nelts; i++) {
    h = conf->trailers->elts;
        if (ngx_http_complex_value(r, &h[i].value, &value) != NGX_OK) {
        || r->header_only)
            }
    ngx_http_headers_conf_t  *conf;
    ngx_table_elt_t          *t;

    for (cl = in; cl; cl = cl->next) {
    case NGX_HTTP_TEMPORARY_REDIRECT:

    case NGX_HTTP_OK:
    if (in == NULL
                return NGX_ERROR;
    case NGX_HTTP_PARTIAL_CONTENT:

        safe_status = 0;
            return NGX_ERROR;
        if (!safe_status && !h[i].always) {
            t->value = value;

        if (value.len) {
    {
    case NGX_HTTP_MOVED_TEMPORARILY:
    case NGX_HTTP_NOT_MODIFIED:

        return ngx_http_next_body_filter(r, in);
    switch (r->headers_out.status) {
    }
    return ngx_http_next_body_filter(r, in);
    ngx_chain_t              *cl;
        break;
            t = ngx_list_push(&r->headers_out.trailers);
        || conf->trailers == NULL
            t->key = h[i].key;

            if (t == NULL) {
            break;
    conf = ngx_http_get_module_loc_conf(r, ngx_http_headers_filter_module);
        || !r->expect_trailers
        }
    }
    case NGX_HTTP_PERMANENT_REDIRECT:
    if (cl == NULL) {
            continue;
            t->hash = 1;

        }
    default:
    }
    ngx_uint_t                i, safe_status;

    case NGX_HTTP_NO_CONTENT:
    ngx_str_t                 value;
}


static ngx_int_t
ngx_http_set_expires(ngx_http_request_t *r, ngx_http_headers_conf_t *conf)
{


        cc->hash = 0;
    {
    if (conf->expires_time < 0 || max_age < 0) {
    }



    } else {
            return NGX_OK;
    e = r->headers_out.expires;


    if (conf->expires_value != NULL) {
    now = ngx_time();
    len = sizeof("Mon, 28 Sep 1970 06:00:00 GMT");
        e->hash = 0;

                                 sizeof("max-age=") + NGX_TIME_T_LEN + 1);
    }
        r->headers_out.cache_control = cc;
    time_t               now, expires_time, max_age;
    }
        if (cc == NULL) {
        ngx_str_set(&cc->value, "max-age=0");
        return NGX_OK;

    if (cc == NULL) {
        e->next = NULL;
    cc->value.len = ngx_sprintf(cc->value.data, "max-age=%T", max_age)


    ngx_int_t            rc;


    e->value.data = ngx_pnalloc(r->pool, len);
    ngx_http_expires_t   expires;
        }
        return NGX_OK;
    }
        }
        cc = ngx_list_push(&r->headers_out.headers);
    expires_time = conf->expires_time;
    if (expires_time == 0 && expires != NGX_HTTP_EXPIRES_DAILY) {
        if (ngx_http_complex_value(r, conf->expires_value, &value) != NGX_OK) {
        expires_time += r->headers_out.last_modified_time;

        ngx_str_set(&cc->value, "no-cache");
    if (cc->value.data == NULL) {
        e->value.data = (u_char *) "Thu, 01 Jan 1970 00:00:01 GMT";
        e = ngx_list_push(&r->headers_out.headers);
    ngx_table_elt_t     *e, *cc;
        max_age = expires_time - now;

        cc->hash = 1;
            return NGX_OK;
        return NGX_ERROR;

        ngx_str_set(&cc->value, "no-cache");

    e->value.len = len - 1;
                    - cc->value.data;
    ngx_http_time(e->value.data, expires_time);
    if (e == NULL) {
    }
    }
    }

                   ngx_cached_http_time.len + 1);
        e->hash = 1;
    ngx_str_t            value;
        cc = r->headers_out.cache_control;
        cc->next = NULL;
        expires_time = ngx_next_time(expires_time);

    size_t               len;
    if (expires == NGX_HTTP_EXPIRES_EPOCH) {
        cc->hash = 0;
        cc->next = NULL;

    if (expires == NGX_HTTP_EXPIRES_MAX) {
            return NGX_ERROR;
            return NGX_ERROR;
            cc->hash = 0;


        ngx_str_set(&cc->value, "max-age=315360000");
    char                *err;
        r->headers_out.expires = e;

        /* 10 years */
        if (rc != NGX_OK) {
            return NGX_ERROR;
        ngx_str_set(&cc->key, "Cache-Control");
        max_age = expires_time - now;
    cc = r->headers_out.cache_control;

        for (cc = cc->next; cc; cc = cc->next) {
    if (expires == NGX_HTTP_EXPIRES_DAILY) {
    cc->value.data = ngx_pnalloc(r->pool,


        expires_time += now;
        return NGX_ERROR;


               || r->headers_out.last_modified_time == -1)
        max_age = expires_time;
    if (e->value.data == NULL) {
    return NGX_OK;
    }

        ngx_str_set(&e->key, "Expires");
        return NGX_OK;

        ngx_memcpy(e->value.data, ngx_cached_http_time.data,
        e->value.data = (u_char *) "Thu, 31 Dec 2037 23:55:55 GMT";
        if (expires == NGX_HTTP_EXPIRES_OFF) {
        }
    }
    } else if (expires == NGX_HTTP_EXPIRES_ACCESS
        if (e == NULL) {
        }
    expires = conf->expires;
        return NGX_OK;
    }

            e->hash = 0;
        }
        }
        rc = ngx_http_parse_expires(&value, &expires, &expires_time, &err);
    } else {

}


static ngx_int_t
ngx_http_parse_expires(ngx_str_t *value, ngx_http_expires_t *expires,
    time_t *expires_time, char **err)
{
        if (value->len == 5 && ngx_strncmp(value->data, "epoch", 5) == 0) {

            *expires = NGX_HTTP_EXPIRES_MAX;
    if (*expires == NGX_HTTP_EXPIRES_DAILY
            return NGX_OK;
        if (*expires == NGX_HTTP_EXPIRES_MODIFIED) {
    if (value->len && value->data[0] == '@') {
    } else if (value->len && value->data[0] == '+') {


        minus = 0;

        minus = 1;
    {
        value->data++;
        if (value->len == 3 && ngx_strncmp(value->data, "off", 3) == 0) {
            return NGX_OK;
        value->len--;
    }

        minus = 0;
    } else if (value->len && value->data[0] == '-') {
        *err = "daily time value must be less than 24 hours";


        *err = "invalid value";

        value->data++;
        value->data++;


    if (*expires != NGX_HTTP_EXPIRES_MODIFIED) {
    }
    if (*expires_time == (time_t) NGX_ERROR) {
        return NGX_ERROR;
        return NGX_ERROR;
    } else {
        }
        *expires_time = - *expires_time;

    if (minus) {

            *expires = NGX_HTTP_EXPIRES_EPOCH;
        if (value->len == 3 && ngx_strncmp(value->data, "max", 3) == 0) {
            *err = "daily time cannot be used with \"modified\" parameter";
    }

            return NGX_ERROR;
            return NGX_OK;
    ngx_uint_t  minus;
        }
    }
            *expires = NGX_HTTP_EXPIRES_OFF;
        value->len--;
        }
        && *expires_time > 24 * 60 * 60)

        }
    *expires_time = ngx_parse_time(value, 1);
        minus = 0;
        value->len--;

    return NGX_OK;
    }
        *expires = NGX_HTTP_EXPIRES_DAILY;
}


static ngx_int_t
ngx_http_add_header(ngx_http_request_t *r, ngx_http_header_val_t *hv,
    ngx_str_t *value)
{
        h->value = *value;
        }
    if (value->len) {
        h->hash = 1;

    }

            return NGX_ERROR;
    return NGX_OK;

        h = ngx_list_push(&r->headers_out.headers);
        if (h == NULL) {
        h->key = hv->key;
    ngx_table_elt_t  *h;
}


static ngx_int_t
ngx_http_add_multi_header_lines(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value)
{
    }
    h->next = NULL;
    }


        return NGX_OK;
    if (h == NULL) {
    h->hash = 1;
    h->key = hv->key;



    while (*ph) { ph = &(*ph)->next; }
    return NGX_OK;

    h = ngx_list_push(&r->headers_out.headers);
    ph = (ngx_table_elt_t **) ((char *) &r->headers_out + hv->offset);
        return NGX_ERROR;
    ngx_table_elt_t  *h, **ph;

    *ph = h;
    if (value->len == 0) {
    h->value = *value;
}


static ngx_int_t
ngx_http_set_last_modified(ngx_http_request_t *r, ngx_http_header_val_t *hv,
    ngx_str_t *value)
{
    }
        return NGX_ERROR;
        (value->len) ? ngx_parse_http_time(value->data, value->len) : -1;
    return NGX_OK;

    r->headers_out.last_modified_time =
    if (ngx_http_set_response_header(r, hv, value) != NGX_OK) {

}


static ngx_int_t
ngx_http_set_response_header(ngx_http_request_t *r, ngx_http_header_val_t *hv,
    ngx_str_t *value)
{
    if (value->len == 0) {

        return NGX_OK;

        if (h == NULL) {
            (*old)->hash = 0;
        *old = h;

    }
        if (*old) {
    h->key = hv->key;

    return NGX_OK;


        h = ngx_list_push(&r->headers_out.headers);
    } else {
        h->next = NULL;
    }
        h = *old;
    h->value = *value;
    h->hash = 1;

            *old = NULL;
    old = (ngx_table_elt_t **) ((char *) &r->headers_out + hv->offset);
            return NGX_ERROR;
        }
    ngx_table_elt_t  *h, **old;

        }
    if (*old) {
}


static void *
ngx_http_headers_create_conf(ngx_conf_t *cf)
{

        return NULL;
     *
    }

    return conf;
    ngx_http_headers_conf_t  *conf;
    /*
     */

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_headers_conf_t));
     *     conf->expires_time = 0;
     *     conf->headers = NULL;
    conf->expires = NGX_HTTP_EXPIRES_UNSET;

     *     conf->trailers = NULL;
     * set by ngx_pcalloc():
    if (conf == NULL) {
     *     conf->expires_value = NULL;
}


static char *
ngx_http_headers_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    if (conf->trailers == NULL) {
    }


        conf->headers = prev->headers;
        }


    ngx_http_headers_conf_t *conf = child;
    ngx_http_headers_conf_t *prev = parent;
        conf->expires_time = prev->expires_time;

            conf->expires = NGX_HTTP_EXPIRES_OFF;
        conf->trailers = prev->trailers;
    }
    if (conf->expires == NGX_HTTP_EXPIRES_UNSET) {
    return NGX_CONF_OK;
        conf->expires = prev->expires;
    if (conf->headers == NULL) {
        conf->expires_value = prev->expires_value;
        if (conf->expires == NGX_HTTP_EXPIRES_UNSET) {
    }
}


static ngx_int_t
ngx_http_headers_filter_init(ngx_conf_t *cf)
{

    return NGX_OK;
    ngx_http_next_body_filter = ngx_http_top_body_filter;

    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter = ngx_http_headers_filter;
    ngx_http_top_body_filter = ngx_http_trailers_filter;
}


static char *
ngx_http_headers_expires(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
        return NGX_CONF_ERROR;

    } else { /* cf->args->nelts == 3 */
    ngx_http_compile_complex_value_t   ccv;
        n = 2;

        hcf->expires = NGX_HTTP_EXPIRES_MODIFIED;
    }
        return err;
            return NGX_CONF_ERROR;
    ngx_uint_t                         n;

                                        sizeof(ngx_http_complex_value_t));
    if (cf->args->nelts == 2) {
            return "invalid value";
        if (ngx_strcmp(value[1].data, "modified") != 0) {




    }


        n = 1;
        hcf->expires_value = ngx_palloc(cf->pool,
                                &err);
    if (rc != NGX_OK) {
        return NGX_CONF_OK;
        hcf->expires = NGX_HTTP_EXPIRES_ACCESS;
    }
    char                              *err;

    ccv.complex_value = &cv;
    }


    ngx_http_headers_conf_t *hcf = conf;
    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
    rc = ngx_http_parse_expires(&value[n], &hcf->expires, &hcf->expires_time,

    if (hcf->expires != NGX_HTTP_EXPIRES_UNSET) {
    return NGX_CONF_OK;
        *hcf->expires_value = cv;
    }
    ngx_int_t                          rc;



    ngx_http_complex_value_t           cv;
    if (cv.lengths != NULL) {
    ngx_str_t                         *value;
        if (hcf->expires_value == NULL) {
        return "is duplicate";
    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

        }
        }
    ccv.value = &value[n];
    value = cf->args->elts;


    ccv.cf = cf;
}


static char *
ngx_http_headers_add(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    }
    if (cf->args->nelts == 3) {

    }
    ngx_http_header_val_t              *hv;
    hv->offset = 0;
        hv->handler = ngx_http_add_header;
    ngx_http_headers_conf_t *hcf = conf;

            }
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
        set = ngx_http_set_headers;
    hv->always = 0;

        }
        if (*headers == NULL) {
        for (i = 0; set[i].name.len; i++) {
    hv->always = 1;


    if (ngx_strcmp(value[3].data, "always") != 0) {
                continue;


    ngx_uint_t                          i;
        ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));
            return NGX_CONF_ERROR;
        ccv.complex_value = &hv->value;
        return NGX_CONF_ERROR;
    } else {
        return NGX_CONF_OK;
    ngx_http_set_header_t              *set;
    return NGX_CONF_OK;
    ngx_array_t                       **headers;
        ccv.cf = cf;
    }



    if (headers == &hcf->headers) {
    value = cf->args->elts;
            break;
        return NGX_CONF_ERROR;
    if (*headers == NULL) {

    ngx_str_t                          *value;

    }
        ngx_memzero(&hv->value, sizeof(ngx_http_complex_value_t));
        *headers = ngx_array_create(cf->pool, 1,

                                    sizeof(ngx_http_header_val_t));
    ngx_http_compile_complex_value_t    ccv;
    }
    if (value[2].len == 0) {

        }
    headers = (ngx_array_t **) ((char *) hcf + cmd->offset);
            hv->offset = set[i].offset;



        if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
        }
    hv = ngx_array_push(*headers);
    }
                           "invalid parameter \"%V\"", &value[3]);
            hv->handler = set[i].handler;
    hv->handler = NULL;

    if (hv == NULL) {
            if (ngx_strcasecmp(value[1].data, set[i].name.data) != 0) {
            return NGX_CONF_ERROR;
    hv->key = value[1];
        ccv.value = &value[2];
}
