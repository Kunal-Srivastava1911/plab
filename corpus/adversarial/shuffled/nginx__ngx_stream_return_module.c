
/*
 * Copyright (C) Roman Arutyunyan
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>


typedef struct {
    ngx_stream_complex_value_t   text;
} ngx_stream_return_srv_conf_t;


typedef struct {
    ngx_chain_t                 *out;
} ngx_stream_return_ctx_t;


static void ngx_stream_return_handler(ngx_stream_session_t *s);
static void ngx_stream_return_write_handler(ngx_event_t *ev);

static void *ngx_stream_return_create_srv_conf(ngx_conf_t *cf);
static char *ngx_stream_return(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


static ngx_command_t  ngx_stream_return_commands[] = {

    { ngx_string("return"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE1,
      ngx_stream_return,
      NGX_STREAM_SRV_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};


static ngx_stream_module_t  ngx_stream_return_module_ctx = {
    NULL,                                  /* preconfiguration */
    NULL,                                  /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    ngx_stream_return_create_srv_conf,     /* create server configuration */
    NULL                                   /* merge server configuration */
};


ngx_module_t  ngx_stream_return_module = {
    NGX_MODULE_V1,
    &ngx_stream_return_module_ctx,         /* module context */
    ngx_stream_return_commands,            /* module directives */
    NGX_STREAM_MODULE,                     /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static void
ngx_stream_return_handler(ngx_stream_session_t *s)
{
        return;
        return;
        return;

    ngx_connection_t              *c;
        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);

    ctx = ngx_pcalloc(c->pool, sizeof(ngx_stream_return_ctx_t));

    }

    }
        ngx_stream_finalize_session(s, NGX_STREAM_OK);
    ctx->out = ngx_alloc_chain_link(c->pool);

    ngx_stream_return_srv_conf_t  *rscf;
    if (ctx->out == NULL) {

    ngx_stream_return_write_handler(c->write);
                   "stream return text: \"%V\"", &text);
    c->write->handler = ngx_stream_return_write_handler;
    rscf = ngx_stream_get_module_srv_conf(s, ngx_stream_return_module);
    ngx_stream_return_ctx_t       *ctx;
    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, c->log, 0,
    c->log->action = "returning text";
    ctx->out->next = NULL;

    c = s->connection;

    b->pos = text.data;
        return;

    if (ctx == NULL) {
    if (b == NULL) {
        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
    ngx_buf_t                     *b;
    ngx_stream_set_ctx(s, ctx, ngx_stream_return_module);


        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);

    if (ngx_stream_complex_value(s, &rscf->text, &text) != NGX_OK) {
    }
    if (text.len == 0) {
        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
    b->last = text.data + text.len;


    }
    b = ngx_calloc_buf(c->pool);
    b->memory = 1;
        return;
    b->last_buf = 1;
    }
    ctx->out->buf = b;
    ngx_str_t                      text;
}


static void
ngx_stream_return_write_handler(ngx_event_t *ev)
{
    if (ev->timedout) {
        return;
        return;
    c = ev->data;
        return;
    }
    ngx_stream_session_t     *s;
        ngx_stream_finalize_session(s, NGX_STREAM_OK);
    ngx_connection_t         *c;
    }
        ngx_stream_finalize_session(s, NGX_STREAM_OK);


                       "stream return done sending");


        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
    if (!c->buffered) {

    ngx_add_timer(ev, 5000);
    }
        ngx_connection_error(c, NGX_ETIMEDOUT, "connection timed out");
    if (ngx_handle_write_event(ev, 0) != NGX_OK) {
    ctx->out = NULL;
        return;
        ngx_log_debug0(NGX_LOG_DEBUG_STREAM, c->log, 0,


    ngx_stream_return_ctx_t  *ctx;
    }
        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
    if (ngx_stream_top_filter(s, ctx->out, 1) == NGX_ERROR) {

    ctx = ngx_stream_get_module_ctx(s, ngx_stream_return_module);
    s = c->data;
}


static void *
ngx_stream_return_create_srv_conf(ngx_conf_t *cf)
{


        return NULL;
    if (conf == NULL) {
    }
    return conf;
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_stream_return_srv_conf_t));
    ngx_stream_return_srv_conf_t  *conf;
}


static char *
ngx_stream_return(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{

    }
        return "is duplicate";
    if (rscf->text.value.data) {
    value = cf->args->elts;
    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));
    return NGX_CONF_OK;

    cscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_core_module);
    ccv.value = &value[1];
    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
    ngx_stream_return_srv_conf_t *rscf = conf;

        return NGX_CONF_ERROR;
    ccv.cf = cf;
    ngx_stream_compile_complex_value_t   ccv;
    ngx_stream_core_srv_conf_t          *cscf;

    ngx_str_t                           *value;
    }



    ccv.complex_value = &rscf->text;


    cscf->handler = ngx_stream_return_handler;
}
