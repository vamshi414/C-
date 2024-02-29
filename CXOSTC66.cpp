//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%5C9CCF9E0276.cm preserve=no
//	$Date:   May 10 2019 08:32:00  $ $Author:   e1009839  $
//	$Revision:   1.1  $
//## end module%5C9CCF9E0276.cm

//## begin module%5C9CCF9E0276.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%5C9CCF9E0276.cp

//## Module: CXOSTC66%5C9CCF9E0276; Package body
//## Subsystem: TCDLL%3884FCAD01AC
//## Source file: C:\bV03.0D.R001\Windows\Build\Dn\Server\Library\Tcdll\CXOSTC66.cpp

//## begin module%5C9CCF9E0276.additionalIncludes preserve=no
//## end module%5C9CCF9E0276.additionalIncludes

//## begin module%5C9CCF9E0276.includes preserve=yes
//## end module%5C9CCF9E0276.includes

#ifndef CXOSRU11_h
#include "CXODRU11.hpp"
#endif
#ifndef CXOSRU34_h
#include "CXODRU34.hpp"
#endif
#ifndef CXOSTC66_h
#include "CXODTC66.hpp"
#endif


//## begin module%5C9CCF9E0276.declarations preserve=no
//## end module%5C9CCF9E0276.declarations

//## begin module%5C9CCF9E0276.additionalDeclarations preserve=yes
//## end module%5C9CCF9E0276.additionalDeclarations


//## Modelname: Totals Management::TotalsCommand_CAT%3884FA670353
namespace totalscommand {
//## begin totalscommand%3884FA670353.initialDeclarations preserve=yes
//## end totalscommand%3884FA670353.initialDeclarations

// Class totalscommand::FinancialSum

FinancialSum::FinancialSum()
  //## begin FinancialSum::FinancialSum%5C9CCF0503CD_const.hasinit preserve=no
  //## end FinancialSum::FinancialSum%5C9CCF0503CD_const.hasinit
  //## begin FinancialSum::FinancialSum%5C9CCF0503CD_const.initialization preserve=yes
  //## end FinancialSum::FinancialSum%5C9CCF0503CD_const.initialization
{
  //## begin totalscommand::FinancialSum::FinancialSum%5C9CCF0503CD_const.body preserve=yes
   memcpy(m_sID,"TC66",4);
  //## end totalscommand::FinancialSum::FinancialSum%5C9CCF0503CD_const.body
}


FinancialSum::~FinancialSum()
{
  //## begin totalscommand::FinancialSum::~FinancialSum%5C9CCF0503CD_dest.body preserve=yes
  //## end totalscommand::FinancialSum::~FinancialSum%5C9CCF0503CD_dest.body
}



//## Other Operations (implementation)
void FinancialSum::join (reusable::Query& hQuery, const string& strTag, const string& strEntityType)
{
  //## begin totalscommand::FinancialSum::join%5C9CD0B20167.body preserve=yes
   string strPeriod("  _PERIOD_ID");
   strPeriod.replace(0,2,strEntityType.data(),2);
   string strT_FIN_PERIOD("T_FIN_PERIOD   _T_FIN_PERIOD");
   strT_FIN_PERIOD.replace(13,2,strEntityType.data(),2);
   string strT_FIN_ENTITY("T_FIN_ENTITY   _T_FIN_ENTITY");
   strT_FIN_ENTITY.replace(13,2,strEntityType.data(),2);
   hQuery.join("T_FIN_SUM","INNER",strT_FIN_PERIOD.c_str(),strPeriod.c_str(),"PERIOD_ID");
   hQuery.join(strT_FIN_PERIOD.c_str(),"INNER",strT_FIN_ENTITY.c_str(),"T_FIN_ENTITY_ID");
  //## end totalscommand::FinancialSum::join%5C9CD0B20167.body
}

void FinancialSum::reset (reusable::Query& hQuery)
{
  //## begin totalscommand::FinancialSum::reset%5C9CD6DB025D.body preserve=yes
   if (m_hTag.empty())
   {
      char* pszTag[55] =
      {
         "Total:AcquirerAmount~T_FIN_SUM~AMT_RECON_ACQ",
         "Total:AcquirerAmount~T_FIN_CATEGORY~CUR_RECON_ACQ",
         "Total:AcquirerBusiness~T_FIN_ENTITY AM_T_FIN_ENTITY~ENTITY_ID AM_ENTITY_ID",
         "Total:AcquirerDate~T_FIN_PERIOD AP_T_FIN_PERIOD~DATE_RECON AP_DATE_RECON",
         "Total:AcquirerImpact~T_FIN_CATEGORY~IMPACT_TO_ACQ",
         "Total:AcquirerInstitution~T_FIN_ENTITY AI_T_FIN_ENTITY~ENTITY_ID AI_ENTITY_ID",
         "Total:AcquirerNetwork~T_FIN_CATEGORY~NET_ID_ACQ",
         "Total:AcquirerProcessor~T_FIN_ENTITY AP_T_FIN_ENTITY~ENTITY_ID AP_ENTITY_ID",
         "Total:AcquirerTerminal~T_FIN_ENTITY AT_T_FIN_ENTITY~ENTITY_ID AT_ENTITY_ID",
         "Total:AcquirerTerminalEndOfDay~T_FIN_PERIOD AT_T_FIN_PERIOD~TSTAMP_END AT_TSTAMP_END",
         "Total:AcquirerInstitutionEndOfDay~T_FIN_PERIOD AI_T_FIN_PERIOD~TSTAMP_END AI_TSTAMP_END",
         "Total:AcquirerInstitutionDate~T_FIN_PERIOD AI_T_FIN_PERIOD~DATE_RECON AI_DATE_RECON",
         "Total:AcquirerInstitutionFrom~T_FIN_PERIOD AI_T_FIN_PERIOD~TSTAMP_TRANS_FROM AI_TSTAMP_TRANS_FROM",
         "Total:AcquirerInstitutionTo~T_FIN_PERIOD AI_T_FIN_PERIOD~TSTAMP_TRANS_TO AI_TSTAMP_TRANS_TO",
         "Total:AcquirerBusinessEndOfDay~T_FIN_PERIOD AM_T_FIN_PERIOD~TSTAMP_END AM_TSTAMP_END",
         "Total:AcquirerProcessorEndOfDay~T_FIN_PERIOD AP_T_FIN_PERIOD~TSTAMP_END AP_TSTAMP_END",
         "Total:AcquirerProcessorDate~T_FIN_PERIOD AP_T_FIN_PERIOD~DATE_RECON AP_DATE_RECON",
         "Total:AcquirerProcessorFrom~T_FIN_PERIOD AP_T_FIN_PERIOD~TSTAMP_TRANS_FROM AP_TSTAMP_TRANS_FROM",
         "Total:AcquirerProcessorTo~T_FIN_PERIOD AP_T_FIN_PERIOD~TSTAMP_TRANS_TO AP_TSTAMP_TRANS_TO",
         "Total:IssuerInstitutionEndOfDay~T_FIN_PERIOD II_T_FIN_PERIOD~TSTAMP_END II_TSTAMP_END",
         "Total:IssuerInstitutionDate~T_FIN_PERIOD II_T_FIN_PERIOD~DATE_RECON II_DATE_RECON",
         "Total:IssuerInstitutionFrom~T_FIN_PERIOD II_T_FIN_PERIOD~TSTAMP_TRANS_FROM II_TSTAMP_TRANS_FROM",
         "Total:IssuerInstitutionTo~T_FIN_PERIOD II_T_FIN_PERIOD~TSTAMP_TRANS_TO II_TSTAMP_TRANS_TO",
         "Total:IssuerProcessorEndOfDay~T_FIN_PERIOD IP_T_FIN_PERIOD~TSTAMP_END IP_TSTAMP_END",
         "Total:IssuerProcessorDate~T_FIN_PERIOD IP_T_FIN_PERIOD~DATE_RECON IP_DATE_RECON",
         "Total:IssuerProcessorFrom~T_FIN_PERIOD IP_T_FIN_PERIOD~TSTAMP_TRANS_FROM IP_TSTAMP_TRANS_FROM",
         "Total:IssuerProcessorTo~T_FIN_PERIOD IP_T_FIN_PERIOD~TSTAMP_TRANS_TO IP_TSTAMP_TRANS_TO",
         "Total:ActionCode~T_FIN_CATEGORY~ACT_CODE",
         "Total:AuthorizedBy~T_FIN_CATEGORY~AUTH_BY",
         "Total:CardholderBillingAmount~T_FIN_SUM~AMT_CARD_BILL",
         "Total:CardholderBillingAmount~T_FIN_CATEGORY~CUR_CARD_BILL",
         "Total:Switch~T_FIN_ENTITY CU_T_FIN_ENTITY~ENTITY_ID CU_ENTITY_ID",
         "Total:SwitchDate~T_FIN_PERIOD CU_T_FIN_PERIOD~DATE_RECON CU_DATE_RECON",
         "Total:DateSettlement~xx_T_FIN_PERIOD~DATE_RECON",
         "Total:FinancialType~T_FIN_CATEGORY~FIN_TYPE",
         "Total:FunctionCode~T_FIN_CATEGORY~FUNC_CODE",
         "Total:IssuerAmount~T_FIN_SUM~AMT_RECON_ISS",
         "Total:IssuerAmount~T_FIN_CATEGORY~CUR_RECON_ISS",
         "Total:IssuerDate~T_FIN_PERIOD IP_T_FIN_PERIOD~DATE_RECON IP_DATE_RECON",
         "Total:IssuerImpact~T_FIN_CATEGORY~IMPACT_TO_ISS",
         "Total:IssuerInstitution~T_FIN_ENTITY II_T_FIN_ENTITY~ENTITY_ID II_ENTITY_ID",
         "Total:IssuerNetwork~T_FIN_CATEGORY~NET_ID_ISS",
         "Total:IssuerProcessor~T_FIN_ENTITY IP_T_FIN_ENTITY~ENTITY_ID IP_ENTITY_ID",
         "Total:MerchantType~T_FIN_CATEGORY~MERCH_TYPE",
         "Total:ReconciliationAmount~T_FIN_SUM~AMT_RECON_NET",
         "Total:ReconciliationAmount~T_FIN_CATEGORY~CUR_RECON_NET",
         "Total:ReversedBy~T_FIN_CATEGORY~REV_BY",
         "Total:TotalType~T_FIN_CATEGORY~TOTAL_TYPE",
         "Total:TransactionAmount~T_FIN_SUM~AMT_TRAN",
         "Total:TransactionAmount~T_FIN_CATEGORY~CUR_TRAN",
         "Total:TransactionClass~T_FIN_CATEGORY~TRAN_CLASS",
         "Total:TransactionCount~T_FIN_SUM~TRAN_COUNT",
         "Total:TransactionDisposition~T_FIN_CATEGORY~TRAN_DISPOSITION",
         "Total:TransactionType~T_FIN_CATEGORY~TRAN_TYPE_ID",
         "Total:NetworkProgram~T_FIN_CATEGORY~NETWORK_PROGRAM"
      };
      for (int i = 0;i < 55;++i)
      {
         vector<string> hTokens;
         Buffer::parse(string(pszTag[i]),"~",hTokens);
         m_hTag.insert(multimap<string,database::Column,less<string> >::value_type(hTokens[0],database::Column(hTokens[1],hTokens[2],0)));
      }
   }
   m_strENTITY_TYPE[0].erase();
   m_strENTITY_TYPE[1].erase();
   m_strStartDate.erase();
   m_strEndDate.erase();
   m_hChild.erase(m_hChild.begin(),m_hChild.end());
   m_hParent.erase(m_hParent.begin(),m_hParent.end());
   hQuery.join("T_FIN_SUM","INNER","T_FIN_CATEGORY","CATEGORY_ID");
  //## end totalscommand::FinancialSum::reset%5C9CD6DB025D.body
}

// Additional Declarations
  //## begin totalscommand::FinancialSum%5C9CCF0503CD.declarations preserve=yes
  //## end totalscommand::FinancialSum%5C9CCF0503CD.declarations

} // namespace totalscommand

//## begin module%5C9CCF9E0276.epilog preserve=yes
//## end module%5C9CCF9E0276.epilog
