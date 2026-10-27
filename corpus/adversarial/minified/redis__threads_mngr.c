#include "threads_mngr.h"
#define UNUSED(V)((void)V)
#ifdef __linux__
#include "atomicvar.h"
#include "server.h"
#include<signal.h>
#include<time.h>
#include<sys/syscall.h>
#define IN_PROGRESS 1
static const clock_t RUN_ON_THREADS_TIMEOUT=2;static run_on_thread_cb g_callback=NULL;static volatile size_t g_tids_len=0;static redisAtomic size_t g_num_threads_done=0;static redisAtomic int g_in_progress=0;static void invoke_callback(int sig);static int test_and_start(void);static void wait_threads(void);static void ThreadsManager_cleanups(void);void ThreadsManager_init(void){struct sigaction act;sigemptyset(&act.sa_mask);act.sa_flags=0;act.sa_handler=invoke_callback;sigaction(SIGUSR2,&act,NULL);}__attribute__((noinline))int ThreadsManager_runOnThreads(pid_t*tids,size_t tids_len,run_on_thread_cb callback){if(test_and_start()==IN_PROGRESS){return 0;}g_callback=callback;g_tids_len=tids_len;g_num_threads_done=0;pid_t pid=getpid();for(size_t i=0;i<tids_len;++i){syscall(SYS_tgkill,pid,tids[i],THREADS_SIGNAL);}wait_threads();ThreadsManager_cleanups();return 1;}static int test_and_start(void){int prev_state;atomicFlagGetSet(g_in_progress,prev_state);return prev_state;}__attribute__((noinline))static void invoke_callback(int sig){UNUSED(sig);run_on_thread_cb callback=g_callback;if(callback){callback();atomicIncr(g_num_threads_done,1);}else{serverLogFromHandler(LL_WARNING,"tid %ld: ThreadsManager g_callback is NULL",syscall(SYS_gettid));}}static void wait_threads(void){struct timespec timeout_time;clock_gettime(CLOCK_REALTIME,&timeout_time);timeout_time.tv_sec+=RUN_ON_THREADS_TIMEOUT;size_t curr_done_count;struct timespec curr_time;do{struct timeval tv={.tv_sec=0,.tv_usec=10};select(0,NULL,NULL,NULL,&tv);atomicGet(g_num_threads_done,curr_done_count);clock_gettime(CLOCK_REALTIME,&curr_time);}while(curr_done_count<g_tids_len&&curr_time.tv_sec<=timeout_time.tv_sec);if(curr_time.tv_sec>timeout_time.tv_sec){serverLogRawFromHandler(LL_WARNING,"wait_threads(): waiting threads timed out");}}static void ThreadsManager_cleanups(void){g_callback=NULL;g_tids_len=0;g_num_threads_done=0;atomicSet(g_in_progress,0);}
#else
void ThreadsManager_init(void){}int ThreadsManager_runOnThreads(pid_t*tids,size_t tids_len,run_on_thread_cb callback){UNUSED(tids);UNUSED(tids_len);UNUSED(callback);return 1;}
#endif

