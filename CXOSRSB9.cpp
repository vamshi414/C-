//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%6385D03600F1.cm preserve=no
//## end module%6385D03600F1.cm

//## begin module%6385D03600F1.cp preserve=no
//	Copyright (c) 1997 - 2022
//	FIS
//## end module%6385D03600F1.cp

//## Module: CXOSRSB9%6385D03600F1; Package body
//## Subsystem: RSDLL%394E1FDA02D9
//## Source file: C:\Repos\DataNavigatorServer\Windows\Build\Dn\Server\Library\Rsdll\CXOSRSB9.cpp

//## begin module%6385D03600F1.additionalIncludes preserve=no
//## end module%6385D03600F1.additionalIncludes

//## begin module%6385D03600F1.includes preserve=yes
#include "CXODRS65.hpp"
#include "CXODRS64.hpp"
#include "CXODRS62.hpp"
#include "CXODRS66.hpp"
#include "CXODRS86.hpp"
#include "CXODIF16.hpp"
#include "CXODTM06.hpp"
#include "CXODTM04.hpp"
#include "CXODIF28.hpp"
//## end module%6385D03600F1.includes

#ifndef CXOSCF01_h
#include "CXODCF01.hpp"
#endif
#ifndef CXOSRU05_h
#include "CXODRU05.hpp"
#endif
#ifndef CXOSBS23_h
#include "CXODBS23.hpp"
#endif
#ifndef CXOSRSB9_h
#include "CXODRSB9.hpp"
#endif


//## begin module%6385D03600F1.declarations preserve=no
//## end module%6385D03600F1.declarations

//## begin module%6385D03600F1.additionalDeclarations preserve=yes
//## end module%6385D03600F1.additionalDeclarations


//## Modelname: DataNavigator Foundation::RepositorySegment_CAT%394E273800F0
namespace repositorysegment {
//## begin repositorysegment%394E273800F0.initialDeclarations preserve=yes
//## end repositorysegment%394E273800F0.initialDeclarations

// Class repositorysegment::AcquirerReferenceNumber 

AcquirerReferenceNumber::AcquirerReferenceNumber()
  //## begin AcquirerReferenceNumber::AcquirerReferenceNumber%6385CDD70179_const.hasinit preserve=no
  //## end AcquirerReferenceNumber::AcquirerReferenceNumber%6385CDD70179_const.hasinit
  //## begin AcquirerReferenceNumber::AcquirerReferenceNumber%6385CDD70179_const.initialization preserve=yes
  //## end AcquirerReferenceNumber::AcquirerReferenceNumber%6385CDD70179_const.initialization
{
  //## begin repositorysegment::AcquirerReferenceNumber::AcquirerReferenceNumber%6385CDD70179_const.body preserve=yes
  //## end repositorysegment::AcquirerReferenceNumber::AcquirerReferenceNumber%6385CDD70179_const.body
}


AcquirerReferenceNumber::~AcquirerReferenceNumber()
{
  //## begin repositorysegment::AcquirerReferenceNumber::~AcquirerReferenceNumber%6385CDD70179_dest.body preserve=yes
  //## end repositorysegment::AcquirerReferenceNumber::~AcquirerReferenceNumber%6385CDD70179_dest.body
}



//## Other Operations (implementation)
void AcquirerReferenceNumber::getACQ_REF_NO (GenericSegment* pGenericSegment, string& strACQ_REF_NO)
{
  //## begin repositorysegment::AcquirerReferenceNumber::getACQ_REF_NO%6385CDD7017E.body preserve=yes
   strACQ_REF_NO.erase();
   string strREF_DATA_ACQ_FMT;
   pGenericSegment->_field("REF_DATA_ACQ_FMT", strREF_DATA_ACQ_FMT, false, false);
   string strREF_DATA_ACQ;
   pGenericSegment->_field("REF_DATA_ACQ", strREF_DATA_ACQ, false, false);
   strREF_DATA_ACQ.resize(99, ' ');
   if (strREF_DATA_ACQ_FMT == "5"
      || strREF_DATA_ACQ_FMT == "6")
   {
      mastercardipm::segREF_DATA_ACQ* p = (struct mastercardipm::segREF_DATA_ACQ*)strREF_DATA_ACQ.data();
      strACQ_REF_NO.assign(p->sACQ_REF_NO, 23);
      return;
   }
   string strDATA_PRIV_ACQ_FMT;
   pGenericSegment->_field("DATA_PRIV_ACQ_FMT", strDATA_PRIV_ACQ_FMT, false, false);
   if (strREF_DATA_ACQ_FMT == "0"
      && strDATA_PRIV_ACQ_FMT == "50")
   {
      mastercardmds::segREF_DATA_ACQ* p = (struct mastercardmds::segREF_DATA_ACQ*)strREF_DATA_ACQ.data();
      strACQ_REF_NO.assign(p->sARN, sizeof(p->sARN));
      return;
   }
   string strREF_DATA_ISS_FMT;
   pGenericSegment->_field("REF_DATA_ISS_FMT", strREF_DATA_ISS_FMT, false, false);
   string strREF_DATA_ISS;
   pGenericSegment->_field("REF_DATA_ISS", strREF_DATA_ISS, false, false);
   strREF_DATA_ISS.resize(99, ' ');
   string strDATA_PRIV_ISS_FMT;
   pGenericSegment->_field("DATA_PRIV_ISS_FMT", strDATA_PRIV_ISS_FMT, false, false);
   if (strREF_DATA_ISS_FMT == "0"
      && strDATA_PRIV_ISS_FMT == "50")
   {
      mastercardmds::segREF_DATA_ISS* p = (struct mastercardmds::segREF_DATA_ISS*)strREF_DATA_ISS.data();
      strACQ_REF_NO.assign(p->sACQ_REF_NO, sizeof(p->sACQ_REF_NO));
      return;
   }
   string strACQ_PLAT_PROD_ID;
   pGenericSegment->_field("ACQ_PLAT_PROD_ID", strACQ_PLAT_PROD_ID, false, false);
   if (strREF_DATA_ACQ_FMT == "4"
      || strREF_DATA_ACQ_FMT == "31")
   {
      if (strACQ_PLAT_PROD_ID == "O"
         || strACQ_PLAT_PROD_ID == "V")
      {
         struct visabaseii::segREF_DATA_ACQ_IST* pREF_DATA_ACQ = (struct visabaseii::segREF_DATA_ACQ_IST*)strREF_DATA_ACQ.data();
         strACQ_REF_NO.assign(pREF_DATA_ACQ->sAcquirerRefNo, 23);
         return;
      }
      if (strREF_DATA_ACQ_FMT == "4")
      {
         string strAcqNetworkID;
         string strFirst("ADMIN_ISO_NETID");
         string strNET_ID_ACQ;
         pGenericSegment->_field("NET_ID_ACQ", strNET_ID_ACQ, false, false);
         strFirst += strNET_ID_ACQ;
         ConfigurationRepository::instance()->translate("X_GENERIC", strFirst, strAcqNetworkID, " ", " ", -1, false);
         visasms::segREF_DATA_ACQ* p = (struct visasms::segREF_DATA_ACQ*)strREF_DATA_ACQ.data();
         if (strAcqNetworkID == "0003" || strAcqNetworkID == "0004" || strAcqNetworkID == "0006")
         {
            strACQ_REF_NO.assign(p->sACQ_BIN, 6);
            strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO, 12);
            strACQ_REF_NO.append(p->sSYS_TRACE_AUDIT_NO, 6);
            return;
         }
         strACQ_REF_NO.assign(p->sRETRIEVAL_REF_NO + 4, 1);
         strACQ_REF_NO.append(p->sACQ_BIN, 6);
         strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO, 4);
         strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO + 6, 6);
         strACQ_REF_NO.append(p->sSYS_TRACE_AUDIT_NO + 1, 5);
         strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO + 5, 1);
         return;
      }
      visabaseii::segREF_DATA_ACQ* p = (struct visabaseii::segREF_DATA_ACQ*)strREF_DATA_ACQ.data();
      strACQ_REF_NO.assign(p->sRTR_REF_ID + 4, 1);
      strACQ_REF_NO.append(p->sACQ_BIN, 6);
      strACQ_REF_NO.append(p->sRTR_REF_ID, 4);
      strACQ_REF_NO.append(p->sRTR_REF_ID + 6, 6);
      strACQ_REF_NO.append(p->sSYS_TRACE_AUDIT_NO + 1, 5);
      strACQ_REF_NO.append(p->sRTR_REF_ID + 5, 1);
      return;

   }
   if (strREF_DATA_ISS_FMT == "4")
   {
      visasms::segREF_DATA_ISS* p = (struct visasms::segREF_DATA_ISS*)strREF_DATA_ISS.data();
      if (Extract::instance()->getCustomCode() == "COLES")
      {
         strACQ_REF_NO.assign("7",1);
         strACQ_REF_NO.append(p->sACQ_BIN, 6);
         if (strACQ_PLAT_PROD_ID == "R")
         {
            strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO, 4);
            strACQ_REF_NO.append("000",3);
            strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO + 4, 8);
         }
         else if (strACQ_PLAT_PROD_ID == "G")
         {
            string strTemp;
            pGenericSegment->_field("TSTAMP_TRANS", strTemp, false, false);
            string strDate(strTemp.data(), 8);
            string strTime;
            if(strTemp.length() > 8 )
               strTime.assign(strTemp.data() + 8, 6);
            if (!IF::Extract::instance()->getRecord("DSPEC   RSB9    DCFGMTOFF~Y", strTemp))
            {
               double dGMTOffset = Clock::instance()->getGMTOffset();
               Timestamp::adjustGMT(strDate, strTime, -int(dGMTOffset * 60));
            }
            Date hDate(strDate.c_str());
            strACQ_REF_NO.append(hDate.asString("%y%j").data() + 1, 4);
            strACQ_REF_NO.append(strTime.data(), 6);
            strACQ_REF_NO.append(p->sSYS_TRACE_AUDIT_NO + 1, 5);
         }
         strACQ_REF_NO.resize(22, '0');
         int k = 0;
         int lsum = 0;
         for (int i = 0; i < 22; i++)
         {
            k = strACQ_REF_NO[i] - '0';
            if (i % 2 == 1)
            {
               k *= 2;
               k = (k / 10) + (k % 10);
            }
            lsum += k;
         }
         int lcheckdigit = (lsum % 10 == 0 ? 0 : (10 - (lsum % 10)));
         char szTemp[PERCENTD];
         snprintf(szTemp, sizeof(szTemp), "%d", lcheckdigit);
         strACQ_REF_NO.append(szTemp, 1);
         return;
      }
      string strIssNetworkID;
      string strFirst("ADMIN_ISO_NETID");
      string strNET_ID_ISS;
      pGenericSegment->_field("NET_ID_ISS", strNET_ID_ISS, false, false);
      strFirst += strNET_ID_ISS;
      ConfigurationRepository::instance()->translate("X_GENERIC", strFirst, strIssNetworkID, " ", " ", -1, false);
      if (strIssNetworkID == "0003" || strIssNetworkID == "0004" || strIssNetworkID == "0006")
      {
         strACQ_REF_NO.assign(p->sACQ_BIN, 6);
         strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO, 12);
         strACQ_REF_NO.append(p->sSYS_TRACE_AUDIT_NO, 6);
         return;
      }
      strACQ_REF_NO.assign(p->sRETRIEVAL_REF_NO + 4, 1);
      strACQ_REF_NO.append(p->sACQ_BIN, 6);
      strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO, 4);
      strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO + 6, 6);
      strACQ_REF_NO.append(p->sSYS_TRACE_AUDIT_NO + 1, 5);
      strACQ_REF_NO.append(p->sRETRIEVAL_REF_NO + 5, 1);
      return;

   }
   if (strDATA_PRIV_ACQ_FMT == "104")
   {
      dina::segREF_DATA_ACQ* pREF_DATA_ACQ;
      pREF_DATA_ACQ = (struct dina::segREF_DATA_ACQ*)strREF_DATA_ACQ.data();
      strACQ_REF_NO.assign(pREF_DATA_ACQ->sRTR_REF_ID + 4, 1);
      strACQ_REF_NO.append(pREF_DATA_ACQ->sACQ_BIN, 6);
      strACQ_REF_NO.append(pREF_DATA_ACQ->sRTR_REF_ID, 4);
      strACQ_REF_NO.append(pREF_DATA_ACQ->sRTR_REF_ID + 6, 6);
      strACQ_REF_NO.append(pREF_DATA_ACQ->sSYS_TRACE_AUDIT_NO + 1, 5);
      strACQ_REF_NO.append(pREF_DATA_ACQ->sRTR_REF_ID + 5, 1);
      return;
   }
  //## end repositorysegment::AcquirerReferenceNumber::getACQ_REF_NO%6385CDD7017E.body
}

// Additional Declarations
  //## begin repositorysegment::AcquirerReferenceNumber%6385CDD70179.declarations preserve=yes
  //## end repositorysegment::AcquirerReferenceNumber%6385CDD70179.declarations

} // namespace repositorysegment

//## begin module%6385D03600F1.epilog preserve=yes
//## end module%6385D03600F1.epilog
