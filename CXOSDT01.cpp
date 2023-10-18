//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%419CCB660148.cm preserve=no
//## end module%419CCB660148.cm

//## begin module%419CCB660148.cp preserve=no
//	Copyright (c) 1997 - 2022
//	FIS
//## end module%419CCB660148.cp

//## Module: CXOSDT01%419CCB660148; Package body
//## Subsystem: DT%41A35178038A
//## Source file: C:\Repos\DataNavigatorServer\Windows\Build\Dn\Server\Application\Dt\CXOSDT01.cpp

//## begin module%419CCB660148.additionalIncludes preserve=no
//## end module%419CCB660148.additionalIncludes

//## begin module%419CCB660148.includes preserve=yes
//## end module%419CCB660148.includes

#ifndef CXOSIF03_h
#include "CXODIF03.hpp"
#endif
#ifndef CXOSDB02_h
#include "CXODDB02.hpp"
#endif
#ifndef CXOSRU12_h
#include "CXODRU12.hpp"
#endif
#ifndef CXOSMN05_h
#include "CXODMN05.hpp"
#endif
#ifndef CXOSIF16_h
#include "CXODIF16.hpp"
#endif
#ifndef CXOSIF01_h
#include "CXODIF01.hpp"
#endif
#ifndef CXOSDB01_h
#include "CXODDB01.hpp"
#endif
#ifndef CXOSRU08_h
#include "CXODRU08.hpp"
#endif
#ifndef CXOSIF15_h
#include "CXODIF15.hpp"
#endif
#ifndef CXOSTM01_h
#include "CXODTM01.hpp"
#endif
#ifndef CXOSPS01_h
#include "CXODPS01.hpp"
#endif
#ifndef CXOSTM02_h
#include "CXODTM02.hpp"
#endif
#ifndef CXOSRU11_h
#include "CXODRU11.hpp"
#endif
#ifndef CXOSIF08_h
#include "CXODIF08.hpp"
#endif
#ifndef CXOSEH25_h
#include "CXODEH25.hpp"
#endif
#ifndef CXOSRU19_h
#include "CXODRU19.hpp"
#endif
#ifndef CXOSTM04_h
#include "CXODTM04.hpp"
#endif
#ifndef CXOSIF44_h
#include "CXODIF44.hpp"
#endif
#ifndef CXOSIF28_h
#include "CXODIF28.hpp"
#endif
#ifndef CXOSMN03_h
#include "CXODMN03.hpp"
#endif
#ifndef CXOSRU34_h
#include "CXODRU34.hpp"
#endif
#ifndef CXOSRX01_h
#include "CXODRX01.hpp"
#endif
#ifndef CXOSIF25_h
#include "CXODIF25.hpp"
#endif
#ifndef CXOSDB25_h
#include "CXODDB25.hpp"
#endif
#ifndef CXOSIF10_h
#include "CXODIF10.hpp"
#endif
#ifndef CXOSIF05_h
#include "CXODIF05.hpp"
#endif
#ifndef CXOSDT01_h
#include "CXODDT01.hpp"
#endif


//## begin module%419CCB660148.declarations preserve=no
//## end module%419CCB660148.declarations

//## begin module%419CCB660148.additionalDeclarations preserve=yes
#ifndef CXOSDB63_h
#include "CXODDB63.hpp"
#endif
#include <algorithm>
//## end module%419CCB660148.additionalDeclarations


// Class FileWriter 

FileWriter::FileWriter()
  //## begin FileWriter::FileWriter%419CCAB200DA_const.hasinit preserve=no
      : m_iDX_REPORT_ID(0),
        m_iEXPORT_RETRY_COUNT(0),
        m_siNull(0),
        m_pExportFile(0),
        m_pFlatFile(0),
        m_pMemory(0)
  //## end FileWriter::FileWriter%419CCAB200DA_const.hasinit
  //## begin FileWriter::FileWriter%419CCAB200DA_const.initialization preserve=yes
  //## end FileWriter::FileWriter%419CCAB200DA_const.initialization
{
  //## begin FileWriter::FileWriter%419CCAB200DA_const.body preserve=yes
   memcpy(m_sID,"DT01",4);
   m_iDX_FILE_ID[0] = 0;
   m_iDX_FILE_ID[1] = 0;
   m_pReport[0] = 0;
   m_pReport[1] = 0;
   m_iPARENT_REPORT_ID = 0;
   m_pMemory = new Memory(4096);
   MinuteTimer::instance()->attach(this);
   Database::instance()->attach(this);
   vector<string> hValue;
   Extract::instance()->getSpec("DT01",hValue);
   std::sort(hValue.begin(),hValue.end());
   hValue.erase(std::unique(hValue.begin(),hValue.end()),hValue.end());
   vector<string>::iterator p;
   for (p = hValue.begin();p != hValue.end();++p)
   {
      if ((*p).length() > 9
         && (*p).substr(0,7) == "REPORT~")
      {
         vector<string> hToken;
         Buffer::parse((*p).substr(7)," ,",hToken);
         if (hToken.size() >= 2)
            m_hClass.insert(std::pair<string,string>(hToken[0],hToken[1]));
      }
      if ((*p).length() > 9
         && (*p).substr(0, 7) == "REPORT:")
      {
         vector<string> hToken;
         int i = Buffer::parse((*p).substr(7), "~", hToken);
         for (int j = 0; j < i; j++)
            m_hReportIDs.push_back(hToken[j]);
      }
      if ((*p).length() > 9
         && (*p).substr(0,6) == "UNION~")
      {
         vector<string> hToken;
         Buffer::parse((*p).substr(6)," ,",hToken);
         if (hToken.size() >= 2)
            m_hUnion.insert(std::pair<string,int>(hToken[0],atoi(hToken[1].c_str())));
      }
   }
   report::TerminalActivity x; // to load RX DLL
  //## end FileWriter::FileWriter%419CCAB200DA_const.body
}


FileWriter::~FileWriter()
{
  //## begin FileWriter::~FileWriter%419CCAB200DA_dest.body preserve=yes
   MinuteTimer::instance()->detach(this);
   delete m_pMemory;
  //## end FileWriter::~FileWriter%419CCAB200DA_dest.body
}



//## Other Operations (implementation)
void FileWriter::bind (const reusable::string& strTableName, Query& hQuery)
{
  //## begin FileWriter::bind%6310B99300D4.body preserve=yes
   if (!m_strORDER_BY.empty())
   {
      char szColumn[PERCENTD + 16];
      char szFunction[PERCENTD * 2 + 9];
      vector<string> hTokens;
      Buffer::parse(m_strORDER_BY,",",hTokens);
      int j = 0;
      for (int i = 0;i < hTokens.size();i += 2)
      {
         snprintf(szColumn,sizeof(szColumn),"DATA_BUFFER KEY%d",j++);
         snprintf(szFunction,sizeof(szFunction),"SUBSTR,%s,%s",hTokens[i].c_str(),hTokens[i + 1].c_str());
         hQuery.bind(strTableName.c_str(),szColumn,reusable::Column::STRING,0,0,szFunction);
      }
   }
  //## end FileWriter::bind%6310B99300D4.body
}

bool FileWriter::complete (int iDX_FILE_ID)
{
  //## begin FileWriter::complete%41DAD3CC002E.body preserve=yes
   UseCase hUseCase("DIST","## DT01 COMPLETE FILE");
   bool b = false;
   int i = 0;
   while ((b = updateProgress(iDX_FILE_ID,"DC")) == false && i++ < 10)
      Sleep::goTo("00003000");
   Database::instance()->commit();
   if (b)
      update(MinuteTimer::instance());
   return UseCase::setSuccess(b);
  //## end FileWriter::complete%41DAD3CC002E.body
}

void FileWriter::displayIssues ()
{
  //## begin FileWriter::displayIssues%48B7C0F703CA.body preserve=yes
   string strDate(Clock::instance()->getDate());
   string strTime(Clock::instance()->getTime().data(),6);
   Timestamp::adjust(strDate,strTime,-30);
   string strTSTAMP_DISTRIBUTED(strDate.data(),8);
   strTSTAMP_DISTRIBUTED += strTime;
   strTSTAMP_DISTRIBUTED += "00";
   Query hQuery(3);
   hQuery.attach(this);
   hQuery.bind("DX_DATA_CONTROL","DX_FILE_ID",Column::LONG,&m_iDX_FILE_ID[0]);
   hQuery.bind("DX_DATA_CONTROL","DX_FILE_TYPE",Column::STRING,&m_strDX_FILE_TYPE[0]);
   hQuery.setBasicPredicate("DX_DATA_CONTROL","TASK_DISTRIBUTED","=",Application::instance()->name().c_str());
   hQuery.setBasicPredicate("DX_DATA_CONTROL","DX_STATE","=","DS");
   hQuery.setBasicPredicate("DX_DATA_CONTROL","TSTAMP_DISTRIBUTED","<",strTSTAMP_DISTRIBUTED.c_str());
   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   pSelectStatement->execute(hQuery);
  //## end FileWriter::displayIssues%48B7C0F703CA.body
}

bool FileWriter::distribute ()
{
  //## begin FileWriter::distribute%419CCFC3034B.body preserve=yes
   UseCase hUseCase("DIST","## DT01 DISTRIBUTE FILE");
   bool b = false;
   {
      Query hQuery1(1);
      hQuery1.attach(this);
      hQuery1.bind("DX_DATA_CONTROL","DATE_RECON",Column::STRING,&m_strDATE_RECON);
      hQuery1.bind("DX_DATA_CONTROL","DX_FILE_ID",Column::LONG,&m_iDX_FILE_ID[0]);
      hQuery1.bind("DX_DATA_CONTROL","DX_FILE_TYPE",Column::STRING,&m_strDX_FILE_TYPE[0]);
      hQuery1.bind("DX_DATA_CONTROL","DX_STATE",Column::STRING,&m_strDX_STATE);
      hQuery1.bind("DX_DATA_CONTROL","DX_REPORT_ID",Column::LONG,&m_iDX_REPORT_ID,&m_siNull);
      hQuery1.bind("DX_DATA_CONTROL","ENTITY_ID",Column::STRING,&m_strENTITY_ID);
      hQuery1.bind("DX_DATA_CONTROL","ENTITY_TYPE",Column::STRING,&m_strENTITY_TYPE);
      hQuery1.bind("DX_DATA_CONTROL","EXPORT_RETRY_COUNT",Column::LONG,&m_iEXPORT_RETRY_COUNT);
      hQuery1.bind("DX_DATA_CONTROL","ROUTING_DATA",Column::STRING,&m_strROUTING_DATA);
      hQuery1.bind("DX_DATA_CONTROL","ROUTING_PASSWORD",Column::STRING,&m_strROUTING_PASSWORD);
      hQuery1.bind("DX_DATA_CONTROL","ROUTING_TYPE",Column::STRING,&m_strROUTING_TYPE);
      hQuery1.bind("DX_DATA_CONTROL","ROUTING_USER_ID",Column::STRING,&m_strROUTING_USER_ID);
      hQuery1.bind("DX_DATA_CONTROL","SCHED_TIME ",Column::STRING,&m_strSCHED_TIME);
      hQuery1.bind("DX_DATA_CONTROL","TSTAMP_FORMATTED",Column::STRING,&m_strTSTAMP_FORMATTED);
      hQuery1.bind("DX_DATA_CONTROL","TASK_FORMATTED",Column::STRING,&m_strTASK_FORMATTED);
      hQuery1.bind("DX_DATA_CONTROL","ORDER_BY",Column::STRING,&m_strORDER_BY);
#ifdef MVS
      if (m_strDX_FILE_TYPE_InList.length() > 0)
      {
         string strClause("NOT IN");
         if (Application::instance()->name().substr(4,2) != "01")
            strClause.assign("IN");
         hQuery1.setBasicPredicate("DX_DATA_CONTROL","DX_FILE_TYPE",strClause.c_str(),m_strDX_FILE_TYPE_InList.c_str());
      }
      else
      if (Application::instance()->name().substr(4,2) != "01")
         return false;
      Query hQuery;
      hQuery.setSubSelect(true);
      hQuery.bind("DX_DATA_CONTROL","DX_FILE_TYPE",Column::STRING,(char*)0);
      hQuery.setBasicPredicate("DX_DATA_CONTROL","DX_STATE","=","DS");
      hQuery.setBasicPredicate("DX_DATA_CONTROL","TASK_DISTRIBUTED","=",Application::instance()->name().c_str());
      auto_ptr<reusable::FormatSelectVisitor>pFormatSelectVisitor
      ((reusable::FormatSelectVisitor*)database::DatabaseFactory::instance()->create("FormatSelectVisitor"));
      hQuery.accept(*pFormatSelectVisitor);
      string strSubSelect = "(" + pFormatSelectVisitor->SQLText() + ")";
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","DX_FILE_TYPE","NOT IN",strSubSelect.c_str());
      hQuery1.getSearchCondition().append(" AND");
#endif
      hQuery1.getSearchCondition().append(" (");
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","DX_STATE","=","DW");
      auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
      hQuery1.getSearchCondition().append(" OR (");
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","DX_STATE","IN","('DE','D1','D2','D3','D4','D5','D6','D7','D8','D9')");
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","TSTAMP_NEXT_EXPORT","<",Clock::instance()->getYYYYMMDDHHMMSSHN().c_str());
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","EXPORT_RETRY_COUNT","<",5);
      hQuery1.getSearchCondition().append(") OR (");
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","DX_STATE","=","DI");
      hQuery1.setBasicPredicate("DX_DATA_CONTROL","TASK_DISTRIBUTED","=",Application::instance()->name().c_str());
      hQuery1.getSearchCondition().append("))");
      hQuery1.setOrderByClause("DATE_RECON ASC,TSTAMP_INITIATED ASC");
      bool b = pSelectStatement->execute(hQuery1);
      if (pSelectStatement->getRows() == 0)
      {
         UseCase::setSuccess(b);
         return false;
      }
   }
   m_strDX_PATH.erase();
   string strKey("DFILES  ");
   strKey += m_strDX_FILE_TYPE[0];
   string strRecord;
   bool bFileDefined = Extract::instance()->getRecord(strKey.c_str(),strRecord);
   string strDX_FILE_TYPE(m_strDX_FILE_TYPE[0]);
   if (bFileDefined == false
      && m_iDX_REPORT_ID > 0)
   {
      string strKey("DFILES  ");
      strKey.append(m_strDX_FILE_TYPE[0].data(),2);
      char szTemp[PERCENTD];
      strKey.append(szTemp,snprintf(szTemp,sizeof(szTemp),"%06d",m_iDX_REPORT_ID));
      string strRecord;
      bFileDefined = Extract::instance()->getRecord(strKey.c_str(),strRecord);
   }
   if (!bFileDefined)
   {
      if (strDX_FILE_TYPE.substr(0,2) == "RF" || strDX_FILE_TYPE.substr(0,2) == "OE")
         strDX_FILE_TYPE = "SMTP";
      else
         return updateProgress(m_iDX_FILE_ID[0],"DC");
   }
   if (!updateProgress(m_iDX_FILE_ID[0],"DI"))
      return false;
   Database::instance()->commit();
   if (m_strDX_FILE_TYPE[0] == "DNBTCH")
      IF::Extract::instance()->getSpec("CUSTOMER",m_strENTITY_ID);
   string strFirst;
   if (m_iDX_REPORT_ID > 0)
   {
      char szDX_REPORT_ID[PERCENTD];
      strFirst.assign(szDX_REPORT_ID,snprintf(szDX_REPORT_ID,sizeof(szDX_REPORT_ID),"%d",m_iDX_REPORT_ID));
   }
   else
      strFirst = m_strDX_FILE_TYPE[0];
   pair<multimap<string,string,less<string> >::iterator,multimap<string,string,less<string> >::iterator> hRange = m_hClass.equal_range(strFirst);
   if (hRange.first != hRange.second)
   {
      int count = 0;
      for (multimap<string,string,less<string> >::iterator pRange = hRange.first;pRange != hRange.second;++pRange)
      {
         if (find(m_hReportIDs.begin(), m_hReportIDs.end(), (*pRange).first) != m_hReportIDs.end()
            && m_hReportIDs[0] != (*pRange).first)
            continue; // skip reports which would be proceesed through PRC999
         if (count++ < atoi(string(1,m_strDX_STATE.data()[1]).c_str()))
            continue; //skip reports that are already finished;
         if (m_hReportIDs[0] == (*pRange).first)
         {
            m_pReport[0] = postingfile::Reports::instance()->getReport(atoi(m_hReportIDs[0].c_str()));
            if (!m_pReport[0])
               return UseCase::setSuccess(false);
            m_iPARENT_REPORT_ID = atoi(m_hReportIDs[0].c_str());
            m_hReportIDs.erase(m_hReportIDs.begin());
            vector<string>::iterator r;
            for (r = m_hReportIDs.begin(); r != m_hReportIDs.end(); r++)
            {
               pair<multimap<string, string, less<string> >::iterator, multimap<string, string, less<string> >::iterator> hRange1 = m_hClass.equal_range((*r).data());
               if (hRange1.first != hRange1.second)
               {
                  multimap<string, string, less<string> >::iterator pRange1 = hRange1.first;
                  for (; pRange1 != hRange1.second; pRange1++)
                  {
                     m_pExportFile = ReportFactory::instance()->create((*pRange1).second);
                     if (m_pExportFile)
                     {
                        m_pExportFile->initialize();
                        m_pExportFile->setPARENT_REPORT_ID(m_iPARENT_REPORT_ID);
                        m_iDX_REPORT_ID = atoi((*pRange1).first.c_str());
                        strDX_FILE_TYPE = m_pExportFile->getDX_FILE_TYPE();
                        b = format(strDX_FILE_TYPE);
                     }
                  }
                  //if (b)
                     //m_hClass.erase((hRange1).first);
                    // m_hClass.erase((*pRange1).first);
               }
            }
         }
         else
         if (m_strDX_FILE_TYPE[0] == (*pRange).second)
            b = format(m_strDX_FILE_TYPE[0]);
         else
         {
            m_pExportFile = ReportFactory::instance()->create((*pRange).second);
            if (m_pExportFile)
            {
               m_pExportFile->initialize();
               m_pExportFile->setDX_REPORT_ID(m_iDX_REPORT_ID);
               strDX_FILE_TYPE = m_pExportFile->getDX_FILE_TYPE();
               b = format(strDX_FILE_TYPE);
            }
         }
         if (b)
         {
            char szBuffer[PERCENTD] = {"  "};
            m_strDX_STATE.assign(szBuffer,snprintf(szBuffer,sizeof(szBuffer),"D%d",count));
            if (!updateProgress(m_iDX_FILE_ID[0],m_strDX_STATE.c_str()))
               return false;
            Database::instance()->commit();
         }
         else
            break;
      }
   }
   else
      b = format(strDX_FILE_TYPE);
#ifndef MVS
   char szDX_FILE_ID[PERCENTD];
   snprintf(szDX_FILE_ID,sizeof(szDX_FILE_ID),"%d",m_iDX_FILE_ID[0]);
   if (b)
      Console::display("ST607",m_strENTITY_ID.c_str(),m_strDX_FILE_TYPE[0].c_str(),szDX_FILE_ID);
   else
      Console::display("ST608",m_strENTITY_ID.c_str(),m_strDX_FILE_TYPE[0].c_str(),szDX_FILE_ID);
#endif
   if (!b)
   {
      updateProgress(m_iDX_FILE_ID[0],"DE");
      return UseCase::setSuccess(false);
   }
#ifdef MVS
   return updateProgress(m_iDX_FILE_ID[0],"DS");
#else
   return updateProgress(m_iDX_FILE_ID[0],"DC");
#endif
  //## end FileWriter::distribute%419CCFC3034B.body
}

bool FileWriter::format (const reusable::string& strDX_FILE_TYPE)
{
  //## begin FileWriter::format%5D0BF68B0242.body preserve=yes
   m_strDX_FILE_TYPE[1] = strDX_FILE_TYPE;
   if (m_iDX_REPORT_ID > 0)
   {
      string strRecord;
      string strKey("DFILES  ");
      strKey += m_strDX_FILE_TYPE[1];
      if (!Extract::instance()->getRecord(strKey.c_str(),strRecord))
      {
         strKey.resize(8,' ');
         strKey.append(m_strDX_FILE_TYPE[0].data(),2);
         char szTemp[PERCENTD];
         strKey.append(szTemp,snprintf(szTemp,sizeof(szTemp),"%06d",m_iDX_REPORT_ID));
         if (Extract::instance()->getRecord(strKey.c_str(),strRecord))
            m_strDX_FILE_TYPE[1].assign(strKey.data() + 8,8);
      }
   }
   m_pFlatFile = new FlatFile(m_strDX_FILE_TYPE[1].c_str());
   m_pFlatFile->setDate(m_strDATE_RECON);
   m_pFlatFile->setScheduledTime(m_strSCHED_TIME);
   m_pFlatFile->setOwner(m_strENTITY_ID);
   m_pFlatFile->setDX_REPORT_ID(m_iDX_REPORT_ID);
   m_pFlatFile->setDX_FILE_ID(m_iDX_FILE_ID[0]);  
   FlatFile::OpenType nOpenType = FlatFile::CX_OPEN_OUTPUT;
   if(strDX_FILE_TYPE == "CMSSTD" || strDX_FILE_TYPE == "CMS622")
   {
      nOpenType = FlatFile::CX_OPEN_OUTPUT_BINARY;
      m_pFlatFile->setRecordFormat("FB");
   }
   if (!m_pFlatFile->open(nOpenType))
   {
      delete m_pFlatFile;
      m_pFlatFile = 0;
      return UseCase::setSuccess(false);
   }
   string strFirst("ZERO");
   string strSecond("NO");
   SiteSpecification::instance()->add(strFirst,strSecond);
   entityhierarchy::Contact hContact;
   bool bEmail = hContact.read(m_strENTITY_TYPE.c_str(),m_strENTITY_ID,"AR");
   if (m_pExportFile == 0)
   {
      ExportFile hExportFile;
      hExportFile.setDX_FILE_TYPE(strDX_FILE_TYPE);
      m_pExportFile = m_hDistributionFileFactory.create(hExportFile);
   }
   m_pExportFile->setDX_FILE_TYPE(strDX_FILE_TYPE);
   m_pExportFile->setDX_FILE_ID(m_iDX_FILE_ID[0]);
   m_pExportFile->setDX_REPORT_ID(m_iDX_REPORT_ID);
   m_pExportFile->setENTITY_TYPE(m_strENTITY_TYPE);
   m_pExportFile->setENTITY_ID(m_strENTITY_ID);
   m_pExportFile->setDATE_RECON(m_strDATE_RECON);
   m_pExportFile->setSCHED_TIME(m_strSCHED_TIME);
   m_pExportFile->setTSTAMP_FORMATTED(m_strTSTAMP_FORMATTED);
   m_pExportFile->setTASK_FORMATTED(m_strTASK_FORMATTED);
   m_pExportFile->setROUTING_DATA(m_strROUTING_DATA);
   m_pExportFile->setROUTING_PASSWORD(m_strROUTING_PASSWORD);
   m_pExportFile->setROUTING_TYPE(m_strROUTING_TYPE);
   m_pExportFile->setROUTING_USER_ID(m_strROUTING_USER_ID);
   string strTableName("DX_DATA_");
   strTableName.append(m_strDATE_RECON);
   strTableName.append(" DX");
   m_strDATA_BUFFER[1].erase();
   int iSEQ_NO[2] = {0,9999};
   Interval hInterval("DIST","## DT05 DISTRIBUTE FILE","AVETIME");
   if (!m_pExportFile->start(*m_pFlatFile))
   {
      delete m_pExportFile;
      m_pExportFile = 0;
      m_pFlatFile->remove();
      delete m_pFlatFile;
      m_pFlatFile = 0;
      return UseCase::setSuccess(false);
   }
   m_strORDER_BY.rtrim();
   string strRecord;
   bool b = true;
   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   int iDX_FILE_ID = -1;
   map<string,int,less<string> >::iterator u = m_hUnion.find(m_strDX_FILE_TYPE[0]);
   if (u != m_hUnion.end())
   {
      Query hQuery;
      hQuery.bind("DX_DATA_CONTROL","DX_FILE_ID",Column::LONG,&iDX_FILE_ID);
      hQuery.setBasicPredicate("DX_DATA_CONTROL","ENTITY_ID","=",m_strENTITY_ID.c_str());
      hQuery.setBasicPredicate("DX_DATA_CONTROL","DATE_RECON","=",m_strDATE_RECON.c_str());
      hQuery.setBasicPredicate("DX_DATA_CONTROL","DX_FILE_TYPE","=","TXNACT");
      hQuery.setBasicPredicate("DX_DATA_CONTROL","DX_REPORT_ID","=",(*u).second);
      if (!pSelectStatement->execute(hQuery))
         return UseCase::setSuccess(false);
   }
   if (!m_pExportFile->getEmptyReport())
   {
      for (;;)
      {
         hInterval.start();
         Query hQuery2(2);
         hQuery2.attach(this);
         hQuery2.setRetainCursor(true);
         if (!m_strORDER_BY.empty())
         {
            string strOrderByClause;
            char szColumn[PERCENTD + 4];
            vector<string> hTokens;
            Buffer::parse(m_strORDER_BY,",",hTokens);
            int j = 0;
            for (int i = 0;i < hTokens.size();i += 2)
            {
               snprintf(szColumn,sizeof(szColumn),"KEY%d",j++);
               if (!strOrderByClause.empty())
                  strOrderByClause.append(",",1);
               strOrderByClause.append(szColumn);
            }
            hQuery2.setOrderByClause(strOrderByClause);
         }
         else
            m_pExportFile->setOrderByClause(hQuery2);
         if (!hQuery2.getTable().empty())
         {
            iSEQ_NO[1] = 2147483647;
            string strOrderByClause(hQuery2.getOrderByClause());
            hQuery2.setOrderByClause("");
            hQuery2.setSubSelect(true);
            hQuery2.bind(strTableName.c_str(),"DATA_BUFFER",Column::STRING,0);
            hQuery2.bind(strTableName.c_str(),"ALT_REC_KEY",Column::STRING,0);
            hQuery2.bind(strTableName.c_str(),"DX_FILE_ID",Column::LONG,0);
            bind(strTableName,hQuery2);
            hQuery2.setBasicPredicate(strTableName.c_str(),"DX_FILE_ID","=",m_iDX_FILE_ID[0]);
            b = m_pExportFile->unionAll(hQuery2);
            if (!b)
               break;
            auto_ptr<reusable::FormatSelectVisitor>pFormatSelectVisitor((reusable::FormatSelectVisitor*)database::DatabaseFactory::instance()->create("FormatSelectVisitor"));
            hQuery2.accept(*pFormatSelectVisitor);
            string strSubSelect = "(" + pFormatSelectVisitor->SQLText();
            Query* pQuery = hQuery2.getQuery();
            while (pQuery)
            {
               pQuery->accept(*pFormatSelectVisitor);
               strSubSelect += ' ';
               strSubSelect += pQuery->getAssociation();
               strSubSelect += ' ';
               strSubSelect += pFormatSelectVisitor->SQLText();
               pQuery = pQuery->getQuery();
            }
            strSubSelect += " ) X";
            hQuery2.reset();
            hQuery2.bind(strSubSelect.c_str(),"DX_FILE_ID",Column::LONG,&m_iDX_FILE_ID[1]);
            hQuery2.bind(strSubSelect.c_str(),"DATA_BUFFER",Column::STRING,&m_strDATA_BUFFER[0]);
            hQuery2.bind(strSubSelect.c_str(),"ALT_REC_KEY",Column::STRING,&m_strALT_REC_KEY);
            bind(strTableName,hQuery2);
            hQuery2.setOrderByClause(strOrderByClause.c_str());
         }
         else
         {
            hQuery2.bind(strTableName.c_str(),"DX_FILE_ID",Column::LONG,&m_iDX_FILE_ID[1]);
            hQuery2.bind(strTableName.c_str(),"DATA_BUFFER",Column::STRING,&m_strDATA_BUFFER[0]);
            hQuery2.bind(strTableName.c_str(),"ALT_REC_KEY",Column::STRING,&m_strALT_REC_KEY);
            bind(strTableName,hQuery2);
            if (iDX_FILE_ID == -1)
               hQuery2.setBasicPredicate(strTableName.c_str(),"DX_FILE_ID","=",m_iDX_FILE_ID[0]);
            else
            {
               char szTemp[PERCENTD * 2 + 4];
               snprintf(szTemp,sizeof(szTemp),"(%d,%d)",m_iDX_FILE_ID[0],iDX_FILE_ID);
               hQuery2.setBasicPredicate(strTableName.c_str(),"DX_FILE_ID","IN",szTemp);
            }
            if (hQuery2.getOrderByClause() != "SEQ_NO")
               iSEQ_NO[1] = 2147483647;
            char szSEQ_NO[PERCENTD * 2 + 6];
            snprintf(szSEQ_NO,sizeof(szSEQ_NO),"%d AND %d",iSEQ_NO[0],iSEQ_NO[1]);
            hQuery2.setBasicPredicate(strTableName.c_str(),"SEQ_NO","BETWEEN",szSEQ_NO);
         }
         if ( b == false
            || pSelectStatement->execute(hQuery2) == false
            || hQuery2.getAbort())
         {
            Database::instance()->rollback();
            delete m_pExportFile;
            m_pExportFile = 0;
            m_pFlatFile->remove();
            delete m_pFlatFile;
            m_pFlatFile = 0;
            return UseCase::setSuccess(false);
         }
         hInterval.stop();
         if (iSEQ_NO[1] == 2147483647)
            break;
         iSEQ_NO[0] = iSEQ_NO[1] + 1;
         if (pSelectStatement->getRows() == 0)
            iSEQ_NO[1] = 2147483647;
         else
         {
            int i = 10000;
            if (hInterval.getSample() > 0)
               i = (int)((double)((10000) / (double)hInterval.getSample()) * (double)pSelectStatement->getRows());
            if (i < 10000)
               i = 10000;
            else
               if (i > 100000)
                  i = 100000;
            iSEQ_NO[1] = iSEQ_NO[0] + i;
         }
      }
      string strCountry;
      if (Extract::instance()->getSpec("DELCNTRY",strCountry))
      {
         if (!m_pExportFile->erase())
         {
            Database::instance()->rollback();
            updateProgress(m_iDX_FILE_ID[0],"DE");
            delete m_pExportFile;
            m_pExportFile = 0;
            m_pFlatFile->remove();
            delete m_pFlatFile;
            m_pFlatFile = 0;
            return UseCase::setSuccess(false);
         }
      }
      if (!m_pExportFile->finish(*m_pFlatFile))
      {
         delete m_pExportFile;
         m_pExportFile = 0;
         m_pFlatFile->remove();
         delete m_pFlatFile;
         m_pFlatFile = 0;
         return UseCase::setSuccess(false);
      }
   }
   if (bEmail)
      m_pExportFile->email();
   delete m_pExportFile;
   m_pExportFile = 0;
   UseCase::addItem(pSelectStatement->getRows());
   string strPath("PATH");
   string strValue(m_pFlatFile->datasetName());
   SiteSpecification::instance()->add(strPath,strValue);
   m_strDX_PATH = strValue;
   bEmail = (strDX_FILE_TYPE == "SMTP" && m_pFlatFile->isMail());
   if (!m_pFlatFile->close())
   {
      m_pFlatFile->remove();
      delete m_pFlatFile;
      m_pFlatFile = 0;
      return UseCase::setSuccess(false);
   }
   delete m_pFlatFile;
   m_pFlatFile = 0;
   if (bEmail)
      return updateProgress(m_iDX_FILE_ID[0],"DC");
   string strFolder("FOLDER1");
   string strFile("FILE");
   char* pszPath = new char[strValue.length() + 1];
   memcpy(pszPath,strValue.data(),strValue.length());
   pszPath[strValue.length()] = '\0';
   char* p = strtok(pszPath,"/\\");
   while (p)
   {
      string strSecond(p);
      SiteSpecification::instance()->add(strFolder,strSecond);
      SiteSpecification::instance()->add(strFile,strSecond);
      strFolder[6] = strFolder[6] + 1;
      p = strtok(0,"/\\");
   }
   delete [] pszPath;
   char szDX_FILE_ID[PERCENTD];
   snprintf(szDX_FILE_ID,sizeof(szDX_FILE_ID),"%d",m_iDX_FILE_ID[0]);
   string strMember("##");
   if (m_siNull != -1
      && (strDX_FILE_TYPE == "TXNACT" || strDX_FILE_TYPE == "EMSACT"))
   {
      char szReportID[PERCENTD];
      snprintf(szReportID,sizeof(szReportID),"%011d",m_iDX_REPORT_ID);
      strMember.append(szReportID+5,6);
   }
   else
      strMember += strDX_FILE_TYPE;
   string strDate;
   strDate = "D" + m_strDATE_RECON.substr(2,6) + ".T" + m_strSCHED_TIME;
   string strZero("&ZERO.");
   SiteSpecification::instance()->substitute(strZero);
   if (strZero != "YES")
      strZero = "NO";
   string strRECON("D");
   strRECON.append(m_strDATE_RECON.data() + 2,6);
#ifdef MVS
   string strApplicationName(Application::instance()->name());
   strApplicationName.trim();
   map<string,string,less<string> > hParameters;
   hParameters.insert(map<string,string,less<string> >::value_type("&FILEID ",string(szDX_FILE_ID)));
   hParameters.insert(map<string,string,less<string> >::value_type("&ENTITY ",m_strENTITY_ID));
   hParameters.insert(map<string,string,less<string> >::value_type("&DATE   ",strDate));
   hParameters.insert(map<string,string,less<string> >::value_type("&DATA   ",m_strROUTING_DATA));
   hParameters.insert(map<string,string,less<string> >::value_type("&USER   ",m_strROUTING_USER_ID));
   hParameters.insert(map<string,string,less<string> >::value_type("&PASS   ",m_strROUTING_PASSWORD));
   hParameters.insert(map<string,string,less<string> >::value_type("&ZERO   ",strZero));
   hParameters.insert(map<string,string,less<string> >::value_type("&RECON  ",strRECON));
   hParameters.insert(map<string,string,less<string> >::value_type("&TASKID ",strApplicationName));
   m_strDX_PATH.rtrim();
   hParameters.insert(map<string,string,less<string> >::value_type("&DSN    ",m_strDX_PATH));
   return Job::submit(strMember.c_str(),hParameters);
#endif
   return Job::submit(strMember.c_str(),
      "&FILEID ",szDX_FILE_ID,
      "&ENTITY ",m_strENTITY_ID.c_str(),
      "&DATE   ",strDate.c_str(),
      "&DATA   ",m_strROUTING_DATA.c_str(),
      "&USER   ",m_strROUTING_USER_ID.c_str(),
      "&PASS   ",m_strROUTING_PASSWORD.c_str(),
      "&ZERO   ",strZero.c_str(),
      "&RECON  ",strRECON.c_str());
  //## end FileWriter::format%5D0BF68B0242.body
}

void FileWriter::redistribute (int iDX_FILE_ID)
{
  //## begin FileWriter::redistribute%41B9F92A0148.body preserve=yes
   UseCase hUseCase("DIST","## DT01 REDISTRIBUTE FILE");
   Table hTable("DX_DATA_CONTROL");
   hTable.set("TSTAMP_DISTRIBUTED"," ");
   hTable.set("TASK_DISTRIBUTED"," ");
   hTable.set("DX_STATE","DW");
   hTable.set("DX_FILE_ID",(int)iDX_FILE_ID,true);
   auto_ptr<Statement> pUpdateStatement ((Statement*)DatabaseFactory::instance()->create("UpdateStatement"));
   UseCase::setSuccess(pUpdateStatement->execute(hTable));
   Database::instance()->commit();
   update(MinuteTimer::instance());
  //## end FileWriter::redistribute%41B9F92A0148.body
}

void FileWriter::update (Subject* pSubject)
{
  //## begin FileWriter::update%419CDDC8030D.body preserve=yes
   if (pSubject == Database::instance())
   {
#ifdef MVS
      if (Database::instance()->state() == Database::CONNECTED)
      {
         displayIssues();
         reusable::Query hQuery(4);
         hQuery.attach(this);
         hQuery.setQualifier("QUALIFY","CRFILET");
         hQuery.bind("CRFILET","GENNAM",Column::STRING,&m_strDX_FILE_TYPE[0]);
         if (Application::instance()->name().substr(4,2) == "01")
         {
            hQuery.bind("CRFILET","TASKID",Column::STRING,&m_strTASKID,0,"MIN");
            hQuery.setBasicPredicate("CRFILET","TASKID","LIKE","__DT__%");
            hQuery.setGroupByClause("GENNAM");
         }
         else
            hQuery.setBasicPredicate("CRFILET","TASKID","=",Application::instance()->name().c_str());
         hQuery.setBasicPredicate("CRFILET","CC_CHANGE_GRP_ID","IS NULL");
         hQuery.setBasicPredicate("CRFILET","CC_STATE","=","A");
         hQuery.setOrderByClause("GENNAM");
         auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
         pSelectStatement->execute(hQuery);
         Database::instance()->commit();
      }
#endif
      return;
   }
   if (pSubject == MinuteTimer::instance())
   {
      while (distribute())
         Database::instance()->commit();
#ifdef MVS
      if (Clock::instance()->getMinute() == 30
         || Clock::instance()->getMinute() == 0)
         displayIssues();
#endif
      Database::instance()->commit();
      return;
   }
   if (((Query*)pSubject)->getIndex() == 1)
   {
      ((Query*)pSubject)->setAbort(true);
      return;
   }
   if (((Query*)pSubject)->getIndex() == 2)
   {
      if (m_strDATA_BUFFER[0] != (const char*)"XZ") // appended by ExportFile::write
      {
         m_strDATA_BUFFER[1] += m_strDATA_BUFFER[0];
         if (m_strALT_REC_KEY.length() > 16)
            m_pExportFile->setALT_REC_KEY(m_strALT_REC_KEY);
      }
      if (m_strDATA_BUFFER[0].length() < 3800)
      {
         if (m_strALT_REC_KEY.length() > 16)
            m_pExportFile->setALT_REC_KEY(m_strALT_REC_KEY);
         if (m_pExportFile->getDX_FILE_TYPE() == "SMTP"
            && m_strDATA_BUFFER[1] == "\\n")
            m_strDATA_BUFFER[1].erase();
         m_pExportFile->setDX_FILE_ID(m_iDX_FILE_ID[1],1);
         if (m_hReportIDs.size() > 0)
         {
            string strDATA_BUFFER;
            vector<postingfile::ReportColumn>::iterator r;
            map<string, pair<int, short>, less<string> >::iterator q;
            map<string, pair<int, short>, less<string> >  hOffsetWidth = m_pReport[0]->getOffsetWidth();
            m_pReport[1] = postingfile::Reports::instance()->getReport(m_pExportFile->getDX_REPORT_ID());
            if (!m_pReport[1])
               return;
            for (r = m_pReport[1]->getReportColumn().begin(); r != m_pReport[1]->getReportColumn().end(); r++)
            {
               if ((q = hOffsetWidth.find(r->getCOLUMN_NAME())) != hOffsetWidth.end())
                  strDATA_BUFFER.append(m_strDATA_BUFFER[1].data() + (*q).second.first, (*q).second.second);
            }
            m_strDATA_BUFFER[1].assign(strDATA_BUFFER);
         }
         if (!m_pExportFile->distribute(m_strDATA_BUFFER[1],*m_pFlatFile))
         {
            Console::display("ST122");
            ((Query*)pSubject)->setAbort(true);
         }
         m_strDATA_BUFFER[1].erase();
      }
      return;
   }
#ifdef MVS
   if (((Query*)pSubject)->getIndex() == 4)
   {
      if (memcmp(Application::instance()->name().data() + 4,"01",2) == 0
         && memcmp(m_strTASKID.data() + 4,"01",2) == 0)
         return;
      if (m_strDX_FILE_TYPE_InList.length() == 0)
         m_strDX_FILE_TYPE_InList += '(';
      else
         m_strDX_FILE_TYPE_InList[m_strDX_FILE_TYPE_InList.length() - 1] = ',';
      m_strDX_FILE_TYPE_InList += '\'';
      m_strDX_FILE_TYPE_InList.append(m_strDX_FILE_TYPE[0]);
      m_strDX_FILE_TYPE_InList.append("\')",2);
      return;
   }
#endif
   string strJob(Application::instance()->name().data(),2);
   strJob += m_strDX_FILE_TYPE[0];
   char szDX_FILE_ID[PERCENTD];
   snprintf(szDX_FILE_ID,sizeof(szDX_FILE_ID),"%d",m_iDX_FILE_ID[0]);
   Console::display("ST145",strJob.c_str(),szDX_FILE_ID);
  //## end FileWriter::update%419CDDC8030D.body
}

bool FileWriter::updateProgress (int iDX_FILE_ID, const char* pszDX_STATE)
{
  //## begin FileWriter::updateProgress%419CEA130251.body preserve=yes
   if (memcmp(pszDX_STATE,"DI",2) == 0 && (m_strDX_STATE.data()[1] >= '1' && m_strDX_STATE.data()[1] <= '9'))
      return true;
   string strSearchCondition;
   Table hTable("DX_DATA_CONTROL");
   hTable.set("DX_FILE_ID",iDX_FILE_ID,true);
   if (memcmp(pszDX_STATE,"DE",2) == 0 && (m_strDX_STATE.data()[1] >= '1' && m_strDX_STATE.data()[1] <= '9'))
      ;
   else
      hTable.set("DX_STATE",string(pszDX_STATE));
   hTable.set("TASK_DISTRIBUTED",Application::instance()->name());
   string strTSTAMP_DISTRIBUTED(Clock::instance()->getYYYYMMDDHHMMSSHN(true));
   hTable.set("TSTAMP_DISTRIBUTED",strTSTAMP_DISTRIBUTED);
   if (!strcmp(pszDX_STATE,"DE"))
   {
      reusable::IString strYYYYMMDDHHMMSShh = strTSTAMP_DISTRIBUTED.c_str();
      DateTime hDateTime;
      hDateTime.timeAdjust(strYYYYMMDDHHMMSShh,5);
      hTable.set("TSTAMP_NEXT_EXPORT",string((char*)strYYYYMMDDHHMMSShh));
      hTable.set("EXPORT_RETRY_COUNT",(int)1,false,"+");
   }
   else
   if (!strcmp(pszDX_STATE,"DI"))
      strSearchCondition = " AND DX_STATE IN ('DI','DW','DE') AND (TASK_DISTRIBUTED = ' ' OR TASK_DISTRIBUTED = '" + Application::instance()->name() + "')";
   if (memcmp(pszDX_STATE,"DC",2) == 0 || (pszDX_STATE[1] >= '1' && pszDX_STATE[1] <= '9'))
   {
      bool b = updatePath(iDX_FILE_ID);
      if (!b)
         return false;
   }
   auto_ptr<Statement> pUpdateStatement((Statement*)DatabaseFactory::instance()->create("UpdateStatement"));
   return UseCase::setSuccess(pUpdateStatement->execute(hTable,strSearchCondition));
  //## end FileWriter::updateProgress%419CEA130251.body
}

bool FileWriter::updatePath (int iDX_FILE_ID)
{
  //## begin FileWriter::updatePath%63C7F2CB03AA.body preserve=yes
   if (m_strDX_PATH.empty())
      return true;
   Table hTable("DX_DATA_PATH");
   hTable.setQualifier("CUSTQUAL");
   hTable.set("DX_FILE_ID",iDX_FILE_ID,true);
   hTable.set("DX_FILE_TYPE",m_strDX_FILE_TYPE[1],false,true);
   hTable.set("DX_PATH",m_strDX_PATH,false,false);
   auto_ptr<Statement> pInsertStatement((Statement*)DatabaseFactory::instance()->create("InsertStatement"));
   if (pInsertStatement->execute(hTable) == false)
   {
      auto_ptr<Statement> pUpdateStatement((Statement*)DatabaseFactory::instance()->create("UpdateStatement"));
      if (!(pInsertStatement->getInfoIDNumber() == STS_DUPLICATE_RECORD
         && pUpdateStatement->execute(hTable)))
      {
         Database::instance()->rollback();
         return UseCase::setSuccess(false);
      }
   }
   return true;
  //## end FileWriter::updatePath%63C7F2CB03AA.body
}

// Additional Declarations
  //## begin FileWriter%419CCAB200DA.declarations preserve=yes
  //## end FileWriter%419CCAB200DA.declarations

//## begin module%419CCB660148.epilog preserve=yes
//## end module%419CCB660148.epilog
