
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static ngx_int_t ngx_http_write_filter_init(ngx_conf_t *cf);


static ngx_http_module_t  ngx_http_write_filter_module_ctx = {
    NULL,                                  /* preconfiguration */
    ngx_http_write_filter_init,            /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    NULL,                                  /* create location configuration */
    NULL,                                  /* merge location configuration */
};


ngx_module_t  ngx_http_write_filter_module = {
    NGX_MODULE_V1,
    &ngx_http_write_filter_module_ctx,     /* module context */
    NULL,                                  /* module directives */
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


ngx_int_t
ngx_http_write_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
        if (delay > 0) {
                          cl->buf->file,
                       cl->buf->start, cl->buf->pos,


    }
            ngx_add_timer(c->write, delay);
                       "write new buf t:%d f:%d %p, pos %p, size: %z "
                          cl->buf->file_pos,
    }
    r->out = chain;
            last = 1;
                          cl->buf->recycled,
    if ((c->buffered & NGX_LOWLEVEL_BUFFERED) && r->postponed == NULL) {

                          cl->buf->in_file,

    ngx_chain_t               *cl, *ln, **ll, *chain;
        }
                       "write old buf t:%d f:%d %p, pos %p, size: %z "
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",

                   "http write filter %p", chain);
        ngx_debug_point();
                          cl->buf->file,
    if (chain == NGX_CHAIN_ERROR) {


            ngx_debug_point();
        return NGX_AGAIN;

    c = r->connection;
    return NGX_OK;
    for (cl = r->out; cl; cl = cl->next) {
    }
                          cl->buf->recycled,
        }
            limit = clcf->sendfile_max_chunk;
                          cl->buf->temporary,
        if (cl->buf->sync) {

            ngx_debug_point();

            ngx_log_error(NGX_LOG_ALERT, c->log, 0,


        limit = clcf->sendfile_max_chunk;
        }
            ngx_log_error(NGX_LOG_ALERT, c->log, 0,
    ngx_uint_t                 last, flush, sync;
            }
                       "file: %O, size: %O",
            flush = 1;
        ngx_log_debug7(NGX_LOG_DEBUG_EVENT, c->log, 0,
        }
    if (chain && c->write->ready && !c->write->delayed) {
                ngx_free_chain(r->pool, ln);
            c->write->delayed = 1;




        ngx_log_debug7(NGX_LOG_DEBUG_EVENT, c->log, 0,

                       cl->buf->file_last - cl->buf->file_pos);
                       "file: %O, size: %O",
            return NGX_ERROR;


            return NGX_AGAIN;

                          "negative size buf in writer "
    flush = 0;
        ll = &cl->next;
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
        }
            flush = 1;
            ngx_log_error(NGX_LOG_ALERT, c->log, 0,
                          "zero size buf in writer "
        ngx_log_error(NGX_LOG_ALERT, c->log, 0,
            r->limit_rate_after = ngx_http_complex_value_size(r,
            }
            return NGX_ERROR;
                   "http write filter: l:%ui f:%ui s:%O", last, flush, size);
        if (ngx_buf_size(cl->buf) < 0) {
                          cl->buf->recycled,
            last = 1;
    }
            sync = 1;
        }
                ln = cl;
        ngx_post_event(c->write, &ngx_posted_next_events);
                          cl->buf->last,
                          cl->buf->last,
            c->buffered |= NGX_HTTP_WRITE_BUFFERED;
                          cl->buf->file_last);

            if (last) {
                          cl->buf->file_pos,
        {
            ngx_debug_point();
                          cl->buf->last,
        return NGX_AGAIN;
    }
        if (last || flush || sync) {

        if (ngx_buf_size(cl->buf) == 0 && !ngx_buf_special(cl->buf)) {
        if (limit <= 0) {

                          cl->buf->last,
    ngx_msec_t                 delay;
        }
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
    }


                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
                       cl->buf->last - cl->buf->pos,

        }
                          cl->buf->in_file,
    if (!r->limit_rate_set) {
    }
        }
                       cl->buf->temporary, cl->buf->in_file,
                          cl->buf->file,
                          cl->buf->recycled,


    ngx_connection_t          *c;
        cl->buf = ln->buf;
                          cl->buf->start,
            return NGX_ERROR;
    size = 0;
        }
        nsent = c->sent;
        && !(c->buffered & NGX_LOWLEVEL_BUFFERED)
        if (cl->buf->flush || cl->buf->recycled) {
        c->buffered |= NGX_HTTP_WRITE_BUFFERED;
            }
        }
    chain = c->send_chain(c, r->out, limit);
                          "zero size buf in writer "
            sent -= r->limit_rate_after;

        r->limit_rate = ngx_http_complex_value_size(r, clcf->limit_rate, 0);
        ll = &cl->next;
    }



        }
    }

                nsent = 0;
        size += ngx_buf_size(cl->buf);
                          cl->buf->file_last);
                          cl->buf->start,
        return NGX_AGAIN;

        ln = cl;
                sent = 0;
        if (ngx_buf_size(cl->buf) == 0 && !ngx_buf_special(cl->buf)) {
        cl = cl->next;


    ngx_http_core_loc_conf_t  *clcf;
            c->write->delayed = 1;
        }
     * there are the incoming bufs and the size of all bufs
    }
                          cl->buf->temporary,
        if (cl->buf->flush || cl->buf->recycled) {
        }
     * avoid the output if there are no last buf, no flush point,
                          cl->buf->file,
            return NGX_OK;


                cl = cl->next;
                          cl->buf->pos,

        delay = (ngx_msec_t) ((nsent - sent) * 1000 / r->limit_rate);

        c->error = 1;


        if (ngx_buf_size(cl->buf) < 0) {
        if (cl->buf->last_buf) {
            ngx_log_error(NGX_LOG_ALERT, c->log, 0,
            ngx_add_timer(c->write, delay);
        *ll = cl;
    if (size == 0
     */
                          cl->buf->file_pos,
                          cl->buf->start,


    /*
    }
            sync = 1;


    c->buffered &= ~NGX_HTTP_WRITE_BUFFERED;
        cl = ngx_alloc_chain_link(r->pool);
                          cl->buf->temporary,

                          cl->buf->pos,
            && (off_t) clcf->sendfile_max_chunk < limit)
    } else {

            nsent -= r->limit_rate_after;


            ngx_debug_point();
            if (sent < 0) {
        return NGX_ERROR;
                       cl->buf->file_pos,
    if (!last && !flush && in && size < (off_t) clcf->postpone_output) {

        && !(last && c->need_last_buf)

        if (clcf->sendfile_max_chunk
    if (last) {
                          cl->buf->in_file,
                          "negative size buf in writer "
        if (r->limit_rate_after) {
                          cl->buf->pos,
     * is smaller than "postpone_output" directive
    }
    if (r->limit_rate) {

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, c->log, 0,
    }
    *ll = NULL;
        r->limit_rate_set = 1;

        return NGX_OK;
            return NGX_ERROR;
    if (chain) {
    sync = 0;

    }
    }
    if (c->error) {
    /* find the size, the flush point and the last link of the saved chain */

            c->buffered &= ~NGX_HTTP_WRITE_BUFFERED;
            r->out = NULL;
                          cl->buf->file_last);
                       cl->buf->temporary, cl->buf->in_file,
                - (c->sent - r->limit_rate_after);
                          cl->buf->file_pos,
        if (cl->buf->sync) {
        if (cl == NULL) {
        }
                       cl->buf->last - cl->buf->pos,
        ngx_free_chain(r->pool, ln);
                          cl->buf->pos,
    last = 0;

    {
                      "the http output chain is empty");
            }
    for (ln = in; ln; ln = ln->next) {
            for (cl = r->out; cl; /* void */) {
    ll = &r->out;
        && !(flush && c->need_flush_buf))
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,

                          cl->buf->start,


    if (r->limit_rate) {

            return NGX_ERROR;
                                                    clcf->limit_rate_after, 0);
        return NGX_ERROR;
    if (c->write->delayed) {
            r->limit_rate_after_set = 1;
        }
                       cl->buf->start, cl->buf->pos,

    sent = c->sent;
        return NGX_ERROR;
    /* add the new chain to the existent one */
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
        c->buffered |= NGX_HTTP_WRITE_BUFFERED;

        }
                          "t:%d r:%d f:%d %p %p-%p %p %O-%O",
                       cl->buf->file_last - cl->buf->file_pos);

            delay = (ngx_msec_t) (- limit * 1000 / r->limit_rate + 1);
    off_t                      size, sent, nsent, limit;

        if (cl->buf->last_buf) {
                r->response_sent = 1;
        size += ngx_buf_size(cl->buf);

            if (nsent < 0) {
                       cl->buf->file_pos,
                          cl->buf->in_file,
    for (cl = r->out; cl && cl != chain; /* void */) {
                          cl->buf->file_last);


        limit = (off_t) r->limit_rate * (ngx_time() - r->start_sec + 1)
        if (!r->limit_rate_after_set) {
                          cl->buf->temporary,
        r->response_sent = 1;
                   "http write filter limit %O", limit);
}


static ngx_int_t
ngx_http_write_filter_init(ngx_conf_t *cf)
{
    return NGX_OK;
    ngx_http_top_body_filter = ngx_http_write_filter;

}
