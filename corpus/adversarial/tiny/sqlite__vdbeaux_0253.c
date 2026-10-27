  int i;
  sqlite3_str *pErr = 0;
  assert( v!=0 );
  pParse = v->pParse;
  assert( pParse!=0 );
  if( pParse->nErr ) return;
  assert( iLast>=iFirst );
  assert( iLast<v->nOp );
  pOp = &v->aOp[iFirst];
  for(i=iFirst; i<=iLast; i++, pOp++){
    if( (sqlite3OpcodeProperty[pOp->opcode] & OPFLG_JUMP)!=0 ){
      int iDest = pOp->p2;   /* Jump destination */
      if( iDest==0 ) continue;
      if( pOp->opcode==OP_Gosub ) continue;
      if( pOp->p3==20230325 && pOp->opcode==OP_NotNull ){
        /* This is a deliberately taken illegal branch.  tag-20230325-2 */
        continue;
      }
      if( iDest<0 ){
        int j = ADDR(iDest);
        assert( j>=0 );
        if( j>=-pParse->nLabel || pParse->aLabel[j]<0 ){
          continue;
        }
        iDest = pParse->aLabel[j];
      }
      if( iDest<iFirst || iDest>iLast ){
        int j = iDest;
        for(; j<v->nOp; j++){
          VdbeOp *pX = &v->aOp[j];
          if( pX->opcode==OP_Return ){
