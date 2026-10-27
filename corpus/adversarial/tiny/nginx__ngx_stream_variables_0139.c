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
