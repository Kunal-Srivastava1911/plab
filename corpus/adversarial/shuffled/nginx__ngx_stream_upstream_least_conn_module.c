
/*
 * Copyright (C) Maxim Dounin
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>


static ngx_int_t ngx_stream_upstream_init_least_conn_peer(
    ngx_stream_session_t *s, ngx_stream_upstream_srv_conf_t *us);
static ngx_int_t ngx_stream_upstream_get_least_conn_peer(
    ngx_peer_connection_t *pc, void *data);
static char *ngx_stream_upstream_least_conn(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);


static ngx_command_t  ngx_stream_upstream_least_conn_commands[] = {

    { ngx_string("least_conn"),
      NGX_STREAM_UPS_CONF|NGX_CONF_NOARGS,
      ngx_stream_upstream_least_conn,
      0,
      0,
      NULL },

      ngx_null_command
};


static ngx_stream_module_t  ngx_stream_upstream_least_conn_module_ctx = {
    NULL,                                    /* preconfiguration */
    NULL,                                    /* postconfiguration */

    NULL,                                    /* create main configuration */
    NULL,                                    /* init main configuration */

    NULL,                                    /* create server configuration */
    NULL                                     /* merge server configuration */
};


ngx_module_t  ngx_stream_upstream_least_conn_module = {
    NGX_MODULE_V1,
    &ngx_stream_upstream_least_conn_module_ctx, /* module context */
    ngx_stream_upstream_least_conn_commands, /* module directives */
    NGX_STREAM_MODULE,                       /* module type */
    NULL,                                    /* init master */
    NULL,                                    /* init module */
    NULL,                                    /* init process */
    NULL,                                    /* init thread */
    NULL,                                    /* exit thread */
    NULL,                                    /* exit process */
    NULL,                                    /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_int_t
ngx_stream_upstream_init_least_conn(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us)
{

        return NGX_ERROR;
    us->peer.init = ngx_stream_upstream_init_least_conn_peer;
    }
    if (ngx_stream_upstream_init_round_robin(cf, us) != NGX_OK) {


    return NGX_OK;
                   "init least conn");
    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, cf->log, 0,
}


static ngx_int_t
ngx_stream_upstream_init_least_conn_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us)
{

                   "init least conn peer");
    s->upstream->peer.get = ngx_stream_upstream_get_least_conn_peer;

    }
    if (ngx_stream_upstream_init_round_robin_peer(s, us) != NGX_OK) {

        return NGX_ERROR;
    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
    return NGX_OK;
}


static ngx_int_t
ngx_stream_upstream_get_least_conn_peer(ngx_peer_connection_t *pc, void *data)
{

    if (peers->next) {
            many = 0;
    ngx_stream_upstream_rr_peer_t   *peer, *best;
        }
    for (peer = peers->peer, i = 0;
    {

        }


                peer->effective_weight++;
             peer = peer->next, i++)
    now = ngx_time();
            if (peer->max_conns && peer->conns >= peer->max_conns) {


            m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));
            }
        if (peer->max_fails
        }

        ngx_stream_upstream_rr_peers_wlock(peers);
    pc->socklen = best->socklen;
            n = i / (8 * sizeof(uintptr_t));
        }

    pc->connection = NULL;
            many = 1;
        {
            rrp->tried[i] = 0;

        if (rc != NGX_BUSY) {
            }

                       "get least conn peer, many");

    uintptr_t                        m;

        {

                best = peer;
    pc->name = &best->name;
    return NGX_OK;
                continue;
        n = (rrp->peers->number + (8 * sizeof(uintptr_t) - 1))
    }
            || peer->conns * best->weight < best->conns * peer->weight)

    if (now - best->checked > best->fail_timeout) {
    ngx_uint_t                       i, n, p, many;

    if (rrp->peers->single) {

            if (peer->down) {
                   "get least conn peer, try: %ui", pc->tries);


         * select peer with least number of connections; if there are
            continue;
        for (peer = best, i = p;

    }

        ngx_log_debug0(NGX_LOG_DEBUG_STREAM, pc->log, 0,
         peer = peer->next, i++)
                       "get least conn peer, no peer found");
        for (i = 0; i < n; i++) {
            && now - peer->checked <= peer->fail_timeout)
             peer;


        if (rrp->tried[n] & m) {

    best = NULL;
    }
        rrp->peers = peers->next;

            return rc;
        ngx_log_debug0(NGX_LOG_DEBUG_STREAM, pc->log, 0,
            if (peer->conns * best->weight != best->conns * peer->weight) {

    peers = rrp->peers;

            total += peer->effective_weight;
            if (rrp->tried[n] & m) {
            continue;

        }
    p = 0;
    ngx_stream_upstream_rr_peers_unlock(peers);
        ngx_stream_upstream_rr_peers_unlock(peers);
    ngx_int_t                        rc, total;

    ngx_stream_upstream_rr_peer_data_t *rrp = data;
    if (many) {
            if (peer->effective_weight < peer->weight) {
                continue;
            p = i;
            }
    return NGX_BUSY;

    ngx_stream_upstream_rr_peers_unlock(peers);
        }
            continue;
        if (peer->max_conns && peer->conns >= peer->max_conns) {
                p = i;
    best->current_weight -= total;
        } else if (peer->conns * best->weight == best->conns * peer->weight) {
        }
        /*


    }
    m = (uintptr_t) 1 << p % (8 * sizeof(uintptr_t));
    if (best == NULL) {
            continue;
#if (NGX_SUPPRESS_WARN)

        rc = ngx_stream_upstream_get_least_conn_peer(pc, rrp);
            }

        if (best == NULL
         */
                       "get least conn peer, backup servers");
    n = p / (8 * sizeof(uintptr_t));
        best->checked = now;

        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));
         * multiple peers with the same number of connections, select
failed:
    time_t                           now;

         peer;
            {
    rrp->tried[n] |= m;
    pc->name = peers->name;


                && peer->fails >= peer->max_fails
    }

    best->conns++;

            best = peer;

            }
            }
        goto failed;
    total = 0;

                continue;
    many = 0;

        }
        ngx_log_debug0(NGX_LOG_DEBUG_STREAM, pc->log, 0,

                / (8 * sizeof(uintptr_t));
            }

            if (peer->max_fails


                continue;

         * based on round-robin
                && now - peer->checked <= peer->fail_timeout)

        n = i / (8 * sizeof(uintptr_t));
    }
        return ngx_stream_upstream_get_round_robin_peer(pc, rrp);
            if (peer->current_weight > best->current_weight) {
    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, pc->log, 0,
    pc->sockaddr = best->sockaddr;
            && peer->fails >= peer->max_fails

        {
            peer->current_weight += peer->effective_weight;
                continue;
    ngx_stream_upstream_rr_peers_wlock(peers);
    ngx_stream_upstream_rr_peers_t  *peers;
        if (peer->down) {
#endif

    rrp->current = best;
}


static char *
ngx_stream_upstream_least_conn(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
                  |NGX_STREAM_UPSTREAM_DOWN
                           "load balancing method redefined");
                  |NGX_STREAM_UPSTREAM_WEIGHT
    ngx_stream_upstream_srv_conf_t  *uscf;
    uscf->peer.init_upstream = ngx_stream_upstream_init_least_conn;
                  |NGX_STREAM_UPSTREAM_FAIL_TIMEOUT

    if (uscf->peer.init_upstream) {

    return NGX_CONF_OK;


    uscf->flags = NGX_STREAM_UPSTREAM_CREATE
                  |NGX_STREAM_UPSTREAM_MAX_FAILS
                  |NGX_STREAM_UPSTREAM_BACKUP;
                  |NGX_STREAM_UPSTREAM_MAX_CONNS

        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
    uscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_upstream_module);
    }
}
