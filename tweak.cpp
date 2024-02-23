void NYCEExport::setDOC_PATH ()
{
  //## begin nyceexception::NYCEExport::getDOC_PATH%65D201B70161.body preserve=yes
   string DOC_PATH;
   Query hQuery;
   short int iSEQ_NO = 0;
   hQuery.bind("EMS_DOCUMENT", "SEQ_NO", Column::SHORT, &iSEQ_NO, 0, "MAX");
   hQuery.bind("EMS_DOCUMENT", "DOC_PATH", Column::STRING, &DOC_PATH);
   hQuery.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
   auto_ptr<reusable::SelectStatement> pSelectStatement((reusable::SelectStatement*)database::DatabaseFactory::instance()->create("SelectStatement"));
   if (!pSelectStatement->execute(hQuery))
      return;
   size_t pos = DOC_PATH.find_last_of("\\");
   if (pos == string::npos)
      pos = DOC_PATH.find_last_of("//");
   if (pos != string::npos)
      m_strFILE_NAME = DOC_PATH.substr(pos + 1, string::npos);
  //## end nyceexception::NYCEExport::getDOC_PATH%65D201B70161.body
}


SELECT EMS_DOCUMENT.DOC_PATH,MAX(EMS_DOCUMENT.SEQ_NO) SEQ_NO FROM DN1PGTWY.EMS_DOCUMENT EMS_DOCUMENT WHERE EMS_DOCUMENT.CASE_ID = ? GROUP BY EMS_DOCUMENT.DOC_PATH
