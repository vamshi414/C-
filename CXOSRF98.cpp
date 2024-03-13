//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%6598CDAC00DD.cm preserve=no
//## end module%6598CDAC00DD.cm

//## begin module%6598CDAC00DD.cp preserve=no
//	Copyright (c) 1997 - 2022
//	FIS
//## end module%6598CDAC00DD.cp

//## Module: CXOSRF98%6598CDAC00DD; Package body
//## Subsystem: RFDLL%439873F400EA
//## Source file: C:\Repos\datanavigatorserver\Windows\Build\Dn\Server\Library\Rfdll\CXOSRF98.cpp

//## begin module%6598CDAC00DD.additionalIncludes preserve=no
//## end module%6598CDAC00DD.additionalIncludes

//## begin module%6598CDAC00DD.includes preserve=yes
#ifndef CXOSIF03_h
#include "CXODIF03.hpp"
#endif
//## end module%6598CDAC00DD.includes

#ifndef CXOSRF10_h
#include "CXODRF10.hpp"
#endif
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
#ifndef CXOSCF01_h
#include "CXODCF01.hpp"
#endif
#ifndef CXOSRU40_h
#include "CXODRU40.hpp"
#endif
#ifndef CXOSCF61_h
#include "CXODCF61.hpp"
#endif
#ifndef CXOSRF98_h
#include "CXODRF98.hpp"
#endif


//## begin module%6598CDAC00DD.declarations preserve=no
#include "CXODRF99.hpp"
#include "CXODRF48.hpp"
//## end module%6598CDAC00DD.declarations

//## begin module%6598CDAC00DD.additionalDeclarations preserve=yes
//## end module%6598CDAC00DD.additionalDeclarations


//## Modelname: Reconciliation::ReconciliationFile_CAT%439754C1037A
namespace reconciliationfile {
//## begin reconciliationfile%439754C1037A.initialDeclarations preserve=yes
//## end reconciliationfile%439754C1037A.initialDeclarations

// Class reconciliationfile::PULSEEnhancedDataFile 

PULSEEnhancedDataFile::PULSEEnhancedDataFile (const string& strClass)
  //## begin reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%6598D5F9033E.hasinit preserve=no
  //## end reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%6598D5F9033E.hasinit
  //## begin reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%6598D5F9033E.initialization preserve=yes
   :InterchangeFile(strClass)
  //## end reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%6598D5F9033E.initialization
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%6598D5F9033E.body preserve=yes
   memcpy(m_sID, "RF98", 4);
   m_strDX_FILE_TYPE.assign("PULIXE", 6);
   setColumns(
      "PAN"
      ",RETRIEVAL_REF_NO"
      ",SYS_TRACE_AUDIT_NO"
      ",TSTAMP_LOCAL"
      ",CARD_ACPT_TERM_ID"
      ",CARD_ACPT_ID"
      ",ACT_CODE"
      ",TRAN_DISPOSITION"
      ",TRAN_TYPE_ID"
      ",AMT_RECON_NET"
      ",INST_ID_ACQ"
      ",INST_ID_ISS"
      ",DATE_RECON_NET"
      ",F_AMT0"
      ",F_TYPE0"
      ",ADL_RQST_AMT0"
      ",ROLE"
   );
  //## end reconciliationfile::PULSEEnhancedDataFile::PULSEEnhancedDataFile%6598D5F9033E.body
}

PULSEEnhancedDataFile::~PULSEEnhancedDataFile()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::~PULSEEnhancedDataFile%6598D0E20194_dest.body preserve=yes
  //## end reconciliationfile::PULSEEnhancedDataFile::~PULSEEnhancedDataFile%6598D0E20194_dest.body
}


//## Other Operations (implementation)
bool PULSEEnhancedDataFile::reFormat ()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::reFormat%6598D4560378.body preserve=yes
   if (!TransactionActivityFile::initReFormat())
      return false;
   bool bAuthorization = false;
   string strRecordType;
   int iOffset = 0;
   NetworkSegment x;
   struct hMainTransactionSegment* pMainSegment = 0;
   struct hFeeSegment* pFeeSegment = (struct hFeeSegment*)m_pBuffer;
   struct hAdditionalDataSegment* pAddDataSegment = (struct hAdditionalDataSegment*)m_pBuffer;
   struct hFileHeader* pHeader = (struct hFileHeader*)m_pBuffer;
   struct hAdditionalAmountSegment* pAddAmountSegment = (struct hAdditionalAmountSegment*)m_pBuffer;
   struct hDisputeSegment* pDisputeSegment = (struct hDisputeSegment*)m_pBuffer;
   struct hTokenSegment* pTokenSegment = (struct hTokenSegment*)m_pBuffer;
   struct hCurrencyTrailer* pCurTrailer = (struct hCurrencyTrailer*)m_pBuffer;
   struct hFileTrailer* pTrailer = (struct hFileTrailer*)m_pBuffer;
   while (m_pGenerationDataGroup->read(m_pBuffer, 1024, &m_lBufferLength))
   {
      strRecordType.assign(m_pBuffer + iOffset, 2);
      if (strRecordType == "01")
      {
         continue;
      }
      else if (strRecordType == "06")
      {
         if (m_strTRAN_TYPE_ID[6] == '2')
         {
            if (pMainSegment && !write())
               return false;
         }
         pMainSegment = (struct hMainTransactionSegment*)m_pBuffer;
         m_strPAN.assign(pMainSegment->sPAN, sizeof(pMainSegment->sPAN));
         KeyRing::instance()->tokenize(pMainSegment->sPAN, sizeof(pMainSegment->sPAN));
         setColumn(PAN, pMainSegment->sPAN, sizeof(pMainSegment->sPAN));
         setColumn(RETRIEVAL_REF_NO, pMainSegment->sRRN, 12);
         setColumn(SYS_TRACE_AUDIT_NO, pMainSegment->sSTAN, 6);
         setColumn(TSTAMP_LOCAL, pMainSegment->sLocalTimeStamp, 14);
         setColumn(CARD_ACPT_TERM_ID, pMainSegment->sCardAcptTermID, 16);
         setColumn(CARD_ACPT_ID, pMainSegment->sCardAcptIDCode, 15);
         if (memcmp(pMainSegment->sActionCode, "0000", 4) == 0)
            setColumn(ACT_CODE, "000", 3);
         else
            setColumn(ACT_CODE, pMainSegment->sActionCode, 3);
         char szTemp[19];
         double dAMT_RECON_NET = x.asDouble(pMainSegment->sSettleAmount, 17);
         snprintf(szTemp, sizeof(szTemp), "%018.0f", dAMT_RECON_NET);
         setColumn(AMT_RECON_NET, szTemp, 18);
         setColumn(F_AMT0, szTemp, 8);
         setColumn(F_TYPE0, "01", 2);
         setColumn(INST_ID_ACQ, pMainSegment->sAcqInstID, 9);
         setColumn(INST_ID_ISS, pMainSegment->sIssInstID, 9);
         setColumn(DATE_RECON_NET, pMainSegment->sSysOwnerBusinessDate, 8);
         m_strRole.assign(&pMainSegment->cISSACQFlag, sizeof(pMainSegment->cISSACQFlag));
         setColumn(ROLE, &pMainSegment->cISSACQFlag, 1);
      }
      else if (strRecordType == "50")
      {
         if (memcmp(pAddDataSegment->sAction, "ACC", 3) == 0)
         {
            setColumn(TRAN_DISPOSITION, "1", 1);
         }
         else if (memcmp(pAddDataSegment->sAction, "REJ", 3) == 0)
         {
            setColumn(TRAN_DISPOSITION, "2", 1);
         }
         else
         {
            setColumn(TRAN_DISPOSITION, "3", 1);
         }
         /*m_strPUL_TRAN_TYPE.assign(pAddDataSegment->sFormat8TxnType, 2);
         if (!configuration::ConfigurationRepository::instance()->translate("X_PULSE_PROC_CODE", m_strPUL_TRAN_TYPE, m_strTRAN_TYPE_ID, "", "", 0, false))
         {
            Trace::put("Unknown PUL Tran Type:", m_strPUL_TRAN_TYPE, true);
            continue;
         } */
         m_strProcessingCode.assign
         setColumn(TRAN_TYPE_ID, m_strTRAN_TYPE_ID.data(), m_strTRAN_TYPE_ID.length());
      }
      else if (strRecordType == "09")
      {
         struct hFeeSegment* pFeeSegment = (struct hFeeSegment*)m_pBuffer;
         int m_iFeecount;
         m_iFeecount = atoi(pFeeSegment->sFeecnt);
         for (int i = 0; i < m_iFeecount; i++)
         {
            double dInterChangeFee;
            char szTemp[19];
            if (memcmp(pFeeSegment->hFee[i].sType, "Interchange Fee Ty  ", 20) == 0)
            {
               formatAmount(pFeeSegment->hFee[i].sValue, sizeof(pFeeSegment->hFee[i].sValue) - 1);
               dInterChangeFee = x.asDouble(pFeeSegment->hFee[i].sValue, 19);
               snprintf(szTemp, sizeof(szTemp), "%018.0f", dInterChangeFee);
               setColumn(ADL_RQST_AMT0, szTemp, 18);
            }
         }
      }
   }
   if (m_strTRAN_TYPE_ID[6] == '2')
   {
      if (!write())
         return false;
   }
   return TransactionActivityFile::reFormat();
  //## end reconciliationfile::PULSEEnhancedDataFile::reFormat%6598D4560378.body
}

void PULSEEnhancedDataFile::setBasicPredicate (Query& hQuery, const string& strTable, int iBegin, int iEnd, int iEntity)
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::setBasicPredicate%6598D4890054.body preserve=yes
   hQuery.setBasicPredicate(strTable.c_str(), "TRAN_TYPE_ID", "LIKE", "______2___");
   TransactionReportFile::setBasicPredicate(hQuery, strTable, iBegin, iEnd, iEntity);
  //## end reconciliationfile::PULSEEnhancedDataFile::setBasicPredicate%6598D4890054.body
}

void PULSEEnhancedDataFile::setMatch ()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::setMatch%6598D5490102.body preserve=yes
   ReconciliationDataset::setMatch();
   m_hFile.setSortByBIN(false);
   if (m_hFile.getMatch().empty())
   {
      m_hFile.setMatch("PAN");
      m_hFile.setMatch("RETRIEVAL_REF_NO");
      m_hFile.setMatch("TSTAMP_LOCAL");
      m_hFile.setMatch("CARD_ACPT_TERM_ID");
      m_hFile.setMatch("TRAN_DISPOSITION");
   }
  //## end reconciliationfile::PULSEEnhancedDataFile::setMatch%6598D5490102.body
}

void PULSEEnhancedDataFile::setOrderByClause (Query& hQuery)
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::setOrderByClause%6598D575009B.body preserve=yes
   TransactionReportFile::setOrderByClause(hQuery);  //do not override because will not sync with match criteria if overridden with DSPEC
  //## end reconciliationfile::PULSEEnhancedDataFile::setOrderByClause%6598D575009B.body
}

bool PULSEEnhancedDataFile::lookupEntity (const string& strINST_ID)
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::lookupEntity%6598D67100AD.body preserve=yes
   string strPROC_ID, strINST_ID_1;
   if (ConfigurationRepository::instance()->translate("INSTITUTION", strINST_ID, strPROC_ID, "", "", -1, false) == false)
   {
      if (NetworkInstitution::getINST_ID("PUL", strINST_ID, "", "", "", strINST_ID_1))
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
  //## end reconciliationfile::PULSEEnhancedDataFile::lookupEntity%6598D67100AD.body
}

bool PULSEEnhancedDataFile::write ()
{
  //## begin reconciliationfile::PULSEEnhancedDataFile::write%6598D6BF00A8.body preserve=yes
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
  //## end reconciliationfile::PULSEEnhancedDataFile::write%6598D6BF00A8.body
}

// Additional Declarations
  //## begin reconciliationfile::PULSEEnhancedDataFile%6598D0E20194.declarations preserve=yes
  //## end reconciliationfile::PULSEEnhancedDataFile%6598D0E20194.declarations

} // namespace reconciliationfile

//## begin module%6598CDAC00DD.epilog preserve=yes
//## end module%6598CDAC00DD.epilog
