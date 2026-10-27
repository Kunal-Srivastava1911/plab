    ngx_stream_variable_t        *v;
    ngx_stream_variable_value_t  *vv;
    ngx_stream_core_main_conf_t  *cmcf;

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    v = ngx_hash_find(&cmcf->variables_hash, key, name->data, name->len);

    if (v) {
        if (v->flags & NGX_STREAM_VAR_INDEXED) {
            return ngx_stream_get_flushed_variable(s, v->index);
        }

        if (ngx_stream_variable_depth == 0) {
            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                          "cycle while evaluating variable \"%V\"", name);
            return NULL;
        }

        ngx_stream_variable_depth--;

        vv = ngx_palloc(s->connection->pool,
                        sizeof(ngx_stream_variable_value_t));

        if (vv && v->get_handler(s, vv, v->data) == NGX_OK) {
            ngx_stream_variable_depth++;
            return vv;
        }

        ngx_stream_variable_depth++;
        return NULL;
    }
