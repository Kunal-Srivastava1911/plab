#include "btreeInt.h"
#ifndef SQLITE_OMIT_SHARED_CACHE
#if SQLITE_THREADSAFE
static void lockBtreeMutex(Btree*p){assert(p->locked==0);assert(sqlite3_mutex_notheld(p->pBt->mutex));assert(sqlite3_mutex_held(p->db->mutex));sqlite3_mutex_enter(p->pBt->mutex);p->pBt->db=p->db;p->locked=1;}static void SQLITE_NOINLINE unlockBtreeMutex(Btree*p){BtShared*pBt=p->pBt;assert(p->locked==1);assert(sqlite3_mutex_held(pBt->mutex));assert(sqlite3_mutex_held(p->db->mutex));assert(p->db==pBt->db);sqlite3_mutex_leave(pBt->mutex);p->locked=0;}static void SQLITE_NOINLINE btreeLockCarefully(Btree*p);void sqlite3BtreeEnter(Btree*p){assert(p->pNext==0||p->pNext->pBt>p->pBt);assert(p->pPrev==0||p->pPrev->pBt<p->pBt);assert(p->pNext==0||p->pNext->db==p->db);assert(p->pPrev==0||p->pPrev->db==p->db);assert(p->sharable||(p->pNext==0&&p->pPrev==0));assert(!p->locked||p->wantToLock>0);assert(p->sharable||p->wantToLock==0);assert(sqlite3_mutex_held(p->db->mutex));assert((p->locked==0&&p->sharable)||p->pBt->db==p->db);if(!p->sharable)return;p->wantToLock++;if(p->locked)return;btreeLockCarefully(p);}static void SQLITE_NOINLINE btreeLockCarefully(Btree*p){Btree*pLater;if(sqlite3_mutex_try(p->pBt->mutex)==SQLITE_OK){p->pBt->db=p->db;p->locked=1;return;}for(pLater=p->pNext;pLater;pLater=pLater->pNext){assert(pLater->sharable);assert(pLater->pNext==0||pLater->pNext->pBt>pLater->pBt);assert(!pLater->locked||pLater->wantToLock>0);if(pLater->locked){unlockBtreeMutex(pLater);}}lockBtreeMutex(p);for(pLater=p->pNext;pLater;pLater=pLater->pNext){if(pLater->wantToLock){lockBtreeMutex(pLater);}}}void sqlite3BtreeLeave(Btree*p){assert(sqlite3_mutex_held(p->db->mutex));if(p->sharable){assert(p->wantToLock>0);p->wantToLock--;if(p->wantToLock==0){unlockBtreeMutex(p);}}}
#ifndef NDEBUG
int sqlite3BtreeHoldsMutex(Btree*p){assert(p->sharable==0||p->locked==0||p->wantToLock>0);assert(p->sharable==0||p->locked==0||p->db==p->pBt->db);assert(p->sharable==0||p->locked==0||sqlite3_mutex_held(p->pBt->mutex));assert(p->sharable==0||p->locked==0||sqlite3_mutex_held(p->db->mutex));return(p->sharable==0||p->locked);}
#endif
static void SQLITE_NOINLINE btreeEnterAll(sqlite3*db){int i;int skipOk=1;Btree*p;assert(sqlite3_mutex_held(db->mutex));for(i=0;i<db->nDb;i++){p=db->aDb[i].pBt;if(p&&p->sharable){sqlite3BtreeEnter(p);skipOk=0;}}db->noSharedCache=skipOk;}void sqlite3BtreeEnterAll(sqlite3*db){if(db->noSharedCache==0)btreeEnterAll(db);}static void SQLITE_NOINLINE btreeLeaveAll(sqlite3*db){int i;Btree*p;assert(sqlite3_mutex_held(db->mutex));for(i=0;i<db->nDb;i++){p=db->aDb[i].pBt;if(p)sqlite3BtreeLeave(p);}}void sqlite3BtreeLeaveAll(sqlite3*db){if(db->noSharedCache==0)btreeLeaveAll(db);}
#ifndef NDEBUG
int sqlite3BtreeHoldsAllMutexes(sqlite3*db){int i;if(!sqlite3_mutex_held(db->mutex)){return 0;}for(i=0;i<db->nDb;i++){Btree*p;p=db->aDb[i].pBt;if(p&&p->sharable&&(p->wantToLock==0||!sqlite3_mutex_held(p->pBt->mutex))){return 0;}}return 1;}
#endif
#ifndef NDEBUG
int sqlite3SchemaMutexHeld(sqlite3*db,int iDb,Schema*pSchema){Btree*p;assert(db!=0);if(db->pVfs==0&&db->nDb==0)return 1;if(pSchema)iDb=sqlite3SchemaToIndex(db,pSchema);assert(iDb>=0&&iDb<db->nDb);if(!sqlite3_mutex_held(db->mutex))return 0;if(iDb==1)return 1;p=db->aDb[iDb].pBt;assert(p!=0);return p->sharable==0||p->locked==1;}
#endif
#else
void sqlite3BtreeEnter(Btree*p){p->pBt->db=p->db;}void sqlite3BtreeEnterAll(sqlite3*db){int i;for(i=0;i<db->nDb;i++){Btree*p=db->aDb[i].pBt;if(p){p->pBt->db=p->db;}}}
#endif
#ifndef SQLITE_OMIT_INCRBLOB
void sqlite3BtreeEnterCursor(BtCursor*pCur){sqlite3BtreeEnter(pCur->pBtree);}
#if SQLITE_THREADSAFE
void sqlite3BtreeLeaveCursor(BtCursor*pCur){sqlite3BtreeLeave(pCur->pBtree);}
#endif
#endif
#endif

