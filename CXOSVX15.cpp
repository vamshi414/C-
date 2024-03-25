//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%5305121C017C.cm preserve=no
//	$Date:   May 13 2020 13:17:30  $ $Author:   e1009510  $
//	$Revision:   1.4  $
//## end module%5305121C017C.cm

//## begin module%5305121C017C.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%5305121C017C.cp

//## Module: CXOSVX04%5305121C017C; Package body
//## Subsystem: VX%4C2B63AB026E
//## Source file: C:\bV02.5B.R003\Windows\Build\Dn\Server\Application\Vx\CXOSVX04.cpp

//## begin module%5305121C017C.additionalIncludes preserve=no
//## end module%5305121C017C.additionalIncludes

//## begin module%5305121C017C.includes preserve=yes
#include "CXODIF16.hpp"
//## end module%5305121C017C.includes

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
#ifndef CXOSES36_h
#include "CXODES36.hpp"
#endif
#ifndef CXOSBS07_h
#include "CXODBS07.hpp"
#endif
#ifndef CXOSVX04_h
#include "CXODVX15.hpp"
#endif


//## begin module%5305121C017C.declarations preserve=no
//## end module%5305121C017C.declarations

//## begin module%5305121C017C.additionalDeclarations preserve=yes
#define BUFFER_SIZE 32767
//## end module%5305121C017C.additionalDeclarations


// Class NYCEUploadFile 

NYCEUploadFile::NYCEUploadFile()
  //## begin NYCEUploadFile::NYCEUploadFile%5305101601E7_const.hasinit preserve=no
  //## end NYCEUploadFile::NYCEUploadFile%5305101601E7_const.hasinit
  //## begin NYCEUploadFile::NYCEUploadFile%5305101601E7_const.initialization preserve=yes
  //## end NYCEUploadFile::NYCEUploadFile%5305101601E7_const.initialization
{
  //## begin NYCEUploadFile::NYCEUploadFile%5305101601E7_const.body preserve=yes
   m_pListSegment = new ListSegment();
   if (!readExtract())
      Trace::put("UploadFile::Extract is not correctly configured");
  //## end NYCEUploadFile::NYCEUploadFile%5305101601E7_const.body
}


NYCEUploadFile::~NYCEUploadFile()
{
  //## begin NYCEUploadFile::~NYCEUploadFile%5305101601E7_dest.body preserve=yes
   delete m_pListSegment;
  //## end NYCEUploadFile::~NYCEUploadFile%5305101601E7_dest.body
}



//## Other Operations (implementation)
string NYCEUploadFile::buildFile (char& cStatus, const string& strFilename)
{
  //## begin NYCEUploadFile::buildFile%531E2F4A0202.body preserve=yes
   string strTempFileName;
   m_strFilename = strFilename;
   FlatFile hPendingFile("UPENDING");
   hPendingFile.setMember(strFilename.c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      return "No header file has been found: " + hPendingFile.getName();
   }
   hPendingFile.getBaseName(strTempFileName, true);
   m_strBatchBaseName = strTempFileName;
   m_strBatchOrigName = strTempFileName;
   size_t pos = hPendingFile.getDatasetName().find_last_of('\\');
   if (pos != string::npos)
   {
      string strFolderName(hPendingFile.getDatasetName().data(), 0, pos);
      if (strFolderName[2] == '\\')
      {
         m_strFolderName = "\\\\";
         m_strFolderName.append(Extract::instance()->getHost());
         m_strFolderName.append(strFolderName.substr(2));
      }
      else
         m_strFolderName = strFolderName;
   }
   hPendingFile.getBaseName(strTempFileName, true);
   m_strBatchBaseName = strTempFileName;
   m_strDocFile.append(Clock::instance()->getYYYYMMDDHHMMSS(), 2, 6);
   m_strDocFile.append(".TB4");
   m_strBatchOrigName = m_strDocFile;
   m_strDocFile.append(".zip");
   FlatFile hPendingFile1("UPENDING");
   hPendingFile1.setMember(m_strBatchBaseName.c_str());
   if (!hPendingFile1.open(FlatFile::CX_OPEN_INPUT))
   {
      hPendingFile1.close();
      return "Unable to open BUA file for rebuild: " + hPendingFile.getName();
   }
   hPendingFile1.close();

   ImportReportAuditSegment::instance()->setFILE(m_strBatchBaseName);
   hPendingFile.move("UPENDING", ("original_" + strTempFileName).c_str());
   hPendingFile.close();
   hPendingFile.setMember(("original_" + strTempFileName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "header file can not be opened for restructuring";
   rebuildNYCEFile(hPendingFile, strTempFileName);
   hPendingFile.close();

   hPendingFile.setName("UPENDING");
   hPendingFile.setMember(("original_" + strTempFileName).c_str());
   if (!hPendingFile.open(FlatFile::CX_OPEN_INPUT))
      return "Unable to open BUA file for rebuild: " + hPendingFile.getName();
   hPendingFile.getBaseName(strTempFileName);
   hPendingFile.move("UPENDING", m_strBatchOrigName.c_str());
   hPendingFile.close();
   m_strDocFile.assign("D" + m_strBatchBaseName);
   if (m_hTifDocs.size() != 0 && !zipImages())
      return "Unable to package tiff images into DUA zip";
   if (!packageNYCEZip())
      return "Unable to add files to final zip package";

   //determine the owner of the files based on the last 4 character extension
   string strOwner("");

   string strFTPDatasetName;
   if (finalizeFiles(strOwner))
   {
      if (writeFTPScript(strFTPDatasetName, strOwner))
      {
         if (executeFTPScript())
            return "Successfully Uploaded: " + (const string)strFTPDatasetName;
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
  //## end NYCEUploadFile::buildFile%531E2F4A0202.body
}

bool NYCEUploadFile::execute ()
{
  //## begin NYCEUploadFile::execute%55C8BA2801E2.body preserve=yes
   if (m_bStatus)
   {
      Trace::put("NYCE Upload is not picked up for processing");
      return false;
   }
   resetVars();
   char cStatus = 'F';
   string strReason;
   strReason = buildFile(cStatus, "NYCE*");
   restoreFiles();
   return true;
  //## end NYCEUploadFile::execute%55C8BA2801E2.body
}

bool NYCEUploadFile::packageNYCEZip ()
{
  //## begin NYCEUploadFile::packageNYCEZip%531E2F4A0205.body preserve=yes
   FlatFile hFinishedFiles("");
   string strZipFile("ECOUT");
   hFinishedFiles.setMember(("processed_" + strZipFile + ".zip").c_str());
   hFinishedFiles.setName("UPENDING");
   hFinishedFiles.remove();
   hFinishedFiles.setMember((m_strBatchOrigName).c_str());
   if (hFinishedFiles.open())
   {
      if (!hFinishedFiles.zip("processed_" + strZipFile))
         return false;
      if (!hFinishedFiles.close())
         return false;
      if (!hFinishedFiles.remove())
         return false;
   }
   if (m_hTifDocs.size() != 0)
   {
      hFinishedFiles.setMember(("D" + m_strBatchOrigName).c_str());
      if (!hFinishedFiles.open())
         return false;
      if (!hFinishedFiles.zip("processed_" + strZipFile))
         return false;
      if (!hFinishedFiles.close())
         return false;
      if (!hFinishedFiles.remove())
         return false;
      hFinishedFiles.setMember(("C" + m_strBatchOrigName).c_str());
      if (!hFinishedFiles.open())
         return false;
      if (!hFinishedFiles.zip("processed_" + strZipFile))
         return false;
      if (!hFinishedFiles.close())
         return false;
      if (!hFinishedFiles.remove())
         return false;
   }
   m_strBatchOrigName = strZipFile;
   return true;
  //## end NYCEUploadFile::packageNYCEZip%531E2F4A0205.body
}

bool NYCEUploadFile::rebuildNYCEFile (IF::FlatFile& hInFile, const string& strOutputXMLFile)
{
  //## begin NYCEUploadFile::rebuildNYCEFile%531E2F4A0207.body preserve=yes
   FlatFile hOutFile("UPENDING");
   hOutFile.setMember(strOutputXMLFile.c_str());
   if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
      return false;
   string strLine;
   //Creates buffer for reading chunks of file
   char szTempLine[BUFFER_SIZE + 1];
   szTempLine[BUFFER_SIZE] = '\0';
   //Clears buffer then adds characters from file
   memset(szTempLine, ' ', BUFFER_SIZE);
   size_t iReadSize = BUFFER_SIZE;
   int i = 1;
   while (hInFile.read(szTempLine, BUFFER_SIZE + 1, &iReadSize) == true)
   {
      strLine = "";
      strLine = szTempLine;
      char szTemp[11];
      char pszLength[9] = { "        " };
      char* psBuffer = szTempLine + 8;
      char* pEndOfMessage = szTempLine + strLine.length();
      while (psBuffer < pEndOfMessage)
      {
         if (memcmp(psBuffer, "DTL", 3) == 0)
         {
            m_pListSegment->import(&psBuffer);
            char* p = (char*)*m_pListSegment;
            if (memcmp(p, (const char*)"S276", 4) == 0)
            {
               string strTemp;
               string strTemp1;
               for (int j = 0; j < m_pListSegment->itemCount(); ++j)
               {
                  if (CaseDocumentSegment::instance()->import(&p) == 0
                     && CaseDocumentSegment::instance()->getDOC_TYPE().find("REQ_") == string::npos)
                  {
                     string strDocCnt(" DOCNYCE");
                     snprintf(szTemp, sizeof(szTemp), "%010d", i++);
                     strDocCnt.append(szTemp);
                     strTemp.assign(CaseDocumentSegment::instance()->getDOC_PATH());
                     strTemp.append(strDocCnt);
                     strTemp1.assign(strTemp);
                     strTemp.assign(strDocCnt);
                     size_t nPos = CaseDocumentSegment::instance()->getDOC_PATH().find("NYC");
                     if (nPos != string::npos)
                     {
                        strTemp.append(" &docpath");
                        m_hTifDocs.push_back(strTemp1);
                        strTemp.append(CaseDocumentSegment::instance()->getDOC_PATH().substr(nPos - 1, CaseDocumentSegment::instance()->getDOC_PATH().length() - nPos + 2));
                        m_hTifCommands.push_back(strTemp);
                     }
                  }
               }
               m_pListSegment->reset();
            }
         }
         memcpy(pszLength, psBuffer + 8, 8);
         psBuffer += atoi(pszLength);
      }
      hOutFile.write((char*)strLine.data(), strLine.length());
   }
   hOutFile.close();
   return true;
  //## end NYCEUploadFile::rebuildNYCEFile%531E2F4A0207.body
}

// Additional Declarations
  //## begin NYCEUploadFile%5305101601E7.declarations preserve=yes
  //## end NYCEUploadFile%5305101601E7.declarations

//## begin module%5305121C017C.epilog preserve=yes
//## end module%5305121C017C.epilog
