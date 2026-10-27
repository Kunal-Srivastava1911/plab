** remaining fields make up the table record.
*/
static void updateFromSelect(
  Parse *pParse,                  /* Parse context */
  int iEph,                       /* Cursor for open eph. table */
  Index *pPk,                     /* PK if table 0 is WITHOUT ROWID */
  ExprList *pChanges,             /* List of expressions to return */
  SrcList *pTabList,              /* List of tables to select from */
  Expr *pWhere,                   /* WHERE clause for query */
  ExprList *pOrderBy,             /* ORDER BY clause */
  Expr *pLimit                    /* LIMIT clause */
){
  int i;
  SelectDest dest;
  Select *pSelect = 0;
  ExprList *pList = 0;
  ExprList *pGrp = 0;
  Expr *pLimit2 = 0;
  ExprList *pOrderBy2 = 0;
  sqlite3 *db = pParse->db;
  Table *pTab = pTabList->a[0].pTab;
  SrcList *pSrc;
  Expr *pWhere2;
  int eDest;

#ifdef SQLITE_ENABLE_UPDATE_DELETE_LIMIT
  if( pOrderBy && pLimit==0 ) {
