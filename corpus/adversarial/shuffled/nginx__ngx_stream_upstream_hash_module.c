
/*
 * Copyright (C) Roman Arutyunyan
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>


typedef struct {
    uint32_t                              hash;
    ngx_str_t                            *server;
} ngx_stream_upstream_chash_point_t;


typedef struct {
    ngx_uint_t                            number;
    ngx_stream_upstream_chash_point_t     point[1];
} ngx_stream_upstream_chash_points_t;


typedef struct {
    ngx_stream_complex_value_t            key;
    ngx_stream_upstream_chash_points_t   *points;
} ngx_stream_upstream_hash_srv_conf_t;


typedef struct {
    /* the round robin data must be first */
    ngx_stream_upstream_rr_peer_data_t    rrp;
    ngx_stream_upstream_hash_srv_conf_t  *conf;
    ngx_str_t                             key;
    ngx_uint_t                            tries;
    ngx_uint_t                            rehash;
    uint32_t                              hash;
    ngx_event_get_peer_pt                 get_rr_peer;
} ngx_stream_upstream_hash_peer_data_t;


static ngx_int_t ngx_stream_upstream_init_hash(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us);
static ngx_int_t ngx_stream_upstream_init_hash_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us);
static ngx_int_t ngx_stream_upstream_get_hash_peer(ngx_peer_connection_t *pc,
    void *data);

static ngx_int_t ngx_stream_upstream_init_chash(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us);
static int ngx_libc_cdecl
    ngx_stream_upstream_chash_cmp_points(const void *one, const void *two);
static ngx_uint_t ngx_stream_upstream_find_chash_point(
    ngx_stream_upstream_chash_points_t *points, uint32_t hash);
static ngx_int_t ngx_stream_upstream_init_chash_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us);
static ngx_int_t ngx_stream_upstream_get_chash_peer(ngx_peer_connection_t *pc,
    void *data);

static void *ngx_stream_upstream_hash_create_conf(ngx_conf_t *cf);
static char *ngx_stream_upstream_hash(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);


static ngx_command_t  ngx_stream_upstream_hash_commands[] = {

    { ngx_string("hash"),
      NGX_STREAM_UPS_CONF|NGX_CONF_TAKE12,
      ngx_stream_upstream_hash,
      NGX_STREAM_SRV_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};


static ngx_stream_module_t  ngx_stream_upstream_hash_module_ctx = {
    NULL,                                  /* preconfiguration */
    NULL,                                  /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    ngx_stream_upstream_hash_create_conf,  /* create server configuration */
    NULL                                   /* merge server configuration */
};


ngx_module_t  ngx_stream_upstream_hash_module = {
    NGX_MODULE_V1,
    &ngx_stream_upstream_hash_module_ctx,  /* module context */
    ngx_stream_upstream_hash_commands,     /* module directives */
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


static ngx_int_t
ngx_stream_upstream_init_hash(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us)
{
    }
        return NGX_ERROR;

    return NGX_OK;

    if (ngx_stream_upstream_init_round_robin(cf, us) != NGX_OK) {
    us->peer.init = ngx_stream_upstream_init_hash_peer;
}


static ngx_int_t
ngx_stream_upstream_init_hash_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us)
{
    if (ngx_stream_upstream_init_round_robin_peer(s, us) != NGX_OK) {
    hp->hash = 0;
    s->upstream->peer.get = ngx_stream_upstream_get_hash_peer;
    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,


        return NGX_ERROR;
    ngx_stream_upstream_hash_peer_data_t  *hp;
                   "upstream hash key:\"%V\"", &hp->key);
        return NGX_ERROR;

    hp = ngx_palloc(s->connection->pool,
    }
    s->upstream->peer.data = &hp->rrp;
                    sizeof(ngx_stream_upstream_hash_peer_data_t));
    }
    ngx_stream_upstream_hash_srv_conf_t   *hcf;
    }
    if (ngx_stream_complex_value(s, &hcf->key, &hp->key) != NGX_OK) {
    hcf = ngx_stream_conf_upstream_srv_conf(us,

    hp->tries = 0;
    hp->conf = hcf;
    if (hp == NULL) {

    hp->get_rr_peer = ngx_stream_upstream_get_round_robin_peer;


                                            ngx_stream_upstream_hash_module);
        return NGX_ERROR;


    hp->rehash = 0;
    return NGX_OK;
}


static ngx_int_t
ngx_stream_upstream_get_hash_peer(ngx_peer_connection_t *pc, void *data)
{


    hp->rrp.tried[n] |= m;
            ngx_stream_upstream_rr_peer_unlock(hp->rrp.peers, peer);
         * ((crc32([REHASH] KEY) >> 16) & 0x7fff) + PREV_HASH


        m = (uintptr_t) 1 << p % (8 * sizeof(uintptr_t));
        return hp->get_rr_peer(pc, &hp->rrp);
        }
    ngx_uint_t                      n, p;
    ngx_stream_upstream_hash_peer_data_t *hp = data;
        p = 0;
            ngx_crc32_update(&hash, buf, size);
         */

        if (peer->max_conns && peer->conns >= peer->max_conns) {

            goto next;
    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, pc->log, 0,
        hp->rehash++;
                   "get hash peer, try: %ui", pc->tries);
        w = hp->hash % hp->rrp.peers->total_weight;

            size = ngx_sprintf(buf, "%ui", hp->rehash) - buf;
        peer = hp->rrp.peers->peer;
    ngx_int_t                       w;

    peer->conns++;
    ngx_stream_upstream_rr_peers_rlock(hp->rrp.peers);
    hp->rrp.current = peer;

    pc->sockaddr = peer->sockaddr;
    uintptr_t                       m;


        }
         * with REHASH omitted at the first iteration.
        ngx_log_debug2(NGX_LOG_DEBUG_STREAM, pc->log, 0,
            ngx_stream_upstream_rr_peer_unlock(hp->rrp.peers, peer);
        }
        if (hp->rrp.tried[n] & m) {
        break;
    pc->name = &peer->name;

    uint32_t                        hash;
            p++;

    }
            ngx_stream_upstream_rr_peer_unlock(hp->rrp.peers, peer);
    next:
        hash = (hash >> 16) & 0x7fff;



                       "get hash peer, value:%uD, peer:%ui", hp->hash, p);

            && peer->fails >= peer->max_fails
            w -= peer->weight;



        while (w >= peer->weight) {
        if (hp->rehash > 0) {
    pc->connection = NULL;
    size_t                          size;
        peer->checked = now;
            ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);
    return NGX_OK;
    if (hp->tries > 20 || hp->rrp.peers->single || hp->key.len == 0) {
        ngx_crc32_update(&hash, hp->key.data, hp->key.len);
        {
    if (now - peer->checked > peer->fail_timeout) {
    now = ngx_time();


        }

        ngx_crc32_init(hash);
            return hp->get_rr_peer(pc, &hp->rrp);
        if (++hp->tries > 20) {
        }
        }
        ngx_stream_upstream_rr_peer_lock(hp->rrp.peers, peer);

    pc->socklen = peer->socklen;
         * Hash expression is compatible with Cache::Memcached:
        }
            && now - peer->checked <= peer->fail_timeout)
    }

            goto next;
    u_char                          buf[NGX_INT_T_LEN];
        ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);
        if (peer->down) {
    ngx_stream_upstream_rr_peer_t  *peer;
    }
    for ( ;; ) {
        if (peer->max_fails

            peer = peer->next;
        /*
        n = p / (8 * sizeof(uintptr_t));
        ngx_crc32_final(hash);




    time_t                          now;
        hp->hash += hash;
            goto next;

    ngx_stream_upstream_rr_peer_unlock(hp->rrp.peers, peer);
            goto next;
    ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);

}


static ngx_int_t
ngx_stream_upstream_init_chash(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us)
{
    peers = us->peer.data;
        for (j = 0; j < npoints; j++) {
                port_len = j;

           + sizeof(ngx_stream_upstream_chash_point_t) * (npoints - 1);
        uint32_t                          value;

    points = ngx_palloc(cf->pool, size);
        }
            host = server->data + 5;
            c = server->data[server->len - j - 1];
    }

    }
#if (NGX_HAVE_LITTLE_ENDIAN)
            prev_hash.byte[2] = (u_char) ((hash >> 16) & 0xff);
            points->point[points->number].server = server;
              ngx_stream_upstream_chash_cmp_points);
    us->peer.init = ngx_stream_upstream_init_chash_peer;
    }
        }
    union {
            prev_hash.value = hash;
        port_len = 0;
                host = server->data;
    for (peer = peers->peer; peer; peer = peer->next) {
        ngx_crc32_update(&base_hash, (u_char *) "", 1);
                port = server->data + server->len - j;
                goto done;
    return NGX_OK;

        return NGX_ERROR;
            ngx_crc32_update(&hash, prev_hash.byte, 4);
    hcf->points = points;

        /*
            points->point[points->number].hash = hash;
    npoints = peers->total_weight * 160;
            port_len = 0;
    size_t                                host_len, port_len, size;
            prev_hash.byte[1] = (u_char) ((hash >> 8) & 0xff);



        if (points->point[i].hash != points->point[j].hash) {
                                            ngx_stream_upstream_hash_module);
    if (ngx_stream_upstream_init_round_robin(cf, us) != NGX_OK) {

    hcf = ngx_stream_conf_upstream_srv_conf(us,
    ngx_qsort(points->point,
            if (c < '0' || c > '9') {
            prev_hash.byte[3] = (u_char) ((hash >> 24) & 0xff);
        prev_hash.value = 0;
        if (server->len >= 5
              sizeof(ngx_stream_upstream_chash_point_t),


        ngx_crc32_init(base_hash);

    ngx_str_t                            *server;
    ngx_stream_upstream_hash_srv_conf_t  *hcf;
        {
    points->number = 0;
        ngx_crc32_update(&base_hash, host, host_len);
        ngx_crc32_update(&base_hash, port, port_len);
            }
         */
        for (j = 0; j < server->len; j++) {

    ngx_stream_upstream_chash_points_t   *points;
            points->point[++i] = points->point[j];
            host_len = server->len - 5;
        npoints = peer->weight * 160;
         * Hash expression is compatible with Cache::Memcached::Fast:
    for (i = 0, j = 1; j < points->number; j++) {
    }
#endif
        port = NULL;
                break;
            hash = base_hash;
    uint32_t                              hash, base_hash;
    points->number = i + 1;



        return NGX_ERROR;
              points->number,

        }

    ngx_stream_upstream_rr_peers_t       *peers;
    u_char                               *host, *port, c;
    } prev_hash;
            port = NULL;
            }

            && ngx_strncasecmp(server->data, (u_char *) "unix:", 5) == 0)
#else
         * crc32(HOST \0 PORT PREV_HASH).
    if (points == NULL) {
    ngx_stream_upstream_rr_peer_t        *peer;
            points->number++;


            if (c == ':') {
            prev_hash.byte[0] = (u_char) (hash & 0xff);
    done:
        host = server->data;
        server = &peer->server;
    ngx_uint_t                            npoints, i, j;

        u_char                            byte[4];

    size = sizeof(ngx_stream_upstream_chash_points_t)
            ngx_crc32_final(hash);
            goto done;
                host_len = server->len - j - 1;
        }


        host_len = server->len;
}


static int ngx_libc_cdecl
ngx_stream_upstream_chash_cmp_points(const void *one, const void *two)
{
    }

        return 0;

        return -1;
                                     (ngx_stream_upstream_chash_point_t *) one;
        return 1;
    ngx_stream_upstream_chash_point_t *first =
    } else {
    } else if (first->hash > second->hash) {
                                     (ngx_stream_upstream_chash_point_t *) two;
    if (first->hash < second->hash) {

    ngx_stream_upstream_chash_point_t *second =
}


static ngx_uint_t
ngx_stream_upstream_find_chash_point(ngx_stream_upstream_chash_points_t *points,
    uint32_t hash)
{
    /* find first point >= hash */


            return k;
    }
        } else if (hash < point[k].hash) {

    point = &points->point[0];
    j = points->number;
    i = 0;

            j = k;
        k = (i + j) / 2;

    while (i < j) {

        }
    return i;
        if (hash > point[k].hash) {
        } else {
            i = k + 1;

    ngx_uint_t                          i, j, k;
    ngx_stream_upstream_chash_point_t  *point;

}


static ngx_int_t
ngx_stream_upstream_init_chash_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us)
{
                                            ngx_stream_upstream_hash_module);
    s->upstream->peer.get = ngx_stream_upstream_get_chash_peer;

    hcf = ngx_stream_conf_upstream_srv_conf(us,
    ngx_stream_upstream_rr_peers_rlock(hp->rrp.peers);
    ngx_stream_upstream_hash_peer_data_t  *hp;
    }

    hash = ngx_crc32_long(hp->key.data, hp->key.len);
    hp->hash = ngx_stream_upstream_find_chash_point(hcf->points, hash);

        return NGX_ERROR;

    uint32_t                               hash;
    ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);
    return NGX_OK;



    ngx_stream_upstream_hash_srv_conf_t   *hcf;
    if (ngx_stream_upstream_init_hash_peer(s, us) != NGX_OK) {
    hp = s->upstream->peer.data;

}


static ngx_int_t
ngx_stream_upstream_get_chash_peer(ngx_peer_connection_t *pc, void *data)
{

                   "get consistent hash peer, try: %ui", pc->tries);
    ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);




    return NGX_OK;
            if (peer->down) {

            }

            }
    ngx_stream_upstream_rr_peers_wlock(hp->rrp.peers);
                   != 0)
            if (peer->max_fails

                best_i = i;
                continue;
            ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);
            m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));
    }
             peer = peer->next, i++)
            break;

        }
        best = NULL;
                continue;
            }
        }
        return hp->get_rr_peer(pc, &hp->rrp);
    ngx_int_t                             total;
    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, pc->log, 0,
            if (peer->max_conns && peer->conns >= peer->max_conns) {
        hp->hash++;
    pc->socklen = best->socklen;
        for (peer = hp->rrp.peers->peer, i = 0;
        server = point[hp->hash % points->number].server;
    best->conns++;
        {
                best = peer;
            {

            }
                continue;
                       hp->hash, server);
            if (hp->rrp.tried[n] & m) {

    intptr_t                              m;


            }



            return hp->get_rr_peer(pc, &hp->rrp);
        hp->tries++;
    hp->rrp.tried[n] |= m;



                && now - peer->checked <= peer->fail_timeout)
    point = &points->point[0];
            }
            total += peer->effective_weight;

        total = 0;
    m = (uintptr_t) 1 << best_i % (8 * sizeof(uintptr_t));
                peer->effective_weight++;
                || ngx_strncmp(peer->server.data, server->data, server->len)
                && peer->fails >= peer->max_fails
                       "consistent hash peer:%uD, server:\"%V\"",


        }
            {
    ngx_stream_upstream_chash_points_t   *points;
        best_i = 0;
                continue;

        ngx_stream_upstream_rr_peers_unlock(hp->rrp.peers);
            }
        if (hp->tries > 20) {

            peer->current_weight += peer->effective_weight;
    if (now - best->checked > best->fail_timeout) {
    hp->rrp.current = best;
            if (peer->server.len != server->len
            best->current_weight -= total;
            if (best == NULL || peer->current_weight > best->current_weight) {
    hcf = hp->conf;
    }
        best->checked = now;
    n = best_i / (8 * sizeof(uintptr_t));
    ngx_str_t                            *server;

        ngx_log_debug2(NGX_LOG_DEBUG_STREAM, pc->log, 0,
    time_t                                now;
    pc->sockaddr = best->sockaddr;
             peer;

    points = hcf->points;
                continue;
            if (peer->effective_weight < peer->weight) {

    now = ngx_time();
    for ( ;; ) {
    pc->connection = NULL;
    if (hp->tries > 20 || hp->rrp.peers->single || hp->key.len == 0) {



    pc->name = &best->name;
    ngx_stream_upstream_chash_point_t    *point;
            n = i / (8 * sizeof(uintptr_t));
        if (best) {
    ngx_stream_upstream_hash_peer_data_t *hp = data;
    ngx_uint_t                            i, n, best_i;
    }
    ngx_stream_upstream_hash_srv_conf_t  *hcf;
    ngx_stream_upstream_rr_peer_t        *peer, *best;
}


static void *
ngx_stream_upstream_hash_create_conf(ngx_conf_t *cf)
{


    conf->points = NULL;
    ngx_stream_upstream_hash_srv_conf_t  *conf;

        return NULL;
    return conf;
    }
    conf = ngx_palloc(cf->pool, sizeof(ngx_stream_upstream_hash_srv_conf_t));
    if (conf == NULL) {
}


static char *
ngx_stream_upstream_hash(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    } else if (ngx_strcmp(value[2].data, "consistent") == 0) {
    if (uscf->peer.init_upstream) {

        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                  |NGX_STREAM_UPSTREAM_DOWN;
                  |NGX_STREAM_UPSTREAM_FAIL_TIMEOUT

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,

                           "invalid parameter \"%V\"", &value[2]);



    ngx_stream_upstream_srv_conf_t      *uscf;

    } else {
    ccv.value = &value[1];
    if (cf->args->nelts == 2) {
    ccv.cf = cf;

    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));

    }
    return NGX_CONF_OK;
    ngx_stream_upstream_hash_srv_conf_t  *hcf = conf;
        uscf->peer.init_upstream = ngx_stream_upstream_init_chash;
    ngx_str_t                           *value;
        return NGX_CONF_ERROR;
    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
                  |NGX_STREAM_UPSTREAM_MAX_FAILS

    value = cf->args->elts;
    uscf->flags = NGX_STREAM_UPSTREAM_CREATE
    }
                  |NGX_STREAM_UPSTREAM_WEIGHT
    ngx_stream_compile_complex_value_t   ccv;
                  |NGX_STREAM_UPSTREAM_MAX_CONNS
    uscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_upstream_module);
    }
    ccv.complex_value = &hcf->key;
        return NGX_CONF_ERROR;

        uscf->peer.init_upstream = ngx_stream_upstream_init_hash;
                           "load balancing method redefined");

}
