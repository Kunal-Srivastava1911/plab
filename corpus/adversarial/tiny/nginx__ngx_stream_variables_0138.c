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

