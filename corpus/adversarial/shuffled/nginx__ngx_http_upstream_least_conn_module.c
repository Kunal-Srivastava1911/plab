
/*
 * Copyright (C) Maxim Dounin
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static ngx_int_t ngx_http_upstream_init_least_conn_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us);
static ngx_int_t ngx_http_upstream_get_least_conn_peer(
    ngx_peer_connection_t *pc, void *data);
static char *ngx_http_upstream_least_conn(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);


static ngx_command_t  ngx_http_upstream_least_conn_commands[] = {

    { ngx_string("least_conn"),
      NGX_HTTP_UPS_CONF|NGX_CONF_NOARGS,
      ngx_http_upstream_least_conn,
      0,
      0,
      NULL },

      ngx_null_command
};


static ngx_http_module_t  ngx_http_upstream_least_conn_module_ctx = {
    NULL,                                  /* preconfiguration */
    NULL,                                  /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    NULL,                                  /* create location configuration */
    NULL                                   /* merge location configuration */
};


ngx_module_t  ngx_http_upstream_least_conn_module = {
    NGX_MODULE_V1,
    &ngx_http_upstream_least_conn_module_ctx, /* module context */
    ngx_http_upstream_least_conn_commands, /* module directives */
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


static ngx_int_t
ngx_http_upstream_init_least_conn(ngx_conf_t *cf,
    ngx_http_upstream_srv_conf_t *us)
{
    if (ngx_http_upstream_init_round_robin(cf, us) != NGX_OK) {
        return NGX_ERROR;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, cf->log, 0,

    }
    return NGX_OK;
                   "init least conn");

    us->peer.init = ngx_http_upstream_init_least_conn_peer;
}


static ngx_int_t
ngx_http_upstream_init_least_conn_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
                   "init least conn peer");
    }

        return NGX_ERROR;
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,

    return NGX_OK;

    r->upstream->peer.get = ngx_http_upstream_get_least_conn_peer;
    if (ngx_http_upstream_init_round_robin_peer(r, us) != NGX_OK) {
}


static ngx_int_t
ngx_http_upstream_get_least_conn_peer(ngx_peer_connection_t *pc, void *data)
{
    time_t                         now;

                continue;
        {

    pc->name = &best->name;
    }
    best->conns++;

        if (peer->max_fails
    pc->cached = 0;
    ngx_http_upstream_rr_peers_unlock(peers);
    m = (uintptr_t) 1 << p % (8 * sizeof(uintptr_t));
    }
            || peer->conns * best->weight < best->conns * peer->weight)
            continue;
    now = ngx_time();
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pc->log, 0,
    }


            && now - peer->checked <= peer->fail_timeout)

    }
    if (now - best->checked > best->fail_timeout) {

    {
        }
                continue;
        } else if (peer->conns * best->weight == best->conns * peer->weight) {
            {
    uintptr_t                      m;

    for (peer = peers->peer, i = 0;


                / (8 * sizeof(uintptr_t));
    pc->socklen = best->socklen;

        n = i / (8 * sizeof(uintptr_t));
        }
        if (rc != NGX_BUSY) {



         peer;
        best->checked = now;
    if (many) {
    pc->name = peers->name;

         * select peer with least number of connections; if there are
    ngx_int_t                      rc, total;
            peer->current_weight += peer->effective_weight;
        }
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0,


    n = p / (8 * sizeof(uintptr_t));

             peer = peer->next, i++)

            }
            }

            best = peer;
    ngx_http_upstream_rr_peers_t  *peers;
        if (peer->max_conns && peer->conns >= peer->max_conns) {

        if (best == NULL
    many = 0;
    ngx_http_upstream_rr_peers_wlock(peers);
    ngx_uint_t                     i, n, p, many;
            }
        }
        return ngx_http_upstream_get_round_robin_peer(pc, rrp);
        rrp->peers = peers->next;
                && peer->fails >= peer->max_fails
                       "get least conn peer, no peer found");
         peer = peer->next, i++)
            many = 1;
                continue;



            n = i / (8 * sizeof(uintptr_t));
            total += peer->effective_weight;
    ngx_http_upstream_rr_peer_data_t  *rrp = data;
            if (peer->effective_weight < peer->weight) {
                && now - peer->checked <= peer->fail_timeout)
    }
            }

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0,
    if (peers->next) {
    total = 0;
        goto failed;
         * based on round-robin
    ngx_http_upstream_rr_peer_t   *peer, *best;

failed:
    best = NULL;

    p = 0;
        if (peer->down) {
#endif
        {


             peer;

            continue;
        for (peer = best, i = p;
            if (peer->max_conns && peer->conns >= peer->max_conns) {

         */

        }
            p = i;
                   "get least conn peer, try: %ui", pc->tries);
    if (best == NULL) {
    pc->connection = NULL;
                peer->effective_weight++;
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0,
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

                       "get least conn peer, many");


    pc->sockaddr = best->sockaddr;


    best->current_weight -= total;
                       "get least conn peer, backup servers");
        /*

        if (rrp->tried[n] & m) {
            }
                continue;

    }
            rrp->tried[i] = 0;
        ngx_http_upstream_rr_peers_unlock(peers);
                continue;
            continue;
        ngx_http_upstream_rr_peers_wlock(peers);
            && peer->fails >= peer->max_fails
        }

            return rc;
            if (peer->max_fails
        }

            if (rrp->tried[n] & m) {
        {
        n = (rrp->peers->number + (8 * sizeof(uintptr_t) - 1))
            if (peer->current_weight > best->current_weight) {

#if (NGX_SUPPRESS_WARN)
         * multiple peers with the same number of connections, select
            m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));
    rrp->tried[n] |= m;
    if (rrp->peers->single) {
    rrp->current = best;
        for (i = 0; i < n; i++) {
                p = i;
            }
            if (peer->down) {
            many = 0;


            continue;
        rc = ngx_http_upstream_get_least_conn_peer(pc, rrp);

        }

    ngx_http_upstream_rr_peers_unlock(peers);
            }
    peers = rrp->peers;
    return NGX_OK;
    return NGX_BUSY;




            if (peer->conns * best->weight != best->conns * peer->weight) {
                best = peer;
}


static char *
ngx_http_upstream_least_conn(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    uscf->flags = NGX_HTTP_UPSTREAM_CREATE
                  |NGX_HTTP_UPSTREAM_MAX_CONNS
    if (uscf->peer.init_upstream) {

    uscf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_upstream_module);

                  |NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
    }

    uscf->peer.init_upstream = ngx_http_upstream_init_least_conn;


        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                  |NGX_HTTP_UPSTREAM_BACKUP;
    return NGX_CONF_OK;
                  |NGX_HTTP_UPSTREAM_WEIGHT
                           "load balancing method redefined");
    ngx_http_upstream_srv_conf_t  *uscf;
                  |NGX_HTTP_UPSTREAM_MAX_FAILS
                  |NGX_HTTP_UPSTREAM_DOWN
}
