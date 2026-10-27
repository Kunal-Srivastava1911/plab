  ** may have modified them). So not loading those that are not going to
  ** be used eliminates some redundant opcodes.
  */
  newmask = sqlite3TriggerColmask(
      pParse, pTrigger, pChanges, 1, TRIGGER_BEFORE, pTab, onError
  );
  for(i=0, k=regNew; i<pTab->nCol; i++, k++){
    if( i==pTab->iPKey ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, k);
    }else if( (pTab->aCol[i].colFlags & COLFLAG_GENERATED)!=0 ){
      if( pTab->aCol[i].colFlags & COLFLAG_VIRTUAL ) k--;
    }else{
      j = aXRef[i];
      if( j>=0 ){
        if( nChangeFrom ){
          int nOff = (isView ? pTab->nCol : nPk);
          assert( eOnePass==ONEPASS_OFF );
          sqlite3VdbeAddOp3(v, OP_Column, iEph, nOff+j, k);
        }else{
          sqlite3ExprCode(pParse, pChanges->a[j].pExpr, k);
        }
      }else if( 0==(tmask&TRIGGER_BEFORE) || i>31 || (newmask & MASKBIT32(i)) ){
        /* This branch loads the value of a column that will not be changed
