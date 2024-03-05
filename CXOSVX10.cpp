//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%530D1B670039.cm preserve=no
//	$Date:   May 13 2020 13:17:30  $ $Author:   e1009510  $
//	$Revision:   1.9  $
//## end module%530D1B670039.cm

//## begin module%530D1B670039.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%530D1B670039.cp

//## Module: CXOSVX10%530D1B670039; Package body
//## Subsystem: VX%4C2B63AB026E
//## Source file: C:\bV02.5B.R003\Windows\Build\Dn\Server\Application\Vx\CXOSVX10.cpp

//## begin module%530D1B670039.additionalIncludes preserve=no
//## end module%530D1B670039.additionalIncludes

//## begin module%530D1B670039.includes preserve=yes
#include "CXODIF16.hpp"
//## end module%530D1B670039.includes

#ifndef CXOSIF10_h
#include "CXODIF10.hpp"
#endif
#ifndef CXOSIF03_h
#include "CXODIF03.hpp"
#endif
#ifndef CXOSTM04_h
#include "CXODTM04.hpp"
#endif
#ifndef CXOSVX02_h
#include "CXODVX02.hpp"
#endif
#ifndef CXOSES49_h
#include "CXODES49.hpp"
#endif
#ifndef CXOSBS24_h
#include "CXODBS24.hpp"
#endif
#ifndef CXOSVX10_h
#include "CXODVX10.hpp"
#endif


//## begin module%530D1B670039.declarations preserve=no
//## end module%530D1B670039.declarations

//## begin module%530D1B670039.additionalDeclarations preserve=yes
#define BUFFER_SIZE 32767
//## end module%530D1B670039.additionalDeclarations


// Class VROLUploadFile 

VROLUploadFile::VROLUploadFile()
  //## begin VROLUploadFile::VROLUploadFile%530CFC340396_const.hasinit preserve=no
  //## end VROLUploadFile::VROLUploadFile%530CFC340396_const.hasinit
  //## begin VROLUploadFile::VROLUploadFile%530CFC340396_const.initialization preserve=yes
  //## end VROLUploadFile::VROLUploadFile%530CFC340396_const.initialization
{
  //## begin VROLUploadFile::VROLUploadFile%530CFC340396_const.body preserve=yes
   memcpy(m_sID,"VX10",4);
   if (!readExtract())
      Trace::put("Extract is not correctly configured");
  //## end VROLUploadFile::VROLUploadFile%530CFC340396_const.body
}


VROLUploadFile::~VROLUploadFile()
{
  //## begin VROLUploadFile::~VROLUploadFile%530CFC340396_dest.body preserve=yes
  //## end VROLUploadFile::~VROLUploadFile%530CFC340396_dest.body
}



//## Other Operations (implementation)
string VROLUploadFile::buildDM3File (char& cStatus, const string& strFilename)
{
  //## begin VROLUploadFile::buildDM3File%530E0922024E.body preserve=yes
   string strTempFileName;
   m_strFilename = strFilename;
   // Cleans up body xml and moves to complete
   FlatFile hPendingFile("UPENDING");
   hPendingFile.setMember(strFilename.c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      return "No header file has been found: "+hPendingFile.getName();
   }
   hPendingFile.getBaseName(strTempFileName,true);
   m_strBatchBaseName = strTempFileName;
   m_strBatchBaseName.erase(0,1);
   ImportReportAuditSegment::instance()->setFILE(m_strBatchBaseName);
   hPendingFile.move("UPENDING",("original_"+strTempFileName).c_str());
   hPendingFile.close();
   hPendingFile.setMember(("original_"+strTempFileName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "header file can not be opened for restructuring";
   rebuildDescriptorXML(hPendingFile,strTempFileName);
   hPendingFile.close();
   m_strBatchOrigName = m_strDocFile;
   m_strBatchOrigName.erase(0,1);
   
   //processing of body file - RDM3
   hPendingFile.setName("UPENDING");
   hPendingFile.setMember(("R"+m_strBatchBaseName).c_str());
   if (hPendingFile.open(FlatFile::CX_OPEN_INPUT))
   {
      hPendingFile.getBaseName(strTempFileName,true);
      hPendingFile.move("UPENDING",("original_"+strTempFileName).c_str());
      hPendingFile.close();
      hPendingFile.setMember(("original_"+strTempFileName).c_str());
      if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
         return "Unable to open RUA file for rebuild: "+hPendingFile.getName();
      rebuildBatchXML(hPendingFile,strTempFileName);
      hPendingFile.close();
      //Rename the body file to the name available in the file
      hPendingFile.setName("UPENDING");
      hPendingFile.setMember(("R"+m_strBatchBaseName).c_str());
      if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
         return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
      hPendingFile.getBaseName(strTempFileName);
      hPendingFile.move("UPENDING",("R"+m_strBatchOrigName).c_str());
      hPendingFile.close();
   }
   //Rename the header file to the name available in the file
   hPendingFile.setName("UPENDING");
   hPendingFile.setMember(("B"+m_strBatchBaseName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
   hPendingFile.getBaseName(strTempFileName);
   hPendingFile.move("UPENDING",("B"+m_strBatchOrigName).c_str());
   hPendingFile.close();

   if(!packageZip())
      return "Unable to add files to final zip package";
   
   //determine the owner of the files based on the last 4 character extension
   string strOwner("VROL");
   if (m_strBatchBaseName.length() > 11)
   {
      size_t nPos = m_strBatchBaseName.find_last_of('.');
      strOwner.assign(m_strBatchBaseName.substr(nPos + 1));
   }

   string strFTPDatasetName;
   if (finalizeFiles(strOwner))
   {
      if (writeFTPScript(strFTPDatasetName, strOwner))
      {
         if (Extract::instance()->getCustomCode() == "DGMC")
         {
            if (executeDGMCFTPScript(strFTPDatasetName, strOwner, strFilename))
                return "Successfully Uploaded: "+(const string)strFTPDatasetName;
            else
               return "Unsuccessful execution of the FTP script";
         }
         if (executeFTPScript())
            return "Successfully Uploaded: "+(const string)strFTPDatasetName;
         else
            return "Unsuccessful execution of the FTP script";
      }
      else
      {
         if (strFTPDatasetName.length() > 0) 
         {
            strFTPDatasetName.append(" Dspec entry is not set up to FTP to IBM"); 
            return strFTPDatasetName;
         }
         else
            return "File length downloaded to PC is less than 11 characters";
       }
   }
   else
       return "Unsuccessful in moving files from Pending to Complete";
  //## end VROLUploadFile::buildDM3File%530E0922024E.body
}

string VROLUploadFile::buildFile (char& cStatus, const string& strFilename)
{
  //## begin VROLUploadFile::buildFile%530E1B7502CC.body preserve=yes
   string strTempFileName;
   m_strFilename = strFilename;
   // Cleans up body xml and moves to complete
   FlatFile hPendingFile("UPENDING");
   hPendingFile.setMember(strFilename.c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      hPendingFile.close();
      return "No body file has been found: "+hPendingFile.getName();
   }
   hPendingFile.getBaseName(strTempFileName,true);
   m_strBatchBaseName = strTempFileName;
   m_strBatchBaseName.erase(0,1);
   size_t pos = hPendingFile.getDatasetName().find_last_of('\\');
   if (pos != string::npos)
   {
      string strFolderName(hPendingFile.getDatasetName().data(),0,pos);
      if (strFolderName[2] == '\\')
      {
         m_strFolderName = "\\\\";
         m_strFolderName.append(Extract::instance()->getHost());
         m_strFolderName.append(strFolderName.substr(2));
      }
      else
         m_strFolderName = strFolderName;
   }
   FlatFile hPendingFile1("UPENDING");
   hPendingFile1.setMember(("B"+m_strBatchBaseName).c_str());
   if (!hPendingFile1.open(FlatFile::CX_OPEN_INPUT))
   {
      hPendingFile1.close();
      return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
   }
   hPendingFile1.close();
   ImportReportAuditSegment::instance()->setFILE(m_strBatchBaseName);
   hPendingFile.move("UPENDING",("original_"+strTempFileName).c_str());
   hPendingFile.close();
   hPendingFile.setMember(("original_"+strTempFileName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Body file cannot be opened for restructuring";	
   rebuildBatchXML(hPendingFile,strTempFileName);
   hPendingFile.close();
   
   //processing of header file - BUA5 or BDM5
   hPendingFile.setName("UPENDING");
   hPendingFile.setMember(("B"+m_strBatchBaseName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
   hPendingFile.getBaseName(strTempFileName,true);
   hPendingFile.move("UPENDING",("original_"+strTempFileName).c_str());
   hPendingFile.close();
   hPendingFile.setMember(("original_"+strTempFileName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
   rebuildDescriptorXML(hPendingFile,strTempFileName);
   hPendingFile.close();

   m_strBatchOrigName = m_strDocFile;
   m_strBatchOrigName.erase(0,1);
   

   //Rename the header file to the name available in the file
   hPendingFile.setName("UPENDING");
   hPendingFile.setMember(("B"+m_strBatchBaseName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
   hPendingFile.getBaseName(strTempFileName);
   hPendingFile.move("UPENDING",("B"+m_strBatchOrigName).c_str());
   hPendingFile.close();
  
   //Rename the body file to the name available in the file
   hPendingFile.setName("UPENDING");
   hPendingFile.setMember(("R"+m_strBatchBaseName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Unable to open BUA file for rebuild: "+hPendingFile.getName();
   hPendingFile.getBaseName(strTempFileName);
   hPendingFile.move("UPENDING",("R"+m_strBatchOrigName).c_str());
   hPendingFile.close();

   //Packages .Tifs in DUA zip and moves to complete
   if(m_hTifDocs.size()!=0 && !zipImages())
      return "Unable to package tiff images into DUA zip";
   if (m_bStatus)
   {
      Trace::put("Waiting for the response from WEB to process documents");
      return "waiting for the process";
   }
   if (!processZIP(strFilename))
      return "File is not successfully uploaded";
   Trace::put("VX02::Restructured both XML docs created document zip and moved to complete");
   return "File is successfully uploaded";
  //## end VROLUploadFile::buildFile%530E1B7502CC.body
}

bool VROLUploadFile::execute ()
{
  //## begin VROLUploadFile::execute%55C8BA3C02DE.body preserve=yes
   if (m_bStatus)
   {
      Trace::put("VROL Upload is not picked up for processing");
      return false;
   }
   resetVars();
   m_hFileName = "VX10";
   char cStatus = 'F';
   string strReason;
   strReason = buildFile(cStatus,"RUA*");
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      sendStatus(cStatus,strReason);
      restoreFiles();
   }
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      strReason = buildFile(cStatus,"RDM5*");
   }
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      sendStatus(cStatus,strReason);
      restoreFiles();
   }
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      strReason = buildDM3File(cStatus,"BDM3*");
   }
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      sendStatus(cStatus,strReason);
      restoreFiles();
   }
   return true;
  //## end VROLUploadFile::execute%55C8BA3C02DE.body
}

bool VROLUploadFile::rebuildDescriptorXML (IF::FlatFile& hInFile, const string& strOutputXMLFile)
{
  //## begin VROLUploadFile::rebuildDescriptorXML%530E09320163.body preserve=yes
   FlatFile hOutFile("UPENDING");
   hOutFile.setMember(strOutputXMLFile.c_str());
   if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
      return false;
   string strLine;
   bool bPackTag=false;
   //Creates buffer for reading chunks of file
   char szTempLine[BUFFER_SIZE +1];
   szTempLine[BUFFER_SIZE] = '\0';
   //Clears buffer then adds characters from file
   memset(szTempLine,' ',BUFFER_SIZE);
   size_t iReadSize = BUFFER_SIZE;
   bool processDM3(false);
   int i = 0;
   int j = 0;
   int k = 0;
   while (hInFile.read(szTempLine,BUFFER_SIZE+1,&iReadSize)==true )
   {
      strLine="";
      strLine=szTempLine;
      //removes trailing whitespace
      strLine.erase(strLine.find_last_not_of(' ')+1,string::npos);
      removePatterns(strLine);
      if (processDM3 == true)
      {
         processDM3 = false;
         size_t nPos = strLine.find("name=");
         if (nPos != string::npos)
            m_strDocFile = strLine.substr(nPos+6,8);
      }         
      if (strOutputXMLFile.find("DM3") != string::npos)
      {
         
         if (strLine.find("<ProcessingReportDownloadResponseDescriptor") != string::npos)
            processDM3 = true;
         hOutFile.write((char*)strLine.data(),strLine.length());
      }
      else      
      {   
         if(strLine.find("batchID")!=string::npos)
            bPackTag = true;
         if(bPackTag == true
         && ((i = strLine.find("name=")) != string::npos 
		 && ((j = strLine.find("UA5")) != string::npos || (k = strLine.find("DM5")) != string::npos)))
         {
            m_strDocFile = "D";
            if (j > 0)
               m_strDocFile.append(strLine.substr(j,7));
            if (k > 0)
               m_strDocFile.append(strLine.substr(k,7));
            bPackTag = false;
         }
         if(strLine.size()!=0
            && strLine.find_first_not_of(' ')!= string::npos
            &&(!(m_hTifDocs.size()==0 && strLine.find("<PackageFile ")!=string::npos)))
         {
            hOutFile.write((char*)strLine.data(),strLine.length());
         }
         memset(szTempLine,' ',BUFFER_SIZE); //Clear buffer
      }
   }
   hOutFile.close();
   return true;
  //## end VROLUploadFile::rebuildDescriptorXML%530E09320163.body
}

// Additional Declarations
  //## begin VROLUploadFile%530CFC340396.declarations preserve=yes
  //## end VROLUploadFile%530CFC340396.declarations

//## begin module%530D1B670039.epilog preserve=yes
//## end module%530D1B670039.epilog
