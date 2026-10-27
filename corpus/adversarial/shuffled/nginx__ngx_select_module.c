
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


static ngx_int_t ngx_select_init(ngx_cycle_t *cycle, ngx_msec_t timer);
static void ngx_select_done(ngx_cycle_t *cycle);
static ngx_int_t ngx_select_add_event(ngx_event_t *ev, ngx_int_t event,
    ngx_uint_t flags);
static ngx_int_t ngx_select_del_event(ngx_event_t *ev, ngx_int_t event,
    ngx_uint_t flags);
static ngx_int_t ngx_select_process_events(ngx_cycle_t *cycle, ngx_msec_t timer,
    ngx_uint_t flags);
static void ngx_select_repair_fd_sets(ngx_cycle_t *cycle);
static char *ngx_select_init_conf(ngx_cycle_t *cycle, void *conf);


static fd_set         master_read_fd_set;
static fd_set         master_write_fd_set;
static fd_set         work_read_fd_set;
static fd_set         work_write_fd_set;

static ngx_int_t      max_fd;
static ngx_uint_t     nevents;

static ngx_event_t  **event_index;


static ngx_str_t           select_name = ngx_string("select");

static ngx_event_module_t  ngx_select_module_ctx = {
    &select_name,
    NULL,                                  /* create configuration */
    ngx_select_init_conf,                  /* init configuration */

    {
        ngx_select_add_event,              /* add an event */
        ngx_select_del_event,              /* delete an event */
        ngx_select_add_event,              /* enable an event */
        ngx_select_del_event,              /* disable an event */
        NULL,                              /* add an connection */
        NULL,                              /* delete an connection */
        NULL,                              /* trigger a notify */
        ngx_select_process_events,         /* process the events */
        ngx_select_init,                   /* init the events */
        ngx_select_done                    /* done the events */
    }

};

ngx_module_t  ngx_select_module = {
    NGX_MODULE_V1,
    &ngx_select_module_ctx,                /* module context */
    NULL,                                  /* module directives */
    NGX_EVENT_MODULE,                      /* module type */
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
ngx_select_init(ngx_cycle_t *cycle, ngx_msec_t timer)
{
        }
    }
                          cycle->log);



    ngx_event_t  **index;

    return NGX_OK;
        FD_ZERO(&master_write_fd_set);
        event_index = index;

        if (index == NULL) {

        || cycle->old_cycle->connection_n < cycle->connection_n)
        FD_ZERO(&master_read_fd_set);
            ngx_free(event_index);
    ngx_event_actions = ngx_select_module_ctx.actions;
        nevents = 0;
    if (event_index == NULL) {
    ngx_event_flags = NGX_USE_LEVEL_EVENT;
    {
        }
        index = ngx_alloc(sizeof(ngx_event_t *) * 2 * cycle->connection_n,
    max_fd = -1;
            ngx_memcpy(index, event_index, sizeof(ngx_event_t *) * nevents);

        || cycle->old_cycle == NULL
    ngx_io = ngx_os_io;

            return NGX_ERROR;
    if (ngx_process >= NGX_PROCESS_WORKER

    }
        if (event_index) {
}


static void
ngx_select_done(ngx_cycle_t *cycle)
{

    ngx_free(event_index);
    event_index = NULL;
}


static ngx_int_t
ngx_select_add_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{

    {
    if (ev->index != NGX_INVALID_INDEX) {

    }
        ngx_log_error(NGX_LOG_ALERT, ev->log, 0,
    if (max_fd != -1 && max_fd < c->fd) {

    ev->index = nevents;
    if (event == NGX_READ_EVENT) {
        || (event == NGX_WRITE_EVENT && !ev->write))
        return NGX_OK;
    }
    c = ev->data;
        FD_SET(c->fd, &master_write_fd_set);
                      ev->write ? "write" : "read", c->fd, event);
    }
    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
    }


                      "select event fd:%d ev:%i is already set", c->fd, event);
                      "invalid select %s event fd:%d ev:%i",
                   "select add event fd:%d ev:%i", c->fd, event);
        max_fd = c->fd;

    if ((event == NGX_READ_EVENT && ev->write)
        FD_SET(c->fd, &master_read_fd_set);
    } else if (event == NGX_WRITE_EVENT) {
    return NGX_OK;
        return NGX_ERROR;
    event_index[nevents] = ev;

        ngx_log_error(NGX_LOG_ALERT, ev->log, 0,
    ev->active = 1;
    ngx_connection_t  *c;



    nevents++;
}


static ngx_int_t
ngx_select_del_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_connection_t  *c;
    if (max_fd == c->fd) {


        FD_CLR(c->fd, &master_read_fd_set);
        FD_CLR(c->fd, &master_write_fd_set);
    if (ev->index < --nevents) {
                   "select del event fd:%d ev:%i", c->fd, event);


    ev->active = 0;

        e->index = ev->index;
    }

    return NGX_OK;
    if (event == NGX_READ_EVENT) {

    }
    ngx_event_t       *e;
    if (ev->index == NGX_INVALID_INDEX) {
        e = event_index[nevents];

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,

        return NGX_OK;
    }
    ev->index = NGX_INVALID_INDEX;
        max_fd = -1;
    }

    c = ev->data;
        event_index[ev->index] = e;
    } else if (event == NGX_WRITE_EVENT) {
}


static ngx_int_t
ngx_select_process_events(ngx_cycle_t *cycle, ngx_msec_t timer,
    ngx_uint_t flags)
{
            nready++;
        }
                ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,

        tv.tv_usec = (long) ((timer % 1000) * 1000);


        tp = NULL;
        }

        found = 0;
                       "change max_fd: %i", max_fd);
        for (i = 0; i < nevents; i++) {
    if (ready != nready) {
        c = ev->data;
            }

    }

        ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
    }
    }
            if (ngx_event_timer_alarm) {
        } else {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
        if (err == NGX_EBADF) {

    for (i = 0; i < nevents; i++) {
    }
    } else {

    ready = select(max_fd + 1, &work_read_fd_set, &work_write_fd_set, NULL, tp);
    }

            }

        if (timer != NGX_TIMER_INFINITE) {
        ngx_log_error(level, cycle->log, err, "select() failed");
        if (err == NGX_EINTR) {
                               "select write %d", c->fd);
                      "select() returned no events without timeout");

    work_write_fd_set = master_write_fd_set;

            ngx_post_event(ev, queue);
        tp = &tv;
            queue = ev->accept ? &ngx_posted_accept_events
    if (max_fd == -1) {
    if (flags & NGX_UPDATE_TIME || ngx_event_timer_alarm) {
                           "select event: fd:%d wr:%d", c->fd, ev->write);
        for (i = 0; i < nevents; i++) {

    }
    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                found = 1;
                       "max_fd: %i", max_fd);
                   "select ready %d", ready);
        }
    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
#if (NGX_DEBUG)
            ev->ready = 1;
    ngx_connection_t  *c;
                ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
    if (cycle->log->log_level & NGX_LOG_DEBUG_ALL) {
    work_read_fd_set = master_read_fd_set;
            level = NGX_LOG_INFO;
        }

                max_fd = c->fd;
    ngx_err_t          err;

            ev->available = -1;
    err = (ready == -1) ? ngx_errno : 0;

    nready = 0;

            }
            if (max_fd < c->fd) {
            if (FD_ISSET(c->fd, &work_write_fd_set)) {
    ngx_event_t       *ev;
                               : &ngx_posted_events;
            level = NGX_LOG_ALERT;
        ngx_uint_t  level;
            c = ev->data;
    return NGX_OK;
        if (found) {
        tv.tv_sec = (long) (timer / 1000);

        ev = event_index[i];
            c = event_index[i]->data;
                return NGX_OK;
                      "select ready != events: %d:%d", ready, nready);
    struct timeval     tv, *tp;
                ngx_event_timer_alarm = 0;
        return NGX_ERROR;



    if (err) {
#endif
        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                found = 1;
        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
        }
        } else {
            ngx_log_debug2(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
    }

    ngx_uint_t         i, found;


        ngx_time_update();
    }

    ngx_queue_t       *queue;
    int                ready, nready;
            ngx_select_repair_fd_sets(cycle);

            if (FD_ISSET(c->fd, &work_read_fd_set)) {

                               "select read %d", c->fd);
                   "select timer: %M", timer);
        ngx_select_repair_fd_sets(cycle);
        }
        if (ev->write) {
        }
            return NGX_OK;

    if (ready == 0) {
        return NGX_ERROR;
    if (timer == NGX_TIMER_INFINITE) {
            ev = event_index[i];




            }

}


static void
ngx_select_repair_fd_sets(ngx_cycle_t *cycle)
{

    for (s = 0; s <= max_fd; s++) {



        if (getsockopt(s, SOL_SOCKET, SO_TYPE, &n, &len) == -1) {
        }
            ngx_log_error(NGX_LOG_ALERT, cycle->log, err,

                          "invalid descriptor #%d in write fd_set", s);
            FD_CLR(s, &master_read_fd_set);
    }
    int           n;


        }
            FD_CLR(s, &master_write_fd_set);
            continue;
        if (FD_ISSET(s, &master_read_fd_set) == 0) {
            err = ngx_socket_errno;
        }
    ngx_socket_t  s;
                          "invalid descriptor #%d in read fd_set", s);
        if (getsockopt(s, SOL_SOCKET, SO_TYPE, &n, &len) == -1) {

        }



    max_fd = -1;

            ngx_log_error(NGX_LOG_ALERT, cycle->log, err,
    ngx_err_t     err;
        len = sizeof(int);
        if (FD_ISSET(s, &master_write_fd_set) == 0) {
    }
    for (s = 0; s <= max_fd; s++) {
        len = sizeof(int);
            continue;
            err = ngx_socket_errno;
    socklen_t     len;

}


static char *
ngx_select_init_conf(ngx_cycle_t *cycle, void *conf)
{
        ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
    }

    if (cycle->connection_n > FD_SETSIZE) {
    }

    ecf = ngx_event_get_conf(cycle->conf_ctx, ngx_event_core_module);
        return NGX_CONF_OK;
                      "supported by select() is %ud", FD_SETSIZE);
        return NGX_CONF_ERROR;

                      "the maximum number of files "
    if (ecf->use != ngx_select_module.ctx_index) {

    ngx_event_conf_t  *ecf;
    return NGX_CONF_OK;
    /* disable warning: the default FD_SETSIZE is 1024U in FreeBSD 5.x */

}
