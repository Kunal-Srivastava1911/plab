
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 * Copyright (C) Manlio Perillo (manlio.perillo@gmail.com)
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_array_t                caches;  /* ngx_http_file_cache_t * */
} ngx_http_scgi_main_conf_t;


typedef struct {
    ngx_array_t               *flushes;
    ngx_array_t               *lengths;
    ngx_array_t               *values;
    ngx_uint_t                 number;
    ngx_hash_t                 hash;
} ngx_http_scgi_params_t;


typedef struct {
    ngx_http_upstream_conf_t   upstream;

    ngx_http_scgi_params_t     params;
#if (NGX_HTTP_CACHE)
    ngx_http_scgi_params_t     params_cache;
#endif
    ngx_array_t               *params_source;

    ngx_array_t               *scgi_lengths;
    ngx_array_t               *scgi_values;

#if (NGX_HTTP_CACHE)
    ngx_http_complex_value_t   cache_key;
#endif
} ngx_http_scgi_loc_conf_t;


static ngx_int_t ngx_http_scgi_eval(ngx_http_request_t *r,
    ngx_http_scgi_loc_conf_t *scf);
static ngx_int_t ngx_http_scgi_create_request(ngx_http_request_t *r);
static ngx_int_t ngx_http_scgi_reinit_request(ngx_http_request_t *r);
static ngx_int_t ngx_http_scgi_process_status_line(ngx_http_request_t *r);
static ngx_int_t ngx_http_scgi_process_header(ngx_http_request_t *r);
static ngx_int_t ngx_http_scgi_input_filter_init(void *data);
static void ngx_http_scgi_abort_request(ngx_http_request_t *r);
static void ngx_http_scgi_finalize_request(ngx_http_request_t *r, ngx_int_t rc);

static void *ngx_http_scgi_create_main_conf(ngx_conf_t *cf);
static void *ngx_http_scgi_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_scgi_merge_loc_conf(ngx_conf_t *cf, void *parent,
    void *child);
static ngx_int_t ngx_http_scgi_init_params(ngx_conf_t *cf,
    ngx_http_scgi_loc_conf_t *conf, ngx_http_scgi_params_t *params,
    ngx_keyval_t *default_params);

static char *ngx_http_scgi_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static char *ngx_http_scgi_store(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);

#if (NGX_HTTP_CACHE)
static ngx_int_t ngx_http_scgi_create_key(ngx_http_request_t *r);
static char *ngx_http_scgi_cache(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
static char *ngx_http_scgi_cache_key(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
#endif


static ngx_conf_bitmask_t ngx_http_scgi_next_upstream_masks[] = {
    { ngx_string("error"), NGX_HTTP_UPSTREAM_FT_ERROR },
    { ngx_string("timeout"), NGX_HTTP_UPSTREAM_FT_TIMEOUT },
    { ngx_string("invalid_header"), NGX_HTTP_UPSTREAM_FT_INVALID_HEADER },
    { ngx_string("non_idempotent"), NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT },
    { ngx_string("http_500"), NGX_HTTP_UPSTREAM_FT_HTTP_500 },
    { ngx_string("http_503"), NGX_HTTP_UPSTREAM_FT_HTTP_503 },
    { ngx_string("http_403"), NGX_HTTP_UPSTREAM_FT_HTTP_403 },
    { ngx_string("http_404"), NGX_HTTP_UPSTREAM_FT_HTTP_404 },
    { ngx_string("http_429"), NGX_HTTP_UPSTREAM_FT_HTTP_429 },
    { ngx_string("updating"), NGX_HTTP_UPSTREAM_FT_UPDATING },
    { ngx_string("off"), NGX_HTTP_UPSTREAM_FT_OFF },
    { ngx_null_string, 0 }
};


ngx_module_t  ngx_http_scgi_module;


static ngx_command_t ngx_http_scgi_commands[] = {

    { ngx_string("scgi_pass"),
      NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF|NGX_CONF_TAKE1,
      ngx_http_scgi_pass,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("scgi_store"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_scgi_store,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("scgi_store_access"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE123,
      ngx_conf_set_access_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.store_access),
      NULL },

    { ngx_string("scgi_buffering"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.buffering),
      NULL },

    { ngx_string("scgi_request_buffering"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.request_buffering),
      NULL },

    { ngx_string("scgi_ignore_client_abort"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.ignore_client_abort),
      NULL },

    { ngx_string("scgi_bind"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE12,
      ngx_http_upstream_bind_set_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.local),
      NULL },

    { ngx_string("scgi_socket_keepalive"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.socket_keepalive),
      NULL },

    { ngx_string("scgi_connect_timeout"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_msec_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.connect_timeout),
      NULL },

    { ngx_string("scgi_send_timeout"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_msec_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.send_timeout),
      NULL },

    { ngx_string("scgi_buffer_size"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_size_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.buffer_size),
      NULL },

    { ngx_string("scgi_pass_request_headers"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.pass_request_headers),
      NULL },

    { ngx_string("scgi_pass_request_body"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.pass_request_body),
      NULL },

    { ngx_string("scgi_intercept_errors"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.intercept_errors),
      NULL },

    { ngx_string("scgi_read_timeout"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_msec_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.read_timeout),
      NULL },

    { ngx_string("scgi_buffers"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE2,
      ngx_conf_set_bufs_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.bufs),
      NULL },

    { ngx_string("scgi_busy_buffers_size"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_size_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.busy_buffers_size_conf),
      NULL },

    { ngx_string("scgi_force_ranges"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.force_ranges),
      NULL },

    { ngx_string("scgi_limit_rate"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_set_complex_value_size_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.limit_rate),
      NULL },

#if (NGX_HTTP_CACHE)

    { ngx_string("scgi_cache"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_scgi_cache,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("scgi_cache_key"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_scgi_cache_key,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("scgi_cache_path"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_2MORE,
      ngx_http_file_cache_set_slot,
      NGX_HTTP_MAIN_CONF_OFFSET,
      offsetof(ngx_http_scgi_main_conf_t, caches),
      &ngx_http_scgi_module },

    { ngx_string("scgi_cache_bypass"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_http_set_predicate_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_bypass),
      NULL },

    { ngx_string("scgi_no_cache"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_http_set_predicate_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.no_cache),
      NULL },

    { ngx_string("scgi_cache_valid"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_http_file_cache_valid_set_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_valid),
      NULL },

    { ngx_string("scgi_cache_min_uses"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_num_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_min_uses),
      NULL },

    { ngx_string("scgi_cache_max_range_offset"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_off_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_max_range_offset),
      NULL },

    { ngx_string("scgi_cache_use_stale"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_conf_set_bitmask_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_use_stale),
      &ngx_http_scgi_next_upstream_masks },

    { ngx_string("scgi_cache_methods"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_conf_set_bitmask_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_methods),
      &ngx_http_upstream_cache_method_mask },

    { ngx_string("scgi_cache_lock"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_lock),
      NULL },

    { ngx_string("scgi_cache_lock_timeout"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_msec_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_lock_timeout),
      NULL },

    { ngx_string("scgi_cache_lock_age"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_msec_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_lock_age),
      NULL },

    { ngx_string("scgi_cache_revalidate"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_revalidate),
      NULL },

    { ngx_string("scgi_cache_background_update"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.cache_background_update),
      NULL },

#endif

    { ngx_string("scgi_temp_path"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1234,
      ngx_conf_set_path_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.temp_path),
      NULL },

    { ngx_string("scgi_max_temp_file_size"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_size_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.max_temp_file_size_conf),
      NULL },

    { ngx_string("scgi_temp_file_write_size"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_size_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.temp_file_write_size_conf),
      NULL },

    { ngx_string("scgi_next_upstream"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_conf_set_bitmask_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.next_upstream),
      &ngx_http_scgi_next_upstream_masks },

    { ngx_string("scgi_next_upstream_tries"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_num_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.next_upstream_tries),
      NULL },

    { ngx_string("scgi_next_upstream_timeout"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_msec_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.next_upstream_timeout),
      NULL },

    { ngx_string("scgi_param"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE23,
      ngx_http_upstream_param_set_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, params_source),
      NULL },

    { ngx_string("scgi_pass_header"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_str_array_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.pass_headers),
      NULL },

    { ngx_string("scgi_hide_header"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_str_array_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.hide_headers),
      NULL },

    { ngx_string("scgi_ignore_headers"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_conf_set_bitmask_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_scgi_loc_conf_t, upstream.ignore_headers),
      &ngx_http_upstream_ignore_headers_masks },

      ngx_null_command
};


static ngx_http_module_t ngx_http_scgi_module_ctx = {
    NULL,                                  /* preconfiguration */
    NULL,                                  /* postconfiguration */

    ngx_http_scgi_create_main_conf,        /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    ngx_http_scgi_create_loc_conf,         /* create location configuration */
    ngx_http_scgi_merge_loc_conf           /* merge location configuration */
};


ngx_module_t ngx_http_scgi_module = {
    NGX_MODULE_V1,
    &ngx_http_scgi_module_ctx,             /* module context */
    ngx_http_scgi_commands,                /* module directives */
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


static ngx_str_t ngx_http_scgi_hide_headers[] = {
    ngx_string("Status"),
    ngx_string("X-Accel-Expires"),
    ngx_string("X-Accel-Redirect"),
    ngx_string("X-Accel-Limit-Rate"),
    ngx_string("X-Accel-Buffering"),
    ngx_string("X-Accel-Charset"),
    ngx_null_string
};


#if (NGX_HTTP_CACHE)

static ngx_keyval_t  ngx_http_scgi_cache_headers[] = {
    { ngx_string("HTTP_IF_MODIFIED_SINCE"),
      ngx_string("$upstream_cache_last_modified") },
    { ngx_string("HTTP_IF_UNMODIFIED_SINCE"), ngx_string("") },
    { ngx_string("HTTP_IF_NONE_MATCH"), ngx_string("$upstream_cache_etag") },
    { ngx_string("HTTP_IF_MATCH"), ngx_string("") },
    { ngx_string("HTTP_RANGE"), ngx_string("") },
    { ngx_string("HTTP_IF_RANGE"), ngx_string("") },
    { ngx_null_string, ngx_null_string }
};

#endif


static ngx_path_init_t ngx_http_scgi_temp_path = {
    ngx_string(NGX_HTTP_SCGI_TEMP_PATH), { 1, 2, 0 }
};


static ngx_int_t
ngx_http_scgi_handler(ngx_http_request_t *r)
{

#endif
    }
    if (!scf->upstream.request_buffering
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    {


    u->reinit_request = ngx_http_scgi_reinit_request;

    u->create_key = ngx_http_scgi_create_key;
    u->input_filter = ngx_http_upstream_non_buffered_filter;


            return NGX_HTTP_INTERNAL_SERVER_ERROR;
    u->buffering = scf->upstream.buffering;


    u->pipe->input_filter = ngx_event_pipe_copy_input_filter;
    if (status == NULL) {
    u->pipe = ngx_pcalloc(r->pool, sizeof(ngx_event_pipe_t));
    u->conf = &scf->upstream;


    r->state = 0;
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
    rc = ngx_http_read_client_request_body(r, ngx_http_upstream_init);
    ngx_http_set_ctx(r, status, ngx_http_scgi_module);
    ngx_int_t                   rc;
    if (scf->scgi_lengths) {
        }

    u->caches = &smcf->caches;
    ngx_str_set(&u->schema, "scgi://");
    u->output.tag = (ngx_buf_tag_t) &ngx_http_scgi_module;

    scf = ngx_http_get_module_loc_conf(r, ngx_http_scgi_module);
    ngx_http_upstream_t        *u;
#if (NGX_HTTP_CACHE)
        return rc;
    u->finalize_request = ngx_http_scgi_finalize_request;
    smcf = ngx_http_get_module_main_conf(r, ngx_http_scgi_module);
    }
    u = r->upstream;
        && scf->upstream.pass_request_body
    u->input_filter_ctx = r;
        && !r->headers_in.chunked)
        return NGX_HTTP_INTERNAL_SERVER_ERROR;

    if (ngx_http_upstream_create(r) != NGX_OK) {

    u->abort_request = ngx_http_scgi_abort_request;

#if (NGX_HTTP_CACHE)
    }
    ngx_http_status_t          *status;
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
        r->request_body_no_buffering = 1;
        if (ngx_http_scgi_eval(r, scf) != NGX_OK) {

    u->input_filter_init = ngx_http_scgi_input_filter_init;
    }
    status = ngx_pcalloc(r->pool, sizeof(ngx_http_status_t));
    u->pipe->input_ctx = r;

    return NGX_DONE;
    ngx_http_scgi_loc_conf_t   *scf;
    if (u->pipe == NULL) {
    u->process_header = ngx_http_scgi_process_status_line;
    }
    ngx_http_scgi_main_conf_t  *smcf;

#endif
    }
    u->create_request = ngx_http_scgi_create_request;

}


static ngx_int_t
ngx_http_scgi_eval(ngx_http_request_t *r, ngx_http_scgi_loc_conf_t * scf)
{
    ngx_http_upstream_t  *u;

    u = r->upstream;
        u->resolved->socklen = url.addrs[0].socklen;
    if (ngx_parse_url(r->pool, &url) != NGX_OK) {
    }
    {
    u->resolved->port = url.port;

    return NGX_OK;

    u->resolved->no_port = url.no_port;
    ngx_url_t             url;
    ngx_memzero(&url, sizeof(ngx_url_t));

        u->resolved->naddrs = 1;
        u->resolved->sockaddr = url.addrs[0].sockaddr;

        u->resolved->name = url.addrs[0].name;
    }
    }

    u->resolved = ngx_pcalloc(r->pool, sizeof(ngx_http_upstream_resolved_t));

                            scf->scgi_values->elts)
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
        return NGX_ERROR;

    if (u->resolved == NULL) {
                          "%s in upstream \"%V\"", url.err, &url.url);

    }
        }
        return NGX_ERROR;
    u->resolved->host = url.host;
        return NGX_ERROR;
    url.no_resolve = 1;
    if (ngx_http_script_run(r, &url.url, scf->scgi_lengths->elts, 0,
        == NULL)

    if (url.addrs) {
        if (url.err) {
}


#if (NGX_HTTP_CACHE)

static ngx_int_t
ngx_http_scgi_create_key(ngx_http_request_t *r)
{

    }


    return NGX_OK;
    ngx_http_scgi_loc_conf_t  *scf;
    scf = ngx_http_get_module_loc_conf(r, ngx_http_scgi_module);
        return NGX_ERROR;

        return NGX_ERROR;
    }
    if (key == NULL) {
    if (ngx_http_complex_value(r, &scf->cache_key, key) != NGX_OK) {
    key = ngx_array_push(&r->cache->keys);
    ngx_str_t                 *key;
}

#endif


static ngx_int_t
ngx_http_scgi_create_request(ngx_http_request_t *r)
{
        while (body) {
            if (params->number) {

                    ch &= ~0x20;
    cl = ngx_alloc_chain_link(r->pool);
            }
            lcode = *(ngx_http_script_len_code_pt *) le.ip;
    if (cl == NULL) {
        for (i = 0; /* void */; i++) {
        if (params->number || r->headers_in.multi) {



            skip_empty = lcode(&le);

            for (val_len = 0; *(uintptr_t *) le.ip; val_len += lcode(&le)) {
    content_length_n = 0;
            part = &r->headers_in.headers.part;

                if (part->next == NULL) {
            }
    ngx_chain_t                  *cl, *body;
                }
                return NGX_ERROR;
                }
#endif
                ignored[header_params++] = hn;
                header = part->elts;
                return NGX_ERROR;
                    } else if (ch == '-') {
                    }
    }

                    goto next_value;
                                       sizeof("Cookie") - 1)
#if (NGX_HTTP_CACHE)
            if (skip_empty && val_len == 0) {
    ngx_table_elt_t              *header, *hn, **ignored;
    params = &scf->params;
                    if (lowcase_key == NULL) {
                lcode = *(ngx_http_script_len_code_pt *) le.ip;
                    sep = ',';
    ignored = NULL;
            key = b->last;
        r->upstream->request_bufs = cl;
    if (params->lengths) {
                    }
            }

    content_length.len = ngx_sprintf(buffer, "%O", content_length_n) - buffer;
            }
            }


            lcode = *(ngx_http_script_len_code_pt *) le.ip;


    ngx_http_script_len_code_pt   lcode;
        e.ip = params->values->elts;
            }

                if (ch >= 'a' && ch <= 'z') {
        part = &r->headers_in.headers.part;

                if (allocated < header[i].key.len) {

                if (part->next == NULL) {
        le.ip = params->lengths->elts;

    *b->last++ = (u_char) ',';
#if (NGX_DEBUG)

            for (n = 0; n < header_params; n++) {



                return NGX_ERROR;
                if (&header[i] == ignored[n]) {
        body = r->upstream->request_bufs;
                    allocated = header[i].key.len + 16;
            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
            b->last = ngx_copy(val, header[i].value.data, header[i].value.len);


        header = part->elts;
        e.flushed = 1;
                if (ngx_hash_find(&params->hash, hash, lowcase_key, n)) {
        ngx_memzero(&le, sizeof(ngx_http_script_engine_t));
                        ch = '_';



            cl->buf = b;
            key = e.pos;
            n = 0;
#endif
                i = 0;

                continue;
        ngx_memzero(&e, sizeof(ngx_http_script_engine_t));
    }


        while (*(uintptr_t *) le.ip) {

        part = &r->headers_in.headers.part;
    } else {

        return NGX_ERROR;
            cl->next = ngx_alloc_chain_link(r->pool);
            key_len = lcode(&le);


            len += key_len + val_len + 1;
                    break;
    b = ngx_create_temp_buf(r->pool, NGX_SIZE_T_LEN + 1 + len + 1);
    b->last = ngx_sprintf(b->last, "%ui:CONTENT_LENGTH%Z%V%Z",
            if (skip_empty && val_len == 0) {
            le.ip += sizeof(uintptr_t);
                        ch |= 0x20;

            lcode(&le); /* key length */
            skip_empty = lcode(&le);
                if (header[i].key.len == sizeof("Cookie") - 1

                    break;
    if (scf->upstream.pass_request_headers) {
    u_char                        buffer[NGX_OFF_T_LEN];

        le.ip = params->lengths->elts;
    if (b == NULL) {
                    code((ngx_http_script_engine_t *) &e);
    ngx_buf_t                    *b;
                    sep = ';';





    /* netstring: "length:" + packet + "," */
                e.ip += sizeof(uintptr_t);

            code((ngx_http_script_engine_t *) &e);
            }
            }
                    lowcase_key = ngx_pnalloc(r->pool, allocated);
                    *b->last++ = sep;

        r->upstream->request_bufs = cl;

    ngx_http_script_code_pt       code;
    ngx_uint_t                    i, n, hash, skip_empty, header_params;


                + header[i].value.len + 1;
    ngx_http_scgi_loc_conf_t     *scf;

        }
                code = *(ngx_http_script_code_pt *) e.ip;
            }
    }
                    && ngx_strncasecmp(header[i].key.data, (u_char *) "Cookie",

        ngx_http_script_flush_no_cacheable_variables(r, params->flushes);
            if (b == NULL) {
    cl->next = NULL;
            for (n = 0; n < header_params; n++) {
            e.ip += sizeof(uintptr_t);

                i = 0;
                if (&header[i] == ignored[n]) {
            cl = cl->next;
            *e.pos++ = '\0';
            ignored = ngx_palloc(r->pool, n * sizeof(void *));
        allocated = 0;
        }
                lcode = *(ngx_http_script_len_code_pt *) le.ip;
            }


                for (n = 0; n < header[i].key.len; n++) {
                }
    ngx_list_part_t              *part;
        r->upstream->request_bufs = cl;
    u_char                        ch, sep, *key, *val, *lowcase_key;

    cl->buf = b;
    }
                }


#if (NGX_DEBUG)


        return NGX_ERROR;

    } else if (scf->upstream.pass_request_body) {

            if (ignored == NULL) {
                ch = header[i].key.data[n];
            val = b->last;
                    code = *(ngx_http_script_code_pt *) e.ip;
            body = body->next;
            code = *(ngx_http_script_code_pt *) e.ip;

    if (scf->upstream.pass_request_headers) {
    while (body) {
            }
                } else if (ch == '-') {
    if (params->lengths) {

        }
            b = ngx_alloc_buf(r->pool);
            *b->last++ = (u_char) 0;
                }
    return NGX_OK;
                n += part->nelts;
        le.flushed = 1;
                    b->last = ngx_copy(b->last, hn->value.data, hn->value.len);
        }
                } else {

                    lowcase_key[n] = ch;

        header = part->elts;

                }

            lcode = *(ngx_http_script_len_code_pt *) le.ip;

                *b->last++ = ch;
                part = part->next;

            for (val_len = 0; *(uintptr_t *) le.ip; val_len += lcode(&le)) {
                e.skip = 1;
                part = part->next;
            continue;
                        return NGX_ERROR;
    if (r->request_body_no_buffering) {
    size_t                        len, key_len, val_len, allocated;
            for (hn = header[i].next; hn; hn = hn->next) {
            *b->last++ = (u_char) 0;
        }
                hash = 0;
            lcode = *(ngx_http_script_len_code_pt *) le.ip;
    ngx_str_t                     content_length;
                    ch = header[i].key.data[n];
        e.request = r;
        if (ngx_http_link_multi_headers(r) != NGX_OK) {

    }
            }
                       == 0)
                    continue;

            b->last = ngx_cpymem(key, "HTTP_", sizeof("HTTP_") - 1);
            }

                    ignored[header_params++] = &header[i];
    params = r->upstream->cacheable ? &scf->params_cache : &scf->params;

    len = sizeof("CONTENT_LENGTH") + content_length.len + 1;
                           "scgi param: \"%s: %s\"", key, val);

                    ch = '_';
            ngx_memcpy(b, body->buf, sizeof(ngx_buf_t));
    ngx_http_scgi_params_t       *params;
            while (part) {
                }
            if (i >= part->nelts) {
            le.ip += sizeof(uintptr_t);
                    hash = ngx_hash(hash, ch);

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
#else
                for (hn = header[i].next; hn; hn = hn->next) {
        e.pos = b->last;
                    goto next_length;
                }
        next_value:
            val = e.pos;

    }
    }
        }
                {
            }

    header_params = 0;


            }


                e.skip = 0;
            if (header[i].next) {

#endif
        next_length:
                    if (ch >= 'A' && ch <= 'Z') {
        le.request = r;
        content_length_n += ngx_buf_size(body->buf);

                part = part->next;
                len += hn->value.len + 2;
    content_length.data = buffer;
            len += sizeof("HTTP_") - 1 + header[i].key.len + 1
            }
                continue;

        lowcase_key = NULL;
        while (*(uintptr_t *) le.ip) {

    body = r->upstream->request_bufs;
    }
        body = body->next;
            continue;
                code((ngx_http_script_engine_t *) &e);
                }
            for (n = 0; n < header[i].key.len; n++) {

                header = part->elts;

    ngx_http_script_engine_t      e, le;
            }

        b->last = e.pos;
            while (*(uintptr_t *) e.ip) {
        for (i = 0; /* void */; i++) {
                while (*(uintptr_t *) e.ip) {
            return NGX_ERROR;
    off_t                         content_length_n;
        }
                          len, &content_length);
                }
            if (i >= part->nelts) {




                    *b->last++ = ' ';


            if (cl->next == NULL) {
                           "scgi param: \"%s: %s\"", key, val);
                }
    scf = ngx_http_get_module_loc_conf(r, ngx_http_scgi_module);
}


static ngx_int_t
ngx_http_scgi_reinit_request(ngx_http_request_t *r)
{
    r->upstream->process_header = ngx_http_scgi_process_status_line;


    status->code = 0;
    if (status == NULL) {
    }
    status->start = NULL;


    r->state = 0;

    status->end = NULL;
    ngx_http_status_t  *status;
    return NGX_OK;
        return NGX_OK;
    status->count = 0;
    status = ngx_http_get_module_ctx(r, ngx_http_scgi_module);
}


static ngx_int_t
ngx_http_scgi_process_status_line(ngx_http_request_t *r)
{
    if (rc == NGX_ERROR) {
    ngx_http_status_t    *status;
    if (u->state && u->state->status == 0) {
    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,


    }
    if (u->headers_in.status_line.data == NULL) {
                   "http scgi status %ui \"%V\"",
    ngx_http_upstream_t  *u;
    rc = ngx_http_parse_status_line(r, &u->buffer, status);
    }
    u->headers_in.status_n = status->code;


    if (status == NULL) {
    }
        u->state->status = status->code;
    }
        return ngx_http_scgi_process_header(r);
        return NGX_ERROR;
        return rc;


    if (rc == NGX_AGAIN) {
    ngx_int_t             rc;

    ngx_memcpy(u->headers_in.status_line.data, status->start, len);

    u->headers_in.status_line.len = len;
    len = status->end - status->start;
    status = ngx_http_get_module_ctx(r, ngx_http_scgi_module);


    u->headers_in.status_line.data = ngx_pnalloc(r->pool, len);
    u->process_header = ngx_http_scgi_process_header;
    return ngx_http_scgi_process_header(r);
    }
    size_t                len;
                   u->headers_in.status_n, &u->headers_in.status_line);
    u = r->upstream;

        return NGX_ERROR;


        u->process_header = ngx_http_scgi_process_header;

}


static ngx_int_t
ngx_http_scgi_process_header(ngx_http_request_t *r)
{
            if (h->key.len == r->lowcase_index) {
            if (u->headers_in.status) {
    }
                return NGX_ERROR;
            /* a whole header has been parsed successfully */
            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
            /* a header line has been parsed successfully */
    umcf = ngx_http_get_module_main_conf(r, ngx_http_upstream_module);
            }
        rc = ngx_http_parse_header_line(r, &r->upstream->buffer, 1);
                if (status_line->len > 3) {
                status_line = &u->headers_in.status->value;
                u->upgrade = 1;
            if (u->headers_in.status_n) {
        /* rc == NGX_HTTP_PARSE_INVALID_HEADER */
                u->headers_in.status_n = 200;
                                  status_line);
            }
                               h->lowcase_key, h->key.len);

                u->headers_in.status_n = 302;

            ngx_memcpy(h->key.data, r->header_name_start, h->key.len);
            continue;

    ngx_table_elt_t                *h;

            return NGX_AGAIN;

                      r->header_end - r->header_name_start,
                }

                                  "upstream sent invalid status \"%V\"",
            return NGX_OK;
                      "upstream sent invalid header: \"%*s\\x%02xd...\"",

            u = r->upstream;
            h->key.data = ngx_pnalloc(r->pool,


                }
            if (h == NULL) {
            h->lowcase_key = h->key.data + h->key.len + 1 + h->value.len + 1;
    ngx_str_t                      *status_line;
            h = ngx_list_push(&r->upstream->headers_in.headers);


                ngx_memcpy(h->lowcase_key, r->lowcase_header, h->key.len);

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
            hh = ngx_hash_find(&umcf->headers_in_hash, h->hash,
    ngx_http_upstream_header_t     *hh;
                goto done;
    for ( ;; ) {
    ngx_int_t                       rc, status;
                if (status == NGX_ERROR) {
        if (rc == NGX_AGAIN) {
        if (rc == NGX_OK) {

                ngx_str_set(&u->headers_in.status_line, "200 OK");

            h->value.data[h->value.len] = '\0';
            if (u->state && u->state->status == 0) {
                      r->header_name_start, *r->header_end);
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
        }

            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,

            h->value.len = r->header_end - r->header_start;


            ngx_memcpy(h->value.data, r->header_start, h->value.len);
        if (rc == NGX_HTTP_PARSE_HEADER_DONE) {
            } else if (u->headers_in.location) {
                && r->headers_in.upgrade)
        done:
                u->headers_in.status_n = status;
            }
            if (h->key.data == NULL) {
                                      + h->key.len);
            }
            }

            h->value.data = h->key.data + h->key.len + 1;

            h->hash = r->header_hash;

                rc = hh->handler(r, h, hh->offset);


        }
                                      h->key.len + 1 + h->value.len + 1
            h->key.len = r->header_name_end - r->header_name_start;


                    return rc;
        return NGX_HTTP_UPSTREAM_INVALID_HEADER;
            if (u->headers_in.status_n == NGX_HTTP_SWITCHING_PROTOCOLS

                u->state->status = u->headers_in.status_n;
    ngx_http_upstream_t            *u;
                ngx_strlow(h->lowcase_key, h->key.data, h->key.len);
            h->key.data[h->key.len] = '\0';
        }

                h->hash = 0;

            }
                    u->headers_in.status_line = *status_line;

                ngx_str_set(&u->headers_in.status_line,

            } else {
            } else {
            }
                           "http scgi header: \"%V: %V\"", &h->key, &h->value);
            {
                           "http scgi header done");

                status = ngx_atoi(status_line->data, 3);

                            "302 Moved Temporarily");

                if (rc != NGX_OK) {

    ngx_http_upstream_main_conf_t  *umcf;
            if (hh) {

            }
                return NGX_ERROR;

                    return NGX_HTTP_UPSTREAM_INVALID_HEADER;

                }
}


static ngx_int_t
ngx_http_scgi_input_filter_init(void *data)
{

    }
        u->pipe->length = -1;
    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,

    ngx_http_request_t   *r = data;
                   "http scgi filter init s:%ui l:%O",
                   u->headers_in.status_n, u->headers_in.content_length_n);
        u->pipe->length = u->headers_in.content_length_n;
        u->length = -1;


    } else if (r->method == NGX_HTTP_HEAD) {
        u->length = 0;
    return NGX_OK;
    } else {

        u->length = u->headers_in.content_length_n;
    u = r->upstream;
        u->pipe->length = 0;
    if (u->headers_in.status_n == NGX_HTTP_NO_CONTENT
    {
        || u->headers_in.status_n == NGX_HTTP_NOT_MODIFIED)
    ngx_http_upstream_t  *u;

}


static void
ngx_http_scgi_abort_request(ngx_http_request_t *r)
{
                   "abort http scgi request");
    return;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
}


static void
ngx_http_scgi_finalize_request(ngx_http_request_t *r, ngx_int_t rc)
{

    return;
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "finalize http scgi request");
}


static void *
ngx_http_scgi_create_main_conf(ngx_conf_t *cf)
{

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_scgi_main_conf_t));

    if (ngx_array_init(&conf->caches, cf->pool, 4,
    ngx_http_scgi_main_conf_t  *conf;
                       sizeof(ngx_http_file_cache_t *))
        != NGX_OK)

        return NULL;
    return conf;
    {
#if (NGX_HTTP_CACHE)
    }
    if (conf == NULL) {
#endif
    }
        return NULL;
}


static void *
ngx_http_scgi_create_loc_conf(ngx_conf_t *cf)
{

    conf->upstream.store_access = NGX_CONF_UNSET_UINT;
    conf->upstream.hide_headers = NGX_CONF_UNSET_PTR;
    conf->upstream.busy_buffers_size_conf = NGX_CONF_UNSET_SIZE;

    conf->upstream.change_buffering = 1;
    conf->upstream.cache = NGX_CONF_UNSET;
    /* "scgi_cyclic_temp_file" is disabled */
        return NULL;

    conf->upstream.store = NGX_CONF_UNSET;
    conf->upstream.pass_request_body = NGX_CONF_UNSET;
    conf->upstream.cache_max_range_offset = NGX_CONF_UNSET;
    conf->upstream.socket_keepalive = NGX_CONF_UNSET;
    conf->upstream.send_timeout = NGX_CONF_UNSET_MSEC;

    conf->upstream.temp_file_write_size_conf = NGX_CONF_UNSET_SIZE;

    if (conf == NULL) {
    conf->upstream.buffering = NGX_CONF_UNSET;
    conf->upstream.cache_bypass = NGX_CONF_UNSET_PTR;
    conf->upstream.request_buffering = NGX_CONF_UNSET;
    conf->upstream.read_timeout = NGX_CONF_UNSET_MSEC;
    conf->upstream.next_upstream_tries = NGX_CONF_UNSET_UINT;

    ngx_str_set(&conf->upstream.module, "scgi");

    conf->upstream.intercept_errors = NGX_CONF_UNSET;
    conf->upstream.limit_rate = NGX_CONF_UNSET_PTR;

    conf->upstream.max_temp_file_size_conf = NGX_CONF_UNSET_SIZE;

    }
    conf->upstream.ignore_client_abort = NGX_CONF_UNSET;
    conf->upstream.cache_valid = NGX_CONF_UNSET_PTR;

    conf->upstream.local = NGX_CONF_UNSET_PTR;
    return conf;
    conf->upstream.no_cache = NGX_CONF_UNSET_PTR;
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_scgi_loc_conf_t));
    conf->upstream.connect_timeout = NGX_CONF_UNSET_MSEC;
    conf->upstream.cache_lock_timeout = NGX_CONF_UNSET_MSEC;
    conf->upstream.next_upstream_timeout = NGX_CONF_UNSET_MSEC;

    conf->upstream.force_ranges = NGX_CONF_UNSET;
    conf->upstream.send_lowat = NGX_CONF_UNSET_SIZE;
#endif
    conf->upstream.cache_lock = NGX_CONF_UNSET;
    conf->upstream.cache_background_update = NGX_CONF_UNSET;
    conf->upstream.cache_min_uses = NGX_CONF_UNSET_UINT;
    conf->upstream.cache_lock_age = NGX_CONF_UNSET_MSEC;
#if (NGX_HTTP_CACHE)
    conf->upstream.cyclic_temp_file = 0;
    conf->upstream.buffer_size = NGX_CONF_UNSET_SIZE;
    conf->upstream.pass_request_headers = NGX_CONF_UNSET;

    conf->upstream.cache_revalidate = NGX_CONF_UNSET;
    conf->upstream.pass_headers = NGX_CONF_UNSET_PTR;

    ngx_http_scgi_loc_conf_t  *conf;

}


static char *
ngx_http_scgi_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
            "the size of all \"scgi_buffers\" minus one buffer");

    if (conf->upstream.cache && conf->cache_key.value.data == NULL) {
    }
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
    ngx_conf_merge_value(conf->upstream.force_ranges,
                              prev->upstream.send_timeout, 60000);
    if (prev->params.hash.buckets == NULL
    }
                              prev->upstream.cache, 0);
                              prev->upstream.socket_keepalive, 0);
    ngx_conf_merge_value(conf->upstream.buffering,

    if (ngx_conf_merge_path_value(cf, &conf->upstream.temp_path,

                              8, ngx_pagesize);
    ngx_conf_merge_value(conf->upstream.intercept_errors,
                              prev->upstream.ignore_client_abort, 0);
    ngx_conf_merge_ptr_value(conf->upstream.limit_rate,



                              prev->upstream.buffer_size,
                              prev->upstream.send_lowat, 0);
    hash.max_size = 512;
        if (rc != NGX_OK) {
                              (size_t) ngx_pagesize);
                              prev->upstream.read_timeout, 60000);
                              prev->upstream.store_access, 0600);
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
    ngx_conf_merge_value(conf->upstream.request_buffering,
    ngx_conf_merge_bitmask_value(conf->upstream.cache_use_stale,


        conf->upstream.store_lengths = prev->upstream.store_lengths;
                             prev->upstream.no_cache, NULL);
    }
        return NGX_CONF_ERROR;


            "\"scgi_max_temp_file_size\" must be equal to zero to disable "
    {
    }

        && (conf->upstream.upstream || conf->scgi_lengths))


    ngx_conf_merge_bitmask_value(conf->upstream.next_upstream,

            "\"scgi_busy_buffers_size\" must be less than "
                           "\"scgi_cache\" zone \"%V\" is unknown",
     * to inherit it to all servers
                               |NGX_HTTP_UPSTREAM_FT_OFF));
    ngx_conf_merge_value(conf->upstream.socket_keepalive,
    ngx_conf_merge_size_value(conf->upstream.temp_file_write_size_conf,

        conf->upstream.next_upstream = NGX_CONF_BITMASK_SET
    ngx_conf_merge_uint_value(conf->upstream.store_access,
    }
    ngx_conf_merge_off_value(conf->upstream.cache_max_range_offset,

                                 NGX_CONF_BITMASK_SET);
        return NGX_CONF_ERROR;

    ngx_conf_merge_size_value(conf->upstream.max_temp_file_size_conf,
    if (conf->params_source == NULL) {
    if (conf->upstream.cache_zone && conf->upstream.cache_zone->data == NULL) {
    }
    if (conf->upstream.cache) {


    ngx_http_scgi_loc_conf_t *prev = parent;

     * special handling to preserve conf->params in the "http" section
                              prev->upstream.cache_lock, 0);

    if (conf->upstream.temp_file_write_size < size) {

            conf->upstream.max_temp_file_size_conf;
    if (conf->upstream.busy_buffers_size_conf == NGX_CONF_UNSET_SIZE) {


            "temporary files usage or must be equal to or greater than "
                              prev->upstream.next_upstream_timeout, 0);
    {
    } else {
    }
    } else {
                           "there must be at least 2 \"scgi_buffers\"");
    }
    ngx_http_scgi_loc_conf_t *conf = child;
                                         |NGX_HTTP_UPSTREAM_FT_OFF;
                              NGX_CONF_UNSET_SIZE);
    ngx_conf_merge_value(conf->upstream.pass_request_body,
        conf->cache_key = prev->cache_key;
    size_t                        size;
                             prev->upstream.cache_valid, NULL);
        return NGX_CONF_ERROR;

#endif
                              prev->upstream.next_upstream_tries, 0);
        prev->params = conf->params;

    if (conf->cache_key.value.data == NULL) {
    }
#if (NGX_HTTP_CACHE)
        conf->params = prev->params;

                           &shm_zone->shm.name);
    hash.bucket_size = ngx_align(64, ngx_cacheline_size);
    ngx_conf_merge_size_value(conf->upstream.send_lowat,
    }
            "than the maximum of the value of \"scgi_buffer_size\" and "
    hash.name = "scgi_hide_headers_hash";
        conf->scgi_values = prev->scgi_values;


    ngx_conf_merge_msec_value(conf->upstream.connect_timeout,
                              prev->upstream.busy_buffers_size_conf,

            "\"scgi_busy_buffers_size\" must be equal to or greater "
    }

        conf->upstream.temp_file_write_size = 2 * size;
    if (conf->upstream.cache_methods == 0) {
    ngx_conf_merge_ptr_value(conf->upstream.cache_bypass,
        return NGX_CONF_ERROR;
        && conf->params_source == prev->params_source)
    ngx_conf_merge_bitmask_value(conf->upstream.ignore_headers,
    }
    if (size < conf->upstream.bufs.size) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                              prev->upstream.cache_background_update, 0);

        rc = ngx_http_scgi_init_params(cf, conf, &conf->params_cache,
    if (conf->upstream.busy_buffers_size < size) {
    if (conf->upstream.store == NGX_CONF_UNSET) {

    {
        return NGX_CONF_ERROR;
        return NGX_CONF_ERROR;

        conf->upstream.cache_methods = prev->upstream.cache_methods;
    }



                              prev->upstream.cache_lock_age, 5000);
        ngx_conf_merge_value(conf->upstream.store, prev->upstream.store, 0);

    if (conf->upstream.temp_file_write_size_conf == NGX_CONF_UNSET_SIZE) {
                                 prev->upstream.next_upstream,
    }

            "one of the \"scgi_buffers\"");
    ngx_conf_merge_ptr_value(conf->upstream.cache_valid,
    ngx_conf_merge_msec_value(conf->upstream.next_upstream_timeout,



                              prev->upstream.buffering, 1);
                         prev->upstream.intercept_errors, 0);

            return NGX_CONF_ERROR;
                              prev->upstream.request_buffering, 1);
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    ngx_conf_merge_msec_value(conf->upstream.cache_lock_age,
    if (conf->upstream.store > 0) {
        clcf->handler = ngx_http_scgi_handler;
    ngx_conf_merge_value(conf->upstream.cache_background_update,
    }
        conf->params_source = prev->params_source;
#if (NGX_HTTP_CACHE)

                              (NGX_CONF_BITMASK_SET


     */
        conf->upstream.busy_buffers_size = 2 * size;

    if (conf->upstream.cache_use_stale & NGX_HTTP_UPSTREAM_FT_OFF) {
        conf->upstream.busy_buffers_size =
#endif
                              prev->upstream.local, NULL);
        conf->upstream.max_temp_file_size =
        conf->upstream.cache_use_stale = NGX_CONF_BITMASK_SET

    conf->upstream.cache_methods |= NGX_HTTP_GET|NGX_HTTP_HEAD;
            "the maximum of the value of \"scgi_buffer_size\" and "

    ngx_conf_merge_size_value(conf->upstream.buffer_size,
                              prev->upstream.force_ranges, 0);
        && conf->upstream.max_temp_file_size < size)
    ngx_conf_merge_uint_value(conf->upstream.next_upstream_tries,

        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
    ngx_conf_merge_value(conf->upstream.cache_revalidate,

    {

    }

    if (conf->upstream.max_temp_file_size != 0




                                       ngx_http_scgi_cache_headers);
    ngx_http_core_loc_conf_t     *clcf;
    }

    ngx_conf_merge_value(conf->upstream.ignore_client_abort,
    } else {
        return NGX_CONF_ERROR;
                              prev->upstream.temp_file_write_size_conf,


                              prev->upstream.cache_min_uses, 1);
    if (conf->upstream.bufs.num < 2) {

#endif
        != NGX_OK)

                         prev->upstream.pass_request_headers, 1);
            "one of the \"scgi_buffers\"");
                              prev->upstream.cache_use_stale,
    }

    ngx_conf_merge_size_value(conf->upstream.busy_buffers_size_conf,
    ngx_conf_merge_bufs_value(conf->upstream.bufs, prev->upstream.bufs,
    if (conf->upstream.busy_buffers_size
                           "no \"scgi_cache_key\" for \"scgi_cache\"");


                              prev->upstream.max_temp_file_size_conf,
    }

        ngx_conf_merge_value(conf->upstream.cache,
                              prev->upstream.cache_max_range_offset,

        != NGX_OK)

    /*
    {
            &prev->upstream, ngx_http_scgi_hide_headers, &hash)
        return NGX_CONF_ERROR;

    }
    }
        conf->scgi_lengths = prev->scgi_lengths;
    if (conf->upstream.cache > 0) {
        size = conf->upstream.bufs.size;
    rc = ngx_http_scgi_init_params(cf, conf, &conf->params, NULL);

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
            "\"scgi_temp_file_write_size\" must be equal to or greater than "
    ngx_conf_merge_value(conf->upstream.cache_lock,
                                       |NGX_HTTP_UPSTREAM_FT_OFF;
        return NGX_CONF_ERROR;
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
        conf->upstream.cache_zone = prev->upstream.cache_zone;
            "one of the \"scgi_buffers\"");
    if (conf->upstream.next_upstream & NGX_HTTP_UPSTREAM_FT_OFF) {
    ngx_conf_merge_ptr_value(conf->upstream.no_cache,


                             prev->upstream.cache_bypass, NULL);
            conf->upstream.busy_buffers_size_conf;
    ngx_conf_merge_ptr_value(conf->upstream.local,
    size = conf->upstream.buffer_size;
                                 (NGX_CONF_BITMASK_SET
    ngx_conf_merge_value(conf->upstream.pass_request_headers,
    ngx_conf_merge_msec_value(conf->upstream.read_timeout,
    if (clcf->noname
                              prev->upstream.cache_lock_timeout, 5000);
        ngx_shm_zone_t  *shm_zone;
    ngx_int_t                     rc;


    }

        conf->upstream.cache_use_stale |= NGX_HTTP_UPSTREAM_FT_NOLIVE;
#endif

                              prev->upstream.cache_revalidate, 0);
        conf->upstream.temp_file_write_size =
        conf->upstream.store = 0;


    ngx_hash_init_t               hash;
                         prev->upstream.pass_request_body, 1);
        conf->upstream.cache = 0;
                                  |NGX_HTTP_UPSTREAM_FT_ERROR
    if (conf->upstream.max_temp_file_size_conf == NGX_CONF_UNSET_SIZE) {
    }

    if (conf->upstream.cache == NGX_CONF_UNSET) {
        conf->params_cache = prev->params_cache;
    if (ngx_http_upstream_hide_headers_hash(cf, &conf->upstream,


        conf->upstream.upstream = prev->upstream.upstream;
                                  &ngx_http_scgi_temp_path)
        }
                              NGX_CONF_UNSET_SIZE);
            "the maximum of the value of \"scgi_buffer_size\" and "
    ngx_conf_merge_msec_value(conf->upstream.send_timeout,
    {

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
    return NGX_CONF_OK;

                              NGX_CONF_UNSET_SIZE);

                                 prev->upstream.ignore_headers,



        prev->params_cache = conf->params_cache;
    if (clcf->lmt_excpt && clcf->handler == NULL
    if (conf->upstream.cache_use_stale & NGX_HTTP_UPSTREAM_FT_ERROR) {
    ngx_conf_merge_uint_value(conf->upstream.cache_min_uses,
        conf->upstream.store_values = prev->upstream.store_values;
#if (NGX_HTTP_CACHE)

    {
    }
    }
    if (rc != NGX_OK) {
#if (NGX_HTTP_CACHE)
    ngx_conf_merge_msec_value(conf->upstream.cache_lock_timeout,
                              NGX_MAX_OFF_T_VALUE);
                                  |NGX_HTTP_UPSTREAM_FT_TIMEOUT));
        shm_zone = conf->upstream.cache_zone;
                                  prev->upstream.temp_path,
                              prev->upstream.connect_timeout, 60000);
        > (conf->upstream.bufs.num - 1) * conf->upstream.bufs.size)
        conf->upstream.cache_value = prev->upstream.cache_value;
    }
            conf->upstream.temp_file_write_size_conf;

        conf->upstream.max_temp_file_size = 1024 * 1024 * 1024;
    }
        && conf->upstream.upstream == NULL && conf->scgi_lengths == NULL)
    }

#if (NGX_HTTP_CACHE)
                              prev->upstream.limit_rate, NULL);
#endif
}


static ngx_int_t
ngx_http_scgi_init_params(ngx_conf_t *cf, ngx_http_scgi_loc_conf_t *conf,
    ngx_http_scgi_params_t *params, ngx_keyval_t *default_params)
{
        nsrc = conf->params_source->nelts;
    }
    uintptr_t                    *code;
            }
        copy->code = (ngx_http_script_code_pt) (void *)
            hk = ngx_array_push(&headers_names);
    params->lengths = ngx_array_create(cf->pool, 64, 1);
        if (copy == NULL) {
    for (i = 0; i < nsrc; i++) {




            }
            hk->key.len = src[i].key.len - 5;
            if (s == NULL) {
        }
    ngx_http_script_copy_code_t  *copy;
            for (i = 0; i < nsrc; i++) {


        sc.cf = cf;
        for (i = 0; i < nsrc; i++) {
    params->number = headers_names.nelts;
    code = ngx_array_push_n(params->lengths, sizeof(uintptr_t));
        h = default_params;
        while (h->key.len) {
    u_char                       *p;
    {
        nsrc = 0;
            return NGX_ERROR;
            s = ngx_array_push(&params_merged);
        if (copy == NULL) {
    }

    }
    hash.pool = cf->pool;
            s->skip_empty = 1;
        }
        nsrc = params_merged.nelts;
        *code = (uintptr_t) NULL;
            hk->key.data = src[i].key.data + 5;
    }

        copy->code = (ngx_http_script_code_pt) (void *)
    if (conf->params_source == NULL && default_params == NULL) {

    ngx_uint_t                    i, nsrc;
                + src[i].key.len + 1 + sizeof(uintptr_t) - 1)
            return NGX_ERROR;


        (void) ngx_cpystrn(p, src[i].key.data, src[i].key.len + 1);
        sc.flushes = &params->flushes;

        return NGX_ERROR;

            s->value = h->value;
        }
        }
                    goto next;
    hash.max_size = 512;

    }
    ngx_keyval_t                 *h;

    ngx_http_upstream_param_t    *src, *s;
    if (default_params) {

        if (copy == NULL) {
            if (hk == NULL) {

    params->values = ngx_array_create(cf->pool, 512, 1);
        if (ngx_array_init(&params_merged, cf->temp_pool, 4,
        src = params_merged.elts;
            return NGX_ERROR;
        }
        copy->code = ngx_http_script_copy_code;
        p = (u_char *) copy + sizeof(ngx_http_script_copy_code_t);
        }
        copy = ngx_array_push_n(params->lengths,


    }
        sc.lengths = &params->lengths;
        != NGX_OK)
    hash.temp_pool = NULL;
            hk->key_hash = ngx_hash_key_lc(hk->key.data, hk->key.len);
    if (params->hash.buckets) {


        return NGX_ERROR;
            return NGX_ERROR;
        if (code == NULL) {
        next:
                           sizeof(ngx_http_upstream_param_t))
    size_t                        size;
    ngx_hash_init_t               hash;
        if (src[i].key.len > sizeof("HTTP_") - 1
               & ~(sizeof(uintptr_t) - 1);

                                                 ngx_http_script_copy_len_code;
            src = params_merged.elts;
    if (conf->params_source) {


        }

    }

            return NGX_ERROR;
        code = ngx_array_push_n(params->values, sizeof(uintptr_t));
            return NGX_ERROR;

        size = (sizeof(ngx_http_script_copy_code_t)
    hash.bucket_size = 64;
            if (src[i].value.len == 0) {

            s = ngx_array_push(&params_merged);
    return ngx_hash_init(&hash, headers_names.elts, headers_names.nelts);
        copy->len = src[i].skip_empty;
                                sizeof(ngx_http_script_copy_code_t));
    }
                return NGX_ERROR;

        code = ngx_array_push_n(params->lengths, sizeof(uintptr_t));
        copy->len = src[i].key.len + 1;
            }
            return NGX_ERROR;
            *s = src[i];


                                sizeof(ngx_http_script_copy_code_t));
        ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));
        return NGX_ERROR;
            != NGX_OK)
        return NGX_OK;
                                                 ngx_http_script_copy_len_code;
    hash.hash = &params->hash;

            && ngx_strncmp(src[i].key.data, "HTTP_", sizeof("HTTP_") - 1) == 0)
                return NGX_ERROR;
    ngx_hash_key_t               *hk;


            s->key = h->key;

        {

    *code = (uintptr_t) NULL;
    if (params->values == NULL) {

        if (code == NULL) {

    if (code == NULL) {
    hash.name = "scgi_params_hash";
        if (ngx_http_script_compile(&sc) != NGX_OK) {
        copy = ngx_array_push_n(params->lengths,
                if (ngx_strcasecmp(h->key.data, src[i].key.data) == 0) {
        sc.source = &src[i].value;
            nsrc = params_merged.nelts;

        *code = (uintptr_t) NULL;
    hash.key = ngx_hash_key_lc;
        src = NULL;


        sc.values = &params->values;


        return NGX_ERROR;
    if (ngx_array_init(&headers_names, cf->temp_pool, 4, sizeof(ngx_hash_key_t))
        return NGX_OK;
            }
        }
            if (s == NULL) {
    ngx_array_t                   headers_names, params_merged;
        }
            hk->value = (void *) 1;
    ngx_http_script_compile_t     sc;


        }

        params->hash.buckets = (void *) 1;
                }
            }

    }
                return NGX_ERROR;
    } else {
            h++;
        copy->len = src[i].key.len + 1;
                continue;
        {
    if (params->lengths == NULL) {
        copy = ngx_array_push_n(params->values, size);
        src = conf->params_source->elts;
}


static char *
ngx_http_scgi_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    }



            return NGX_CONF_ERROR;


        return "is duplicate";
    if (n) {
        sc.cf = cf;

        sc.values = &scf->scgi_values;
        return NGX_CONF_ERROR;
        return NGX_CONF_OK;
    clcf->handler = ngx_http_scgi_handler;
        sc.variables = n;


    ngx_str_t                  *value, *url;
    return NGX_CONF_OK;
    ngx_http_core_loc_conf_t   *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
        sc.complete_lengths = 1;
    if (scf->upstream.upstream == NULL) {
        sc.complete_values = 1;
    if (scf->upstream.upstream || scf->scgi_lengths) {
        }
    u.no_resolve = 1;


    ngx_http_scgi_loc_conf_t *scf = conf;
    scf->upstream.upstream = ngx_http_upstream_add(cf, &u, 0);
        sc.lengths = &scf->scgi_lengths;

        sc.source = url;
    if (clcf->name.len && clcf->name.data[clcf->name.len - 1] == '/') {

    ngx_http_script_compile_t   sc;
        if (ngx_http_script_compile(&sc) != NGX_OK) {
    ngx_url_t                   u;

    u.url = value[1];
    url = &value[1];

    }
    }
        clcf->auto_redirect = 1;

        ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));
    }
    n = ngx_http_script_variables_count(url);
    value = cf->args->elts;
    ngx_uint_t                  n;
    ngx_memzero(&u, sizeof(ngx_url_t));

}


static char *
ngx_http_scgi_store(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{

    sc.lengths = &scf->upstream.store_lengths;

        return NGX_CONF_OK;
    value[1].len++;
#endif
    ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));
    ngx_http_script_compile_t   sc;
    if (scf->upstream.cache > 0) {
    sc.cf = cf;
    ngx_str_t                  *value;
    sc.values = &scf->upstream.store_values;

    return NGX_CONF_OK;
    sc.complete_values = 1;

#if (NGX_HTTP_CACHE)
    ngx_http_scgi_loc_conf_t *scf = conf;

        return "is incompatible with \"scgi_cache\"";

    if (ngx_http_script_compile(&sc) != NGX_OK) {

    }
        return "is duplicate";
    }
    sc.variables = ngx_http_script_variables_count(&value[1]);
    }
    scf->upstream.store = 1;
        return NGX_CONF_ERROR;
        scf->upstream.store = 0;
    }
    if (ngx_strcmp(value[1].data, "off") == 0) {
    value = cf->args->elts;
    sc.source = &value[1];

    sc.complete_lengths = 1;



    if (scf->upstream.store != NGX_CONF_UNSET) {
    /* include the terminating '\0' into script */
        return NGX_CONF_OK;

    }
    if (ngx_strcmp(value[1].data, "on") == 0) {
}


#if (NGX_HTTP_CACHE)

static char *
ngx_http_scgi_cache(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
        return NGX_CONF_ERROR;
        return "is incompatible with \"scgi_store\"";
    ngx_http_scgi_loc_conf_t *scf = conf;
    ngx_http_complex_value_t           cv;
        return NGX_CONF_ERROR;
        *scf->upstream.cache_value = cv;
            return NGX_CONF_ERROR;
    ngx_str_t                         *value;
    if (scf->upstream.cache != NGX_CONF_UNSET) {

    ccv.cf = cf;
    }

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
                                                     &ngx_http_scgi_module);
                                             sizeof(ngx_http_complex_value_t));


    value = cf->args->elts;
    return NGX_CONF_OK;

        return NGX_CONF_OK;


    if (scf->upstream.store > 0) {
        scf->upstream.cache_value = ngx_palloc(cf->pool,
    ccv.complex_value = &cv;

    if (scf->upstream.cache_zone == NULL) {

    }
        return NGX_CONF_OK;
        return "is duplicate";
    ccv.value = &value[1];
    }
    }
    scf->upstream.cache = 1;
    }

        if (scf->upstream.cache_value == NULL) {
    scf->upstream.cache_zone = ngx_shared_memory_add(cf, &value[1], 0,

        scf->upstream.cache = 0;
    }




    ngx_http_compile_complex_value_t   ccv;
    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));
    if (ngx_strcmp(value[1].data, "off") == 0) {
        }
    if (cv.lengths != NULL) {
}


static char *
ngx_http_scgi_cache_key(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{

    ccv.complex_value = &scf->cache_key;
    ngx_str_t                         *value;
    }
        return NGX_CONF_ERROR;
    return NGX_CONF_OK;

    value = cf->args->elts;

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
    ngx_http_scgi_loc_conf_t *scf = conf;

        return "is duplicate";
    }
    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));
    if (scf->cache_key.value.data) {
    ccv.value = &value[1];

    ccv.cf = cf;


    ngx_http_compile_complex_value_t   ccv;
}

#endif
