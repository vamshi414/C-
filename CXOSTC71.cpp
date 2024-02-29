//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%53BAD1990182.cm preserve=no
//	$Date:   Jun 11 2020 10:49:56  $ $Author:   e5579974  $
//	$Revision:   1.2  $
//## end module%53BAD1990182.cm

//## begin module%53BAD1990182.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%53BAD1990182.cp

//## Module: CXOSTC71%53BAD1990182; Package body
//## Subsystem: TCDLL%3884FCAD01AC
//## Source file: C:\bV03.0D.R001\Windows\Build\Dn\Server\Library\Tcdll\CXOSTC71.cpp

//## begin module%53BAD1990182.additionalIncludes preserve=no
//## end module%53BAD1990182.additionalIncludes

//## begin module%53BAD1990182.includes preserve=yes
#ifndef CXOSIF16_h
#include "CXODIF16.hpp"
#endif

//## end module%53BAD1990182.includes

#ifndef CXOSBS26_h
#include "CXODBS26.hpp"
#endif
#ifndef CXOSTC72_h
#include "CXODTC72.hpp"
#endif
#ifndef CXOSDB02_h
#include "CXODDB02.hpp"
#endif
#ifndef CXOSRU12_h
#include "CXODRU12.hpp"
#endif
#ifndef CXOSDB01_h
#include "CXODDB01.hpp"
#endif
#ifndef CXOSTC58_h
#include "CXODTC58.hpp"
#endif
#ifndef CXOSTC57_h
#include "CXODTC57.hpp"
#endif
#ifndef CXOSTC59_h
#include "CXODTC59.hpp"
#endif
#ifndef CXOSTC66_h
#include "CXODTC66.hpp"
#endif
#ifndef CXOSNS29_h
#include "CXODNS29.hpp"
#endif
#ifndef CXOSDB47_h
#include "CXODDB47.hpp"
#endif
#ifndef CXOSTC71_h
#include "CXODTC71.hpp"
#endif


//## begin module%53BAD1990182.declarations preserve=no
//## end module%53BAD1990182.declarations

//## begin module%53BAD1990182.additionalDeclarations preserve=yes
//## end module%53BAD1990182.additionalDeclarations


//## Modelname: Totals Management::TotalsCommand_CAT%3884FA670353
namespace totalscommand {
//## begin totalscommand%3884FA670353.initialDeclarations preserve=yes
//## end totalscommand%3884FA670353.initialDeclarations

// Class totalscommand::FinancialTotalsCommand

FinancialTotalsCommand::FinancialTotalsCommand()
  //## begin FinancialTotalsCommand::FinancialTotalsCommand%53BACFE303A4_const.hasinit preserve=no
      : m_pView(0)
  //## end FinancialTotalsCommand::FinancialTotalsCommand%53BACFE303A4_const.hasinit
  //## begin FinancialTotalsCommand::FinancialTotalsCommand%53BACFE303A4_const.initialization preserve=yes
   ,SOAPCommand("S0003D",0)
  //## end FinancialTotalsCommand::FinancialTotalsCommand%53BACFE303A4_const.initialization
{
  //## begin totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%53BACFE303A4_const.body preserve=yes
#ifdef MVS
   m_strTemplate.assign("RXRFINT",7);
#else
   m_strTemplate.assign("CXORRF01",8);
#endif
   m_hXMLText.add('T',(Segment*)totalscommand::FinancialTotal::instance()->getGenericSegment());
   m_hXMLText.add('F',(Segment*)totalscommand::TransactionTotal::instance()->getGenericSegment());
   m_hXMLText.add('X',segment::SOAPSegment::instance());
   m_pXMLItem = new XMLItem();
   m_pXMLHandler = new FinancialTotalsHandler(m_pXMLItem,this);
   m_hQuery[0].attach(this);
   m_hQuery[1].attach(this);
  //## end totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%53BACFE303A4_const.body
}

FinancialTotalsCommand::FinancialTotalsCommand (Handler* pSuccessor)
  //## begin totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%54F4DD1F023A.hasinit preserve=no
      : m_pView(0)
  //## end totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%54F4DD1F023A.hasinit
  //## begin totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%54F4DD1F023A.initialization preserve=yes
   ,SOAPCommand("S0003D","@##XRFINT ")
  //## end totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%54F4DD1F023A.initialization
{
  //## begin totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%54F4DD1F023A.body preserve=yes
   m_pSuccessor = pSuccessor;
#ifdef MVS
   m_strTemplate.assign("RXRFINT",7);
#else
   m_strTemplate.assign("CXORRF01",8);
#endif
  // if (entitysegment::Customer::instance()->getTotalsVersion() == 2)
  //    new totalscommand::FinancialSum;
   m_hXMLText.add('T',(Segment*)totalscommand::FinancialTotal::instance()->getGenericSegment());
   m_hXMLText.add('F',(Segment*)totalscommand::TransactionTotal::instance()->getGenericSegment());
   m_hXMLText.add('X',segment::SOAPSegment::instance());
   m_pXMLItem = new XMLItem();
   m_pXMLHandler = new FinancialTotalsHandler(m_pXMLItem,this);
   m_hQuery[0].attach(this);
   m_hQuery[1].attach(this);
  //## end totalscommand::FinancialTotalsCommand::FinancialTotalsCommand%54F4DD1F023A.body
}


FinancialTotalsCommand::~FinancialTotalsCommand()
{
  //## begin totalscommand::FinancialTotalsCommand::~FinancialTotalsCommand%53BACFE303A4_dest.body preserve=yes
  //## end totalscommand::FinancialTotalsCommand::~FinancialTotalsCommand%53BACFE303A4_dest.body
}



//## Other Operations (implementation)
bool FinancialTotalsCommand::execute ()
{
  //## begin totalscommand::FinancialTotalsCommand::execute%53BAD4820269.body preserve=yes
   m_hQuery[0].reset();
   m_hQuery[1].reset();
   m_hQuery[0].setTruncate(false);
   m_hQuery[1].setTruncate(false);
   ((Segment*)totalscommand::FinancialTotal::instance()->getGenericSegment())->reset();
   ((Segment*)totalscommand::TransactionTotal::instance()->getGenericSegment())->reset();
   totalscommand::FinancialTotal::instance()->reset(m_hQuery[0]);
   totalscommand::TransactionTotal::instance()->reset(m_hQuery[1]);
   if (!m_pXMLDocument)
#ifdef MVS
      m_pXMLDocument = new XMLDocument("JCL", m_strTemplate.c_str(), &m_hRow, &m_hXMLText);
#else
      m_pXMLDocument = new XMLDocument("SOURCE", m_strTemplate.c_str(), &m_hRow, &m_hXMLText);
#endif
   m_pXMLDocument->reset();
   m_pXMLDocument->setMaximumSize(64000);
   m_pXMLDocument->add("FinancialTotalsRsp");
   int i = parse();
   if (i != 0)
   {
      reply();
      return true;
   }
   if (((totalscommand::FinancialTotal::instance()->getENTITY_TYPE(0) == "AT"
      || totalscommand::FinancialTotal::instance()->getENTITY_TYPE(1) == "AT")
      && totalscommand::Total::instance()->isDisabled("AT"))
      || ((totalscommand::FinancialTotal::instance()->getENTITY_TYPE(0) == "AM"
      || totalscommand::FinancialTotal::instance()->getENTITY_TYPE(1) == "AM")
      && totalscommand::Total::instance()->isDisabled("AM"))
      || Extract::instance()->getCustomCode() == "RPSL")
   {
      totalscommand::TransactionTotal::instance()->setDatePredicate(m_hQuery[1]);
      m_hQuery[0] = m_hQuery[1]; // query FIN_Lyyyymm/FIN_RECORDyyyymm instead of T_FIN_TOTAL/T_FIN_CATEGORY
      m_pView = totalscommand::TransactionTotal::instance();
   }
   else
   {
      totalscommand::FinancialTotal::instance()->setDatePredicate(m_hQuery[0]);
      m_pView = totalscommand::FinancialTotal::instance();
   }
   segment::SOAPSegment::instance()->setRtnCde('0');
   m_hQuery[0].setRetainCursor(true);
   auto_ptr<SelectStatement> pSelectStatement((SelectStatement*) DatabaseFactory::instance()->create("SelectStatement"));
   if (!pSelectStatement->execute(m_hQuery[0]))
      SOAPSegment::instance()->setRtnCde('5');
   else
      SOAPSegment::instance()->setRtnCde(m_iRows == 0 ? '2' : m_hQuery[0].getAbort() ? '1' : '0');
   reply();
   return true;
  //## end totalscommand::FinancialTotalsCommand::execute%53BAD4820269.body
}

int FinancialTotalsCommand::parse ()
{
  //## begin totalscommand::FinancialTotalsCommand::parse%53BAD48701CF.body preserve=yes
   int iRC = SOAPCommand::parse();
   if (iRC != 0)
      return iRC;
   // !!! add checks for input
   return 0;
  //## end totalscommand::FinancialTotalsCommand::parse%53BAD48701CF.body
}

void FinancialTotalsCommand::update (Subject* pSubject)
{
  //## begin totalscommand::FinancialTotalsCommand::update%53BAD48A00DB.body preserve=yes
   if (pSubject == &m_hQuery[0])
   {
      if (++m_iRows > m_iSkipRows)
      {
         if ((m_iRows - m_iSkipRows) <= m_iMaxRows)
         {
            m_pXMLDocument->save();
            map<string,set<string,less<string> >,less<string> >::const_iterator q = m_pView->getChild().begin();
            if (m_pXMLDocument->add(m_pView->getParent().begin(),m_pView->getParent().end()) == false
               || m_pXMLDocument->add((*q).second.begin(),(*q).second.end()) == false)
            {
               m_pXMLDocument->revert();
               m_hQuery[0].setAbort(true);
               return;
            }
            m_pXMLDocument->write("Total");
         }
         else
            m_hQuery[0].setAbort(true);
      }
      return;
   }
   SOAPCommand::update(pSubject);
  //## end totalscommand::FinancialTotalsCommand::update%53BAD48A00DB.body
}

// Additional Declarations
  //## begin totalscommand::FinancialTotalsCommand%53BACFE303A4.declarations preserve=yes
  //## end totalscommand::FinancialTotalsCommand%53BACFE303A4.declarations

} // namespace totalscommand

//## begin module%53BAD1990182.epilog preserve=yes
//## end module%53BAD1990182.epilog
