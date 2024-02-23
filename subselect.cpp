void NYCEExport::setDOC_PATH()
{
    //## begin nyceexception::NYCEExport::getDOC_PATH%65D201B70161.body preserve=yes
    string DOC_PATH;
    Query hQuery;
    
    // Subquery to get the maximum SEQ_NO for the given CASE_ID
    hQuery.bind("EMS_DOCUMENT", "DOC_PATH", Column::STRING, &DOC_PATH);
    hQuery.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
    hQuery.setCustomPredicate("EMS_DOCUMENT.SEQ_NO = (SELECT MAX(SEQ_NO) FROM EMS_DOCUMENT WHERE CASE_ID = ?)");

    auto_ptr<reusable::SelectStatement> pSelectStatement((reusable::SelectStatement*)database::DatabaseFactory::instance()->create("SelectStatement"));
    if (!pSelectStatement->execute(hQuery))
        return;

    // Use DOC_PATH as needed, for example, extracting the file name
    size_t pos = DOC_PATH.find_last_of("\\");
    if (pos == string::npos)
        pos = DOC_PATH.find_last_of("//");

    if (pos != string::npos)
        m_strFILE_NAME = DOC_PATH.substr(pos + 1, string::npos);
    //## end nyceexception::NYCEExport::getDOC_PATH%65D201B70161.body
}
