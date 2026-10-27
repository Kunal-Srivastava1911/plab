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
