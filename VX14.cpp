//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%6384DA480273.cm preserve=no
//## end module%6384DA480273.cm

//## begin module%6384DA480273.cp preserve=no
//	Copyright (c) 1997 - 2022
//	FIS
//## end module%6384DA480273.cp

//## Module: CXOSVX14%6384DA480273; Package body
//## Subsystem: VX%4C2B63AB026E
//## Source file: C:\Repos\DataNavigatorServer\Windows\Build\Dn\Server\Application\Vx\CXOSVX14.cpp

//## begin module%6384DA480273.additionalIncludes preserve=no
//## end module%6384DA480273.additionalIncludes

//## begin module%6384DA480273.includes preserve=yes
//## end module%6384DA480273.includes

#ifndef CXOSIF10_h
#include "CXODIF10.hpp"
#endif
#ifndef CXOSIF03_h
#include "CXODIF03.hpp"
#endif
#ifndef CXOSTM04_h
#include "CXODTM04.hpp"
#endif
#ifndef CXOSBS24_h
#include "CXODBS24.hpp"
#endif
#ifndef CXOSIF16_h
#include "CXODIF16.hpp"
#endif
#ifndef CXOSVX14_h
#include "CXODVX14.hpp"
#endif


//## begin module%6384DA480273.declarations preserve=no
//## end module%6384DA480273.declarations

//## begin module%6384DA480273.additionalDeclarations preserve=yes
//## end module%6384DA480273.additionalDeclarations


// Class STARUploadFile 

STARUploadFile::STARUploadFile()
  //## begin STARUploadFile::STARUploadFile%6384DBB101A2_const.hasinit preserve=no
  //## end STARUploadFile::STARUploadFile%6384DBB101A2_const.hasinit
  //## begin STARUploadFile::STARUploadFile%6384DBB101A2_const.initialization preserve=yes
  //## end STARUploadFile::STARUploadFile%6384DBB101A2_const.initialization
{
  //## begin STARUploadFile::STARUploadFile%6384DBB101A2_const.body preserve=yes
   memcpy(m_sID,"VX14",4);
   if (!readExtract())
      Trace::put("UploadFile::Extract is not correctly configured");
  //## end STARUploadFile::STARUploadFile%6384DBB101A2_const.body
}


STARUploadFile::~STARUploadFile()
{
  //## begin STARUploadFile::~STARUploadFile%6384DBB101A2_dest.body preserve=yes
  //## end STARUploadFile::~STARUploadFile%6384DBB101A2_dest.body
}



//## Other Operations (implementation)
reusable::string STARUploadFile::buildFile (char& cStatus, const reusable::string& strFilename)
{
  //## begin STARUploadFile::buildFile%6384DFFE01C2.body preserve=yes
   string strTempFileName;
   m_strFilename = strFilename;
   FlatFile hPendingFile("UPENDING");
   hPendingFile.setMember(strFilename.c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      return "No header file has been found: " + hPendingFile.getName();
   }
   hPendingFile.getBaseName(strTempFileName,true);
   m_strBatchBaseName = strTempFileName;
   m_strBatchOrigName = strTempFileName.substr(0,7);
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
   ImportReportAuditSegment::instance()->setFILE(m_strBatchBaseName);
   hPendingFile.move("UPENDING",("original_" + strTempFileName).c_str());
   hPendingFile.close();
   hPendingFile.setMember(("original_" + strTempFileName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "header file can not be opened for restructuring";
   rebuildBatchXML(hPendingFile,strTempFileName);
   hPendingFile.close();
   const char* pEprTag = "<ep-routing-id>";
   size_t uTagPos = m_strBatchOrigName.find(pEprTag);
   string strEproutingid = m_strBatchOrigName.substr(uTagPos + strlen(pEprTag),m_strBatchOrigName.find("</ep-routing-id>") - uTagPos - strlen(pEprTag));
   m_strBatchOrigName.erase(m_strBatchOrigName.find(pEprTag),m_strBatchOrigName.length() - uTagPos);
   m_strBatchBaseName = strEproutingid + "-inbound.xml";

   m_strFilename = m_strBatchBaseName;
   FlatFile hPendingFile1("UPENDING");
   hPendingFile1.setMember(strTempFileName.c_str());
   if (!hPendingFile1.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      return "No file found with name" + hPendingFile.getName();
   }
   hPendingFile1.move("UPENDING",m_strBatchBaseName.c_str());
   hPendingFile1.close();
   m_strBatchOrigName = "ImageIn_" + Clock::instance()->getYYYYMMDDHHMMSS().substr(0,8) + "_"
      + Clock::instance()->getYYYYMMDDHHMMSS().substr(8,8) + "_" + strEproutingid;
   m_strFilename = strFilename;
   m_strDocFile = m_strBatchOrigName + ".zip";
   if (m_hTifDocs.size() != 0)
   {
      for (std::vector<string>::iterator it = m_hTifDocs.begin(); it != m_hTifDocs.end(); ++it)
      {
         size_t pos = it->find(m_strFilename.substr(0, 3));
         if (pos != string::npos)
            it->erase(0, (pos - 1));
      }
   }
   if (m_hTifDocs.size() != 0 && !zipImages())
      return "Unable to package images into DUA zip"; 
   if (m_bStatus)
   {
      Trace::put("Waiting for the response from WEB to process documents");
      return "waiting for the process";
   }
   if(!processZIP(strFilename))
      return "File is not successfully uploaded";
   Trace::put("VX14::Restructured both XML docs created document zip and moved to complete");
   return "File is successfully uploaded";
   return "successful";
  //## end STARUploadFile::buildFile%6384DFFE01C2.body
}

bool STARUploadFile::execute ()
{
  //## begin STARUploadFile::execute%6384E031026C.body preserve=yes
   if (m_bStatus)
   {
      Trace::put("STR Upload is not picked up for processing");
      return false;
   }
   resetVars();
   char cStatus = 'F';
   string strReason;
   m_hFileName = "VX14";   //needs to be changed for zip 
   strReason = buildFile(cStatus,"STR*");  // this to fetch list of images and copy
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      sendStatus(cStatus,strReason);
      restoreFiles();
   }
   if (!m_bStatus)
   {
      resetVars();
      m_hFileName = "VX14";
      strReason = buildFile(cStatus,"CPY*");  // this to fetch list of images and copy
   }
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      sendStatus(cStatus,strReason);
      restoreFiles();
   }
   if (!m_bStatus)
   {
      resetVars();
      m_hFileName = "VX14";
      strReason = buildFile(cStatus,"CPP*");  // this to fetch list of images and copy
   }
   if (!m_bStatus)
   {
      m_bDownloadFile = false;
      sendStatus(cStatus,strReason);
      restoreFiles();
   }
   return true;
  //## end STARUploadFile::execute%6384E031026C.body
}

bool STARUploadFile::packageZip ()
{
  //## begin STARUploadFile::packageZip%6384E06900B3.body preserve=yes
   FlatFile hFinishedFiles("");
   hFinishedFiles.setMember(m_strBatchBaseName.c_str());
   hFinishedFiles.setName("UPENDING");
   if (!hFinishedFiles.open())
      return false;
   if (!hFinishedFiles.zip(m_strBatchOrigName))
      return false;
   if (!hFinishedFiles.close())
      return false;
   if (!hFinishedFiles.remove())
      return false;
   return true;
  //## end STARUploadFile::packageZip%6384E06900B3.body
}

bool STARUploadFile::processZIP (const reusable::string& strFilename)
{
  //## begin STARUploadFile::processZIP%6384E0790017.body preserve=yes
   if (!packageZip())
      return false;
   Trace::put("VX14::Packaged xml and document zip into UA zip");
   string strOwner("VROL");
   if (m_strFilename.length() > 3 && memcmp(m_strFilename.c_str(), "VROL", 4) != 0)
      strOwner.assign(m_strFilename.c_str(), 3);
   string strFTPDatasetName;
   string strBatchOrigName(m_strBatchOrigName);
   m_strBatchOrigName = m_strFilename;
   if (finalizeFiles(strOwner))
   {
      m_strBatchOrigName = strBatchOrigName;
      if (finalizeFiles(strOwner))
      {
         if (writeFTPScript(strFTPDatasetName,strOwner))
         {
            if (executeFTPScript())
            {
               Trace::put("Successfully Uploaded");
               return true;
            }
            else
            {
               Trace::put("Unsuccessful execution of the FTP script");
               return false;
            }
         }
         else
         {
            if (strFTPDatasetName.length() > 0)
            {
               strFTPDatasetName.append(" Dspec entry is not set up to FTP to IBM");
               Trace::put(strFTPDatasetName.c_str());
               return false;
            }
            else
               Trace::put("File length downloaded to PC is less than 11 characters");
            return false;
         }
      }
      else
         return false;
   }
   else
   {
      Trace::put("Unsuccessful in moving files from Pending to Complete");
      return false;
   }
  //## end STARUploadFile::processZIP%6384E0790017.body
}

// Additional Declarations
  //## begin STARUploadFile%6384DBB101A2.declarations preserve=yes
  //## end STARUploadFile%6384DBB101A2.declarations

//## begin module%6384DA480273.epilog preserve=yes
//## end module%6384DA480273.epilog