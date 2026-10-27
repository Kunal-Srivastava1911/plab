ngx_stream_variable_not_found(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    v->not_found = 1;
    return NGX_OK;
}


ngx_stream_regex_t *
ngx_stream_regex_compile(ngx_conf_t *cf, ngx_regex_compile_t *rc)
{
    u_char                       *p;
    size_t                        size;
    ngx_str_t                     name;
    ngx_uint_t                    i, n;
    ngx_stream_variable_t        *v;
    ngx_stream_regex_t           *re;
    ngx_stream_regex_variable_t  *rv;
    ngx_stream_core_main_conf_t  *cmcf;

    rc->pool = cf->pool;

    if (ngx_regex_compile(rc) != NGX_OK) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "%V", &rc->err);
        return NULL;
    }

    re = ngx_pcalloc(cf->pool, sizeof(ngx_stream_regex_t));
    if (re == NULL) {
        return NULL;
    }

    re->regex = rc->regex;
    re->ncaptures = rc->captures;
    re->name = rc->pattern;

