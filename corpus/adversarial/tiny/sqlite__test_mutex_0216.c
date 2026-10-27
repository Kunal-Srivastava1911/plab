  assert( iMutex!=SQLITE_MUTEX_FAST && iMutex!=SQLITE_MUTEX_RECURSIVE );
  return counterMutexAlloc(iMutex);
}

static int SQLITE_TCLAPI test_enter_static_mutex(
  void * clientData,
  Tcl_Interp *interp,
  int objc,
  Tcl_Obj *CONST objv[]
){
  sqlite3_mutex *pMutex;
  if( objc!=2 ){
    Tcl_WrongNumArgs(interp, 1, objv, "NAME");
    return TCL_ERROR;
  }
  pMutex = getStaticMutexPointer(interp, objv[1]);
  if( !pMutex ){
    return TCL_ERROR;
  }
  sqlite3_mutex_enter(pMutex);
  return TCL_OK;
}

static int SQLITE_TCLAPI test_leave_static_mutex(
  void * clientData,
  Tcl_Interp *interp,
  int objc,
  Tcl_Obj *CONST objv[]
){
  sqlite3_mutex *pMutex;
  if( objc!=2 ){
    Tcl_WrongNumArgs(interp, 1, objv, "NAME");
    return TCL_ERROR;
  }
  pMutex = getStaticMutexPointer(interp, objv[1]);
  if( !pMutex ){
    return TCL_ERROR;
  }
  sqlite3_mutex_leave(pMutex);
  return TCL_OK;
}

static int SQLITE_TCLAPI test_enter_db_mutex(
