  "static_open", "static_prng", "static_lru",    "static_pmem",
  "static_app1", "static_app2", "static_app3",   "static_vfs1",
  "static_vfs2", "static_vfs3", 0
};

/* A countable mutex */
struct sqlite3_mutex {
  sqlite3_mutex *pReal;
  int eType;
};

/* State variables */
static struct test_mutex_globals {
  int isInstalled;           /* True if installed */
  int disableInit;           /* True to cause sqlite3_initialize() to fail */
  int disableTry;            /* True to force sqlite3_mutex_try() to fail */
  int isInit;                /* True if initialized */
  sqlite3_mutex_methods m;   /* Interface to "real" mutex system */
  int aCounter[MAX_MUTEXES]; /* Number of grabs of each type of mutex */
  sqlite3_mutex aStatic[STATIC_MUTEXES]; /* The static mutexes */
} g = {0};

/* Return true if the countable mutex is currently held */
static int counterMutexHeld(sqlite3_mutex *p){
  return g.m.xMutexHeld(p->pReal);
}

