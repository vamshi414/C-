//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%55BF7B800027.cm preserve=no
//## end module%55BF7B800027.cm

//## begin module%55BF7B800027.cp preserve=no
//	Copyright (c) 1997 - 2022
//	FIS
//## end module%55BF7B800027.cp

//## Module: CXOSNE02%55BF7B800027; Package body
//## Subsystem: NEDLL%55BF6ACC0235
//## Source file: C:\Repos\datanavigatorserver\Windows\Build\Dn\Server\Library\Nedll\CXOSNE02.cpp

//## begin module%55BF7B800027.additionalIncludes preserve=no
//## end module%55BF7B800027.additionalIncludes

//## begin module%55BF7B800027.includes preserve=yes
#include "CXODNE00.hpp"
#include "CXODRU28.hpp"
//## end module%55BF7B800027.includes

#ifndef CXOSIF16_h
#include "CXODIF16.hpp"
#endif
#ifndef CXOSRU10_h
#include "CXODRU10.hpp"
#endif
#ifndef CXOSDB01_h
#include "CXODDB01.hpp"
#endif
#ifndef CXOSDB02_h
#include "CXODDB02.hpp"
#endif
#ifndef CXOSIF15_h
#include "CXODIF15.hpp"
#endif
#ifndef CXOSRU11_h
#include "CXODRU11.hpp"
#endif
#ifndef CXOSRU12_h
#include "CXODRU12.hpp"
#endif
#ifndef CXOSES01_h
#include "CXODES01.hpp"
#endif
#ifndef CXOSES24_h
#include "CXODES24.hpp"
#endif
#ifndef CXOSES18_h
#include "CXODES18.hpp"
#endif
#ifndef CXOSRU34_h
#include "CXODRU34.hpp"
#endif
#ifndef CXOSRU07_h
#include "CXODRU07.hpp"
#endif
#ifndef CXOSTM04_h
#include "CXODTM04.hpp"
#endif
#ifndef CXOSES13_h
#include "CXODES13.hpp"
#endif
#ifndef CXOSES03_h
#include "CXODES03.hpp"
#endif
#ifndef CXOSDB24_h
#include "CXODDB24.hpp"
#endif
#ifndef CXOSRU08_h
#include "CXODRU08.hpp"
#endif
#ifndef CXOSEX01_h
#include "CXODEX01.hpp"
#endif
#ifndef CXOSTM06_h
#include "CXODTM06.hpp"
#endif
#ifndef CXOSRU19_h
#include "CXODRU19.hpp"
#endif
#ifndef CXOSMN05_h
#include "CXODMN05.hpp"
#endif
#ifndef CXOSNE02_h
#include "CXODNE02.hpp"
#endif
//## begin module%55BF7B800027.declarations preserve=no
//## end module%55BF7B800027.declarations

//## begin module%55BF7B800027.additionalDeclarations preserve=yes
//## end module%55BF7B800027.additionalDeclarations


//## Modelname: Transaction Research and Adjustments::NyceException_CAT%55BF69210380
namespace nyceexception {
//## begin nyceexception%55BF69210380.initialDeclarations preserve=yes
//## end nyceexception%55BF69210380.initialDeclarations

// Class nyceexception::NYCEExport 

NYCEExport::NYCEExport()
  //## begin NYCEExport::NYCEExport%55BF7B300314_const.hasinit preserve=no
      : m_iBATCHSEQNO(0)
  //## end NYCEExport::NYCEExport%55BF7B300314_const.hasinit
  //## begin NYCEExport::NYCEExport%55BF7B300314_const.initialization preserve=yes
  //## end NYCEExport::NYCEExport%55BF7B300314_const.initialization
{
  //## begin nyceexception::NYCEExport::NYCEExport%55BF7B300314_const.body preserve=yes
    memcpy(m_sID,"NE02",4);
    string strRecord;
    int i=0;
    vector<string> hTokens;
    while(IF::Extract::instance()->getRecord(i++,strRecord))
    {
       if(strRecord.length() > 16
          & strRecord.substr(0,16) == "DSPEC   NYCQUAL ")
       {
          if(Buffer::parse(strRecord," ",hTokens) > 4)
             m_hCustomer.insert(map<string,pair<string,string>,less<string> >::value_type(hTokens[2],make_pair(hTokens[3],hTokens[4])));
       }
       if(strRecord.length() >16
          & strRecord.substr(0,16) == "DSPEC   NYCLOGN1")
          m_strLOGONID1 = strRecord.substr(16,8);
       if(strRecord.length() >16
          & strRecord.substr(0,16) == "DSPEC   NYCLOGN2")
          m_strLOGONID2 = strRecord.substr(16,8);
       if(strRecord.length() >16
          & strRecord.substr(0,16) == "DSPEC   NYCRMTID")
          m_strREMOTEID = strRecord.substr(16,8);
       if(strRecord.length() >16
          & strRecord.substr(0,16) == "DSPEC   BATCHID ")
          m_strBATCHID = strRecord.substr(16,3);
       if(strRecord.length() >16
          & strRecord.substr(0,16) == "DSPEC   INSTID  ")
          m_strINSTID= strRecord.substr(16,11);
    }
    for(int i=0;i<=6;i++)
       m_lEXCEPTIONCOUNT[i]=0;
  //## end nyceexception::NYCEExport::NYCEExport%55BF7B300314_const.body
}


NYCEExport::~NYCEExport()
{
  //## begin nyceexception::NYCEExport::~NYCEExport%55BF7B300314_dest.body preserve=yes
   m_hCustomer.erase(m_hCustomer.begin(), m_hCustomer.end());
  //## end nyceexception::NYCEExport::~NYCEExport%55BF7B300314_dest.body
}



//## Other Operations (implementation)
bool NYCEExport::create ()
{
  //## begin nyceexception::NYCEExport::create%55C0AE2A01C6.body preserve=yes
   writeHeader(Clock::instance()->getYYYYMMDDHHMMSS());
   map<string,pair<string,string>,less<string> >::iterator pCustomer;
   for (pCustomer = m_hCustomer.begin();pCustomer != m_hCustomer.end();++pCustomer)
   {
      m_strCUST_ID = (*pCustomer).first;
      Transaction::instance()->setQualifier((*pCustomer).second.first);
      processExports();
      Transaction::instance()->commit();
   }
   if(m_hCustomer.empty())
   {
      processExports();
      Transaction::instance()->commit();
   }
   writeTrailer();
   return (Database::instance()->transactionState() == Database::COMMITREQUIRED);
  //## end nyceexception::NYCEExport::create%55C0AE2A01C6.body
}

void NYCEExport::processExports ()
{
  //## begin nyceexception::NYCEExport::processExports%55C0AE5A02EE.body preserve=yes
   m_strPROCESSDATE = getDATE_RECON() + "23595999";
   string StartDate = "0000000000000000";
   m_hQuery.reset();
   m_hQuery.attach(this);
   m_hQuery.bind("EMS_CASE_CONTEXT","CASE_ID",Column::LONG,&m_iCASE_ID);
   m_hQuery.bind("EMS_CASE_CONTEXT","TSTAMP_PHASE",Column::STRING,&m_strTSTAMP_PHASE);
   m_hQuery.setBasicPredicate("EMS_CASE_CONTEXT","CONTEXT_TYPE","=","EXPORT");
   m_hQuery.setBasicPredicate("EMS_CASE_CONTEXT","NET_ID","=","NYC");
   m_hQuery.setBasicPredicate("EMS_CASE_CONTEXT","PROCESSED_FLG","=","N");
   m_hQuery.setBasicPredicate("EMS_CASE_CONTEXT","TSTAMP_CREATED",">",StartDate.c_str());
   m_hQuery.setBasicPredicate("EMS_CASE_CONTEXT","TSTAMP_CREATED","<",m_strPROCESSDATE.c_str());
   m_hQuery.setOrderByClause("EMS_CASE_CONTEXT.TSTAMP_CREATED");
   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   if (!pSelectStatement->execute(m_hQuery) || m_hQuery.getAbort())
   {
      Console::display("ST205");
      return;
   }
  //## end nyceexception::NYCEExport::processExports%55C0AE5A02EE.body
}

bool NYCEExport::transitionCase (const string& strReqStatusNext, const string& strReqTypeNext)
{
  //## begin nyceexception::NYCEExport::transitionCase%566AD55E00E3.body preserve=yes
   CaseTransitionSegment::instance()->setREQUEST_TYPE_PREV(CaseSegment::instance()->getREQUEST_TYPE());
   CaseTransitionSegment::instance()->setSTATUS_PREV(CaseSegment::instance()->getSTATUS());
   if (strReqTypeNext.length() == 0)
      CaseTransitionSegment::instance()->setREQUEST_TYPE_NEXT(CaseSegment::instance()->getREQUEST_TYPE());
   else
      CaseTransitionSegment::instance()->setREQUEST_TYPE_NEXT(strReqTypeNext);
   CaseTransitionSegment::instance()->setSTATUS_NEXT(strReqStatusNext);
   CaseTransitionSegment::instance()->setSEQ_NO(0);
   CaseTransitionSegment::instance()->setMANUAL_OVERRIDE("N");
   CaseTransitionSegment::instance()->setUSER_ID("SYSTEM");
   if (Case::instance()->transition() != 0)
   {
      Console::display("ST131", CaseSegment::instance()->getCASE_NO().c_str(),strReqStatusNext.c_str(),m_strCUST_ID.data());
      return false;
   }
   return true;
  //## end nyceexception::NYCEExport::transitionCase%566AD55E00E3.body
}

void NYCEExport::update (Subject* pSubject)
{
  //## begin nyceexception::NYCEExport::update%55C0ADB300D6.body preserve=yes
   Query hQuery;
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_PHASE","CASE_ID");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_PHASE","TSTAMP_PHASE","TSTAMP_CREATED");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_CASE","CASE_ID");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_PHASE_NYC","CASE_ID");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_PHASE_NYC","TSTAMP_PHASE","TSTAMP_CREATED");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_TRANSITION","CASE_ID");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_TRANSITION","TSTAMP_PHASE","PHASE_TSTAMP");
   hQuery.join("EMS_CASE_CONTEXT","INNER","EMS_CASE_NYC","CASE_ID");
   CaseSegment::instance()->bind(hQuery);
   CasePhaseSegment::instance()->bind(hQuery);
   CasePhaseNyceSegment::instance()->bind(hQuery);
   CaseTransitionSegment::instance()->bind(hQuery);
   CaseNyceSegment::instance()->bind(hQuery);
   hQuery.setBasicPredicate("EMS_CASE","CASE_ID","=",m_iCASE_ID);
   hQuery.setBasicPredicate("EMS_PHASE","TSTAMP_CREATED","=",m_strTSTAMP_PHASE.c_str());
   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   pSelectStatement->execute(hQuery);
   if (pSelectStatement->getRows() == 0)
   {
         Console::display("ST205");
         return;
   }
   struct segExceptionDetail* pBuffer = (struct segExceptionDetail*)(char*)getDATA_BUFFER();
   memset(pBuffer,' ',sizeof(struct segExceptionDetail));
   //m_siSEQ_NO++;
   m_iBATCHSEQNO++;
   char szBuffer[PERCENTF];
   char* pztemp;
   char BATCHSEQNO;
   memcpy(pBuffer->sMsgType,"DTL",3);
   memcpy(pBuffer->sBatchSeqNo,szBuffer,snprintf(szBuffer,sizeof(szBuffer),"%05d",m_iBATCHSEQNO));
   memcpy(pBuffer->sVersion,"4",1);
   pBuffer->cNetwork = 'N';
   string strExceptionType = CasePhaseNyceSegment::instance()->getEXCEPTION_TYPE();
   if (CaseSegment::instance()->getSTATUS() == "REVF")
      strExceptionType.append("R");
   if (CaseSegment::instance()->getREQUEST_TYPE() == "ADJG" && (CaseSegment::instance()->getSTATUS() == "ACPF" ||
       CaseSegment::instance()->getSTATUS() == "DNYF"))
      strExceptionType.append("D");
   memcpy(pBuffer->sExceptionType,strExceptionType.data(),strExceptionType.length());
   pBuffer->cIssAcqFlag = CasePhaseSegment::instance()->getUSER_ROLE()[0];
   if (!CasePhaseNyceSegment::instance()->getNYCE_CASE_NO().empty())
      memcpy(pBuffer->sTraceNumber, CasePhaseNyceSegment::instance()->getNYCE_CASE_NO().data(), CasePhaseNyceSegment::instance()->getNYCE_CASE_NO().length());
   else
   {
      if (CasePhaseSegment::instance()->getUSER_ROLE() == "I")
      {
         memcpy(pBuffer->sPan, CaseSegment::instance()->getPAN().data(), CaseSegment::instance()->getPAN().length());
         memcpy(pBuffer->sAccount1, CaseSegment::instance()->getACCT_ID_1().data(), CaseSegment::instance()->getACCT_ID_1().length());
         pBuffer->cIssCred = 'Y';
      }
      else
         pBuffer->cIssCred = 'N';
      memcpy(pBuffer->sSwitchTermId,CaseNyceSegment::instance()->getNYCE_TERM_ID().data(),CaseNyceSegment::instance()->getNYCE_TERM_ID().length());
      memcpy(pBuffer->sAcqTermId,CaseSegment::instance()->getCARD_ACPT_TERM_ID().data(),CaseSegment::instance()->getCARD_ACPT_TERM_ID().length());
      string strDate = CaseSegment::instance()->getTSTAMP_LOCAL().c_str();
      Date hDate(strDate.c_str());
      memcpy(pBuffer->sLocalDate,hDate.asString("%m%d%y").data(),CaseSegment::instance()->getTSTAMP_LOCAL().length());
      memcpy(pBuffer->sLocalTime,CaseSegment::instance()->getTSTAMP_LOCAL().substr(8,13).data(),CaseSegment::instance()->getTSTAMP_LOCAL().substr(8,13).length());
      memcpy(pBuffer->sLocalSeq,CaseSegment::instance()->getRETRIEVAL_REF_NO().data(),CaseSegment::instance()->getRETRIEVAL_REF_NO().length());
   }
   string strActualAmount;
   double dAMT_ADJUSTMENT = CasePhaseSegment::instance()->getAMT_ADJUSTMENT();
   if (CaseSegment::instance()->getTRAN_TYPE_ID().length() && CaseSegment::instance()->getTRAN_TYPE_ID().substr(0, 2) != "21")  //Deposit
   {
      if (dAMT_ADJUSTMENT == CaseSegment::instance()->getAMT_TRAN() + CaseSegment::instance()->getAMT_SURCHARGE_FEE())  //full
      {
         dAMT_ADJUSTMENT -= CaseSegment::instance()->getAMT_SURCHARGE_FEE();
         memcpy(pBuffer->sActualSurch, "     0.00", 9);
      }
      else
      {
         string strAMT_SURCHARGE_FEE = CurrencyCode::instance()->formatAmount(CaseSegment::instance()->getAMT_SURCHARGE_FEE(), (CaseSegment::instance()->getCUR_SURCHARGE_FEE().length() > 0 ? CaseSegment::instance()->getCUR_SURCHARGE_FEE() : CaseSegment::instance()->getCUR_RECON_NET()), 9, false);
         memcpy(pBuffer->sActualSurch, strAMT_SURCHARGE_FEE.data(), strAMT_SURCHARGE_FEE.length());
      }
      if (CasePhaseSegment::instance()->getACTION_TO_CARDHLDR() == "C")
         strActualAmount = CurrencyCode::instance()->formatAmount((CaseSegment::instance()->getAMT_TRAN() - dAMT_ADJUSTMENT), CaseSegment::instance()->getCUR_TRAN(), 13, false);
      else
         strActualAmount = CurrencyCode::instance()->formatAmount((CaseSegment::instance()->getAMT_TRAN() + dAMT_ADJUSTMENT), CaseSegment::instance()->getCUR_TRAN(), 13, false);
   }
   else
   {
      if (CasePhaseSegment::instance()->getACTION_TO_CARDHLDR() == "C")
         strActualAmount = CurrencyCode::instance()->formatAmount((CaseSegment::instance()->getAMT_TRAN() + dAMT_ADJUSTMENT), CaseSegment::instance()->getCUR_TRAN(), 13, false);
      else
         strActualAmount = CurrencyCode::instance()->formatAmount((CaseSegment::instance()->getAMT_TRAN() - dAMT_ADJUSTMENT), CaseSegment::instance()->getCUR_TRAN(), 13, false);
      string strAMT_SURCHARGE_FEE = CurrencyCode::instance()->formatAmount(CaseSegment::instance()->getAMT_SURCHARGE_FEE(), (CaseSegment::instance()->getCUR_SURCHARGE_FEE().length() > 0 ? CaseSegment::instance()->getCUR_SURCHARGE_FEE() : CaseSegment::instance()->getCUR_RECON_NET()), 9, false);
      memcpy(pBuffer->sActualSurch, strAMT_SURCHARGE_FEE.data(), strAMT_SURCHARGE_FEE.length());
   }
   memcpy(pBuffer->sActualAmt, strActualAmount.data(), strActualAmount.length());
   if (CaseSegment::instance()->getREQUEST_TYPE() == "ADJG" && (CaseSegment::instance()->getSTATUS() == "ACPF" ||
       CaseSegment::instance()->getSTATUS() == "DNYF"))
       memcpy(pBuffer->sRespCode,CasePhaseSegment::instance()->getREASON_CODE().data(),CasePhaseSegment::instance()->getREASON_CODE().length());
   else
      memcpy(pBuffer->sReasonCode,CasePhaseSegment::instance()->getREASON_CODE().data(),CasePhaseSegment::instance()->getREASON_CODE().length());
   memcpy(pBuffer->sReqContact,CasePhaseSegment::instance()->getREQ_CONTACT_NAME().data(),CasePhaseSegment::instance()->getREQ_CONTACT_NAME().length());
   memcpy(pBuffer->sReqPhone,CasePhaseSegment::instance()->getREQ_CONTACT_PHONE().data(),CasePhaseSegment::instance()->getREQ_CONTACT_PHONE().length());
   memcpy(pBuffer->sReqFax,CasePhaseSegment::instance()->getREQ_CONTACT_FAX().data(),CasePhaseSegment::instance()->getREQ_CONTACT_FAX().length());
   memcpy(pBuffer->sRecContact,CasePhaseSegment::instance()->getREC_CONTACT_NAME().data(),CasePhaseSegment::instance()->getREC_CONTACT_NAME().length());
   memcpy(pBuffer->sRecPhone,CasePhaseSegment::instance()->getREC_CONTACT_PHONE().data(),CasePhaseSegment::instance()->getREC_CONTACT_PHONE().length());
   memcpy(pBuffer->sRecFax,CasePhaseSegment::instance()->getREC_CONTACT_FAX().data(),CasePhaseSegment::instance()->getREC_CONTACT_FAX().length());
   memcpy(pBuffer->sText,CasePhaseNyceSegment::instance()->getNYC_MMT().data(),CasePhaseNyceSegment::instance()->getNYC_MMT().length());

   if (!setDOC_PATH())
        return;
   memcpy(pBuffer->sExcpDocFileName,m_strFILE_NAME.data(),m_strFILE_NAME.length());

   if (CaseSegment::instance()->getSTATUS() == "REP1")
   {
      if (!updateExportInd())
         return;
   }

   if(CaseSegment::instance()->getSTATUS() =="FWRD")
   {
      if(!transitionCase("PNDR"))
         return;
   }
   else if (CaseSegment::instance()->getSTATUS() == "REVF")
   {
      if (!transitionCase("REVP"))
         return;
   }
   else if(CaseSegment::instance()->getSTATUS() == "ACPF")
   {
      if (!transitionCase("REVP"))
         return;
   }
   else if(CaseSegment::instance()->getSTATUS() == "DNYF")
   {
      if (!transitionCase("DNYP"))
         return;
   }
   Table hTable("EMS_CASE_CONTEXT");
   hTable.set("CASE_ID",m_iCASE_ID,true);
   hTable.set("PROCESSED_FLG","Y");
   hTable.set("TSTAMP_UPDATED",Clock::instance()->getYYYYMMDDHHMMSSHN());
   auto_ptr<Statement> pUpdateStatement((Statement*)DatabaseFactory::instance()->create("UpdateStatement"));
   if (!pUpdateStatement->execute(hTable))
   {
      Database::instance()->rollback();
      return;
   }
   writeLine(636);
   char szREQUEST_TYPE[20]={"ADJCHBREPCRDFREFDR"};
   string strRequestType = CaseSegment::instance()->getREQUEST_TYPE().substr(0,3);
   char* p = strstr(szREQUEST_TYPE,strRequestType.c_str());
   m_lEXCEPTIONCOUNT[(p-szREQUEST_TYPE)/3]++;
  //## end nyceexception::NYCEExport::update%55C0ADB300D6.body
}

bool NYCEExport::writeHeader (string strFileDate)
{
  //## begin nyceexception::NYCEExport::writeHeader%55C0AD43011F.body preserve=yes
   struct segExceptionHeader* pHeader = (struct segExceptionHeader*)(char*)getDATA_BUFFER();
   memset(pHeader,' ',sizeof(struct segExceptionHeader));
   memcpy(pHeader->sMsgType,"HDR",3);
   memcpy(pHeader->sInstID,m_strINSTID.data(),m_strINSTID.length());
   memcpy(pHeader->sLogonID1,m_strLOGONID1.data(),m_strLOGONID1.length());
   memcpy(pHeader->sLogonID2,m_strLOGONID2.data(),m_strLOGONID2.length());
   memcpy(pHeader->sRemoteID,m_strREMOTEID.data(),m_strREMOTEID.length());
   memcpy(pHeader->sApplID,"TES",3);
   if(m_strBATCHID.length() == 0)
      memcpy(pHeader->sBatchID,"001",3);
   else
      memcpy(pHeader->sBatchID,m_strBATCHID.data(),m_strBATCHID.length());
   string strDate = Clock::instance()->getYYYYMMDDHHMMSSHN();
   Date hDate(strDate.c_str());
   strDate = hDate.asString("%m%d%y");
   memcpy(pHeader->sDate,strDate.data(),strDate.length());
   memcpy(pHeader->sSetlDate, strDate.data(), strDate.length());
   writeLine(sizeof(struct segExceptionHeader));
   return true;
  //## end nyceexception::NYCEExport::writeHeader%55C0AD43011F.body
}

bool NYCEExport::writeLine (int iDATA_BUFFER)
{
  //## begin nyceexception::NYCEExport::writeLine%55C0AE04023A.body preserve=yes
   char* p = (char*)getDATA_BUFFER();
   write (iDATA_BUFFER,-1,false,false);
   return true;
  //## end nyceexception::NYCEExport::writeLine%55C0AE04023A.body
}

bool NYCEExport::writeTrailer ()
{
  //## begin nyceexception::NYCEExport::writeTrailer%55C0AD90039F.body preserve=yes
   struct segExceptionTrailer* pTrailer = (struct segExceptionTrailer*)(char*)getDATA_BUFFER();
   memset(pTrailer,' ',sizeof(segExceptionTrailer));
   char szTemp[PERCENTD];
   memcpy(pTrailer->sMsgType,"TRL",3);
   memcpy(pTrailer->sInstID,m_strINSTID.data(),m_strINSTID.length());
   if(m_strBATCHID.length() == 0)
      memcpy(pTrailer->sBatchID,"001",3);
   else
      memcpy(pTrailer->sBatchID,m_strBATCHID.data(),m_strBATCHID.length());
   string strDate = Clock::instance()->getYYYYMMDDHHMMSSHN();
   Date hDate(strDate.c_str());
   strDate = hDate.asString("%m%d%y");
   memcpy(pTrailer->sDate,strDate.data(),strDate.length());
   Date hSettleDate (getDATE_RECON().c_str());
   string strSettleDate = hSettleDate.asString("%m%d%y");
   memcpy(pTrailer->sSetlDate,strSettleDate.data(),strSettleDate.length());
   memcpy(pTrailer->sAdjCount,szTemp,snprintf(szTemp,sizeof(szTemp),"%07d",m_lEXCEPTIONCOUNT[0]));
   memcpy(pTrailer->sCBCount,szTemp,snprintf(szTemp,sizeof(szTemp),"%07d",m_lEXCEPTIONCOUNT[1]));
   memcpy(pTrailer->sRepCount,szTemp,snprintf(szTemp,sizeof(szTemp),"%07d",m_lEXCEPTIONCOUNT[2]));
   memcpy(pTrailer->sFreCount,szTemp,snprintf(szTemp,sizeof(szTemp),"%07d",m_lEXCEPTIONCOUNT[3]));
   memcpy(pTrailer->sFRCount,szTemp,snprintf(szTemp,sizeof(szTemp),"%07d",m_lEXCEPTIONCOUNT[4]));
   writeLine(sizeof(struct segExceptionTrailer));
   return true;
  //## end nyceexception::NYCEExport::writeTrailer%55C0AD90039F.body
}

bool NYCEExport::updateExportInd()
{
   if (m_strEXPORT_IND == "R")
   {
      Table hTable("EMS_DOCUMENT");
      hTable.set("CASE_ID", CaseSegment::instance()->getCASE_ID(), true);
      hTable.set("SEQ_NO", m_siSEQ_NO, true);
      hTable.set("EXPORT_IND", "S", false, false);
      SearchCondition hSearchCondition;
      hSearchCondition.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
      hSearchCondition.setBasicPredicate("EMS_DOCUMENT", "DELETE_FLG", "=", "N");
      hSearchCondition.setBasicPredicate("EMS_DOCUMENT", "EXPORT_IND", "=", "X");
      auto_ptr<Statement> pUpdateStatement((Statement*)DatabaseFactory::instance()->create("UpdateStatement"));
      if (!pUpdateStatement->execute(hTable, hSearchCondition.getText()))
         return false;
   }

}

bool NYCEExport::setDOC_PATH ()
{
  //## begin nyceexception::NYCEExport::setDOC_PATH%65D201B70161.body preserve=yes
   Query hQuery;
   short iSEQ_NO = 0;
   short iNull = -1;
   Query hSubQuery;

   hSubQuery.setSubSelect(true);
   hSubQuery.bind("EMS_DOCUMENT", "SEQ_NO", Column::SHORT, &m_siSEQ_NO, &iNull, "MAX");
   hSubQuery.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
   auto_ptr<FormatSelectVisitor> pFormatSelectVisitor((FormatSelectVisitor*)DatabaseFactory::instance()->create("FormatSelectVisitor"));
   hSubQuery.accept(*pFormatSelectVisitor);
   string strSubQuery = "(" + pFormatSelectVisitor->SQLText() + ")";
   hQuery.bind("EMS_DOCUMENT", "DOC_PATH", Column::STRING, &m_strFILE_NAME);
   hQuery.bind("EMS_DOCUMENT", "EXPORT_IND", Column::STRING, &m_strEXPORT_IND);
   hQuery.bind("EMS_DOCUMENT", "SEQ_NO", Column::SHORT, &m_siSEQ_NO);
   hQuery.setBasicPredicate("EMS_DOCUMENT", "CASE_ID", "=", CaseSegment::instance()->getCASE_ID());
   hQuery.setBasicPredicate("EMS_DOCUMENT", "SEQ_NO", "IN", strSubQuery.c_str());

   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   if (!pSelectStatement->execute(hQuery))
      return false;

   size_t pos = m_strFILE_NAME.find_last_of("\\");
   if (pos == string::npos)
      pos = m_strFILE_NAME.find_last_of("//");
   if (pos != string::npos)
      m_strFILE_NAME = m_strFILE_NAME.substr(pos + 1, string::npos);
   return true;
  //## end nyceexception::NYCEExport::setDOC_PATH%65D201B70161.body
}

// Additional Declarations
  //## begin nyceexception::NYCEExport%55BF7B300314.declarations preserve=yes
  //## end nyceexception::NYCEExport%55BF7B300314.declarations

} // namespace nyceexception

//## begin module%55BF7B800027.epilog preserve=yes
//## end module%55BF7B800027.epilog
