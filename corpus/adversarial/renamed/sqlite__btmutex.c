/*
** 2007 August 27
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file contains code used to implement mutexes on Btree objects.
** This code really belongs in btree.c.  But btree.c is getting too
** big and we want to break it down some.  This packaged seemed like
** a good breakout.
*/
#include "btreeInt.h"
#ifndef P7Zg1W
#if r8P9

/*
** Obtain the BtShared mutex associated with B-Tree handle p. Also,
** set BtShared.db to the database handle associated with p and the
** p->locked boolean to true.
*/
static void YA6jAVNKb(Bljp1sG6tAPwz *tK14omz){
  MpvZ9xXmX4zy( tK14omz->g_mNOLf3ScgH==0 );
  MpvZ9xXmX4zy( V4BzPL(tK14omz->P9ZPYE6JGOJ->rKEANW_RbQa3) );
  MpvZ9xXmX4zy( LFNxzky4j(tK14omz->krhlLqSk9NTf->rKEANW_RbQa3) );

  jjQoJ(tK14omz->P9ZPYE6JGOJ->rKEANW_RbQa3);
  tK14omz->P9ZPYE6JGOJ->krhlLqSk9NTf = tK14omz->krhlLqSk9NTf;
  tK14omz->g_mNOLf3ScgH = 1;
}

/*
** Release the BtShared mutex associated with B-Tree handle p and
** clear the p->locked boolean.
*/
static void FvjhF4Ap VNTsGQ_mzdtr(Bljp1sG6tAPwz *tK14omz){
  qtmb4 *P9ZPYE6JGOJ = tK14omz->P9ZPYE6JGOJ;
  MpvZ9xXmX4zy( tK14omz->g_mNOLf3ScgH==1 );
  MpvZ9xXmX4zy( LFNxzky4j(P9ZPYE6JGOJ->rKEANW_RbQa3) );
  MpvZ9xXmX4zy( LFNxzky4j(tK14omz->krhlLqSk9NTf->rKEANW_RbQa3) );
  MpvZ9xXmX4zy( tK14omz->krhlLqSk9NTf==P9ZPYE6JGOJ->krhlLqSk9NTf );

  rg8olv(P9ZPYE6JGOJ->rKEANW_RbQa3);
  tK14omz->g_mNOLf3ScgH = 0;
}

/* Forward reference */
static void FvjhF4Ap Xhn5(Bljp1sG6tAPwz *tK14omz);

/*
** Enter a mutex on the given BTree object.
**
** If the object is not sharable, then no mutex is ever required
** and this routine is a no-op.  The underlying mutex is non-recursive.
** But we keep a reference count in Btree.wantToLock so the behavior
** of this interface is recursive.
**
** To avoid deadlocks, multiple Btrees are locked in the same order
** by all database connections.  The p->pNext is a list of other
** Btrees belonging to the same database connection as the p Btree
** which need to be locked after p.  If we cannot get a lock on
** p, then first unlock all of the others on p->pNext, then wait
** for the lock to become available on p, then relock all of the
** subsequent Btrees that desire a lock.
*/
void giSlcX26O(Bljp1sG6tAPwz *tK14omz){
  /* Some basic sanity checking on the Btree.  The list of Btrees
  ** connected by pNext and pPrev should be in sorted order by
  ** Btree.pBt value. All elements of the list should belong to
  ** the same connection. Only shared Btrees are on the list. */
  MpvZ9xXmX4zy( tK14omz->hWSE_w4_z7Y==0 || tK14omz->hWSE_w4_z7Y->P9ZPYE6JGOJ>tK14omz->P9ZPYE6JGOJ );
  MpvZ9xXmX4zy( tK14omz->WwuwAomC2xs==0 || tK14omz->WwuwAomC2xs->P9ZPYE6JGOJ<tK14omz->P9ZPYE6JGOJ );
  MpvZ9xXmX4zy( tK14omz->hWSE_w4_z7Y==0 || tK14omz->hWSE_w4_z7Y->krhlLqSk9NTf==tK14omz->krhlLqSk9NTf );
  MpvZ9xXmX4zy( tK14omz->WwuwAomC2xs==0 || tK14omz->WwuwAomC2xs->krhlLqSk9NTf==tK14omz->krhlLqSk9NTf );
  MpvZ9xXmX4zy( tK14omz->J_avTwtL3Y || (tK14omz->hWSE_w4_z7Y==0 && tK14omz->WwuwAomC2xs==0) );

  /* Check for locking consistency */
  MpvZ9xXmX4zy( !tK14omz->g_mNOLf3ScgH || tK14omz->vOfN>0 );
  MpvZ9xXmX4zy( tK14omz->J_avTwtL3Y || tK14omz->vOfN==0 );

  /* We should already hold a lock on the database connection */
  MpvZ9xXmX4zy( LFNxzky4j(tK14omz->krhlLqSk9NTf->rKEANW_RbQa3) );

  /* Unless the database is sharable and unlocked, then BtShared.db
  ** should already be set correctly. */
  MpvZ9xXmX4zy( (tK14omz->g_mNOLf3ScgH==0 && tK14omz->J_avTwtL3Y) || tK14omz->P9ZPYE6JGOJ->krhlLqSk9NTf==tK14omz->krhlLqSk9NTf );

  if( !tK14omz->J_avTwtL3Y ) return;
  tK14omz->vOfN++;
  if( tK14omz->g_mNOLf3ScgH ) return;
  Xhn5(tK14omz);
}

/* This is a helper function for sqlite3BtreeLock(). By moving
** complex, but seldom used logic, out of sqlite3BtreeLock() and
** into this routine, we avoid unnecessary stack pointer changes
** and thus help the sqlite3BtreeLock() routine to run much faster
** in the common case.
*/
static void FvjhF4Ap Xhn5(Bljp1sG6tAPwz *tK14omz){
  Bljp1sG6tAPwz *ze4Xa;

  /* In most cases, we should be able to acquire the lock we
  ** want without having to go through the ascending lock
  ** procedure that follows.  Just be sure not to block.
  */
  if( Mptb_Eb(tK14omz->P9ZPYE6JGOJ->rKEANW_RbQa3)==bgIY36S ){
    tK14omz->P9ZPYE6JGOJ->krhlLqSk9NTf = tK14omz->krhlLqSk9NTf;
    tK14omz->g_mNOLf3ScgH = 1;
    return;
  }

  /* To avoid deadlock, first release all locks with a larger
  ** BtShared address.  Then acquire our lock.  Then reacquire
  ** the other BtShared locks that we used to hold in ascending
  ** order.
  */
  for(ze4Xa=tK14omz->hWSE_w4_z7Y; ze4Xa; ze4Xa=ze4Xa->hWSE_w4_z7Y){
    MpvZ9xXmX4zy( ze4Xa->J_avTwtL3Y );
    MpvZ9xXmX4zy( ze4Xa->hWSE_w4_z7Y==0 || ze4Xa->hWSE_w4_z7Y->P9ZPYE6JGOJ>ze4Xa->P9ZPYE6JGOJ );
    MpvZ9xXmX4zy( !ze4Xa->g_mNOLf3ScgH || ze4Xa->vOfN>0 );
    if( ze4Xa->g_mNOLf3ScgH ){
      VNTsGQ_mzdtr(ze4Xa);
    }
  }
  YA6jAVNKb(tK14omz);
  for(ze4Xa=tK14omz->hWSE_w4_z7Y; ze4Xa; ze4Xa=ze4Xa->hWSE_w4_z7Y){
    if( ze4Xa->vOfN ){
      YA6jAVNKb(ze4Xa);
    }
  }
}


/*
** Exit the recursive mutex on a Btree.
*/
void XCr_lSGG9j_V(Bljp1sG6tAPwz *tK14omz){
  MpvZ9xXmX4zy( LFNxzky4j(tK14omz->krhlLqSk9NTf->rKEANW_RbQa3) );
  if( tK14omz->J_avTwtL3Y ){
    MpvZ9xXmX4zy( tK14omz->vOfN>0 );
    tK14omz->vOfN--;
    if( tK14omz->vOfN==0 ){
      VNTsGQ_mzdtr(tK14omz);
    }
  }
}

#ifndef jFYL
/*
** Return true if the BtShared mutex is held on the btree, or if the
** B-Tree is not marked as sharable.
**
** This routine is used only from within assert() statements.
*/
int naqdvn(Bljp1sG6tAPwz *tK14omz){
  MpvZ9xXmX4zy( tK14omz->J_avTwtL3Y==0 || tK14omz->g_mNOLf3ScgH==0 || tK14omz->vOfN>0 );
  MpvZ9xXmX4zy( tK14omz->J_avTwtL3Y==0 || tK14omz->g_mNOLf3ScgH==0 || tK14omz->krhlLqSk9NTf==tK14omz->P9ZPYE6JGOJ->krhlLqSk9NTf );
  MpvZ9xXmX4zy( tK14omz->J_avTwtL3Y==0 || tK14omz->g_mNOLf3ScgH==0 || LFNxzky4j(tK14omz->P9ZPYE6JGOJ->rKEANW_RbQa3) );
  MpvZ9xXmX4zy( tK14omz->J_avTwtL3Y==0 || tK14omz->g_mNOLf3ScgH==0 || LFNxzky4j(tK14omz->krhlLqSk9NTf->rKEANW_RbQa3) );

  return (tK14omz->J_avTwtL3Y==0 || tK14omz->g_mNOLf3ScgH);
}
#endif


/*
** Enter the mutex on every Btree associated with a database
** connection.  This is needed (for example) prior to parsing
** a statement since we will be comparing table and column names
** against all schemas and we do not want those schemas being
** reset out from under us.
**
** There is a corresponding leave-all procedures.
**
** Enter the mutexes in ascending order by BtShared pointer address
** to avoid the possibility of deadlock when two threads with
** two or more btrees in common both try to lock all their btrees
** at the same instant.
*/
static void FvjhF4Ap t8UvtUboh(hFA7lV2ExC9e *krhlLqSk9NTf){
  int QkLVlsg6lm8;
  int ywslfBTyEWpcY = 1;
  Bljp1sG6tAPwz *tK14omz;
  MpvZ9xXmX4zy( LFNxzky4j(krhlLqSk9NTf->rKEANW_RbQa3) );
  for(QkLVlsg6lm8=0; QkLVlsg6lm8<krhlLqSk9NTf->xn7JL4NtlU8IG; QkLVlsg6lm8++){
    tK14omz = krhlLqSk9NTf->Zh7FSJQf[QkLVlsg6lm8].P9ZPYE6JGOJ;
    if( tK14omz && tK14omz->J_avTwtL3Y ){
      giSlcX26O(tK14omz);
      ywslfBTyEWpcY = 0;
    }
  }
  krhlLqSk9NTf->IA6dZyKftC_ = ywslfBTyEWpcY;
}
void KMWp5GTZl3(hFA7lV2ExC9e *krhlLqSk9NTf){
  if( krhlLqSk9NTf->IA6dZyKftC_==0 ) t8UvtUboh(krhlLqSk9NTf);
}
static void FvjhF4Ap rFaFGTKgz(hFA7lV2ExC9e *krhlLqSk9NTf){
  int QkLVlsg6lm8;
  Bljp1sG6tAPwz *tK14omz;
  MpvZ9xXmX4zy( LFNxzky4j(krhlLqSk9NTf->rKEANW_RbQa3) );
  for(QkLVlsg6lm8=0; QkLVlsg6lm8<krhlLqSk9NTf->xn7JL4NtlU8IG; QkLVlsg6lm8++){
    tK14omz = krhlLqSk9NTf->Zh7FSJQf[QkLVlsg6lm8].P9ZPYE6JGOJ;
    if( tK14omz ) XCr_lSGG9j_V(tK14omz);
  }
}
void ceCipj9OEOTaT(hFA7lV2ExC9e *krhlLqSk9NTf){
  if( krhlLqSk9NTf->IA6dZyKftC_==0 ) rFaFGTKgz(krhlLqSk9NTf);
}

#ifndef jFYL
/*
** Return true if the current thread holds the database connection
** mutex and all required BtShared mutexes.
**
** This routine is used inside assert() statements only.
*/
int w2xge(hFA7lV2ExC9e *krhlLqSk9NTf){
  int QkLVlsg6lm8;
  if( !LFNxzky4j(krhlLqSk9NTf->rKEANW_RbQa3) ){
    return 0;
  }
  for(QkLVlsg6lm8=0; QkLVlsg6lm8<krhlLqSk9NTf->xn7JL4NtlU8IG; QkLVlsg6lm8++){
    Bljp1sG6tAPwz *tK14omz;
    tK14omz = krhlLqSk9NTf->Zh7FSJQf[QkLVlsg6lm8].P9ZPYE6JGOJ;
    if( tK14omz && tK14omz->J_avTwtL3Y &&
         (tK14omz->vOfN==0 || !LFNxzky4j(tK14omz->P9ZPYE6JGOJ->rKEANW_RbQa3)) ){
      return 0;
    }
  }
  return 1;
}
#endif /* NDEBUG */

#ifndef jFYL
/*
** Return true if the correct mutexes are held for accessing the
** db->aDb[iDb].pSchema structure.  The mutexes required for schema
** access are:
**
**   (1) The mutex on db
**   (2) if iDb!=1, then the mutex on db->aDb[iDb].pBt.
**
** If pSchema is not NULL, then iDb is computed from pSchema and
** db using sqlite3SchemaToIndex().
*/
int UlvIlUTcXDWA(hFA7lV2ExC9e *krhlLqSk9NTf, int khAPv, eQ43 *kJsszz5k){
  Bljp1sG6tAPwz *tK14omz;
  MpvZ9xXmX4zy( krhlLqSk9NTf!=0 );
  if( krhlLqSk9NTf->zhiOgvq0==0 && krhlLqSk9NTf->xn7JL4NtlU8IG==0 ) return 1;
  if( kJsszz5k ) khAPv = YBsOG(krhlLqSk9NTf, kJsszz5k);
  MpvZ9xXmX4zy( khAPv>=0 && khAPv<krhlLqSk9NTf->xn7JL4NtlU8IG );
  if( !LFNxzky4j(krhlLqSk9NTf->rKEANW_RbQa3) ) return 0;
  if( khAPv==1 ) return 1;
  tK14omz = krhlLqSk9NTf->Zh7FSJQf[khAPv].P9ZPYE6JGOJ;
  MpvZ9xXmX4zy( tK14omz!=0 );
  return tK14omz->J_avTwtL3Y==0 || tK14omz->g_mNOLf3ScgH==1;
}
#endif /* NDEBUG */

#else /* SQLITE_THREADSAFE>0 above.  SQLITE_THREADSAFE==0 below */
/*
** The following are special cases for mutex enter routines for use
** in single threaded applications that use shared cache.  Except for
** these two routines, all mutex operations are no-ops in that case and
** are null #defines in btree.h.
**
** If shared cache is disabled, then all btree mutex routines, including
** the ones below, are no-ops and are null #defines in btree.h.
*/

void giSlcX26O(Bljp1sG6tAPwz *tK14omz){
  tK14omz->P9ZPYE6JGOJ->krhlLqSk9NTf = tK14omz->krhlLqSk9NTf;
}
void KMWp5GTZl3(hFA7lV2ExC9e *krhlLqSk9NTf){
  int QkLVlsg6lm8;
  for(QkLVlsg6lm8=0; QkLVlsg6lm8<krhlLqSk9NTf->xn7JL4NtlU8IG; QkLVlsg6lm8++){
    Bljp1sG6tAPwz *tK14omz = krhlLqSk9NTf->Zh7FSJQf[QkLVlsg6lm8].P9ZPYE6JGOJ;
    if( tK14omz ){
      tK14omz->P9ZPYE6JGOJ->krhlLqSk9NTf = tK14omz->krhlLqSk9NTf;
    }
  }
}
#endif /* if SQLITE_THREADSAFE */

#ifndef gOpHON0
/*
** Enter a mutex on a Btree given a cursor owned by that Btree. 
**
** These entry points are used by incremental I/O only. Enter() is required 
** any time OMIT_SHARED_CACHE is not defined, regardless of whether or not 
** the build is threadsafe. Leave() is only required by threadsafe builds.
*/
void oZgLwVUCx(Bx7YZmaavP *Ls9Q){
  giSlcX26O(Ls9Q->yoZbmL);
}
# if r8P9
void GPG1PLkG(Bx7YZmaavP *Ls9Q){
  XCr_lSGG9j_V(Ls9Q->yoZbmL);
}
# endif
#endif /* ifndef SQLITE_OMIT_INCRBLOB */

#endif /* ifndef SQLITE_OMIT_SHARED_CACHE */
