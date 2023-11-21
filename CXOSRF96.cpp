//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%59BAA50A03CC.cm preserve=no
//## end module%59BAA50A03CC.cm

//## begin module%59BAA50A03CC.cp preserve=no
//	Copyright (c) 1997 - 2022
//	FIS
//## end module%59BAA50A03CC.cp

//## Module: CXOSRF63%59BAA50A03CC; Package body
//## Subsystem: RFDLL%439873F400EA
//## Source file: C:\Repos\datanavigatorserver\Windows\Build\Dn\Server\Library\Rfdll\CXOSRF63.cpp

//## begin module%59BAA50A03CC.additionalIncludes preserve=no
//## end module%59BAA50A03CC.additionalIncludes

//## begin module%59BAA50A03CC.includes preserve=yes
//#include "CXODRF64.hpp"
//#include "CXODCF01.hpp"
#ifndef CXOSIF03_h
#include "CXODIF03.hpp"
#endif
//## end module%59BAA50A03CC.includes

#ifndef CXOSIF05_h
#include "CXODIF05.hpp"
#endif
#ifndef CXOSRS78_h
#include "CXODRS78.hpp"
#endif
#ifndef CXOSMN05_h
#include "CXODMN05.hpp"
#endif
#ifndef CXOSRF48_h
#include "CXODRF48.hpp"
#endif
#ifndef CXOSTM04_h
#include "CXODTM04.hpp"
#endif
#ifndef CXOSIF28_h
#include "CXODIF28.hpp"
#endif
#ifndef CXOSNS40_h
#include "CXODNS40.hpp"
#endif
#ifndef CXOSRF10_h
#include "CXODRF10.hpp"
#endif
#ifndef CXOSCF01_h
#include "CXODCF01.hpp"
#endif
#ifndef CXOSIF04_h
#include "CXODIF04.hpp"
#endif
#ifndef CXOSRU40_h
#include "CXODRU40.hpp"
#endif
#ifndef CXOSCF61_h
#include "CXODCF61.hpp"
#endif
#ifndef CXOSRF96_h
#include "CXODRF96.hpp"
#endif


//## begin module%59BAA50A03CC.declarations preserve=no
//## end module%59BAA50A03CC.declarations

//## begin module%59BAA50A03CC.additionalDeclarations preserve=yes
#include "CXODRF97.hpp"
#include "CXODRF48.hpp"

//## end module%59BAA50A03CC.additionalDeclarations


//## Modelname: Reconciliation::ReconciliationFile_CAT%439754C1037A
namespace reconciliationfile {
//## begin reconciliationfile%439754C1037A.initialDeclarations preserve=yes
//## end reconciliationfile%439754C1037A.initialDeclarations

// Class reconciliationfile::PULSEEnhancedDataFile 

PULSEEnhancedDataFile::PULSEEnhancedDataFile(const string& strClass)
  //## begin reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%651C26EB00A6.hasinit preserve=no
  //## end reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%651C26EB00A6.hasinit
  //## begin reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%651C26EB00A6.initialization preserve=yes
   :InterchangeFile(strClass)
  //## end reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%651C26EB00A6.initialization
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%651C26EB00A6.body preserve=yes
   memcpy(m_sID, "RF96", 4);
   m_strDX_FILE_TYPE.assign("PULIXE", 6);
   setColumns(
      "PAN"
      ",RETRIEVAL_REF_NO"
      ",SYS_TRACE_AUDIT_NO"
      ",TSTAMP_LOCAL"
      ",CARD_ACPT_TERM_ID"
      ",CARD_ACPT_ID"
      ",NET_TERM_ID"
      ",CARD_ACPT_BUS_CODE"
      ",MTI"
      ",ACT_CODE"
      ",TRAN_DISPOSITION"
      ",TRAN_TYPE_ID"
      ",APPROVAL_CODE"
      ",AMT_RECON_NET"
      ",CUR_RECON_NET"
      ",INST_ID_ACQ"
      ",INST_ID_ISS"
      ",PROC_ID_ACQ"
      ",PROC_ID_ISS_B"
      ",NET_ID_ISS"
      ",NET_ID_ACQ"
      ",DATE_RECON_NET"
      ",F_AMT0"
      ",F_TYPE0"
      ",F_CUR_CODE0"
      ",ACCT_ID_1"
      ",ACCT_ID_2"
      ",ROLE_IND"
      ",ADL_RQST_AMT0"
      ",ROLE"
   );
   m_bIncludeSurcharge = true;
  //## end reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%651C26EB00A6.body
}


PULSEEnhancedDataFile::~PULSEEnhancedDataFile()
{
  //## begin reconciliationfile::NYCEEnhancedDataFile::~NYCEEnhancedDataFile%59BAA4570128_dest.body preserve=yes
  //## end reconciliationfile::NYCEEnhancedDataFile::~NYCEEnhancedDataFile%59BAA4570128_dest.body
}



//## Other Operations (implementation)
bool PULSEEnhancedDataFile::reFormat ()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::reFormat%59BAA4B70315.body preserve=yes
   if (!TransactionActivityFile::initReFormat())
      return false;
   //char sPreviousRecord[380];
   bool bAuthorization = false;
   string strPULSETranType;
   //memset(sPreviousRecord, ' ', 380);
   //memset(m_pBuffer, ' ', 1024);
   string strSettleDate;
   string strRecordType;
   int iOffset = 0;
   while (m_pGenerationDataGroup->read(m_pBuffer, 1024, &m_lBufferLength))
   {
      //struct hAdditionalDataSegment* pAddDataSegment = (struct hAdditionalDataSegment*)m_pBuffer;
      //struct hAdditionalAmountSegment* pAddAmountSegment = (struct hAdditionalAmountSegment*)m_pBuffer;
      // struct hDisputeSegment* pDisputeSegment = (struct hDisputeSegment*)m_pBuffer;
      //struct hTokenSegment* pTokenSegment = (struct hTokenSegment*)m_pBuffer;
      //struct cTrailer* pCurTrailer = (struct cTrailer*)m_pBuffer;
      //struct hTrailer* pTrailer = (struct hTrailer*)m_pBuffer;

      strRecordType.assign(m_pBuffer + iOffset, 2);
      if (strRecordType == "01")
      {
         struct hHeader* pHeader = (struct hHeader*)m_pBuffer;
         strSettleDate.assign(pHeader->sSettleDate, 8);
         continue;
      }
      else if (strRecordType == "06")
      {
         struct hMainTransactionSegment* pMainSegment = (struct hMainTransactionSegment*)m_pBuffer;
         m_strPAN.assign(pMainSegment->sPAN, sizeof(pMainSegment->sPAN));
         KeyRing::instance()->tokenize(pMainSegment->sPAN, sizeof(pMainSegment->sPAN));
         setColumn(PAN, pMainSegment->sPAN, sizeof(pMainSegment->sPAN));
         setColumn(RETRIEVAL_REF_NO, pMainSegment->sRRN,12);
         setColumn(SYS_TRACE_AUDIT_NO, pMainSegment->sSTAN,6);
         string strTSTAMP_LOCAL;
         if (strSettleDate.length() == 8)
            strTSTAMP_LOCAL.assign(strSettleDate);
         else
         {
            strTSTAMP_LOCAL.assign(Clock::instance()->getDate());
            strSettleDate.assign(strTSTAMP_LOCAL);
         }
         setColumn(TSTAMP_LOCAL, strTSTAMP_LOCAL.c_str(), 14);
         setColumn(CARD_ACPT_TERM_ID, pMainSegment->sCardAcptTermID,16);
         setColumn(CARD_ACPT_ID, pMainSegment->sCardAcptIDCode,15);
         setColumn(NET_TERM_ID, pMainSegment->sNetTermID,6);
         string strACT_CODE("000", 3);
         setColumn(TRAN_DISPOSITION, pMainSegment->cRevFlag == 'Y' ? "3" : "1", 1);
         if (memcmp(pMainSegment->sActionCode, "0000", 4) == 0)
         {
            setColumn(ACT_CODE, "000", 3);
         }
         char szTemp[19];
         NetworkSegment x;
         double dAMT_RECON_NET = x.asDouble(pMainSegment->sSettleAmount, 19);
         snprintf(szTemp, sizeof(szTemp), "%018.0f", dAMT_RECON_NET);
         setColumn(AMT_RECON_NET, szTemp, 18);
         setColumn(F_AMT0, szTemp, 8);
         setColumn(CUR_RECON_NET, pMainSegment->sSettleCur, 3);
         setColumn(INST_ID_ACQ, pMainSegment->sAcqInstID, 9);
         setColumn(INST_ID_ISS, pMainSegment->sIssInstID, 9);
         setColumn(PROC_ID_ISS_B, "PULSE", 5);
         setColumn(NET_ID_ISS, pMainSegment->sIssNetID, 3);
         setColumn(NET_ID_ACQ, pMainSegment->sAcqNetID, 3);
         setColumn(DATE_RECON_NET, strSettleDate.c_str(), 8);
         setColumn(ACCT_ID_1, pMainSegment->sACT_ID1, 28);
         setColumn(ACCT_ID_2, pMainSegment->sACT_ID2, 28);

         setColumn(TXN_AMT_IMPACT_TYP, &pMainSegment->cTranAmountImpactType, 1);
         //setColumn(ROLE_IND, &pMainSegment->cISSACQFlag, 1);
         //m_strRole.assign(pMainSegment->cISSACQFlag, sizeof(pMainSegment->cISSACQFlag));
         m_strRole.assign("I");
         setColumn(ROLE, &pMainSegment->cISSACQFlag, 1);
         m_strProcessingCode.assign(pMainSegment->sProcCode,6);
         if (!configuration::ConfigurationRepository::instance()->translate("X_PULSE_PROC_CODE", m_strProcessingCode, m_strTRAN_TYPE_ID, " ", " ", 0, false))
         {
            m_strTRAN_TYPE_ID = m_strProcessingCode;
            m_strTRAN_TYPE_ID.append("2000");
         }
         bAuthorization = m_strTRAN_TYPE_ID[6] == '1';
         if (bAuthorization)
            continue;
         setColumn(TRAN_TYPE_ID, m_strTRAN_TYPE_ID.data(), m_strTRAN_TYPE_ID.length());
      }

   /*   if (memcmp(pAddDataSegment->sRecordType, "50", 2) == 0)
      {
        // if (memcmp(pAddDataSegment->sAddDataNational, "000", 3) == 0)
        // {
        //    strncpy(pAddDataSegment->sAddDataNational, "000", 3);

        // }

         if (strncmp(pAddDataSegment->sNationalPosCondCode, "000", 3) != 0)
         {
            char lengthposcode[4];
            strncpy(lengthposcode, pAddDataSegment->sNationalPosCondCode, 3);
            lengthposcode[3] = '\0';
            int poscodelength = atoi(lengthposcode);
            for (int i = 3; i < poscodelength + 3; i++)
            {
               pAddDataSegment->sNationalPosCondCode[i - 3] = pAddDataSegment->sNationalPosCondCode[i];
            }
         }
         else if (strncmp(pAddDataSegment->sNationalPosCondCode, "000", 3) == 0)
         {
            strncpy(pAddDataSegment->sNationalPosCondCode, "000", 3);
         }
         if (strncmp(pAddDataSegment->sTranDesc, "000", 3) != 0)
         {
            char lengthtrandesc[4];
            strncpy(lengthtrandesc, pAddDataSegment->sTranDesc, 3);
            lengthtrandesc[3] = '\0';
            int trandesclength = atoi(lengthtrandesc);
            for (int i = 3; i < trandesclength + 3; i++)
            {
               pAddDataSegment->sTranDesc[i - 3] = pAddDataSegment->sTranDesc[i];
            }
         }
         else if (strncmp(pAddDataSegment->sTranDesc, "000", 3) == 0)
         {
            strncpy(pAddDataSegment->sTranDesc, "000", 3);
         }
         if (strncmp(pAddDataSegment->sAddDataPrivAcq, "000", 3) != 0)
         {
            char lenadddataprivacq[4];
            strncpy(lenadddataprivacq, pAddDataSegment->sAddDataPrivAcq, 3);
            lenadddataprivacq[3] = '\0';
            int adddataprivacqlength = atoi(lenadddataprivacq);
            for (int i = 3; i < adddataprivacqlength + 3; i++)
            {
               pAddDataSegment->sAddDataPrivAcq[i - 3] = pAddDataSegment->sAddDataPrivAcq[i];
            }
         }
         else if (strncmp(pAddDataSegment->sAddDataPrivAcq, "000", 3) == 0)
         {
            strncpy(pAddDataSegment->sAddDataPrivAcq, "000", 3);
         }
         if (strncmp(pAddDataSegment->sAVSAuthData, "000", 3) != 0)
         {
            char lenAVSAuthData[4];
            strncpy(lenAVSAuthData, pAddDataSegment->sAVSAuthData, 3);
            lenAVSAuthData[3] = '\0';
            int AVSAuthDatalength = atoi(lenAVSAuthData);
            for (int i = 3; i < AVSAuthDatalength + 3; i++)
            {
               pAddDataSegment->sAVSAuthData[i - 3] = pAddDataSegment->sAVSAuthData[i];
            }
         }
         else if (strncmp(pAddDataSegment->sAVSAuthData, "000", 3) == 0)
         {
            strncpy(pAddDataSegment->sAVSAuthData, "000", 3);
         }
         if (strncmp(pAddDataSegment->sIssTraceData, "000", 3) != 0)
         {
            char lenIssTraceData[4];
            strncpy(lenIssTraceData, pAddDataSegment->sIssTraceData, 3);
            lenIssTraceData[3] = '\0';
            int IssTraceDatalength = atoi(lenIssTraceData);
            for (int i = 3; i < IssTraceDatalength + 3; i++)
            {
               pAddDataSegment->sIssTraceData[i - 3] = pAddDataSegment->sIssTraceData[i];
            }
         }
         else if (strncmp(pAddDataSegment->sIssTraceData, "000", 3) == 0)
         {
            strncpy(pAddDataSegment->sIssTraceData, "000", 3);
         }
         if (strncmp(pAddDataSegment->sAcqTraceData, "000", 3) != 0)
         {
            char lenAcqTraceData[4];
            strncpy(lenAcqTraceData, pAddDataSegment->sAcqTraceData, 3);
            lenAcqTraceData[3] = '\0';
            int IssTraceDatalength = atoi(lenAcqTraceData);
            for (int i = 3; i < IssTraceDatalength + 3; i++)
            {
               pAddDataSegment->sAcqTraceData[i - 3] = pAddDataSegment->sAcqTraceData[i];
            }
         }
         else if (strncmp(pAddDataSegment->sAcqTraceData, "000", 3) == 0)
         {
            strncpy(pAddDataSegment->sAcqTraceData, "000", 3);
         }
         setColumn(APPROVAL_CODE, pAddDataSegment->sApprovalCode, 6);
         //strPULSETranType = pAddDataSegment->sFormat8TxnType;
      } */
         
      //struct hDisputeSegment* pDisputeSegment = (struct hDisputeSegment*)m_pBuffer;
      //if (memcmp(pDisputeSegment->sRecordType, "30", 2) == 0)
      //{
        // setColumn(PROC_ID_ACQ, pDisputeSegment->sAcqProcID, 6);
      //}

      
      else if (strRecordType == "09")
      {
         struct hFeeSegment* pFeeSegment = (struct hFeeSegment*)m_pBuffer;
         int m_iFeecount;
         m_iFeecount = atoi(pFeeSegment->sFeecnt);
         for (int i = 0; i < m_iFeecount; i++)
         {
            string strInterChangeFee;
            if (memcmp(pFeeSegment->hFee[i].sType, "Interchange Fee Ty  ", 20) == 0)
            {
               formatAmount(pFeeSegment->hFee[i].sValue, sizeof(pFeeSegment->hFee[i].sValue) - 1);
               strInterChangeFee.append(pFeeSegment->hFee[i].sValue, 19);
               setColumn(ADL_RQST_AMT0, strInterChangeFee.c_str(), strInterChangeFee.length());
               //setColumn(ADL_RQST_CUR_CODE0, pFeeSegment->hFee[i].sCur, 3);
            }
         }
      }

      //struct hTokenSegment* pTokenSegment = (struct hTokenSegment*)m_pBuffer;
      //if (memcmp(pFeeSegment->sRecordType, "20", 2) == 0)
      //{

      //}
      //memcpy(sPreviousRecord, m_pBuffer, 380);
      if (!write())
         return false;
   }
   return TransactionActivityFile::reFormat();
  //## end reconciliationfile::PULSEEnhancedDataFile::reFormat%59BAA4B70315.body
}

void PULSEEnhancedDataFile::setBasicPredicate (Query& hQuery, const string& strTable, int iBegin, int iEnd, int iEntity)
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::setBasicPredicate%62AB5D010186.body preserve=yes
   hQuery.setBasicPredicate(strTable.c_str(), "TRAN_TYPE_ID", "LIKE", "______2___");
   TransactionReportFile::setBasicPredicate(hQuery, strTable, iBegin, iEnd,iEntity);
  //## end reconciliationfile::PULSEEnhancedDataFile::setBasicPredicate%62AB5D010186.body
}

void PULSEEnhancedDataFile::setMatch ()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::setMatch%62BDE2950093.body preserve=yes
   ReconciliationDataset::setMatch();
   m_hFile.setSortByBIN(false);
   if (m_hFile.getMatch().empty())
   {
      m_hFile.setMatch("PAN");
      m_hFile.setMatch("RETRIEVAL_REF_NO");
      m_hFile.setMatch("TSTAMP_LOCAL");
      m_hFile.setMatch("CARD_ACPT_TERM_ID");
      m_hFile.setMatch("TRAN_DISPOSITION");
      m_hFile.setMatch("AMT_RECON_NET");
   }
  //## end reconciliationfile::PULSEEnhancedDataFile::setMatch%62BDE2950093.body
}

void PULSEEnhancedDataFile::setOrderByClause (Query& hQuery)
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::setOrderByClause%62BDE28103AB.body preserve=yes
   TransactionReportFile::setOrderByClause(hQuery);  //do not override because will not sync with match criteria if overridden with DSPEC
  //## end reconciliationfile::PULSEEnhancedDataFile::setOrderByClause%62BDE28103AB.body
}

bool PULSEEnhancedDataFile::lookupEntity (const string& strINST_ID)
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::lookupEntity%652D31AF0005.body preserve=yes
   string strPROC_ID, strINST_ID_1;
   if (ConfigurationRepository::instance()->translate("INSTITUTION", strINST_ID, strPROC_ID, "", "", -1, false) == false)
   {
      if (NetworkInstitution::getINST_ID("PUL", strINST_ID, m_strPAN, "", "", strINST_ID_1))
      {
         if (ConfigurationRepository::instance()->translate("INSTITUTION", strINST_ID_1, strPROC_ID, "", "", -1, false) == false)
         {
            (m_strRole == "A") ? m_pReformatAudit->report('A') : m_pReformatAudit->report('I');
            return false;
         }
      }
      else
      {
         (m_strRole == "A") ? m_pReformatAudit->report('A') : m_pReformatAudit->report('I');
         return false;
      }
   }
   return true;
  //## end reconciliationfile::PULSEEnhancedDataFile::lookupEntity%652D31AF0005.body
}

bool PULSEEnhancedDataFile::write ()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::write%652D321902B8.body preserve=yes
   setColumn(DATE_RECON_NET, getColumn(DATE_RECON_NET).c_str(), 8);
   bool bFound = true;
   if (m_bEntityDetail)
   {
      m_hGenericSegment.reset();
      m_hGenericSegment.set("DATE_RECON_NET", getColumn(DATE_RECON_NET));
      m_hGenericSegment.set("INST_ID_ACQ", getColumn(INST_ID_ACQ));
      m_hGenericSegment.set("INST_ID_ISS", getColumn(INST_ID_ISS));
      m_hGenericSegment.set("PAN", m_strPAN);
      m_hGenericSegment.set("RETRIEVAL_REF_NO", getColumn(RETRIEVAL_REF_NO));
      m_hGenericSegment.set("TSTAMP_LOCAL", getColumn(TSTAMP_LOCAL));
      if (!m_pReformatAudit)
         InterchangeFile::initializeAudit("PULRFA", getColumn(DATE_RECON_NET));
      bFound = (m_strRole == "A") ? lookupEntity(getColumn(INST_ID_ACQ)) : lookupEntity(getColumn(INST_ID_ISS));
      m_hGenericSegment.reset();
   }
   if (bFound)
      return TransactionReportFile::write();
   return true;
  //## end reconciliationfile::PULSEEnhancedDataFile::write%652D321902B8.body
}

// Additional Declarations
  //## begin reconciliationfile::PULSEEnhancedDataFile%59BAA4570128.declarations preserve=yes
  //## end reconciliationfile::PULSEEnhancedDataFile%59BAA4570128.declarations

} // namespace reconciliationfile

//## begin module%59BAA50A03CC.epilog preserve=yes
//## end module%59BAA50A03CC.epilog
