  ** obvious when looking at aXRef[] in a symbolic debugger.
  */
  if( pTab->tabFlags & TF_HasGenerated ){
    int bProgress;
    testcase( pTab->tabFlags & TF_HasVirtual );
    testcase( pTab->tabFlags & TF_HasStored );
    do{
      bProgress = 0;
      for(i=0; i<pTab->nCol; i++){
        if( aXRef[i]>=0 ) continue;
        if( (pTab->aCol[i].colFlags & COLFLAG_GENERATED)==0 ) continue;
        if( sqlite3ExprReferencesUpdatedColumn(
                sqlite3ColumnExpr(pTab, &pTab->aCol[i]),
                 aXRef, chngRowid)
        ){
          aXRef[i] = 99999;
          bProgress = 1;
        }
      }
    }while( bProgress );
  }
#endif

  /* The SET expressions are not actually used inside the WHERE loop.
  ** So reset the colUsed mask. Unless this is a virtual table. In that
  ** case, set all bits of the colUsed mask (to ensure that the virtual
  ** table implementation makes all columns available).
  */
