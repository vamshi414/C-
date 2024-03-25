//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%53051219002D.cm preserve=no
//	$Date:   Aug 27 2015 14:39:44  $ $Author:   e1009591  $
//	$Revision:   1.1  $
//## end module%53051219002D.cm

//## begin module%53051219002D.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%53051219002D.cp

//## Module: CXOSVX04%53051219002D; Package specification
//## Subsystem: VX%4C2B63AB026E
//## Source file: C:\bV02.5B.R003\Windows\Build\Dn\Server\Application\Vx\CXODVX04.hpp

#ifndef CXOSVX04_h
#define CXOSVX04_h 1

//## begin module%53051219002D.additionalIncludes preserve=no
//## end module%53051219002D.additionalIncludes

//## begin module%53051219002D.includes preserve=yes
//## end module%53051219002D.includes

#ifndef CXOSVX02_h
#include "CXODVX02.hpp"
#endif

//## Modelname: Transaction Research and Adjustments::EMSSegment_CAT%394E27A9030F
namespace emssegment {
class CaseDocumentSegment;
} // namespace emssegment

//## Modelname: Connex Library::IF_CAT%3451F55F009E
namespace IF {
class FlatFile;
class Trace;
} // namespace IF

//## Modelname: Connex Library::Timer_CAT%3451F2410231
namespace timer {
class Clock;
} // namespace timer

//## Modelname: Connex Library::Segment_CAT%3471F0BE0219
namespace segment {
class ImportReportAuditSegment;
class ListSegment;

} // namespace segment

//## begin module%53051219002D.declarations preserve=no
//## end module%53051219002D.declarations

//## begin module%53051219002D.additionalDeclarations preserve=yes
//## end module%53051219002D.additionalDeclarations


//## begin ECHISTUploadFile%5305101601E7.preface preserve=yes
//## end ECHISTUploadFile%5305101601E7.preface

//## Class: ECHISTUploadFile%5305101601E7
//## Category: DataNavigator Foundation::Application::VROLInterface_CAT%4C2B5E9102E8
//## Subsystem: VX%4C2B63AB026E
//## Persistence: Transient
//## Cardinality/Multiplicity: n



//## Uses: <unnamed>%531E2FF20106;IF::FlatFile { -> F}
//## Uses: <unnamed>%531E2FF403BE;IF::Trace { -> F}
//## Uses: <unnamed>%531E2FF7020E;timer::Clock { -> F}
//## Uses: <unnamed>%531E2FF903E6;segment::ImportReportAuditSegment { -> F}
//## Uses: <unnamed>%531E331501E9;emssegment::CaseDocumentSegment { -> F}

class DllExport NYCEUploadFile : public UploadFile  //## Inherits: <unnamed>%531E2FED02EE
{
  //## begin ECHISTUploadFile%5305101601E7.initialDeclarations preserve=yes
  //## end ECHISTUploadFile%5305101601E7.initialDeclarations

  public:
    //## Constructors (generated)
      NYCEUploadFile();

    //## Destructor (generated)
      virtual ~NYCEUploadFile();


    //## Other Operations (specified)
      //## Operation: buildFile%531E2F4A0202
      virtual string buildFile (char& cStatus, const string& strFilename);

      //## Operation: execute%55C8BA2801E2
      //	Perform the functions of this command.
      virtual bool execute ();

      //## Operation: packageECHISTZip%531E2F4A0205
      bool packageNYCEZip ();

      //## Operation: rebuildECHISTFile%531E2F4A0207
      bool rebuildNYCEFile (IF::FlatFile& hInFile, const string& strOutputXMLFile);

    // Additional Public Declarations
      //## begin ECHISTUploadFile%5305101601E7.public preserve=yes
      //## end ECHISTUploadFile%5305101601E7.public

  protected:
    // Additional Protected Declarations
      //## begin ECHISTUploadFile%5305101601E7.protected preserve=yes
      //## end ECHISTUploadFile%5305101601E7.protected

  private:
    // Additional Private Declarations
      //## begin ECHISTUploadFile%5305101601E7.private preserve=yes
      //## end ECHISTUploadFile%5305101601E7.private

  private: //## implementation
    // Data Members for Associations

      //## Association: DataNavigator Foundation::Application::VROLInterface_CAT::<unnamed>%531E324D03B4
      //## Role: ECHISTUploadFile::<m_pListSegment>%531E324F0168
      //## begin ECHISTUploadFile::<m_pListSegment>%531E324F0168.role preserve=no  public: segment::ListSegment { -> RFHgN}
      segment::ListSegment *m_pListSegment;
      //## end ECHISTUploadFile::<m_pListSegment>%531E324F0168.role

    // Additional Implementation Declarations
      //## begin ECHISTUploadFile%5305101601E7.implementation preserve=yes
      //## end ECHISTUploadFile%5305101601E7.implementation

};

//## begin ECHISTUploadFile%5305101601E7.postscript preserve=yes
//## end ECHISTUploadFile%5305101601E7.postscript

//## begin module%53051219002D.epilog preserve=yes
//## end module%53051219002D.epilog


#endif
