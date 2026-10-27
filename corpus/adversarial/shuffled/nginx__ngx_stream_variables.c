
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>
#include <nginx.h>

static ngx_stream_variable_t *ngx_stream_add_prefix_variable(ngx_conf_t *cf,
    ngx_str_t *name, ngx_uint_t flags);

static ngx_int_t ngx_stream_variable_binary_remote_addr(
    ngx_stream_session_t *s, ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_remote_addr(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_remote_port(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_proxy_protocol_addr(
    ngx_stream_session_t *s, ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_proxy_protocol_port(
    ngx_stream_session_t *s, ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_proxy_protocol_tlv(
    ngx_stream_session_t *s, ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_server_addr(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_server_port(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_server_name(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_bytes(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_session_time(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_status(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_connection(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);

static ngx_int_t ngx_stream_variable_nginx_version(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_hostname(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_pid(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_msec(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_time_iso8601(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_time_local(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);
static ngx_int_t ngx_stream_variable_protocol(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data);


static ngx_stream_variable_t  ngx_stream_core_variables[] = {

    { ngx_string("binary_remote_addr"), NULL,
      ngx_stream_variable_binary_remote_addr, 0, 0, 0 },

    { ngx_string("remote_addr"), NULL,
      ngx_stream_variable_remote_addr, 0, 0, 0 },

    { ngx_string("remote_port"), NULL,
      ngx_stream_variable_remote_port, 0, 0, 0 },

    { ngx_string("proxy_protocol_addr"), NULL,
      ngx_stream_variable_proxy_protocol_addr,
      offsetof(ngx_proxy_protocol_t, src_addr), 0, 0 },

    { ngx_string("proxy_protocol_port"), NULL,
      ngx_stream_variable_proxy_protocol_port,
      offsetof(ngx_proxy_protocol_t, src_port), 0, 0 },

    { ngx_string("proxy_protocol_server_addr"), NULL,
      ngx_stream_variable_proxy_protocol_addr,
      offsetof(ngx_proxy_protocol_t, dst_addr), 0, 0 },

    { ngx_string("proxy_protocol_server_port"), NULL,
      ngx_stream_variable_proxy_protocol_port,
      offsetof(ngx_proxy_protocol_t, dst_port), 0, 0 },

    { ngx_string("proxy_protocol_tlv_"), NULL,
      ngx_stream_variable_proxy_protocol_tlv,
      0, NGX_STREAM_VAR_PREFIX, 0 },

    { ngx_string("server_addr"), NULL,
      ngx_stream_variable_server_addr, 0, 0, 0 },

    { ngx_string("server_port"), NULL,
      ngx_stream_variable_server_port, 0, 0, 0 },

    { ngx_string("server_name"), NULL, ngx_stream_variable_server_name,
      0, 0, 0 },

    { ngx_string("bytes_sent"), NULL, ngx_stream_variable_bytes,
      0, 0, 0 },

    { ngx_string("bytes_received"), NULL, ngx_stream_variable_bytes,
      1, 0, 0 },

    { ngx_string("session_time"), NULL, ngx_stream_variable_session_time,
      0, NGX_STREAM_VAR_NOCACHEABLE, 0 },

    { ngx_string("status"), NULL, ngx_stream_variable_status,
      0, NGX_STREAM_VAR_NOCACHEABLE, 0 },

    { ngx_string("connection"), NULL,
      ngx_stream_variable_connection, 0, 0, 0 },

    { ngx_string("nginx_version"), NULL, ngx_stream_variable_nginx_version,
      0, 0, 0 },

    { ngx_string("hostname"), NULL, ngx_stream_variable_hostname,
      0, 0, 0 },

    { ngx_string("pid"), NULL, ngx_stream_variable_pid,
      0, 0, 0 },

    { ngx_string("msec"), NULL, ngx_stream_variable_msec,
      0, NGX_STREAM_VAR_NOCACHEABLE, 0 },

    { ngx_string("time_iso8601"), NULL, ngx_stream_variable_time_iso8601,
      0, NGX_STREAM_VAR_NOCACHEABLE, 0 },

    { ngx_string("time_local"), NULL, ngx_stream_variable_time_local,
      0, NGX_STREAM_VAR_NOCACHEABLE, 0 },

    { ngx_string("protocol"), NULL,
      ngx_stream_variable_protocol, 0, 0, 0 },

      ngx_stream_null_variable
};


ngx_stream_variable_value_t  ngx_stream_variable_null_value =
    ngx_stream_variable("");
ngx_stream_variable_value_t  ngx_stream_variable_true_value =
    ngx_stream_variable("1");


static ngx_uint_t  ngx_stream_variable_depth = 100;


ngx_stream_variable_t *
ngx_stream_add_variable(ngx_conf_t *cf, ngx_str_t *name, ngx_uint_t flags)
{
    ngx_hash_key_t               *key;

    ngx_strlow(v->name.data, name->data, name->len);
    v->name.data = ngx_pnalloc(cf->pool, name->len);
    rc = ngx_hash_add_key(cmcf->variables_keys, &v->name, v, 0);
        if (!(flags & NGX_STREAM_VAR_WEAK)) {
    v->index = 0;
    v->data = 0;


        if (name->len != key[i].key.len

                           "invalid variable name \"$\"");
    if (name->len == 0) {
        return NULL;
    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);
    }
            continue;

    }
        {

    v->get_handler = NULL;

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
            || ngx_strncasecmp(name->data, key[i].key.data, name->len) != 0)
    ngx_stream_variable_t        *v;
    }
    v->flags = flags;
                           "conflicting variable name \"%V\"", name);


        if (!(v->flags & NGX_STREAM_VAR_CHANGEABLE)) {
    if (flags & NGX_STREAM_VAR_PREFIX) {

    ngx_uint_t                    i;
        }
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
    }
        v = key[i].value;
        return NULL;
    return v;
    }
    }

        return NULL;
                               "the duplicate \"%V\" variable", name);
            return NULL;
    v->set_handler = NULL;
    if (rc == NGX_BUSY) {
        }
        return NULL;

    v = ngx_palloc(cf->pool, sizeof(ngx_stream_variable_t));
    key = cmcf->variables_keys->keys.elts;
            v->flags &= ~NGX_STREAM_VAR_WEAK;
    }
        return v;
    for (i = 0; i < cmcf->variables_keys->keys.nelts; i++) {
        return NULL;

        return ngx_stream_add_prefix_variable(cf, name, flags);
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
    if (v->name.data == NULL) {
    v->name.len = name->len;

    ngx_stream_core_main_conf_t  *cmcf;

        }
    ngx_int_t                     rc;

    if (v == NULL) {
    if (rc == NGX_ERROR) {
}


static ngx_stream_variable_t *
ngx_stream_add_prefix_variable(ngx_conf_t *cf, ngx_str_t *name,
    ngx_uint_t flags)
{
    v->name.data = ngx_pnalloc(cf->pool, name->len);

        return NULL;
    return v;
    ngx_strlow(v->name.data, name->data, name->len);
        }

    v->data = 0;
    v = cmcf->prefix_variables.elts;
    ngx_uint_t                    i;


    }
    }
            return NULL;

        return v;

    v->flags = flags;
        v = &v[i];
                               "the duplicate \"%V\" variable", name);

    if (v->name.data == NULL) {

    v->set_handler = NULL;
        }
        if (!(v->flags & NGX_STREAM_VAR_CHANGEABLE)) {
    v->index = 0;


            v->flags &= ~NGX_STREAM_VAR_WEAK;
        {

    v->get_handler = NULL;
            || ngx_strncasecmp(name->data, v[i].name.data, name->len) != 0)
    v = ngx_array_push(&cmcf->prefix_variables);
            continue;
        if (name->len != v[i].name.len
        }
    v->name.len = name->len;
        if (!(flags & NGX_STREAM_VAR_WEAK)) {
    for (i = 0; i < cmcf->prefix_variables.nelts; i++) {
        return NULL;
    ngx_stream_variable_t        *v;
    }
    ngx_stream_core_main_conf_t  *cmcf;
    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);
    if (v == NULL) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
}


ngx_int_t
ngx_stream_get_variable_index(ngx_conf_t *cf, ngx_str_t *name)
{
    v->data = 0;
        if (ngx_array_init(&cmcf->variables, cf->pool, 4,
    v->set_handler = NULL;
    } else {
            {
            return NGX_ERROR;
    v->name.len = name->len;
    v->get_handler = NULL;
        {
    v->index = cmcf->variables.nelts - 1;

    if (v == NULL) {
        }
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);
            return i;
        return NGX_ERROR;
    ngx_stream_core_main_conf_t  *cmcf;
            if (name->len != v[i].name.len
                || ngx_strncasecmp(name->data, v[i].name.data, name->len) != 0)
        for (i = 0; i < cmcf->variables.nelts; i++) {
    ngx_uint_t                    i;
            != NGX_OK)
    if (name->len == 0) {
            }
    ngx_strlow(v->name.data, name->data, name->len);
    ngx_stream_variable_t        *v;

    v = cmcf->variables.elts;

    v->flags = 0;
                           "invalid variable name \"$\"");

        return NGX_ERROR;
    return v->index;
    if (v == NULL) {


    v = ngx_array_push(&cmcf->variables);
    }



    }
    }
    if (v->name.data == NULL) {
    v->name.data = ngx_pnalloc(cf->pool, name->len);
    }
                continue;
                           sizeof(ngx_stream_variable_t))
        }


        return NGX_ERROR;
}


ngx_stream_variable_value_t *
ngx_stream_get_indexed_variable(ngx_stream_session_t *s, ngx_uint_t index)
{
    if (ngx_stream_variable_depth == 0) {

    }
    }

    ngx_stream_variable_t        *v;


        return &s->variables[index];

    if (s->variables[index].not_found || s->variables[index].valid) {
                      "unknown variable index: %ui", index);
    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);
    s->variables[index].not_found = 1;
            s->variables[index].no_cacheable = 1;
        ngx_log_error(NGX_LOG_ALERT, s->connection->log, 0,
        return NULL;


                      &v[index].name);
    if (cmcf->variables.nelts <= index) {
    ngx_stream_variable_depth--;
        if (v[index].flags & NGX_STREAM_VAR_NOCACHEABLE) {
    s->variables[index].valid = 0;
    {
                      "cycle while evaluating variable \"%V\"",

    }
    ngx_stream_variable_depth++;

        ngx_stream_variable_depth++;
        return &s->variables[index];
        return NULL;
    return NULL;
    if (v[index].get_handler(s, &s->variables[index], v[index].data)
    }
        == NGX_OK)
        }



        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
    ngx_stream_core_main_conf_t  *cmcf;
    v = cmcf->variables.elts;
}


ngx_stream_variable_value_t *
ngx_stream_get_flushed_variable(ngx_stream_session_t *s, ngx_uint_t index)
{
    v = &s->variables[index];

        if (!v->no_cacheable) {
            return v;
    ngx_stream_variable_value_t  *v;

        v->valid = 0;
        v->not_found = 0;


    return ngx_stream_get_indexed_variable(s, index);
    if (v->valid || v->not_found) {
    }
        }
}


ngx_stream_variable_value_t *
ngx_stream_get_variable(ngx_stream_session_t *s, ngx_str_t *name,
    ngx_uint_t key)
{

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);
    }

            return ngx_stream_get_flushed_variable(s, v->index);
        return NULL;
    }

        ngx_stream_variable_depth++;


            return vv;

    size_t                        len;

        return NULL;
    v = ngx_hash_find(&cmcf->variables_hash, key, name->data, name->len);

        }

    return vv;

            n = i;
    }
        }

            return vv;
    vv = ngx_palloc(s->connection->pool, sizeof(ngx_stream_variable_value_t));
    ngx_stream_variable_t        *v;

    ngx_uint_t                    i, n;
        }
    ngx_stream_core_main_conf_t  *cmcf;
        return NULL;
        if (v[n].get_handler(s, vv, (uintptr_t) name) == NGX_OK) {


            len = v[i].name.len;
    vv->not_found = 1;
        }
        ngx_stream_variable_depth--;
            return NULL;
        if (vv && v->get_handler(s, vv, v->data) == NGX_OK) {
    if (v) {
    n = cmcf->prefix_variables.nelts;
                          "cycle while evaluating variable \"%V\"", name);
        if (name->len >= v[i].name.len && name->len > len
    ngx_stream_variable_value_t  *vv;
            && ngx_strncmp(name->data, v[i].name.data, v[i].name.len) == 0)
        if (ngx_stream_variable_depth == 0) {
            ngx_stream_variable_depth++;

        if (v->flags & NGX_STREAM_VAR_INDEXED) {
    if (n != cmcf->prefix_variables.nelts) {
    if (vv == NULL) {
        }
            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
    v = cmcf->prefix_variables.elts;
                        sizeof(ngx_stream_variable_value_t));
        {
        vv = ngx_palloc(s->connection->pool,
    len = 0;
    }

    for (i = 0; i < cmcf->prefix_variables.nelts; i++) {
}


static ngx_int_t
ngx_stream_variable_binary_remote_addr(ngx_stream_session_t *s,
     ngx_stream_variable_value_t *v, uintptr_t data)
{
    return NGX_OK;
        v->data = (u_char *) &sin->sin_addr;
        break;
#endif
        v->valid = 1;

    default: /* AF_INET */

        v->len = sizeof(in_addr_t);
#if (NGX_HAVE_INET6)

        v->not_found = 0;
        break;

        v->not_found = 0;
        v->no_cacheable = 0;
        sin6 = (struct sockaddr_in6 *) s->connection->sockaddr;


        break;
#endif

    switch (s->connection->sockaddr->sa_family) {
        v->not_found = 0;

        v->no_cacheable = 0;
        v->valid = 1;
        v->valid = 1;
    case AF_UNIX:
#if (NGX_HAVE_INET6)


    struct sockaddr_in   *sin;
        v->len = s->connection->addr_text.len;
        sin = (struct sockaddr_in *) s->connection->sockaddr;
        v->data = s->connection->addr_text.data;
    }

#if (NGX_HAVE_UNIX_DOMAIN)
    case AF_INET6:
        v->data = sin6->sin6_addr.s6_addr;
#endif
    struct sockaddr_in6  *sin6;
        v->no_cacheable = 0;
        v->len = sizeof(struct in6_addr);
}


static ngx_int_t
ngx_stream_variable_remote_addr(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->no_cacheable = 0;
    return NGX_OK;

    v->valid = 1;
    v->len = s->connection->addr_text.len;
    v->data = s->connection->addr_text.data;
    v->not_found = 0;
}


static ngx_int_t
ngx_stream_variable_remote_port(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_uint_t  port;
    v->valid = 1;
    v->len = 0;
    }
    port = ngx_inet_get_port(s->connection->sockaddr);
    }
    v->no_cacheable = 0;
        return NGX_ERROR;


    if (v->data == NULL) {


    v->not_found = 0;
    return NGX_OK;
    v->data = ngx_pnalloc(s->connection->pool, sizeof("65535") - 1);
        v->len = ngx_sprintf(v->data, "%ui", port) - v->data;

    if (port > 0 && port < 65536) {
}


static ngx_int_t
ngx_stream_variable_proxy_protocol_addr(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_str_t             *addr;
    pp = s->connection->proxy_protocol;
    v->len = addr->len;
    if (pp == NULL) {


        v->not_found = 1;
        return NGX_OK;
    v->valid = 1;
    return NGX_OK;
    v->data = addr->data;
    addr = (ngx_str_t *) ((char *) pp + data);
    ngx_proxy_protocol_t  *pp;

    v->no_cacheable = 0;

    }
    v->not_found = 0;
}


static ngx_int_t
ngx_stream_variable_proxy_protocol_port(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->no_cacheable = 0;
    }
    v->not_found = 0;

    pp = s->connection->proxy_protocol;

    return NGX_OK;
        v->not_found = 1;
    port = *(in_port_t *) ((char *) pp + data);
    v->data = ngx_pnalloc(s->connection->pool, sizeof("65535") - 1);
    ngx_proxy_protocol_t  *pp;

    }
    }
    if (v->data == NULL) {
        v->len = ngx_sprintf(v->data, "%ui", port) - v->data;
    v->len = 0;
    v->valid = 1;
    if (pp == NULL) {


        return NGX_ERROR;
    ngx_uint_t             port;
        return NGX_OK;

    if (port > 0 && port < 65536) {
}


static ngx_int_t
ngx_stream_variable_proxy_protocol_tlv(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{

    tlv.len = name->len - (sizeof("proxy_protocol_tlv_") - 1);
        return NGX_OK;
    tlv.data = name->data + sizeof("proxy_protocol_tlv_") - 1;
    ngx_str_t *name = (ngx_str_t *) data;


    if (rc == NGX_ERROR) {
    return NGX_OK;
    v->len = value.len;

    }
    v->data = value.data;
    v->not_found = 0;


    rc = ngx_proxy_protocol_get_tlv(s->connection, &tlv, &value);
    v->no_cacheable = 0;
    ngx_int_t  rc;
    ngx_str_t  tlv, value;
    }
        return NGX_ERROR;
    if (rc == NGX_DECLINED) {
        v->not_found = 1;
    v->valid = 1;

}


static ngx_int_t
ngx_stream_variable_server_addr(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{

    if (ngx_connection_local_sockaddr(s->connection, &str, 0) != NGX_OK) {
    u_char     addr[NGX_SOCKADDR_STRLEN];


    if (str.data == NULL) {
    ngx_memcpy(str.data, addr, str.len);
    return NGX_OK;
    v->no_cacheable = 0;
    str.data = addr;
    v->valid = 1;
    str.len = NGX_SOCKADDR_STRLEN;
    v->len = str.len;
    v->not_found = 0;
    ngx_str_t  str;


        return NGX_ERROR;
    v->data = str.data;
    }

        return NGX_ERROR;
    str.data = ngx_pnalloc(s->connection->pool, str.len);
    }
}


static ngx_int_t
ngx_stream_variable_server_port(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->valid = 1;
    v->data = ngx_pnalloc(s->connection->pool, sizeof("65535") - 1);
    if (ngx_connection_local_sockaddr(s->connection, NULL, 0) != NGX_OK) {
        return NGX_ERROR;
    v->not_found = 0;
    }
    if (port > 0 && port < 65536) {

    }
        v->len = ngx_sprintf(v->data, "%ui", port) - v->data;

    }
    v->no_cacheable = 0;
        return NGX_ERROR;
    ngx_uint_t  port;
    if (v->data == NULL) {
    v->len = 0;

    return NGX_OK;


    port = ngx_inet_get_port(s->connection->local_sockaddr);

}


static ngx_int_t
ngx_stream_variable_server_name(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->len = cscf->server_name.len;
    v->no_cacheable = 0;
    v->not_found = 0;
    cscf = ngx_stream_get_module_srv_conf(s, ngx_stream_core_module);
    return NGX_OK;


    ngx_stream_core_srv_conf_t  *cscf;

    v->data = cscf->server_name.data;
    v->valid = 1;
}


static ngx_int_t
ngx_stream_variable_bytes(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    p = ngx_pnalloc(s->connection->pool, NGX_OFF_T_LEN);
        v->len = ngx_sprintf(p, "%O", s->received) - p;


    u_char  *p;
    } else {
    if (p == NULL) {
    v->not_found = 0;
    }
        v->len = ngx_sprintf(p, "%O", s->connection->sent) - p;
    }
    v->valid = 1;
    v->no_cacheable = 0;
        return NGX_ERROR;

    return NGX_OK;


    if (data == 1) {
    v->data = p;
}


static ngx_int_t
ngx_stream_variable_session_time(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ms = ngx_max(ms, 0);
             ((tp->sec - s->start_sec) * 1000 + (tp->msec - s->start_msec));
    ngx_msec_int_t   ms;
    ms = (ngx_msec_int_t)

    v->data = p;
    v->no_cacheable = 0;
    }

    tp = ngx_timeofday();

    v->not_found = 0;
    v->valid = 1;
    p = ngx_pnalloc(s->connection->pool, NGX_TIME_T_LEN + 4);
    if (p == NULL) {

    u_char          *p;
    return NGX_OK;
    ngx_time_t      *tp;
        return NGX_ERROR;
    v->len = ngx_sprintf(p, "%T.%03M", (time_t) ms / 1000, ms % 1000) - p;

}


static ngx_int_t
ngx_stream_variable_status(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{

    v->not_found = 0;
    }
        return NGX_ERROR;
    v->data = ngx_pnalloc(s->connection->pool, NGX_INT_T_LEN);
    return NGX_OK;

    v->no_cacheable = 0;
    v->valid = 1;
    if (v->data == NULL) {
    v->len = ngx_sprintf(v->data, "%03ui", s->status) - v->data;
}


static ngx_int_t
ngx_stream_variable_connection(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->valid = 1;
    p = ngx_pnalloc(s->connection->pool, NGX_ATOMIC_T_LEN);
    v->len = ngx_sprintf(p, "%uA", s->connection->number) - p;
    v->no_cacheable = 0;
    v->data = p;
    }

    return NGX_OK;


    v->not_found = 0;
    if (p == NULL) {
    u_char  *p;
        return NGX_ERROR;
}


static ngx_int_t
ngx_stream_variable_nginx_version(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{

    return NGX_OK;
    v->not_found = 0;
    v->len = sizeof(NGINX_VERSION) - 1;
    v->data = (u_char *) NGINX_VERSION;
    v->no_cacheable = 0;
    v->valid = 1;
}


static ngx_int_t
ngx_stream_variable_hostname(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{

    v->valid = 1;
    v->no_cacheable = 0;
    return NGX_OK;
    v->not_found = 0;
    v->len = ngx_cycle->hostname.len;
    v->data = ngx_cycle->hostname.data;
}


static ngx_int_t
ngx_stream_variable_pid(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->data = p;
    u_char  *p;
    if (p == NULL) {

    }
    v->not_found = 0;
    v->len = ngx_sprintf(p, "%P", ngx_pid) - p;
        return NGX_ERROR;
    return NGX_OK;
    v->no_cacheable = 0;

    p = ngx_pnalloc(s->connection->pool, NGX_INT64_LEN);
    v->valid = 1;

}


static ngx_int_t
ngx_stream_variable_msec(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    if (p == NULL) {
    tp = ngx_timeofday();
    v->valid = 1;
    v->len = ngx_sprintf(p, "%T.%03M", tp->sec, tp->msec) - p;

    v->not_found = 0;

    v->data = p;
    u_char      *p;

    ngx_time_t  *tp;
    }
        return NGX_ERROR;
    p = ngx_pnalloc(s->connection->pool, NGX_TIME_T_LEN + 4);
    return NGX_OK;

    v->no_cacheable = 0;
}


static ngx_int_t
ngx_stream_variable_time_iso8601(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
               ngx_cached_http_log_iso8601.len);

    v->data = p;
    p = ngx_pnalloc(s->connection->pool, ngx_cached_http_log_iso8601.len);
    }
    v->valid = 1;
    v->not_found = 0;
    v->len = ngx_cached_http_log_iso8601.len;

    v->no_cacheable = 0;

    ngx_memcpy(p, ngx_cached_http_log_iso8601.data,

    if (p == NULL) {
    u_char  *p;
        return NGX_ERROR;
    return NGX_OK;
}


static ngx_int_t
ngx_stream_variable_time_local(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->valid = 1;

    u_char  *p;
    v->not_found = 0;
    v->no_cacheable = 0;
    p = ngx_pnalloc(s->connection->pool, ngx_cached_http_log_time.len);
    if (p == NULL) {
    ngx_memcpy(p, ngx_cached_http_log_time.data, ngx_cached_http_log_time.len);

    v->len = ngx_cached_http_log_time.len;
    return NGX_OK;
    }

    v->data = p;
        return NGX_ERROR;

}


static ngx_int_t
ngx_stream_variable_protocol(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->data = (u_char *) (s->connection->type == SOCK_DGRAM ? "UDP" : "TCP");
    v->len = 3;

    v->no_cacheable = 0;
    v->not_found = 0;
    v->valid = 1;
    return NGX_OK;
}


void *
ngx_stream_map_find(ngx_stream_session_t *s, ngx_stream_map_t *map,
    ngx_str_t *match)
{
    key = ngx_hash_strlow(low, match->data, len);
            return NULL;
    if (len) {
                continue;
    } else {
        low = ngx_pnalloc(s->connection->pool, len);
#endif
    len = match->len;
    ngx_uint_t   key;
    if (len && map->nregex) {
        ngx_stream_map_regex_t  *reg;
    }
        }
    if (value) {

        ngx_uint_t               i;
    return NULL;




            if (n == NGX_OK) {
    value = ngx_hash_find_combined(&map->hash, key, low, len);


    }
            n = ngx_stream_regex_exec(s, reg[i].regex, match);

            return NULL;
    }
        }
            }
            if (n == NGX_DECLINED) {

    void        *value;

        low = NULL;
        return value;




            }

            /* NGX_ERROR */
        if (low == NULL) {
        reg = map->regex;
    u_char      *low;
                return reg[i].value;
#if (NGX_PCRE)
        for (i = 0; i < map->nregex; i++) {
    size_t       len;

        ngx_int_t                n;
}


#if (NGX_PCRE)

static ngx_int_t
ngx_stream_variable_not_found(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->not_found = 1;
    return NGX_OK;
}


ngx_stream_regex_t *
ngx_stream_regex_compile(ngx_conf_t *cf, ngx_regex_compile_t *rc)
{
        rv[i].index = ngx_stream_get_variable_index(cf, &name);

    }

    if (ngx_regex_compile(rc) != NGX_OK) {


    re->ncaptures = rc->captures;
        }
            return NULL;
        v->get_handler = ngx_stream_variable_not_found;
            return NULL;
        return NULL;
        name.len = ngx_strlen(name.data);
        return NULL;
    size_t                        size;
    ngx_uint_t                    i, n;
    rc->pool = cf->pool;
        if (rv[i].index == NGX_ERROR) {
    re = ngx_pcalloc(cf->pool, sizeof(ngx_stream_regex_t));

    }
    ngx_stream_core_main_conf_t  *cmcf;
    if (re == NULL) {
    ngx_stream_regex_t           *re;
    u_char                       *p;
        if (v == NULL) {
    cmcf->ncaptures = ngx_max(cmcf->ncaptures, re->ncaptures);
    }
        name.data = &p[2];
        p += size;

    n = (ngx_uint_t) rc->named_captures;

    re->nvariables = n;
    ngx_str_t                     name;
        }

        v = ngx_stream_add_variable(cf, &name, NGX_STREAM_VAR_CHANGEABLE);
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "%V", &rc->err);


    }
    if (rv == NULL) {
    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);
    ngx_stream_variable_t        *v;




    re->variables = rv;
    p = rc->names;
        return NULL;

    return re;
    }
    rv = ngx_palloc(rc->pool, n * sizeof(ngx_stream_regex_variable_t));
    re->name = rc->pattern;
    re->regex = rc->regex;

        return re;
    ngx_stream_regex_variable_t  *rv;
        rv[i].capture = 2 * ((p[0] << 8) + p[1]);
    if (n == 0) {
    size = rc->name_size;

    for (i = 0; i < n; i++) {
}


ngx_int_t
ngx_stream_regex_exec(ngx_stream_session_t *s, ngx_stream_regex_t *re,
    ngx_str_t *str)
{
                return NGX_ERROR;
        v = cmcf->variables.elts;
#endif
    ngx_int_t                     rc, index;
            }
        vv = &s->variables[index];
        index = re->variables[i].index;
    } else {
    s->captures_data = str->data;

        vv->not_found = 0;
        return NGX_DECLINED;

        vv->no_cacheable = 0;

        }

    s->ncaptures = rc * 2;
    ngx_stream_variable_value_t  *vv;
                       "stream regex set $%V to \"%v\"", &v[index].name, vv);
    }


            if (s->captures == NULL) {

    if (rc < 0) {
        len = cmcf->ncaptures;
        ngx_stream_variable_t  *v;
                      rc, str, &re->name);

    }
    return NGX_OK;
        len = 0;
    ngx_stream_core_main_conf_t  *cmcf;

#if (NGX_DEBUG)
        vv->valid = 1;
        if (s->captures == NULL) {
        ngx_log_debug2(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,

        }
    ngx_uint_t                    i, n, len;


    if (rc == NGX_REGEX_NO_MATCHED) {

        n = re->variables[i].capture;

        ngx_log_error(NGX_LOG_ALERT, s->connection->log, 0,
            s->captures = ngx_palloc(s->connection->pool, len * sizeof(int));
        return NGX_ERROR;
    if (re->ncaptures) {
    for (i = 0; i < re->nvariables; i++) {
    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);
        {
    }

        vv->data = &str->data[s->captures[n]];
        vv->len = s->captures[n + 1] - s->captures[n];
    rc = ngx_regex_exec(re->regex, str, s->captures, len);
    }
                      ngx_regex_exec_n " failed: %i on \"%V\" using \"%V\"",
}

#endif


ngx_int_t
ngx_stream_variables_add_core_vars(ngx_conf_t *cf)
{
        != NGX_OK)
    return NGX_OK;
    if (ngx_array_init(&cmcf->prefix_variables, cf->pool, 8,

    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);

    ngx_stream_variable_t        *cv, *v;
    cmcf->variables_keys->temp_pool = cf->pool;
    }
        if (v == NULL) {
                       sizeof(ngx_stream_variable_t))
    if (cmcf->variables_keys == NULL) {

        != NGX_OK)
    cmcf->variables_keys = ngx_pcalloc(cf->temp_pool,
        return NGX_ERROR;
                                       sizeof(ngx_hash_keys_arrays_t));
        return NGX_ERROR;


        }
    }
    if (ngx_hash_keys_array_init(cmcf->variables_keys, NGX_HASH_SMALL)
        *v = *cv;

    {
        return NGX_ERROR;
    for (cv = ngx_stream_core_variables; cv->name.len; cv++) {
    ngx_stream_core_main_conf_t  *cmcf;


    }
    {
    }
    cmcf->variables_keys->pool = cf->pool;
            return NGX_ERROR;
        v = ngx_stream_add_variable(cf, &cv->name, cv->flags);
}


ngx_int_t
ngx_stream_variables_init_vars(ngx_conf_t *cf)
{
    hash.name = "variables_hash";
    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);
    {
        len = 0;
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
        if (av->flags & NGX_STREAM_VAR_NOHASH) {

    size_t                        len;
    key = cmcf->variables_keys->keys.elts;

            if (v[i].name.len >= pv[n].name.len && v[i].name.len > len
        }
    ngx_hash_init_t               hash;
        av = key[n].value;

                len = pv[n].name.len;
        if (av) {
                    break;
    ngx_hash_key_t               *key;
                    || (av->flags & NGX_STREAM_VAR_WEAK))

            {
        for (n = 0; n < cmcf->prefix_variables.nelts; n++) {
    }

            return NGX_ERROR;
                      cmcf->variables_keys->keys.nelts)
                          "unknown \"%V\" variable", &v[i].name);
                && ngx_strncmp(v[i].name.data, pv[n].name.data, pv[n].name.len)

    for (n = 0; n < cmcf->variables_keys->keys.nelts; n++) {




            }
            key[n].key.data = NULL;
                   == 0)
            if (v[i].name.len == key[n].key.len
    /* set the handlers for the indexed stream variables */
    ngx_stream_variable_t        *v, *av, *pv;
        return NGX_ERROR;
        != NGX_OK)


    if (ngx_hash_init(&hash, cmcf->variables_keys->keys.elts,



                   == 0)
    v = cmcf->variables.elts;
                if (av->get_handler == NULL
    next:
                && ngx_strncmp(v[i].name.data, key[n].key.data, v[i].name.len)
                v[i].data = av->data;

    ngx_uint_t                    i, n;
                }
                v[i].flags = av->flags;
        if (v[i].get_handler == NULL) {
            {



                av->index = i;

        }
        continue;
            av = key[n].value;
    hash.temp_pool = NULL;
                goto next;
                av->flags |= NGX_STREAM_VAR_INDEXED;
    return NGX_OK;
        }

        av = NULL;
    hash.max_size = cmcf->variables_hash_max_size;
    for (i = 0; i < cmcf->variables.nelts; i++) {
            }
    hash.pool = cf->pool;
    ngx_stream_core_main_conf_t  *cmcf;
    cmcf->variables_keys = NULL;
            v[i].data = (uintptr_t) &v[i].name;
        for (n = 0; n < cmcf->variables_keys->keys.nelts; n++) {
    hash.hash = &cmcf->variables_hash;
            v[i].get_handler = av->get_handler;
         }

    hash.bucket_size = cmcf->variables_hash_bucket_size;

    }

                v[i].get_handler = av->get_handler;
    hash.key = ngx_hash_key;
                {
            v[i].flags = av->flags;
            goto next;
    }
                av = &pv[n];

        }
    pv = cmcf->prefix_variables.elts;
}
