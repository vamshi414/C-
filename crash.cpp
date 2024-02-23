void NYCEExport::setDOC_PATH ()
{
  //## begin nyceexception::NYCEExport::getDOC_PATH%65D201B70161.body preserve=yes
   string DOC_PATH;
   Query hQuery;
   short iSEQ_NO = 0;
   short iNull;
   
   Query hSubQuery;
   hSubQuery.setSubSelect(true);
   hQuery.bind("EMS_DOCUMENT", "SEQ_NO", Column::SHORT, &iSEQ_NO, &iNull, "MAX");
   hSubQuery.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
   auto_ptr<FormatSelectVisitor> pFormatSelectVisitor((FormatSelectVisitor*)DatabaseFactory::instance()->create("FormatSelectVisitor"));
   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   hSubQuery.accept(*pFormatSelectVisitor);
   string strSubQuery = "(" + pFormatSelectVisitor->SQLText() + ")";
   hQuery.bind("EMS_DOCUMENT", "DOC_PATH", Column::STRING, &DOC_PATH);
   hQuery.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
   hQuery.setBasicPredicate("EMS_DOCUMENT", "SEQ_NO", "=", strSubQuery.c_str());
   if (!pSelectStatement->execute(hQuery))
      return;

   size_t pos = DOC_PATH.find_last_of("\\");
   if (pos == string::npos)
      pos = DOC_PATH.find_last_of("//");
   if (pos != string::npos)
      m_strFILE_NAME = DOC_PATH.substr(pos + 1, string::npos);
  //## end nyceexception::NYCEExport::getDOC_PATH%65D201B70161.body
}
