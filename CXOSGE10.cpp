//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%4AE9FBEC000F.cm preserve=no
//	$Date:   Apr 08 2021 15:22:52  $ $Author:   e5549623  $
//	$Revision:   1.27.1.12.2.1.1.0  $
//## end module%4AE9FBEC000F.cm

//## begin module%4AE9FBEC000F.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%4AE9FBEC000F.cp

//## Module: CXOSGE10%4AE9FBEC000F; Package body
//## Subsystem: GEDLL%4ADF1BD6035B
//## Source file: C:\bV02.5B.R001\Windows\Build\Dn\Server\Library\Gedll\CXOSGE10.cpp

//## begin module%4AE9FBEC000F.additionalIncludes preserve=no
//## end module%4AE9FBEC000F.additionalIncludes

//## begin module%4AE9FBEC000F.includes preserve=yes
#include "CXODIF03.hpp"
#include "CXODRS66.hpp"
#include "CXODBS06.hpp"
#include "CXODRU10.hpp"
#include "CXODES66.hpp"
#include "CXODRU54.hpp"
#include "CXODDB10.hpp"
#include "CXODIF16.hpp"
//## end module%4AE9FBEC000F.includes

#ifndef CXOSES01_h
#include "CXODES01.hpp"
#endif
#ifndef CXOSTM06_h
#include "CXODTM06.hpp"
#endif
#ifndef CXOSMN05_h
#include "CXODMN05.hpp"
#endif
#ifndef CXOSIF16_h
#include "CXODIF16.hpp"
#endif
#ifndef CXOSES18_h
#include "CXODES18.hpp"
#endif
#ifndef CXOSES34_h
#include "CXODES34.hpp"
#endif
#ifndef CXOSEX01_h
#include "CXODEX01.hpp"
#endif
#ifndef CXOSGE02_h
#include "CXODGE02.hpp"
#endif
#ifndef CXOSUC16_h
#include "CXODUC16.hpp"
#endif
#ifndef CXOSRU20_h
#include "CXODRU20.hpp"
#endif
#ifndef CXOSDB02_h
#include "CXODDB02.hpp"
#endif
#ifndef CXOSRU12_h
#include "CXODRU12.hpp"
#endif
#ifndef CXOSES60_h
#include "CXODES60.hpp"
#endif
#ifndef CXOSES73_h
#include "CXODES73.hpp"
#endif
#ifndef CXOSES67_h
#include "CXODES67.hpp"
#endif
#ifndef CXOSRS70_h
#include "CXODRS70.hpp"
#endif
#ifndef CXOSRS40_h
#include "CXODRS40.hpp"
#endif
#ifndef CXOSRS95_h
#include "CXODRS95.hpp"
#endif
#ifndef CXOSBC36_h
#include "CXODBC36.hpp"
#endif
#ifndef CXOSGE52_h
#include "CXODGE52.hpp"
#endif
#ifndef CXOSGE10_h
#include "CXODGE10.hpp"
#endif


//## begin module%4AE9FBEC000F.declarations preserve=no
//## end module%4AE9FBEC000F.declarations

//## begin module%4AE9FBEC000F.additionalDeclarations preserve=yes
//## end module%4AE9FBEC000F.additionalDeclarations


//## Modelname: Transaction Research and Adjustments::GenericException_CAT%4ADF1B4C003E
namespace genericexception {
//## begin genericexception%4ADF1B4C003E.initialDeclarations preserve=yes
//## end genericexception%4ADF1B4C003E.initialDeclarations

// Class genericexception::Transaction 

//## begin genericexception::Transaction::Instance%4AE9FDEB02AF.attr preserve=no  private: static genericexception::Transaction* {V} 0
genericexception::Transaction* Transaction::m_pInstance = 0;
//## end genericexception::Transaction::Instance%4AE9FDEB02AF.attr

Transaction::Transaction()
  //## begin Transaction::Transaction%4AE9FB8A034B_const.hasinit preserve=no
  //## end Transaction::Transaction%4AE9FB8A034B_const.hasinit
  //## begin Transaction::Transaction%4AE9FB8A034B_const.initialization preserve=yes
  //## end Transaction::Transaction%4AE9FB8A034B_const.initialization
{
  //## begin genericexception::Transaction::Transaction%4AE9FB8A034B_const.body preserve=yes
   memcpy(m_sID,"GE10",4);
  //## end genericexception::Transaction::Transaction%4AE9FB8A034B_const.body
}


Transaction::~Transaction()
{
  //## begin genericexception::Transaction::~Transaction%4AE9FB8A034B_dest.body preserve=yes
  //## end genericexception::Transaction::~Transaction%4AE9FB8A034B_dest.body
}



//## Other Operations (implementation)
int Transaction::find ()
{
  //## begin genericexception::Transaction::find%4AE9FBA603D8.body preserve=yes
   bool bIncludeRetRefNo(false);
   bool bIncludeSysTraceAuditNo(false);
   bool bIncludeAmt(true);
   if (!CaseSegment::instance()->getRETRIEVAL_REF_NO().empty())
      bIncludeRetRefNo = true;
   if (IF::Extract::instance()->getCustomCode() != "NPCI")
   {
      if (CaseSegment::instance()->getSYS_TRACE_AUDIT_NO().empty())
      {
         if (CaseSegment::instance()->getCASE_EXTENSION() == "VNT" && CaseNationalNetworkSegment::instance()->getACQ_REF_NO().length() > 21)
         {
            bIncludeSysTraceAuditNo = true;
            string strSYS_TRACE_AUDIT_NO;
            if (IF::Extract::instance()->getCustomCode() == "REGIONS") 
               strSYS_TRACE_AUDIT_NO = "0"+
                  CaseNationalNetworkSegment::instance()->getACQ_REF_NO().substr(17,5);
            else
               strSYS_TRACE_AUDIT_NO.assign(CaseNationalNetworkSegment::instance()->getACQ_REF_NO().data(),16,6);
            CaseSegment::instance()->setSYS_TRACE_AUDIT_NO(strSYS_TRACE_AUDIT_NO); 
         }
      }
      else 
         bIncludeSysTraceAuditNo = true;
   }
   if (CaseManifestSegment::instance()->getFile() == "ISIARC")
      bIncludeAmt = CaseSegment::instance()->getAMT_RECON_NET() > 0;
   else
      bIncludeAmt = CaseSegment::instance()->getAMT_TRAN() > 0;
   if (CaseManifestSegment::instance()->getFile() == "DNRDM5")
   {
      string strTemp;
      CaseManifest::instance()->get("User Id",strTemp);
      CommonHeaderSegment::instance()->setUserID(strTemp);
      CommonHeaderSegment::instance()->setCUST_ID(reusable::Transaction::instance()->getCustomer());
   }
   bool bReturn = false;
   string strMemberRole;
   CaseManifest::instance()->get("CaseManifest memberRole",strMemberRole);
   if (strMemberRole == "A" 
      && CaseManifestSegment::instance()->getFile() == "VRRDM5")
   {
      bReturn = retrieveVisaAcqTransaction();
   }
   else
   {
      bReturn = retrieveTransaction(
         CasePhaseSegment::instance()->getUSER_ROLE(),
         bIncludeRetRefNo, bIncludeSysTraceAuditNo, bIncludeAmt);
   }
   if (bReturn)
   {
      if (CaseManifestSegment::instance()->getFile() == "DNRDM5"
         || CaseManifestSegment::instance()->getFile() == "VRRDM5")
         CaseSegment::instance()->setCaseSource("X");
      else
         CaseSegment::instance()->setCaseSource("I");
      CreditSegment::instance()->setFinancialData();
      CasePhaseSegment::instance()->setFinancialData();
      if (CaseIntegratedCircuitCardSegment::instance()->presence())
         CaseIntegratedCircuitCardSegment::instance()->setFinancialData();
      return 1;
   }
   else
      FinancialBaseSegment::instance()->setPresence(false);
   CaseSegment::instance()->setINST_ID_RECON_ACQ(CaseSegment::instance()->getINST_ID_ACQ());
   CaseSegment::instance()->setINST_ID_RECON_ISS(CaseSegment::instance()->getINST_ID_ISS());
   return 0;  
  //## end genericexception::Transaction::find%4AE9FBA603D8.body
}

Transaction* Transaction::instance ()
{
  //## begin genericexception::Transaction::instance%4AE9FE0800FA.body preserve=yes
   if (!m_pInstance)
      m_pInstance = new Transaction;
   return m_pInstance;
  //## end genericexception::Transaction::instance%4AE9FE0800FA.body
}

void Transaction::reset ()
{
  //## begin genericexception::Transaction::reset%4AEA01DE004E.body preserve=yes
  //## end genericexception::Transaction::reset%4AEA01DE004E.body
}

bool Transaction::retrieveTransaction (const string& strUserRole, bool bIncludeRetRefNo, bool bIncludeSysTraceAuditNo, bool bIncludeAmount)
{
  //## begin genericexception::Transaction::retrieveTransaction%54E5F8B0039A.body preserve=yes
   Trace::put("in GE retrievetran");
   QueryAide hQueryAide;
   Row hRow;
   Query hQuery(2);
   hQuery.attach(this);
   auto_ptr<SelectStatement>pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));
   auto_ptr<DatabaseCatalog> pDatabaseCatalog((DatabaseCatalog*)DatabaseFactory::instance()->create("DatabaseCatalog"));

   FinancialBaseSegment::instance()->reset();
   string strBegin("000000");
   string strEnd("000000");
   string strValue;
   double dAMT_RECON_NET = 0;
   bool bReturn = true;
   if (CaseSegment::instance()->getTSTAMP_TRANS().length() == 16)
   {
      if (bReturn)
      {
         if (!ems::Case::instance()->findLocator(CaseSegment::instance()->getTSTAMP_TRANS().substr(0, 6), strBegin, strEnd))
            return false;
      }
      string strLocator("FIN_L" + CaseSegment::instance()->getTSTAMP_TRANS().substr(0, 6) + " FIN_L");
      string strICCLocator("FIN_ICC" + CaseSegment::instance()->getTSTAMP_TRANS().substr(0, 6) + " FIN_ICC");
      string strFIN_PAYLocator("FIN_PAYMENT" + CaseSegment::instance()->getTSTAMP_TRANS().substr(0, 6) + " FIN_PAYMENT");
      hQuery.join(strLocator.c_str(), "LEFT OUTER", strICCLocator.c_str(), "TSTAMP_TRANS");
      hQuery.join(strLocator.c_str(), "LEFT OUTER", strICCLocator.c_str(), "UNIQUENESS_KEY");
      hQuery.join(strLocator.c_str(), "LEFT OUTER", strFIN_PAYLocator.c_str(), "TSTAMP_TRANS");
      hQuery.join(strLocator.c_str(), "LEFT OUTER", strFIN_PAYLocator.c_str(), "UNIQUENESS_KEY");
      hQuery.join(strLocator.c_str(), "LEFT OUTER", "FIN_RECORD R", "TSTAMP_TRANS");
      hQuery.join(strLocator.c_str(), "LEFT OUTER", "FIN_RECORD R", "UNIQUENESS_KEY");
      IntegratedCircuitCardSegment::instance()->bind(hQuery);
      FinancialBaseSegment::instance()->bind(hQuery, strLocator.c_str());
      FinancialSettlementSegment::instance()->bind(hQuery);
      FinancialUserSegment::instance()->bind(hQuery);
      FinancialAdjustmentSegment::instance()->bind(hQuery);
      FinancialPaymentSegment::instance()->bind(hQuery);
      hQuery.setBasicPredicate(strLocator.c_str(), "TSTAMP_TRANS", "=", CaseSegment::instance()->getTSTAMP_TRANS().c_str());
      hQuery.setBasicPredicate(strLocator.c_str(), "UNIQUENESS_KEY", "=", (int)CaseSegment::instance()->getUNIQUENESS_KEY());
      if (CaseManifestSegment::instance()->getFile() == "DNBXML")
      {
         hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "<>", "208");
         if (CaseSegment::instance()->getCASE_TYPE_IND() != "D")
            hQuery.setBasicPredicate(strLocator.c_str(), "FIN_TYPE", "NOT LIKE", "__1");
         hQuery.getSearchCondition().append(" AND ");
         hQuery.getSearchCondition().append("(");
         if (strUserRole == "A")
         {
            hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "LIKE", "1%");
            hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "LIKE", "2%", false, false);
         }
         else
         {
            hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "NOT LIKE", "1%");
         }
         hQuery.getSearchCondition().append(")");
      }
#ifdef MVS
      if (hQueryAide.execute(hQuery, pSelectStatement.get(), &hRow) == false)
         return false;
#else
      if (!pSelectStatement->execute(hQuery))
         return false;
#endif
      if (pSelectStatement->getRows() != 0)
      {
         CaseSegment::instance()->setFinancialData();
         Trace::put("Found an exactly matching financial transaction.");
         return true;
      }
      return false;
   }
   else if (CaseSegment::instance()->getTSTAMP_LOCAL().length() >= 8)
   {
      string strFIN_TYPE;
      if (bReturn)
      {
         if (!ems::Case::instance()->findLocator("", strBegin, strEnd))
            return false;
      }
      //if previous day month is less than min locator table
      //search between currenday & next day
      //otherwise search between previous day & next day
      string strTransmissionDate;
      Date hDate(CaseSegment::instance()->getTSTAMP_LOCAL().c_str());
      hDate -= 1;
      string strBeginDateTime(hDate.asString("%Y%m%d000000"));
      string strSingleTranDate;
      bool bTranDate = genericexception::CaseManifest::instance()->get("SingleTranDate",strSingleTranDate);
      if (bReturn && !bTranDate)
      {
         if (strBeginDateTime.substr(0, 6) < strBegin)
         {
            hDate += 1;
            strBeginDateTime = hDate.asString("%Y%m%d000000");
            hDate += 4;
         }
         else
            hDate += 5;
      }
      string strEndDateTime(hDate.asString("%Y%m%d235959"));
      string strDateTime("'");
      strDateTime += strBeginDateTime;
      strDateTime += "' AND '";
      strDateTime += strEndDateTime;
      strDateTime += "'";
      string strLocatorDate(strBeginDateTime);
      if (CaseManifest::instance()->get("TransmissionDate", strTransmissionDate))
      {
         size_t pos = string::npos;
         while ((pos = strTransmissionDate.find('-')) != string::npos)
            strTransmissionDate.erase(pos, 1);
         if (strTransmissionDate.length() >= 6 )
            strLocatorDate = strTransmissionDate;
      }
      for (;;)
      {
         string strLocator("FIN_L" + strLocatorDate.substr(0, 6) + " FIN_L");
         string strICCLocator("FIN_ICC" + strLocatorDate.substr(0, 6) + " FIN_ICC");
         string strFIN_PAYLocator("FIN_PAYMENT" + strLocatorDate.substr(0, 6) + " FIN_PAYMENT");
         hQuery.bind(strLocator.c_str(), "FIN_TYPE", Column::STRING, &strFIN_TYPE);
         hQuery.join(strLocator.c_str(), "INNER", "FIN_RECORD R", "TSTAMP_TRANS");
         hQuery.join(strLocator.c_str(), "INNER", "FIN_RECORD R", "UNIQUENESS_KEY");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", strICCLocator.c_str(), "TSTAMP_TRANS");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", strICCLocator.c_str(), "UNIQUENESS_KEY");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", strFIN_PAYLocator.c_str(), "TSTAMP_TRANS");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", strFIN_PAYLocator.c_str(), "UNIQUENESS_KEY");
         if (IF::Extract::instance()->getCustomCode(1) == "PYPL"
            && (CaseSegment::instance()->getCASE_EXTENSION() == "MCI"
               || CaseSegment::instance()->getCASE_EXTENSION() == "VNT"))
         {
            string strFIN_STATE("FIN_STATEyyyymm");
            strFIN_STATE.replace(9, 6, strLocatorDate.substr(0, 6).c_str(), 6);
            if (pDatabaseCatalog->isExisting(strFIN_STATE))
            {
               hQuery.join(strLocator.c_str(), "INNER", strFIN_STATE.c_str(), "TSTAMP_TRANS");
               hQuery.join(strLocator.c_str(), "INNER", strFIN_STATE.c_str(), "UNIQUENESS_KEY");
               hQuery.setBasicPredicate(strFIN_STATE.c_str(), "NETWORK_STATE", "IN", "('F','U')");
            }
         }
         FinancialBaseSegment::instance()->bind(hQuery, strLocator.c_str());
         FinancialSettlementSegment::instance()->bind(hQuery);
         FinancialUserSegment::instance()->bind(hQuery);
         FinancialAdjustmentSegment::instance()->bind(hQuery);
         FinancialPaymentSegment::instance()->bind(hQuery);
         IntegratedCircuitCardSegment::instance()->bind(hQuery);
         string strTemp;
         if ((CaseManifestSegment::instance()->getFile() == "DNRDM5" 
         || CaseManifestSegment::instance()->getFile() == "EMSSHT" 
         || CaseManifestSegment::instance() ->getFile() == "DNBXML"
         || CaseManifestSegment::instance()->getFile() == "EFTPOS")
         && (CaseSegment::instance()->getPAN_PREFIX().length() 
         && CaseSegment::instance()->getPAN_SUFFIX().length()))
         {
            if (CaseManifest::instance()->get("AccountNumberPrefixExtn", strTemp))
               hQuery.setBasicPredicate(strLocator.c_str(), "PAN_PREFIX", "=", strTemp.c_str());
            else
            {
               string strPanPrefix = CaseSegment::instance()->getPAN_PREFIX();
               strTemp = "'";
               strTemp += strPanPrefix;
               strTemp += "' AND '";
               if (strPanPrefix.length() < 8)
                  strPanPrefix.resize(8, '9');
               strTemp += strPanPrefix;
               strTemp += "'";
               hQuery.setBasicPredicate(strLocator.c_str(), "PAN_PREFIX", "BETWEEN", strTemp.c_str());
            }
            hQuery.setBasicPredicate(strLocator.c_str(), "PAN_SUFFIX", "=", CaseSegment::instance()->getPAN_SUFFIX().c_str());
         }
         else if (CaseSegment::instance()->getPAN().length())
            hQuery.setBasicPredicate(strLocator.c_str(), "PAN", "=", CaseSegment::instance()->getPAN().c_str());
         if (CaseManifest::instance()->get("Token", strTemp) && strTemp.empty() == false )
         {
            hQuery.setBasicPredicate(strLocator.c_str(), "PAN", "=", strTemp.c_str(), false, false);
         }
         if (CaseManifestSegment::instance()->getFile() == "ISIARC")
         {
            hQuery.setBasicPredicate(strLocator.c_str(),"FIN_TYPE","<>","080");
            if (bIncludeSysTraceAuditNo)
               hQuery.setBasicPredicate(strLocator.c_str(),"SYS_TRACE_AUDIT_NO","=",CaseSegment::instance()->getSYS_TRACE_AUDIT_NO().c_str());
            if (bIncludeAmount)
               dAMT_RECON_NET = CaseSegment::instance()->getAMT_RECON_NET();
         }
         else if (bIncludeAmount)
            hQuery.setBasicPredicate("FIN_RECORD R", "AMT_TRAN", "=", CaseSegment::instance()->getAMT_TRAN());
         hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "<>", "208");
         if (!IF::Extract::instance()->getRecord("DSPEC   GE10    MULTICHB~Y", strValue))
            hQuery.setBasicPredicate(strLocator.c_str(), "FIN_TYPE", "NOT LIKE", "__1");
         hQuery.setBasicPredicate(strLocator.c_str(), "TSTAMP_LOCAL", "BETWEEN", strDateTime.c_str());
         if (strUserRole == "A"
            || (CaseManifestSegment::instance()->getFile() == "ISIARC"
               && bIncludeAmount == false))
            hQuery.setOrderByClause("FIN_L.FUNC_CODE DESC, FIN_L.FIN_TYPE DESC");
         else
            hQuery.setOrderByClause("FIN_L.FUNC_CODE ASC, FIN_L.FIN_TYPE DESC");
         Query hQuery3(hQuery);
         hQuery3.setIndex(2);
         if (bIncludeRetRefNo)
         {
            if (CaseManifestSegment::instance()->getFile() == "ISIARC")
            {
               string strRETRIEVAL_REF_NO(CaseSegment::instance()->getRETRIEVAL_REF_NO());
               strRETRIEVAL_REF_NO.trim();
               if (strRETRIEVAL_REF_NO.length() > 6)
                  strRETRIEVAL_REF_NO.erase(0,strRETRIEVAL_REF_NO.length() - 6);
               strRETRIEVAL_REF_NO.insert(0,"%",1);
               strRETRIEVAL_REF_NO.append("%",1);
               hQuery.setBasicPredicate(strLocator.c_str(),"RETRIEVAL_REF_NO","LIKE",strRETRIEVAL_REF_NO.c_str());
            }
            else
            {
               hQuery.getSearchCondition().append(" AND ");
               hQuery.getSearchCondition().append("(");
               hQuery.setBasicPredicate(strLocator.c_str(),"RETRIEVAL_REF_NO","=",CaseSegment::instance()->getRETRIEVAL_REF_NO().c_str());
               if (strLocator.substr(5, 6) >= DataModel::instance()->getFirstMonth("FIN_RECORD", "VISA_TRANSACTION_ID"))
                  hQuery.setBasicPredicate("FIN_RECORD R", "VISA_TRANSACTION_ID", "=", CaseVisaSegment::instance()->getTRAN_IDENTIFIER().c_str(), false, false);
               hQuery.getSearchCondition().append(")");
            }
         }
         Query hQuery2(hQuery);
         hQuery2.setIndex(2);
         hQuery.getSearchCondition().append(" AND ");
         hQuery.getSearchCondition().append("(");
         if (strUserRole == "A")
         {
            hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "LIKE", "1%");
            hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "LIKE", "2%", false, false);
         }
         else
         {
            hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "NOT LIKE", "1%");
         }
         hQuery.getSearchCondition().append(")");
         bool bSecure = false;
         string strValue;
         IF::Extract::instance()->getSpec("FBDNBDM5", strValue);
         if (CaseManifestSegment::instance()->getFile() == "DNRDM5"
            && !(genericexception::Extract::instance()->isOtherDN(BatchDescriptorSegment::instance()->getPROC_ID()))
            && strValue != "USPS")
            SOAPCommand::secure(hQuery, strLocator.c_str());
         if (strUserRole == "A" && IF::Extract::instance()->getCustomCode() == "CBA")
            hQuery.setBasicPredicate(strLocator.c_str(), "TRAN_TYPE_ID", "NOT LIKE", "20%");
         Query hQuery1(2);
         if (CaseManifestSegment::instance()->getFile() == "ISIARC")
         {
            if (!bIncludeSysTraceAuditNo && !bIncludeRetRefNo)
               return false;
            hQuery1 = hQuery;
            hQuery.setBasicPredicate(strLocator.c_str(),"ACT_CODE","LIKE","0%");
         }
         else
         {
            hQuery.setBasicPredicate(strLocator.c_str(),"ACT_CODE","LIKE","0%");
            hQuery1 = hQuery;
            if ((bIncludeSysTraceAuditNo) && (CaseManifestSegment::instance()->getFile() != "VRRDM5"))
               hQuery.setBasicPredicate(strLocator.c_str(),"SYS_TRACE_AUDIT_NO","=",CaseSegment::instance()->getSYS_TRACE_AUDIT_NO().c_str());
         }
#ifdef MVS
         if (hQueryAide.execute(hQuery, pSelectStatement.get(), &hRow) == false)
            break;
#else
         if (!pSelectStatement->execute(hQuery))
            break;
#endif
         if (pSelectStatement->getRows() == 0 
            && (bIncludeSysTraceAuditNo || CaseManifestSegment::instance()->getFile() == "ISIARC"))
         {
#ifdef MVS
            if (hQueryAide.execute(hQuery1, pSelectStatement.get(), &hRow) == false)
               break;
#else
            if (!pSelectStatement->execute(hQuery1))
               break;
#endif
         }
         if (pSelectStatement->getRows() == 0
            && CaseManifestSegment::instance()->getFile() == "ISIARC")
         {
            if (bIncludeRetRefNo)
            {
#ifdef MVS
               if (hQueryAide.execute(hQuery2, pSelectStatement.get(), &hRow) == false)
                  break;
#else
               if (!pSelectStatement->execute(hQuery2))
                  break;
#endif
            }
            if (pSelectStatement->getRows() == 0 && bIncludeSysTraceAuditNo)
            {
#ifdef MVS
               if (hQueryAide.execute(hQuery3, pSelectStatement.get(), &hRow) == false)
                  break;
#else
               if (!pSelectStatement->execute(hQuery3))
                  break;
#endif
            }
         }
         else if (pSelectStatement->getRows() == 0 &&
            IF::Extract::instance()->getCustomCode(1) == "PYPL" && CaseSegment::instance()->getCASE_EXTENSION() == "VNT")
         {
            hQuery3.setBasicPredicate("FIN_RECORD R","ACQ_REF_NO","=",CaseNationalNetworkSegment::instance()->getACQ_REF_NO().c_str());
#ifdef MVS
            if (hQueryAide.execute(hQuery3,pSelectStatement.get(),&hRow) == false)
               break;
#else
            if (!pSelectStatement->execute(hQuery3))
               break;
#endif
         }
         if (hQuery.getAbort() || hQuery1.getAbort() || hQuery2.getAbort() || hQuery3.getAbort())
         {
            if (!IF::Extract::instance()->getRecord("DSPEC   GE10    MULTICHB~Y", strValue)
               && strFIN_TYPE.length() > 2 && strFIN_TYPE[2] > '0')
            {
               Query hQueryTranExists;
               hQueryTranExists.setBasicPredicate("EMS_CASE", "TSTAMP_TRANS", "=", FinancialBaseSegment::instance()->getTSTAMP_TRANS().c_str());
               hQueryTranExists.setBasicPredicate("EMS_CASE", "UNIQUENESS_KEY", "=", (int)FinancialBaseSegment::instance()->getUNIQUENESS_KEY());
               hQueryTranExists.setBasicPredicate("EMS_CASE", "CASE_TYPE_IND", "=", "X");
               if (!pSelectStatement->execute(hQueryTranExists) || pSelectStatement->getRows() > 0)
               {
                  Trace::put("Standard case already exists on this transaction");
                  return false;
               }
            }
            if (FinancialBaseSegment::instance()->getFUNC_CODE().substr(0, 1) == "1"
               && CaseSegment::instance()->getOTHER_CUST_ID() != "XPRT"
               && CaseManifestSegment::instance()->getFile() != "ISIARC")
            {
               CaseSegment::instance()->setTSTAMP_TRANS(FinancialBaseSegment::instance()->getTSTAMP_TRANS());
               CaseSegment::instance()->setUNIQUENESS_KEY(FinancialBaseSegment::instance()->getUNIQUENESS_KEY());
               CaseSegment::instance()->setTRAN_TYPE_ID(FinancialBaseSegment::instance()->getTRAN_TYPE_ID());
               CaseSegment::instance()->setNET_TERM_ID(FinancialBaseSegment::instance()->getNET_TERM_ID());
               CaseSegment::instance()->setNET_ID_ACQ(FinancialBaseSegment::instance()->getNET_ID_ACQ());
               CaseSegment::instance()->setNET_ID_ISS(FinancialBaseSegment::instance()->getNET_ID_ISS());
            }
            else
               CaseSegment::instance()->setFinancialData();
            if (CaseManifestSegment::instance()->getFile() == "ISIARC"
               && bIncludeAmount
               && dAMT_RECON_NET != CaseSegment::instance()->getAMT_RECON_NET())
            {
               CaseSegment::instance()->setTSTAMP_TRANS("");
               return false;
            }
            if (CaseManifestSegment::instance()->getFile() == "VCR")
               CasePhaseSegment::instance()->setPresence(true);
            Trace::put("Found a financial transaction.");
            return true;
         }
         if (strLocator.substr(5, 6) == strEndDateTime.substr(0, 6))
            break;
         hQueryAide.reset();
         hQuery.reset();
         strLocatorDate.replace(0, 6, strEndDateTime.data(), 6);
      }
   }
   return false;
  //## end genericexception::Transaction::retrieveTransaction%54E5F8B0039A.body
}

bool Transaction::retrieveVisaAcqTransaction ()
{
  //## begin genericexception::Transaction::retrieveVisaAcqTransaction%5653244901E7.body preserve=yes
   Trace::put("in GE retrieveacqtran");
   QueryAide hQueryAide;
   Row hRow;
   Query hQuery(1);
   hQuery.attach(this);
   m_iMatchingScore = 0;
   auto_ptr<SelectStatement>pSelectStatement((SelectStatement*)DatabaseFactory::instance()->create("SelectStatement"));

   m_hFinancialBaseSegment.reset();

   if (CaseSegment::instance()->getTSTAMP_LOCAL().length() >= 8)
   {
      int lMinLocator = 0;
      string strTableName;
      //if previous day month is less than min locator table
      //search between currenday & next day
      //otherwise search between previous day & next day
      string strBegin("000000");
      string strEnd("000000");
      if (!ems::Case::instance()->findLocator("", strBegin, strEnd))
         return false;

      //if previous day month is less than min locator table
      //search between currenday & next day
      //otherwise search between previous day & next day
      Date hDate(CaseSegment::instance()->getTSTAMP_LOCAL().c_str());
      hDate -= 1;
      string strBeginDateTime(hDate.asString("%Y%m%d000000"));
      if (atoi(strBeginDateTime.substr(0, 6).c_str()) < atoi(strBegin.c_str()))
      {
         hDate += 1;
         strBeginDateTime = hDate.asString("%Y%m%d000000");
         hDate += 1;
      }
      else
         hDate += 2;
      string strEndDateTime(hDate.asString("%Y%m%d235959"));
      string strDateTime("'");
      strDateTime += strBeginDateTime;
      strDateTime += "' AND '";
      strDateTime += strEndDateTime;
      strDateTime += "'";
      string strLocator("FIN_L" + strBeginDateTime.substr(0, 6) + " FIN_L");
      string strICCLocator("FIN_ICC" + strBeginDateTime.substr(0, 6) + " FIN_ICC");
      for (;;)
      {
         hQuery.join(strLocator.c_str(), "LEFT OUTER", strICCLocator.c_str(), "TSTAMP_TRANS");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", strICCLocator.c_str(), "UNIQUENESS_KEY");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", "FIN_RECORD R", "TSTAMP_TRANS");
         hQuery.join(strLocator.c_str(), "LEFT OUTER", "FIN_RECORD R", "UNIQUENESS_KEY");
         m_hFinancialBaseSegment.bind(hQuery, strLocator.c_str());
         m_hFinancialSettlementSegment.bind(hQuery);
         m_hFinancialAdjustmentSegment.bind(hQuery);
         FinancialUserSegment::instance()->bind(hQuery);
         hQuery.setBasicPredicate(strLocator.c_str(), "PAN", "=", CaseSegment::instance()->getPAN().c_str());
         hQuery.setBasicPredicate(strLocator.c_str(), "FUNC_CODE", "<>", "208");
         hQuery.setBasicPredicate(strLocator.c_str(), "TSTAMP_LOCAL", "BETWEEN", strDateTime.c_str());
         hQuery.setOrderByClause("FIN_L.FUNC_CODE ASC");
#ifdef MVS
         if (hQueryAide.execute(hQuery, pSelectStatement.get(), &hRow) == false)
            break;
#else
         if (!pSelectStatement->execute(hQuery))
            break;
#endif
         if (hQuery.getAbort() || m_iMatchingScore > 0)
         {
            if (FinancialBaseSegment::instance()->getFUNC_CODE().substr(0, 1) == "1")
            {
               CaseSegment::instance()->setTSTAMP_TRANS(FinancialBaseSegment::instance()->getTSTAMP_TRANS());
               CaseSegment::instance()->setUNIQUENESS_KEY(FinancialBaseSegment::instance()->getUNIQUENESS_KEY());
               CaseSegment::instance()->setTRAN_TYPE_ID(FinancialBaseSegment::instance()->getTRAN_TYPE_ID());
               CaseSegment::instance()->setNET_TERM_ID(FinancialBaseSegment::instance()->getNET_TERM_ID());
               CaseSegment::instance()->setNET_ID_ACQ(FinancialBaseSegment::instance()->getNET_ID_ACQ());
               CaseSegment::instance()->setNET_ID_ISS(FinancialBaseSegment::instance()->getNET_ID_ISS());
            }
            else
            {
               Trace::put("Found a financial transaction.");
               string strSYS_TRACE_AUDIT_NO(CaseSegment::instance()->getSYS_TRACE_AUDIT_NO());
               CaseSegment::instance()->setFinancialData();
               CaseSegment::instance()->setSYS_TRACE_AUDIT_NO(strSYS_TRACE_AUDIT_NO);
               return true;
            }
         }
         if (strLocator.substr(5, 6) == strEndDateTime.substr(0, 6))
            break;
         hQueryAide.reset();
         hQuery.reset();
         strLocator.replace(5, 6, strEndDateTime.data(), 6);
      }
   }
   return false;
  //## end genericexception::Transaction::retrieveVisaAcqTransaction%5653244901E7.body
}

void Transaction::update (Subject* pSubject)
{
  //## begin genericexception::Transaction::update%4AEAFEA20109.body preserve=yes
   Trace::put("GE10 update");
   if (((Query*)pSubject)->getIndex() == 1)
   {
      int iCurrentScore = 0;
      char szREF_DATA_ISS[99];
      memset(szREF_DATA_ISS, ' ', sizeof(szREF_DATA_ISS));
      memcpy(szREF_DATA_ISS, m_hFinancialSettlementSegment.getREF_DATA_ISS().data(),
         m_hFinancialSettlementSegment.getREF_DATA_ISS().length());
      visasms::segREF_DATA_ISS *pREF_DATA_ISS;
      pREF_DATA_ISS = (struct visasms::segREF_DATA_ISS*) szREF_DATA_ISS;
      Trace::put("STAN-RD,Visa");
      Trace::put(pREF_DATA_ISS->sSYS_TRACE_AUDIT_NO,sizeof(pREF_DATA_ISS->sSYS_TRACE_AUDIT_NO));
      Trace::put(CaseSegment::instance()->getSYS_TRACE_AUDIT_NO().c_str());
      Trace::put("RRN-RD,Visa");
      Trace::put(pREF_DATA_ISS->sRETRIEVAL_REF_NO,sizeof(pREF_DATA_ISS->sRETRIEVAL_REF_NO));
      Trace::put(CaseSegment::instance()->getRETRIEVAL_REF_NO().c_str());
      Trace::put("TranID-RD,Visa");
      Trace::put(pREF_DATA_ISS->sTRAN_IDENTIFIER,sizeof(pREF_DATA_ISS->sTRAN_IDENTIFIER));
      Trace::put(CaseVisaSegment::instance()->getTRAN_IDENTIFIER().c_str());
	  if (CaseVisaSegment::instance()->getTRAN_IDENTIFIER().length() == sizeof(pREF_DATA_ISS->sTRAN_IDENTIFIER))
	  {
		  if (memcmp(pREF_DATA_ISS->sTRAN_IDENTIFIER, CaseVisaSegment::instance()->getTRAN_IDENTIFIER().data(),
			  sizeof(pREF_DATA_ISS->sTRAN_IDENTIFIER)) == 0)
		  {
			  m_iMatchingScore = 2;
			  *FinancialBaseSegment::instance() = m_hFinancialBaseSegment;
			  *FinancialSettlementSegment::instance() = m_hFinancialSettlementSegment;
			  *FinancialAdjustmentSegment::instance() = m_hFinancialAdjustmentSegment;
			  ((Query*)pSubject)->setAbort(true);
			  return;
		  }
	  }
	  else
	  {
		  if ((memcmp(pREF_DATA_ISS->sSYS_TRACE_AUDIT_NO, CaseSegment::instance()->getSYS_TRACE_AUDIT_NO().c_str(),
			  sizeof(pREF_DATA_ISS->sSYS_TRACE_AUDIT_NO)) == 0)
			  && (memcmp(pREF_DATA_ISS->sRETRIEVAL_REF_NO, CaseSegment::instance()->getRETRIEVAL_REF_NO().c_str(),
			  sizeof(pREF_DATA_ISS->sRETRIEVAL_REF_NO)) == 0))
		  {
			  iCurrentScore = 2;
			  ((Query*)pSubject)->setAbort(true);
		  }
		  if (iCurrentScore < 2 && (memcmp(pREF_DATA_ISS->sRETRIEVAL_REF_NO, CaseSegment::instance()->getRETRIEVAL_REF_NO().c_str(),
			  sizeof(pREF_DATA_ISS->sRETRIEVAL_REF_NO)) == 0))
			  iCurrentScore = 1;
		  if (iCurrentScore > m_iMatchingScore)
		  {
			  m_iMatchingScore = iCurrentScore;
			  *FinancialBaseSegment::instance() = m_hFinancialBaseSegment;
			  *FinancialSettlementSegment::instance() = m_hFinancialSettlementSegment;
			  *FinancialAdjustmentSegment::instance() = m_hFinancialAdjustmentSegment;
		  }
		  return;
	  }
   }
   if (((Query*)pSubject)->getIndex() == 2)
   {
	   string strNetworkID, strTranID, strValue, strUserRole;
	   char szREF_DATA_ACQ[99], szREF_DATA_ISS[99];
	   memset(szREF_DATA_ACQ, ' ', sizeof(szREF_DATA_ACQ));
	   memcpy(szREF_DATA_ACQ, FinancialSettlementSegment::instance()->getREF_DATA_ACQ().data(),
		   FinancialSettlementSegment::instance()->getREF_DATA_ACQ().length());
	   visasms::segREF_DATA_ACQ *pREF_DATA_ACQ;
	   pREF_DATA_ACQ = (struct visasms::segREF_DATA_ACQ*) szREF_DATA_ACQ;
	   memset(szREF_DATA_ISS, ' ', sizeof(szREF_DATA_ISS));
	   memcpy(szREF_DATA_ISS, FinancialSettlementSegment::instance()->getREF_DATA_ISS().data(),
		   FinancialSettlementSegment::instance()->getREF_DATA_ISS().length());
	   visasms::segREF_DATA_ISS *pREF_DATA_ISS;
	   pREF_DATA_ISS = (struct visasms::segREF_DATA_ISS*) szREF_DATA_ISS;
	   CaseManifest::instance()->get("CaseManifest memberRole", strUserRole);
	   CaseManifest::instance()->get("NetworkID", strNetworkID);
	   CaseManifest::instance()->get("TransactionID", strTranID);
	   if (strTranID.length() > 15)
		   strTranID.resize(15);
	   if ((strUserRole == "I") && (strNetworkID == "0002" || strNetworkID == "0003" || strNetworkID == "0004")
		   && (pREF_DATA_ACQ->sTRAN_IDENTIFIER[0] != ' ') && strTranID.length() > 0)
	   {
		   if (memcmp(pREF_DATA_ACQ->sTRAN_IDENTIFIER, strTranID.data(), sizeof(pREF_DATA_ACQ->sTRAN_IDENTIFIER)) == 0)
			   ((Query*)pSubject)->setAbort(true);
		   return;
	   }
	   else if ((strUserRole == "A") && (strNetworkID == "0002" || strNetworkID == "0003" || strNetworkID == "0004")
		   && (pREF_DATA_ISS->sTRAN_IDENTIFIER[0] != ' ') && strTranID.length() > 0)
	   {
		   if (memcmp(pREF_DATA_ISS->sTRAN_IDENTIFIER, strTranID.data(), sizeof(pREF_DATA_ISS->sTRAN_IDENTIFIER)) == 0)
			   ((Query*)pSubject)->setAbort(true);
		   return;
	   }
	   else
	   {
		   if (strUserRole == "A")
			   strValue = FinancialBaseSegment::instance()->getPROC_ID_ISS_B();
		   else
			   strValue = FinancialBaseSegment::instance()->getPROC_ID_ACQ_B();
		   strValue += strNetworkID;
		   Trace::put(strValue.c_str());
		   if (genericexception::Extract::instance()->getProcessorNetID(strValue))
			   ((Query*)pSubject)->setAbort(true);
	   }
   }
  //## end genericexception::Transaction::update%4AEAFEA20109.body
}

// Additional Declarations
  //## begin genericexception::Transaction%4AE9FB8A034B.declarations preserve=yes
  //## end genericexception::Transaction%4AE9FB8A034B.declarations

} // namespace genericexception

//## begin module%4AE9FBEC000F.epilog preserve=yes
//## end module%4AE9FBEC000F.epilog
