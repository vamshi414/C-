//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%53BD5B760028.cm preserve=no
//	$Date:   Jan 15 2021 09:20:20  $ $Author:   e1009839  $
//	$Revision:   1.16  $
//## end module%53BD5B760028.cm

//## begin module%53BD5B760028.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%53BD5B760028.cp

//## Module: CXOSTC58%53BD5B760028; Package body
//## Subsystem: TCDLL%3884FCAD01AC
//## Source file: C:\bV03.0D.R001\Windows\Build\Dn\Server\Library\Tcdll\CXOSTC58.cpp

//## begin module%53BD5B760028.additionalIncludes preserve=no
//## end module%53BD5B760028.additionalIncludes

//## begin module%53BD5B760028.includes preserve=yes
#include "CXODRU34.hpp"
#include "CXODIF16.hpp"
#include "CXODDB48.hpp"
//## end module%53BD5B760028.includes

#ifndef CXOSRU11_h
#include "CXODRU11.hpp"
#endif
#ifndef CXOSBS26_h
#include "CXODBS26.hpp"
#endif
#ifndef CXOSBS23_h
#include "CXODBS23.hpp"
#endif
#ifndef CXOSTC58_h
#include "CXODTC58.hpp"
#endif


//## begin module%53BD5B760028.declarations preserve=no
//## end module%53BD5B760028.declarations

//## begin module%53BD5B760028.additionalDeclarations preserve=yes
//## end module%53BD5B760028.additionalDeclarations


//## Modelname: Totals Management::TotalsCommand_CAT%3884FA670353
namespace totalscommand {
//## begin totalscommand%3884FA670353.initialDeclarations preserve=yes
//## end totalscommand%3884FA670353.initialDeclarations

// Class totalscommand::FinancialTotal

//## begin totalscommand::FinancialTotal::Instance%53BD5E16016C.attr preserve=no  private: static totalscommand::FinancialTotal* {V} 0
totalscommand::FinancialTotal* FinancialTotal::m_pInstance = 0;
//## end totalscommand::FinancialTotal::Instance%53BD5E16016C.attr

FinancialTotal::FinancialTotal()
  //## begin FinancialTotal::FinancialTotal%53BD5B370101_const.hasinit preserve=no
      : m_pGenericSegment(0)
  //## end FinancialTotal::FinancialTotal%53BD5B370101_const.hasinit
  //## begin FinancialTotal::FinancialTotal%53BD5B370101_const.initialization preserve=yes
  //## end FinancialTotal::FinancialTotal%53BD5B370101_const.initialization
{
  //## begin totalscommand::FinancialTotal::FinancialTotal%53BD5B370101_const.body preserve=yes
   memcpy(m_sID,"TC58",4);
   m_pGenericSegment = new GenericSegment;
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("AcquirerBusiness"),make_pair(string("AM"),3)));
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("AcquirerInstitution"),make_pair(string("AI"),4)));
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("AcquirerProcessor"),make_pair(string("AP"),5)));
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("AcquirerTerminal"),make_pair(string("AT"),2)));
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("Switch"),make_pair(string("CU"), 1)));
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("IssuerInstitution"),make_pair(string("II"),6)));
   m_hEntityType.insert(map<string,pair<string,int>,less<string> >::value_type(string("IssuerProcessor"),make_pair(string("IP"),7)));
   m_pInstance = this;
  //## end totalscommand::FinancialTotal::FinancialTotal%53BD5B370101_const.body
}


FinancialTotal::~FinancialTotal()
{
  //## begin totalscommand::FinancialTotal::~FinancialTotal%53BD5B370101_dest.body preserve=yes
   delete m_pGenericSegment;
  //## end totalscommand::FinancialTotal::~FinancialTotal%53BD5B370101_dest.body
}



//## Other Operations (implementation)
void FinancialTotal::bind (reusable::Query& hQuery, const string& strParent, const string& strTag)
{
  //## begin totalscommand::FinancialTotal::bind%53BD5DD6007A.body preserve=yes
   m_hParent.insert(strParent);
   map<string,set<string,less<string> >,less<string> >::iterator q = m_hChild.find(strParent);
   if (q == m_hChild.end())
   {
      set<string,less<string> > x;
      pair<map<string,set<string,less<string> >,less<string> >::iterator,bool> hResult;
      hResult = m_hChild.insert(map<string,set<string,less<string> >,less<string> >::value_type(strParent,x));
      q = hResult.first;
   }
   (*q).second.insert(strTag);
   string strFirst(strParent);
   strFirst += ':';
   strFirst += strTag;
   pair<multimap<string,database::Column,less<string> >::iterator,multimap<string,database::Column,less<string> >::iterator> hRange = m_hTag.equal_range(strFirst);
   if (hRange.first == hRange.second)
   {
      string strTxt("Undefined column: ");
      strTxt += strTag;
      SOAPSegment::instance()->setMsg("RS90.1","Validation Error",strTxt);
      return;
   }
   if (strTag == "DateSettlement")
      return;
   char* pszFunction = 0;
   multimap<string,database::Column,less<string> >::iterator p = hRange.first;
   for (;p != hRange.second;++p)
   {
      if ((*p).second.getTable() == "T_FIN_TOTAL"
         || (*p).second.getTable() == "T_FIN_SUM")
         pszFunction = "SUM";
      else
      {
         vector<string> hTokens;
         Buffer::parse((*p).second.getColumn()," ",hTokens);
         if (hTokens[0] == "ENTITY_ID")
         {
            if (m_strENTITY_TYPE[0] != hTokens[1].substr(0,2))
            {
               m_strENTITY_TYPE[1] = hTokens[1].substr(0,2);
               join(hQuery,strTag,hTokens[1]);
            }
         }
         pszFunction = 0;
         vector<string> hTokens2;
         Buffer::parse((*p).second.getTable()," ",hTokens2);
         string strColumn(hTokens2[hTokens2.size() - 1]);
         strColumn += ".";
         strColumn += hTokens[0];
         if (hQuery.getGroupByClause().find(strColumn) == string::npos)
         {
            string strGroupByClause(hQuery.getGroupByClause());
            if (!strGroupByClause.empty())
               strGroupByClause.append(",",1);
            strGroupByClause += strColumn;
            hQuery.setGroupByClause(strGroupByClause);
            hQuery.setOrderByClause(strGroupByClause);
         }
      }
      m_pGenericSegment->bind((*p).second.getTable().c_str(),(*p).second.getColumn().c_str(),hQuery,pszFunction,(*p).second.getNPI());
   }
  //## end totalscommand::FinancialTotal::bind%53BD5DD6007A.body
}

totalscommand::FinancialTotal* FinancialTotal::instance ()
{
  //## begin totalscommand::FinancialTotal::instance%53BD5DEF005C.body preserve=yes
   if (!m_pInstance)
      new FinancialTotal;
   return m_pInstance;
  //## end totalscommand::FinancialTotal::instance%53BD5DEF005C.body
}

void FinancialTotal::join (reusable::Query& hQuery, const string& strTag, const string& strEntityType)
{
  //## begin totalscommand::FinancialTotal::join%53E35F700214.body preserve=yes
   string strT_FIN_E_GROUP_ITEM("T_FIN_E_GROUP_ITEM   _T_FIN_E_GROUP_ITEM");
   strT_FIN_E_GROUP_ITEM.replace(19,2,strEntityType.data(),2);
   string strT_FIN_PERIOD("T_FIN_PERIOD   _T_FIN_PERIOD");
   strT_FIN_PERIOD.replace(13,2,strEntityType.data(),2);
   string strT_FIN_ENTITY("T_FIN_ENTITY   _T_FIN_ENTITY");
   strT_FIN_ENTITY.replace(13,2,strEntityType.data(),2);
   hQuery.join("T_FIN_TOTAL","INNER",strT_FIN_E_GROUP_ITEM.c_str(),"ENTITY_GROUP_ID");
   hQuery.join(strT_FIN_E_GROUP_ITEM.c_str(),"INNER",strT_FIN_PERIOD.c_str(),"PERIOD_ID");
   hQuery.join(strT_FIN_PERIOD.c_str(),"INNER",strT_FIN_ENTITY.c_str(),"T_FIN_ENTITY_ID");
   map<string,pair<string,int>,less<string> >::const_iterator p = m_hEntityType.find(strTag);
   hQuery.setBasicPredicate(strT_FIN_E_GROUP_ITEM.c_str(),"SEQUENCE_NO","=",(*p).second.second);
  //## end totalscommand::FinancialTotal::join%53E35F700214.body
}

void FinancialTotal::reset (reusable::Query& hQuery)
{
  //## begin totalscommand::FinancialTotal::reset%53BDB00F01BA.body preserve=yes
   if (m_hTag.empty())
   {
      char* pszTag[55] =
      {
         "Total:AcquirerAmount~T_FIN_TOTAL~AMT_RECON_ACQ",
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
         "Total:CardholderBillingAmount~T_FIN_TOTAL~AMT_CARD_BILL",
         "Total:CardholderBillingAmount~T_FIN_CATEGORY~CUR_CARD_BILL",
         "Total:Switch~T_FIN_ENTITY CU_T_FIN_ENTITY~ENTITY_ID CU_ENTITY_ID",
         "Total:SwitchDate~T_FIN_PERIOD CU_T_FIN_PERIOD~DATE_RECON CU_DATE_RECON",
         "Total:DateSettlement~xx_T_FIN_PERIOD~DATE_RECON",
         "Total:FinancialType~T_FIN_CATEGORY~FIN_TYPE",
         "Total:FunctionCode~T_FIN_CATEGORY~FUNC_CODE",
         "Total:IssuerAmount~T_FIN_TOTAL~AMT_RECON_ISS",
         "Total:IssuerAmount~T_FIN_CATEGORY~CUR_RECON_ISS",
         "Total:IssuerDate~T_FIN_PERIOD IP_T_FIN_PERIOD~DATE_RECON IP_DATE_RECON",
         "Total:IssuerImpact~T_FIN_CATEGORY~IMPACT_TO_ISS",
         "Total:IssuerInstitution~T_FIN_ENTITY II_T_FIN_ENTITY~ENTITY_ID II_ENTITY_ID",
         "Total:IssuerNetwork~T_FIN_CATEGORY~NET_ID_ISS",
         "Total:IssuerProcessor~T_FIN_ENTITY IP_T_FIN_ENTITY~ENTITY_ID IP_ENTITY_ID",
         "Total:MerchantType~T_FIN_CATEGORY~MERCH_TYPE",
         "Total:ReconciliationAmount~T_FIN_TOTAL~AMT_RECON_NET",
         "Total:ReconciliationAmount~T_FIN_CATEGORY~CUR_RECON_NET",
         "Total:ReversedBy~T_FIN_CATEGORY~REV_BY",
         "Total:TotalType~T_FIN_CATEGORY~TOTAL_TYPE",
         "Total:TransactionAmount~T_FIN_TOTAL~AMT_TRAN",
         "Total:TransactionAmount~T_FIN_CATEGORY~CUR_TRAN",
         "Total:TransactionClass~T_FIN_CATEGORY~TRAN_CLASS",
         "Total:TransactionCount~T_FIN_TOTAL~TRAN_COUNT",
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
   hQuery.join("T_FIN_TOTAL","INNER","T_FIN_CATEGORY","CATEGORY_ID");
  //## end totalscommand::FinancialTotal::reset%53BDB00F01BA.body
}

void FinancialTotal::setBasicPredicate (reusable::Query& hQuery, const string& strParent, const string& strTag, string& strOperator, const string& strToken)
{
  //## begin totalscommand::FinancialTotal::setBasicPredicate%53BD5DDF0031.body preserve=yes
   if (strTag == "StartDate")
   {
      m_strStartDate = strToken;
      return;
   }
   if (strTag == "EndDate")
   {
      m_strEndDate = strToken;
      return;
   }
   string strFirst(strParent);
   strFirst += ':';
   strFirst += strTag;
   multimap<string,database::Column,less<string> >::iterator p = m_hTag.find(strFirst);
   if (p != m_hTag.end())
   {
      vector<string> hTokens;
      Buffer::parse((*p).second.getColumn()," ",hTokens);
      if (hTokens[0] == "ENTITY_ID")
      {
         join(hQuery,strTag,hTokens[1]);
         map<string,pair<string,int>,less<string> >::const_iterator q = m_hEntityType.find(strTag);
         if (q != m_hEntityType.end())
         {
            m_strENTITY_TYPE[0] = (*q).second.first;
            string strTable("T_FIN_PERIOD   _T_FIN_PERIOD");
            strTable.replace(13,2,m_strENTITY_TYPE[0].data(),2);
            string strColumn("DATE_RECON   _DATE_RECON");
            strColumn.replace(11,2,m_strENTITY_TYPE[0].data(),2);
            m_pGenericSegment->bind(strTable.c_str(),strColumn.c_str(),hQuery);
            string strGroupByClause(hQuery.getGroupByClause());
            if (!strGroupByClause.empty())
               strGroupByClause.append(",",1);
            strGroupByClause.append(strTable.data() + 13,15);
            strGroupByClause += ".DATE_RECON";
            hQuery.setGroupByClause(strGroupByClause);
            hQuery.setOrderByClause(strGroupByClause);
            string strParent("Total");
            map<string,set<string,less<string> >,less<string> >::iterator q = m_hChild.find(strParent);
            if (q == m_hChild.end())
            {
               set<string,less<string> > x;
               pair<map<string,set<string,less<string> >,less<string> >::iterator,bool> hResult;
               hResult = m_hChild.insert(map<string,set<string,less<string> >,less<string> >::value_type(strParent,x));
               q = hResult.first;
                     }
            string strTag("AcquirerDate");
            (*q).second.insert(strTag);
         }
      }
      if (strTag == "AcquirerBusiness"
         && Extract::instance()->getDatabaseVendor() != "SQLSERVER")
         database::ReportingLevel::join(hQuery,(*p).second.getTable().c_str(),hTokens[0].c_str(),strOperator,strToken);
      else
         hQuery.setBasicPredicate((*p).second.getTable().c_str(),hTokens[0].c_str(),strOperator.c_str(),strToken.c_str());
   }
  //## end totalscommand::FinancialTotal::setBasicPredicate%53BD5DDF0031.body
}

void FinancialTotal::setDatePredicate (reusable::Query& hQuery)
{
  //## begin totalscommand::FinancialTotal::setDatePredicate%53E24E5802B0.body preserve=yes
   if (m_strENTITY_TYPE[0].empty())
   {
      if (!hQuery.getSearchCondition().empty())
         hQuery.getSearchCondition().append(" AND");
      hQuery.getSearchCondition().append(" ((");
      hQuery.setBasicPredicate("T_FIN_PERIOD AP_T_FIN_PERIOD","DATE_RECON",">=",m_strStartDate.c_str());
      hQuery.setBasicPredicate("T_FIN_PERIOD AP_T_FIN_PERIOD","DATE_RECON","<=",m_strEndDate.c_str());
      hQuery.getSearchCondition().append(") OR (");
      hQuery.setBasicPredicate("T_FIN_PERIOD IP_T_FIN_PERIOD", "DATE_RECON", ">=", m_strStartDate.c_str());
      hQuery.setBasicPredicate("T_FIN_PERIOD IP_T_FIN_PERIOD", "DATE_RECON", "<=", m_strEndDate.c_str());
      hQuery.getSearchCondition().append(") OR (");
      hQuery.setBasicPredicate("T_FIN_PERIOD II_T_FIN_PERIOD", "DATE_RECON", ">=", m_strStartDate.c_str());
      hQuery.setBasicPredicate("T_FIN_PERIOD II_T_FIN_PERIOD", "DATE_RECON", "<=", m_strEndDate.c_str());
      hQuery.getSearchCondition().append(") OR (");
      hQuery.setBasicPredicate("T_FIN_PERIOD AI_T_FIN_PERIOD", "DATE_RECON", ">=", m_strStartDate.c_str());
      hQuery.setBasicPredicate("T_FIN_PERIOD AI_T_FIN_PERIOD", "DATE_RECON", "<=", m_strEndDate.c_str());
      hQuery.getSearchCondition().append(") OR (");
      hQuery.setBasicPredicate("T_FIN_PERIOD CU_T_FIN_PERIOD", "DATE_RECON", ">=", m_strStartDate.c_str());
      hQuery.setBasicPredicate("T_FIN_PERIOD CU_T_FIN_PERIOD", "DATE_RECON", "<=", m_strEndDate.c_str());
      hQuery.getSearchCondition().append("))");
      return;
   }
   string strTable("T_FIN_PERIOD   _T_FIN_PERIOD");
   strTable.replace(13,2,m_strENTITY_TYPE[0].data(),2);
   if (!m_strStartDate.empty())
      hQuery.setBasicPredicate(strTable.c_str(),"DATE_RECON",">=",m_strStartDate.c_str());
   if (!m_strEndDate.empty())
      hQuery.setBasicPredicate(strTable.c_str(),"DATE_RECON","<=",m_strEndDate.c_str());
  //## end totalscommand::FinancialTotal::setDatePredicate%53E24E5802B0.body
}

// Additional Declarations
  //## begin totalscommand::FinancialTotal%53BD5B370101.declarations preserve=yes
  //## end totalscommand::FinancialTotal%53BD5B370101.declarations

} // namespace totalscommand

//## begin module%53BD5B760028.epilog preserve=yes
//## end module%53BD5B760028.epilog
