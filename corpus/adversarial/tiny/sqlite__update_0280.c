          pRowidExpr = pChanges->a[i].pExpr;
          iRowidExpr = i;
        }else if( pPk && (pTab->aCol[j].colFlags & COLFLAG_PRIMKEY)!=0 ){
          chngPk = 1;
        }
#ifndef SQLITE_OMIT_GENERATED_COLUMNS
        else if( pTab->aCol[j].colFlags & COLFLAG_GENERATED ){
          testcase( pTab->aCol[j].colFlags & COLFLAG_VIRTUAL );
          testcase( pTab->aCol[j].colFlags & COLFLAG_STORED );
          sqlite3ErrorMsg(pParse,
             "cannot UPDATE generated column \"%s\"",
             pTab->aCol[j].zCnName);
          goto update_cleanup;
        }
#endif
        aXRef[j] = i;
        break;
      }
    }
    if( j>=pTab->nCol ){
      if( pPk==0 && sqlite3IsRowid(pChanges->a[i].zEName) ){
        j = -1;
        chngRowid = 1;
        pRowidExpr = pChanges->a[i].pExpr;
        iRowidExpr = i;
      }else{
        sqlite3ErrorMsg(pParse, "no such column: %s", pChanges->a[i].zEName);
        pParse->checkSchema = 1;
