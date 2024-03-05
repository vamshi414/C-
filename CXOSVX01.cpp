//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%4C2B67DC0225.cm preserve=no
//	$Date:   May 26 2020 10:23:52  $ $Author:   e1009591  $
//	$Revision:   1.59  $
//## end module%4C2B67DC0225.cm

//## begin module%4C2B67DC0225.cp preserve=no
//	Copyright (c) 1997 - 2012
//	FIS
//## end module%4C2B67DC0225.cp

//## Module: CXOSVX01%4C2B67DC0225; Package body
//## Subsystem: VX%4C2B63AB026E
//## Source file: C:\bV02.4B.R001\Build\Dn\Server\Application\Vx\CXOSVX01.cpp

//## begin module%4C2B67DC0225.additionalIncludes preserve=no
//## end module%4C2B67DC0225.additionalIncludes

//## begin module%4C2B67DC0225.includes preserve=yes
#include <algorithm>
#include "CXODIF16.hpp"
#include "CXODIF48.hpp"
#include "CXODRU34.hpp"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <direct.h>
#include <winsock2.h>
#endif
#include "CXODIF80.hpp"
//## end module%4C2B67DC0225.includes

#ifndef CXOSIF10_h
#include "CXODIF10.hpp"
#endif
#ifndef CXOSIF03_h
#include "CXODIF03.hpp"
#endif
#ifndef CXOSNS29_h
#include "CXODNS29.hpp"
#endif
#ifndef CXOSTM06_h
#include "CXODTM06.hpp"
#endif
#ifndef CXOSBC25_h
#include "CXODBC25.hpp"
#endif
#ifndef CXOSNS10_h
#include "CXODNS10.hpp"
#endif
#ifndef CXOSUS21_h
#include "CXODUS21.hpp"
#endif
#ifndef CXOSBS24_h
#include "CXODBS24.hpp"
#endif
#ifndef CXOSTM04_h
#include "CXODTM04.hpp"
#endif
#ifndef CXOSTM01_h
#include "CXODTM01.hpp"
#endif
#ifndef CXOSVX01_h
#include "CXODVX01.hpp"
#endif


//## begin module%4C2B67DC0225.declarations preserve=no
//## end module%4C2B67DC0225.declarations

//## begin module%4C2B67DC0225.additionalDeclarations preserve=yes
#define BUFFER_SIZE1 1028
//## end module%4C2B67DC0225.additionalDeclarations


// Class DownloadFile 

DownloadFile::DownloadFile()
  //## begin DownloadFile::DownloadFile%4C2B622B026D_const.hasinit preserve=no
  //## end DownloadFile::DownloadFile%4C2B622B026D_const.hasinit
  //## begin DownloadFile::DownloadFile%4C2B622B026D_const.initialization preserve=yes
   :m_hFTPScriptFile1("DCOMPLET")
  //## end DownloadFile::DownloadFile%4C2B622B026D_const.initialization
{
  //## begin DownloadFile::DownloadFile%4C2B622B026D_const.body preserve=yes
//   m_hFTPScriptFile1("DCOMPLET");
   memcpy(m_sID,"VX01",4);
   if (!readExtract())
       Trace::put("DownloadFile::Extract is not correctly configured");
   int i = 0;
   string strRecord;
   vector<string> hTokens;
   while (IF::Extract::instance()->getRecord(i++,strRecord))
   {
      if (strRecord.length() > 16
         && strRecord.substr(0,16) == "DSPEC   DFOLDER ")
      {
          // DSPEC  DFOLDER DVROL DUSPS DCARD DAFFN
         if (Buffer::parse(strRecord," ",hTokens) >= 2)
         {
            for (int j = 2; j < hTokens.size(); ++j)
               m_hCustomers.push_back(hTokens[j]);
         }
      }
      if (strRecord.length() > 16
         && strRecord.substr(0,16) == "DSPEC   DOCEXT  ")
      {
         if (Buffer::parse(strRecord," ",hTokens) >= 2)
         {
            for (int j = 2; j < hTokens.size(); ++j)
               m_hValidFileExtensions.insert(hTokens[j]);
         }                    
      }
   }
   m_iConsecutiveErrorCount=0;
   m_strPreviousError.erase();
  //## end DownloadFile::DownloadFile%4C2B622B026D_const.body
}


DownloadFile::~DownloadFile()
{
  //## begin DownloadFile::~DownloadFile%4C2B622B026D_dest.body preserve=yes
   m_hCustomers.erase(m_hCustomers.begin(),m_hCustomers.end());
  //## end DownloadFile::~DownloadFile%4C2B622B026D_dest.body
}



//## Other Operations (implementation)
bool DownloadFile::checkDocExtension (string strFileName)
{
  //## begin DownloadFile::checkDocExtension%53D24D7B034F.body preserve=yes
   int i = strFileName.find(".",0);
   int j = strFileName.find("</",0);
   string strExtension = strFileName.substr(i+1,j-(i+1));
   transform (strExtension.begin(),strExtension.end(), strExtension.begin(), ::tolower);
   if (m_hValidFileExtensions.find(strExtension) == m_hValidFileExtensions.end())
   {
      j = strFileName.find_first_of(">",0);
      m_hInvalidFiles.push_back(strFileName.substr(j+1,i-(j+1)));
      return false;
   }
   else
   {
      i = strFileName.find_first_of(">",0);
      m_hDocFileNames.push_back(strFileName.substr(i+1,j-(i+1)));
      return true;
   }
  //## end DownloadFile::checkDocExtension%53D24D7B034F.body
}

void DownloadFile::cleanup ()
{
  //## begin DownloadFile::cleanup%4C695A6E0378.body preserve=yes
   Date hDate = Date::today() - m_iDaysUntilDelete;
   char * sMonth[]={"1","2","3","4","5","6","7","8","9","A","B","C"};
   char * sDay[]={"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V"};

   string strBuffer;
   if (!(Extract::instance()->getRecord("DFILES  DCOMPLET",strBuffer)
      && strBuffer.length()>24
      && strBuffer.find("%member")!=string::npos))
      return;
   strBuffer.erase(0,16);
   size_t n = strBuffer.find("%o");
   if (n != string::npos)
      strBuffer.replace(n,2,m_strEntityFolder);
   n = strBuffer.find_first_of("%");
   if (n != string::npos)
      strBuffer.erase(n-1);

   hDate -= 31;
   for (int i = 0;i < 32; i++)
   {
      hDate += 1;
      string strDate(hDate.asString("%Y%m%d"));
      if (m_strEntityFolder == "ECHIST")
      {
         string strTemp(strBuffer);
         strTemp.append("\\");
         strTemp.append("ECOUT");
         FlatFile::purgeFolder(strTemp.c_str(),strDate.c_str());
      }
      else
      {
         char szFilecnt[5];
         for (int j = 0; j < 100 ; j++)
         {
            snprintf(szFilecnt,sizeof(szFilecnt),"%s%s%02d",sMonth[hDate.getMonth()-1],sDay[hDate.getDay()-1],j);
            FlatFile::purgeFolder(strBuffer.c_str(),"BDM5" +(string)szFilecnt);
            FlatFile::purgeFolder(strBuffer.c_str(),"BDM3" +(string)szFilecnt);
         }
           string strTemp(strBuffer);
         strTemp.append("\\");
         strTemp.append("CommandFiles");
         FlatFile::purgeFolder(strTemp.c_str(),strDate.c_str());
      }
   }
  //## end DownloadFile::cleanup%4C695A6E0378.body
}

bool DownloadFile::createDocumentFolder (const string& strFolder, string& strSource)
{
  //## begin DownloadFile::createDocumentFolder%5362A9B50010.body preserve=yes
   FlatFile hCreateFolderFile(strFolder.c_str(),"foldercreator");
   hCreateFolderFile.setOwner(m_strEntityFolder);
   hCreateFolderFile.setFolder(m_strHeaderFile);
   if (!(hCreateFolderFile.open(FlatFile::CX_OPEN_OUTPUT)
      && hCreateFolderFile.close()
      && hCreateFolderFile.remove()))
   {
      Trace::put("Document folder create failed");
      return false;
   }
   string strCommand("move ");
   strSource.append("*.TIF* ");
   size_t nPos = hCreateFolderFile.getName().find_last_of('\\');
   string strDest;
   string strTemp1;
   if (Extract::instance()->find(strFolder.c_str(),strTemp1))
   {
      if ((strTemp1[16] != '.')
         && (strTemp1[18] != '\\')
         && (memcmp(strTemp1.data()+16,"\\\\",2) != 0))
      {
         strDest.append(Extract::instance()->getNode001());
         strDest += "\\";
      }
      strDest.append(hCreateFolderFile.getName(),0,nPos);
      strCommand.append(strSource);
      strCommand.append(strDest);
      size_t pos = strDest.find_last_of('\\');
      if (pos != string::npos)
      {
         if (strDest[2] == '\\')
         {
            m_strFolderName = "\\\\";
            m_strFolderName.append(Extract::instance()->getHost());
            m_strFolderName.append(strDest.substr(2,strDest.length()-2));
         }
         else
            m_strFolderName = strDest;
      }
      if (!system(strCommand.c_str()))
         Trace::put("Issues with system command while copying documents");
      return true;
   }
   return false;
  //## end DownloadFile::createDocumentFolder%5362A9B50010.body
}

bool DownloadFile::createFolder (const string& strFolder)
{
  //## begin DownloadFile::createFolder%4D2E214401A8.body preserve=yes
   FlatFile hCreateFolderFile(strFolder.c_str(),"foldercreator");
   hCreateFolderFile.setOwner(m_strEntityFolder);
   hCreateFolderFile.setFolder(m_strHeaderFile);
   if (!(hCreateFolderFile.open(FlatFile::CX_OPEN_OUTPUT)
      && hCreateFolderFile.close()
      && hCreateFolderFile.remove()))
      return false;
   return true;
  //## end DownloadFile::createFolder%4D2E214401A8.body
}

bool DownloadFile::email ()
{
  //## begin DownloadFile::email%4C72866602A7.body preserve=yes
   string strDate = Date::today().asString("%Y%m%d");
   m_pEmail = new Email("VXDLAU","CU",Customer::instance()->getCUST_ID(),strDate,"235959");
   string strValue;
   Extract::instance()->getSpec("PROC",strValue);
   usersegment::EmailSegment::instance()->setServer(strValue);
   string strTime(Clock::instance()->getYYYYMMDDHHMMSS(),8,4);
   strTime.insert(2,":");
   usersegment::EmailSegment::instance()->setSCHED_TIME(strTime);
   strDate = Date::today().asString("%Y-%m-%d");
   usersegment::EmailSegment::instance()->setDATE_RECON(strDate);
   m_pEmail->add('Z',usersegment::EmailSegment::instance());
   m_pEmail->add('A',ImportReportAuditSegment::instance());
   string strTemp = ("CRCPT TO:<"+m_strContactEmailAddress+">");
   string strTemp2 = ("CTO:<"+m_strContactEmailAddress+">");
   const char* pszEmail[] =
   {
      "CHELO ~Z.PROC.",
      "CMAIL FROM:<DataNavigator>",
      strTemp.c_str(),
      "CDATA",
      strTemp2.c_str(),
      "CSUBJECT:DataNavigator VROL Interface:Download",
      "C",
      "CRun Time: ~Z.DATE_RECON. ~Z.SCHED_TIME.",
      "C",
      "SVRDM download file has been successfully processed",
      "SFile: ~A.FILE",
      "FProcessing of the VRDM download file was unsuccessful",
      "FFTP Script: ~A.FILE",
      "F~A.REJECT_CODES",
       0
   };
   m_pEmail->setTemplate(&pszEmail[0]);
   m_pEmail->report('C');
   return true;
  //## end DownloadFile::email%4C72866602A7.body
}

bool DownloadFile::execute ()
{
  //## begin DownloadFile::execute%5612D0060397.body preserve=yes
   Trace::put("DownloadFile::execute()");
   if (m_bStatus)
   {
      Trace::put("VROL Download is not picked up for processing");
      return false;
   }
   char cStatus;
   bool b = false;
   for (int i = 0; i < m_hCustomers.size(); i++)
   {
      Transaction::instance()->setTimeStamp(Clock::instance()->getYYYYMMDDHHMMSS(true));
      resetVars();
      cStatus = 'F';
      m_strCustomer = m_hCustomers[i];
      m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length() - 1));
      string strReason;
      cleanup();
      if (m_strCustomer == "DECHIST" && m_bStatus == false)
      {
         b = processECHIST(cStatus);
         Trace::put(strReason.data(),strReason.length());
         ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
         sendStatus(cStatus,strReason);
      }
      else if (m_strCustomer == "DMSTR" && m_bStatus == false)
      {
         b = processMSTR(cStatus);
         Trace::put(strReason.data(),strReason.length());
         ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
         sendStatus(cStatus,strReason);
      }
      else if ((m_strCustomer == "DSTR" || m_strCustomer == "DCPP" || m_strCustomer == "DCPY") && m_bStatus == false)
      {
         b = processSTAR(cStatus);
         Trace::put(strReason.data(),strReason.length());
         ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
         sendStatus(cStatus,strReason);
         m_strFolderName.erase(0, (m_strFolderName.find(m_strCustomer.substr(1, 3))) - 1);
      }
      else if (m_strCustomer == "DBAMS" && m_bStatus == false)
      {
         b = processBAMS(cStatus);
         Trace::put(strReason.data(),strReason.length());
         ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
         sendStatus(cStatus,strReason);
      }
      else if (m_bStatus == false && m_strCustomer != "DENCR")
      {
         b = processVRDM(cStatus);
         Trace::put(strReason.data(),strReason.length());
         ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
         sendStatus(cStatus,strReason);
         if (b == false && m_bStatus == false)
         {
            b = processCommand(cStatus,"VROLCUST.cmd");
            Trace::put(strReason.data(),strReason.length());
            ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
            sendStatus(cStatus,strReason);
         }
         if (b == false && m_bStatus == false)
         {
            b = processCommand(cStatus,"VROLCOMN.cmd");
            Trace::put(strReason.data(),strReason.length());
            ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
            sendStatus(cStatus,strReason);
         }
      }
      string strTemp;
      Extract::instance()->getSpec("WEBSER",strTemp);
      if (b == true && m_strFolderName.length() > 0 && strTemp == "ON")
      {
         m_bDownloadFile = true;
         m_hFileName = "VX01";
         string strXMLText("<DocEncryptOsi>");
         strXMLText += "<Folder>";
         string strSearch1;
         string strSearch2;
         string strLETTER_STORAGE_LOCATION;
         if (Extract::instance()->getSpec("WEBDOC",strLETTER_STORAGE_LOCATION))
         {
            strSearch1.assign(m_strFolderName);
            transform(strSearch1.begin(),strSearch1.end(),strSearch1.begin(),::toupper);
            strSearch2 = strLETTER_STORAGE_LOCATION;
            transform(strSearch2.begin(),strSearch2.end(),strSearch2.begin(),::toupper);
            size_t pos = strSearch1.find(strSearch2);
            if (pos != string::npos)
               m_strFolderName.erase(pos,strLETTER_STORAGE_LOCATION.length());
         }
         strXMLText += m_strFolderName;
         strXMLText += "</Folder>";
         strXMLText += "</DocEncryptOsi>";
         m_bStatus = true;
         if (!post(strXMLText))
         {
            m_bStatus = false;
            Trace::put("Not able to connect to the server");
            return false;
         }
         return true;
      }
   }
   return true;
  //## end DownloadFile::execute%5612D0060397.body
}

bool DownloadFile::finalizeFiles ()
{
  //## begin DownloadFile::finalizeFiles%4C5AD3E3012C.body preserve=yes
   //creates and deletes a file for the purpose of creating the complete directory
   //cleanup();
   if (!createFolder("DCOMPLET"))
      return false;
   if (!createFolder("DDOC    "))
      return false;
   //moves all files that include the batch base name to the complete folder
   string strBatchBaseName(m_strHeaderFile,1,5);
   if (!(moveFinishedFiles(strBatchBaseName)
      && moveFinishedFiles(m_strMainFile)))
      return false;
   string strTemp;
   if (Extract::instance()->find("DFILES  DDOC1   ",strTemp))
   {
      createFolder("DDOC1   ");
      FlatFile hDocFile("DDOC   ",("*"+strBatchBaseName+"*").c_str());
      hDocFile.setOwner(m_strEntityFolder);
      hDocFile.setFolder(m_strHeaderFile);
      if (hDocFile.open())
         hDocFile.copy("DDOC1   ");
      hDocFile.close();
   }
   return true;
  //## end DownloadFile::finalizeFiles%4C5AD3E3012C.body
}

bool DownloadFile::finishFTP ()
{
  //## begin DownloadFile::finishFTP%4C6959F40302.body preserve=yes
   m_hFTPScriptFile1.write("bye",3);
   m_hFTPScriptFile1.close();
   string strSSLFTP;
   string strTemppath;
   Extract::instance()->getSpec("SSLFTP",strSSLFTP);
   if (strSSLFTP == "ON")
   {
      if (m_hFTPScriptFile1.open())
      {
         string strftpFilepath;
         strTemppath = m_hFTPScriptFile1.getName();
         if ((strTemppath[0] != '.')
            && (strTemppath[2] != '\\')
            && (memcmp(strTemppath.data(),"\\\\",2) != 0))
         {
            strftpFilepath.append(Extract::instance()->getNode001());
            strftpFilepath += "\\";
         }
         strftpFilepath.append(strTemppath);
         m_hFTPScriptFile1.close();
         string strCommand("perl ");
         strCommand.append(Extract::instance()->getNode001());
         strCommand.append("\\Alpha\\Bin\\");
         strCommand.append("ftpsslvx.pl -i \"");
         strCommand.append(strftpFilepath);
         strCommand.append("\"");
         Trace::put(strCommand.c_str());
         system(strCommand.c_str());
      }
      else
      {
         Trace::put("Unsuccessful execution of the FTP script");
         return false;
      }
   }
   else
   {
      if (m_hFTPScriptFile1.open() 
      && m_hFTPScriptFile1.executeFtp()
      && m_hFTPScriptFile1.close())
      {
         Trace::put("Successfully Uploaded: ");
         return true;
      }
      else
      {
         Trace::put("Unsuccessful execution of the FTP script");
         return false;
      }
   }
   return true;
  //## end DownloadFile::finishFTP%4C6959F40302.body
}

bool DownloadFile::finalizeNonVisaFiles (char& cStatus)
{
  //## begin DownloadFile::finalizeNonVisaFiles%4F593CED039B.body preserve=yes
   //creates and deletes a file for the purpose of creating the complete directory
   //cleanup();
   if (!createFolder("DCOMPLET"))
      return false;
   //moves all files that include the batch base name to the complete folder
   string strTemp1("*ECHIST*");
   if (m_strCustomer == "DBAMS")
      strTemp1 = "*chargeback*";
   if (m_strCustomer == "DMSTR")
      strTemp1 = m_strMainFile + "*";
   else if(m_strCustomer == "DSTR" || m_strCustomer == "DCPP" || m_strCustomer == "DCPY")
      strTemp1 = "*Outbound.xml";
   FlatFile hCleanupFile(m_strCustomer.c_str(),strTemp1.c_str());
   hCleanupFile.setOwner(m_strEntityFolder);
   hCleanupFile.setFolder(m_strHeaderFile);
   while(hCleanupFile.open())
   {
      if (!hCleanupFile.move("DCOMPLET"))
      {
         hCleanupFile.close(); 
         return false;
      }
      hCleanupFile.close();
      hCleanupFile.setName(m_strCustomer.c_str());
   }
   strTemp1.assign("original_*");
   FlatFile hCleanupFile1(m_strCustomer.c_str(),strTemp1.c_str());
   hCleanupFile1.setOwner(m_strEntityFolder);
   hCleanupFile1.setFolder(m_strHeaderFile);
   while(hCleanupFile1.open())
   {
      if (!hCleanupFile1.move("DCOMPLET"))
      {
         hCleanupFile1.close();
         return false;
      }
      hCleanupFile1.close();
      hCleanupFile1.setName(m_strCustomer.c_str());
   }
   if (Extract::instance()->getCustomCode() == "DGMC")
   {
      if (setupDGMCFTP())
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
   m_hFTPScriptFile1.setName("DCOMPLET");
   m_hFTPScriptFile1.setFolder(m_strHeaderFile);
   m_hFTPScriptFile1.setOwner(m_strEntityFolder);
   m_hFTPScriptFile1.setMember((m_strMainFile+".ftp").c_str());
   if (!m_hFTPScriptFile1.open(FlatFile::CX_OPEN_OUTPUT))
   {
      Trace::put("Not able to open the file for FTP script");
      return false;
   }
   string strSSLFTP;
   string strPort;
   Extract::instance()->getSpec("SSLFTP",strSSLFTP);
   Extract::instance()->getSpec("PORT",strPort);
   if (strSSLFTP == "ON")
   {
      m_hFTPScriptFile1.write((char*)m_strFTPUsername.data(),m_strFTPUsername.length());			
      m_hFTPScriptFile1.write((char*)m_strFTPPassword.data(),m_strFTPPassword.length());
      m_hFTPScriptFile1.write((char*)strPort.data(),strPort.length());
   }
   string strFTPOutputLine("open ");
   strFTPOutputLine += m_strFTPIbmHost;
   m_hFTPScriptFile1.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
   if (strSSLFTP != "ON")
   {
      m_hFTPScriptFile1.write((char*)m_strFTPUsername.data(),m_strFTPUsername.length());			
      m_hFTPScriptFile1.write((char*)m_strFTPPassword.data(),m_strFTPPassword.length());
   }
   setSpaceParam();
   FlatFile hFinishedFiles("DCOMPLET");
   hFinishedFiles.setOwner(m_strEntityFolder);
   hFinishedFiles.setFolder(m_strHeaderFile);
   hFinishedFiles.setMember(m_strMainFile.c_str());
   if (!hFinishedFiles.open())
   {
      Trace::put("FTP Failed for BAMS or ECHIST");
      return false;
   }
   string strTemp(m_strEntityFolder);
   strTemp.append("D5");
   if (!Extract::instance()->getSpec(strTemp.c_str(),m_strFTPIbmDsName))
   {
      Trace::put("Extract for Upload is not set up for BAMS or ECHIST");
      return false;
   }
   if (m_strEntityFolder == "BAMS"
   || m_strEntityFolder == "MSTR")
   {
      m_hFTPScriptFile1.write("quote SITE LRECL=1500 BLKSIZE=22500 RECFM=VB",44);
      if (m_strEntityFolder == "MSTR")
         strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName + 
         m_strMainFile.substr(0,8) + ".D" + Clock::instance()->getYYYYMMDDHHMMSS().substr(2,6) + ".T" + Clock::instance()->getYYYYMMDDHHMMSS().substr(8,6) + "'" ;
      else
         strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName + "D" + Clock::instance()->getYYYYMMDDHHMMSS().substr(2,6) + "'";
   }
   else
   {
      m_hFTPScriptFile1.write("quote SITE LRECL=32756 BLKSIZE=32760 RECFM=VB",45);  
      strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName + m_strEntityFolder + "." + m_strHeaderFile +"'";
   }
   m_hFTPScriptFile1.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
   hFinishedFiles.close();
   if (finishFTP()==true)
   {
      ImportReportAuditSegment::instance()->setFILE(m_strMainFile+".ftp");
      Trace::put("Successfully Uploaded");
      return true;
   }
   return false;
  //## end DownloadFile::finalizeNonVisaFiles%63D69A870343.body
}

bool DownloadFile::moveFinishedFiles (const string& strIdentifier)
{
  //## begin DownloadFile::moveFinishedFiles%4C6EB2500376.body preserve=yes
   FlatFile hCleanupFile(m_strCustomer.c_str(),("*"+strIdentifier+"*").c_str());
   hCleanupFile.setOwner(m_strEntityFolder);
   hCleanupFile.setFolder(m_strHeaderFile);
   string strTemp;
   while(hCleanupFile.open())
   {
      hCleanupFile.getBaseName(strTemp,true);
      if (strTemp.substr(0,1) == "D")
      {
         if (!hCleanupFile.move("DDOC    "))
            return false;
      }
      else
      if (!hCleanupFile.move("DCOMPLET"))
         return false;
      hCleanupFile.close();
      hCleanupFile.setName(m_strCustomer.c_str());
   }
   return true;
  //## end DownloadFile::moveFinishedFiles%4C6EB2500376.body
}

bool DownloadFile::processBAMS (char& cStatus)
{
  //## begin DownloadFile::processBAMS%517588850372.body preserve=yes
   Trace::put("VX01::processBAMS");
   FlatFile hVRDMFile(m_strCustomer.c_str());
   hVRDMFile.setMember("BAMS*");
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      hVRDMFile.close();
      cStatus = 'N';
      Trace::put("Cannot find BAMSIN Files");
      return false;
   }
   hVRDMFile.getBaseName(m_strMainFile,true);
   hVRDMFile.setMember(m_strMainFile.c_str());
   m_strHeaderFile = "BAMSIN";
   hVRDMFile.close();
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      Trace::put ("Cannot access BAMS file");
      return false;
   }
   if (m_strMainFile.find("original_") != string::npos)
   {
      string strTemp = m_strMainFile+".cleanup";
      hVRDMFile.move(m_strCustomer.c_str(),strTemp.c_str());
      Trace::put("Renamed a file for cleanup");
      return false;
   }
   Trace::put("VX01: Going to unzip the file"); 
   hVRDMFile.getBaseName(m_strMainFile,true);
   m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length()-1));
   ImportReportAuditSegment::instance()->setFILE(m_strMainFile);
   if (!hVRDMFile.unzip())
   {
      hVRDMFile.close();
      cStatus = 'F';
      Trace::put("Unable to exratract BAMS file");
      return false;
   }
   if (!hVRDMFile.move(m_strCustomer.c_str(),("original_"+m_strMainFile).c_str()))
   {
      hVRDMFile.close();
      cStatus = 'F';
      Trace::put("Unable rename BAMS file to: original_");
      return false;
   }
   hVRDMFile.close();
   if (!createFolder("DBAMSDOC"))
      return false;

   FlatFile hVRDMFile3(m_strCustomer.c_str());
   hVRDMFile3.setMember("Images*");
   if (hVRDMFile3.open(FlatFile::CX_OPEN_INPUT))
   {
      hVRDMFile3.getBaseName(m_strMainFile,true);
      hVRDMFile3.setMember(m_strMainFile.c_str());
      hVRDMFile3.close();
      if (!hVRDMFile3.open(FlatFile::CX_OPEN_INPUT))
      {
         cStatus = 'F';
         Trace::put("Cannot access ZIP file");
         return false;
      }
      m_strMainFile = "Images";
      m_strMainFile.append(Clock::instance()->getYYYYMMDDHHMMSS().substr(0,8));
      m_strMainFile.append(".zip");
      hVRDMFile3.move("DBAMSDOC",m_strMainFile.c_str());
      hVRDMFile3.close();
      FlatFile hVRDMFile4("DBAMSDOC");
      hVRDMFile4.setMember(m_strMainFile.c_str());
      if (hVRDMFile4.open(FlatFile::CX_OPEN_INPUT))
      {
         size_t pos = hVRDMFile4.getDatasetName().find_last_of('\\');
         if (pos != string::npos)
         {
            string strFolderName(hVRDMFile4.getDatasetName().data(),0,pos);
            if (strFolderName[2] == '\\')
            {
               m_strFolderName = "\\\\";
               m_strFolderName.append(Extract::instance()->getHost());
               m_strFolderName.append(strFolderName.substr(2));
            }
            else
               m_strFolderName = strFolderName;
         }
         if (!hVRDMFile4.unzip())
         {
            cStatus = 'F';
            Trace::put("Unable to exratract DOCUMENT file");
            return false;
         }
      }
   }   
   m_strMainFile = "chargebacks";
   processDocument("chargebacks.xml");
   if (!finalizeNonVisaFiles(cStatus))
   {
      Trace::put("Unsuccessful execution of the FTP script");
      return false;
   }
   cStatus='S';
   return true;
  //## end DownloadFile::processBAMS%517588850372.body
}

bool DownloadFile::processCommand (char& cStatus, const string& strFilename)
{
  //## begin DownloadFile::processCommand%4FCFA6A80271.body preserve=yes
   Trace::put("VX01::processCommand");
   //restoreFiles();
   FlatFile hVRDMFile(m_strCustomer.c_str());
   hVRDMFile.setMember("*.cmd");
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find VRDM file");
      return false;
   }
   hVRDMFile.getBaseName(m_strMainFile,true);
   hVRDMFile.setMember(m_strMainFile.c_str());
   hVRDMFile.close();
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      hVRDMFile.close();
      cStatus = 'N';
      Trace::put("Cannot find Command Files");
      return false;
   }
   char szTempLine[BUFFER_SIZE +1];
   szTempLine[BUFFER_SIZE] = '\0';
   memset(szTempLine,' ',BUFFER_SIZE);
   size_t iReadSize = BUFFER_SIZE;
   string strLine;
   string strFolderName;
   string strzipFileName;
   while (hVRDMFile.read(szTempLine,BUFFER_SIZE+1,&iReadSize)==true )
   {
      strLine=szTempLine;
      transform (strLine.begin(),strLine.end(), strLine.begin(), ::toupper);
      if (strLine.find("COPY") != string::npos && strLine.find("VROLBATCH") != string::npos)
      {
         size_t nPos2 = strLine.find("VROLBATCH");
         size_t nPos3 = strLine.find(".ZIP",nPos2);
         if (nPos3!=string::npos)
            strzipFileName.assign(strLine,nPos2+11,nPos3 + 3 - (nPos2 + 10));
         break;
      }
      size_t nPos1 = strLine.find("SET VROLBATCH=");
      if (nPos1 != string::npos)
         strFolderName = strLine.substr(nPos1+14);
   }
   if (strFolderName.length() > 2 && strFolderName[2] == '\\')
   {
      m_strFolderName = "\\\\";
      m_strFolderName.append(Extract::instance()->getHost());
      m_strFolderName.append(strFolderName.substr(2));
   }
   else
      m_strFolderName = strFolderName;
   m_strHeaderFile = "CommandFiles";
   string strDatasetName = hVRDMFile.getDatasetName();
   hVRDMFile.getBaseName(m_strMainFile,true);
   hVRDMFile.close();
   m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length()-1));
   ImportReportAuditSegment::instance()->setFILE(m_strMainFile);
   size_t npos = strDatasetName.find_last_of('\\');
   string strOutput;
   strOutput.assign(strDatasetName,0,npos+1);
   string strLogFileName;
   if (m_strMainFile.find("VROLCUST") != string::npos)
      strLogFileName.assign("VROLCUSTLOG" + Clock::instance()->getYYYYMMDDHHMMSSHN().substr(2, 12) + ".txt");
   else
      strLogFileName.assign("VROLCOMNLOG" + Clock::instance()->getYYYYMMDDHHMMSSHN().substr(2, 12) + ".txt");
   strOutput.append(strLogFileName);
   strDatasetName.append(" >> ");
   strDatasetName.append(strOutput);
   if (system(strDatasetName.c_str()) != 0)
      Trace::put("System Command has issues");
   if (!createFolder("DCOMPLET"))
   {
      cStatus = 'F';
      Trace::put("Failed to create DCOMMAND folder");
      return false;
   }
   FlatFile hCleanupFile(m_strCustomer.c_str(),m_strMainFile.c_str());
   hCleanupFile.setOwner(m_strEntityFolder);
   hCleanupFile.setFolder(m_strHeaderFile);
   if (hCleanupFile.open())
   {
      if (!hCleanupFile.move("DCOMPLET"))
      {
         hCleanupFile.close();
         cStatus = 'F';
         Trace::put("Failed to move to DCOMPLET folder");
         return false;
      }
   }
   hCleanupFile.setMember(strLogFileName.c_str());
   hCleanupFile.setName(m_strCustomer.c_str());
   if (hCleanupFile.open())
   {
      if (!hCleanupFile.move("DCOMPLET"))
      {
         hCleanupFile.close();
         cStatus = 'F';
         Trace::put("Failed to move to DCOMPLET folder");
         return false;
      }
   }
   string strTemp(m_strFolderName);
   trim(strTemp);
   strTemp.append("\\");
   strTemp.append(strzipFileName);
   Trace::put(strTemp.c_str());
#ifdef _WIN64
   long long m_lFile;
   m_lFile = (long long)fopen(strTemp.c_str(), "rb");
#else
   long m_lFile;
   m_lFile = (long)fopen(strTemp.c_str(),"rb");
#endif
   if (m_lFile == 0)
   {
      Trace::put("ZIP file referred in command file is not available");
      m_strFolderName.erase();
      return true;
   }      
   fclose((FILE*)m_lFile);
   cStatus = 'S';
   return true;
  //## end DownloadFile::processCommand%4FCFA6A80271.body
}

bool DownloadFile::processDocument (const string& strFileName)
{
  //## begin DownloadFile::processDocument%4C695B460013.body preserve=yes
   FlatFile hRecordFile(m_strCustomer.c_str());
   FlatFile hExtractedFiles(m_strCustomer.c_str(),strFileName.c_str());
   hExtractedFiles.setOwner(m_strEntityFolder);
   if (!hExtractedFiles.open(FlatFile::CX_OPEN_INPUT))
      return false;
   string strTempFileName;
   hExtractedFiles.getBaseName(strTempFileName, true);
   //adds an .xml extension to the extracted original docs
   hExtractedFiles.move(m_strCustomer.c_str(),(strTempFileName+"_unstructured").c_str());
   hExtractedFiles.close();
   hExtractedFiles.setMember((strTempFileName+"_unstructured").c_str());
   if (!hExtractedFiles.open(FlatFile::CX_OPEN_INPUT))
      return false;
   if (strTempFileName[0] == 'B')
   {
      m_strHeaderFile = strTempFileName;
      rebuildXML(hExtractedFiles, true);
   }
   else if (strTempFileName[0] == 'R' || strTempFileName[0] == 'c')
      rebuildXML(hExtractedFiles);
   else
      return false;
   hExtractedFiles.close();
   hExtractedFiles.remove();
   return true;
  //## end DownloadFile::processDocument%4C695B460013.body
}

bool DownloadFile::processECHIST (char& cStatus)
{
  //## begin DownloadFile::processECHIST%4F593D120172.body preserve=yes
   Trace::put("VX01::processECHIST");
   FlatFile hVRDMFile(m_strCustomer.c_str());
   hVRDMFile.setMember("ECOUT*");
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find ECHIST file");
      return false;
   }
   hVRDMFile.getBaseName(m_strMainFile,true);
   hVRDMFile.setMember(m_strMainFile.c_str());
   m_strHeaderFile = m_strMainFile;
   hVRDMFile.close();
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      Trace::put("Cannot access ECHIST file");
      return false;
   }
   if (m_strMainFile.find("original_") != string::npos)
   {
      string strTemp = m_strMainFile+".cleanup";
      hVRDMFile.move(m_strCustomer.c_str(),strTemp.c_str());
      Trace::put("Renamed a file for cleanup");
      return false;
   }
   Trace::put("VX01: Going to unzip the file"); 
   hVRDMFile.getBaseName(m_strMainFile,true);
   m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length()-1));
   ImportReportAuditSegment::instance()->setFILE(m_strMainFile);
   if (!hVRDMFile.unzip())
   {
      hVRDMFile.close();
      cStatus = 'F';
      Trace::put("Unable to exratract ECHIST file");
      return false;
   }
   if (!hVRDMFile.move(m_strCustomer.c_str(),("original_"+m_strMainFile).c_str()))
   {
      hVRDMFile.close();
      cStatus = 'F';
      Trace::put("Unable rename ECHIST file to: original_");
      return false;
   }
   hVRDMFile.close();

   FlatFile hVRDMFile3(m_strCustomer.c_str());
   hVRDMFile3.setMember("ECHIST*");
   if (!hVRDMFile3.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find VRDM file");
      return false;
   }
   hVRDMFile3.getBaseName(m_strMainFile,true);
   hVRDMFile3.setMember(m_strMainFile.c_str());
   hVRDMFile3.close();
   if (!hVRDMFile3.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      Trace::put("Cannot access ECHIST file");
      return false;
   }
   hVRDMFile3.close();
   string strMainFile;
   strMainFile.assign(m_strMainFile);
   FlatFile hVRDMFile1(m_strCustomer.c_str());
   hVRDMFile1.setMember("DECHIST*");
   if (hVRDMFile1.open(FlatFile::CX_OPEN_INPUT))
   {
      hVRDMFile1.getBaseName(m_strMainFile,true);
      hVRDMFile1.setMember(m_strMainFile.c_str());
      hVRDMFile1.close();
      if (!hVRDMFile1.open(FlatFile::CX_OPEN_INPUT))
      {
         cStatus = 'F';
         Trace::put("Cannot access DOCUMENT file");
         return false;
      }
      if (!hVRDMFile1.unzip())
      {
         cStatus = 'F';
         Trace::put("Unable to exratract DOCUMENT file");
         return false;
      }
      string strBaseName;
      size_t pos = hVRDMFile1.getDatasetName().find_last_of('\\');
      if (pos != string::npos)
         strBaseName.assign(hVRDMFile1.getDatasetName(),0,pos+1);
      hVRDMFile1.close();
      FlatFile hVRDMFile2(m_strCustomer.c_str());
      hVRDMFile2.setMember("CECHIST*");
      if (!hVRDMFile2.open(FlatFile::CX_OPEN_INPUT))
      {
         cStatus = 'N';
         Trace::put("Cannot find COMMAND file");
         return false;
      }
      if (!hVRDMFile2.open(FlatFile::CX_OPEN_INPUT))
      {
         cStatus = 'F';
         Trace::put("Cannot access COMMAND file");
         return false;
      }
      char szTempLine[BUFFER_SIZE1 +1];
      szTempLine[BUFFER_SIZE1] = '\0';
      memset(szTempLine,' ',BUFFER_SIZE1);
      size_t iReadSize = BUFFER_SIZE1;
      int i = 1;
      string strDOC_PATH;
      string strLine;
      if (!(Extract::instance()->getSpec("DOCPATH",strDOC_PATH)))
      {
         cStatus = 'N';
         Trace::put("DOCPATH is not found");
         return false;
      }
      while (hVRDMFile2.read(szTempLine,BUFFER_SIZE1+1,&iReadSize)==true )
      {
         string strTempDOC_PATH(strDOC_PATH);
         string strFileLocation(strBaseName); 
         string strFileDestinationName; 
         strLine="";
         strLine=szTempLine;
         size_t nPos = strLine.find("&docpath");
         string strFolder;
         if (nPos > 7)
            strFolder.assign(strLine,nPos + 9, strLine.length()-nPos - 8);
         strFileLocation.append(strLine.substr(1,nPos - 2));
         strFileDestinationName.assign(strDOC_PATH);
         strFileDestinationName.append("\\");
         strFileDestinationName.append(strFolder);
         vector<string> hTokens;
         Buffer::parse(strFolder,"\\",hTokens);
         int i =0;
         while (hTokens.size() > 0 && i < hTokens.size()-1)
         {
            strTempDOC_PATH.append("\\");
            strTempDOC_PATH.append(hTokens[i]);
            CreateDirectory(strTempDOC_PATH.c_str(),NULL);
            i++;
         }
         bool b = CopyFile(strFileLocation.c_str(),strFileDestinationName.c_str(),false);
         if (!b)
         {
            Trace::put("Copying Document for ECHIST is failed");
            Trace::put(strFileLocation.c_str());
         }
         b = DeleteFile(strFileLocation.c_str());
      }
      hVRDMFile2.close();
   }
   m_strMainFile = strMainFile;
   if (!finalizeNonVisaFiles(cStatus))
   {
      Trace::put("Unable to move files to complete folder");
      return false;
   }
   Trace::put("SuccesFully Exported ECHIST file");
   return true;
  //## end DownloadFile::processECHIST%4F593D120172.body
}

bool DownloadFile::processMSTR (char& cStatus)
{
  //## begin DownloadFile::processMSTR%535E9CC2015E.body preserve=yes
   Trace::put("VX01::processMSTR");
   FlatFile hMSTRFile(m_strCustomer.c_str());
   hMSTRFile.setMember("MSTRIN*");
   if (!hMSTRFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find MSTR file");
      return false;
   }
   m_strHeaderFile = "MSTRIN";
   hMSTRFile.getBaseName(m_strMainFile,true);
   hMSTRFile.setMember(m_strMainFile.c_str());
   size_t nPos = hMSTRFile.getName().find_last_of("\\");
   string strLocation(hMSTRFile.getName(),0,nPos+1);
   hMSTRFile.close();
   //reopens specifically named MSTR file
   if (!hMSTRFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      Trace::put("Cannot access MSTR file");
      return false;
   }
   if (m_strMainFile.find("original_") != string::npos)
   {
      string strTemp = m_strMainFile+".cleanup";
      hMSTRFile.move(m_strCustomer.c_str(),strTemp.c_str());
      Trace::put("Renamed a file for cleanup");
      return false;
   }
   hMSTRFile.getBaseName(m_strMainFile,true);
   m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length()-1));
   ImportReportAuditSegment::instance()->setFILE(m_strMainFile);
   //Unzips the MSTR zip and moves it to complete with original_ prefix.
   if (!hMSTRFile.unzip())
   {
      Trace::put("Unable to exratract MSTR file");
      return false;
   }
   if (!hMSTRFile.move(m_strCustomer.c_str(),("original_"+m_strMainFile).c_str()))
   {
      Trace::put("Unable rename MSTR file to: original_");
      return false;
   }
   hMSTRFile.close();

   string strCommand("copy ");
   string strSource,strDest,strTemp1;
   if (Extract::instance()->find(("DFILES  "+m_strCustomer).c_str(),strTemp1))
   {
      if ((strTemp1[16] != '.')
         && (strTemp1[18] != '\\')
         && (memcmp(strTemp1.data()+16,"\\\\",2) != 0))
      {
         strSource = Extract::instance()->getNode001();
         strSource += "\\";
      }
   }
   strSource.append(strLocation);
   strCommand.append(strSource);
   strCommand.append("*.xml ");
   FlatFile hRemoveFile("MSTRTEMP");
   hRemoveFile.setMember("*");
   hRemoveFile.remove();
   nPos = hRemoveFile.getName().find_last_of("\\");
   string strLocation1(hRemoveFile.getName(),0,nPos+1);
   if (Extract::instance()->find(("DFILES  MSTRTEMP"),strTemp1))
   {
      if ((strTemp1[16] != '.')
         && (strTemp1[18] != '\\')
         && (memcmp(strTemp1.data()+16,"\\\\",2) != 0))
      {
         strDest = Extract::instance()->getNode001();
         strDest += "\\";
      }
   }
   strDest.append(strLocation1);
   strDest.append("MSTRTEMP.xml");
   strCommand.append(strDest);
   Trace::put(strCommand.c_str());
   if (!system(strCommand.c_str()))
      Trace::put("Issues with copying to MSTRTEMP folder");
   hMSTRFile.setMember("*.xml");
   hMSTRFile.remove();
   hRemoveFile.setMember("MSTRTEMP.xml");
   if (!hRemoveFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      return "Cannot access MSTR file";
   }
   rebuildXML(hRemoveFile);
   hRemoveFile.remove();
// Read The file and add wrapper tags
// Move all TIF files to another location
   Extract::instance()->find(("DFILES  MSTRTEMP"),strTemp1);
   string strTemp;
   string strTemp2("DFILES  DMSTRDOC");
   strTemp2.replace(8, 5, m_strCustomer);
   if (Extract::instance()->getRecord(strTemp2.c_str(), strTemp))
   {
      string strRecord("DFILES  ");
      strRecord.append(m_strCustomer);
      strRecord.append("DO1");
      strRecord.resize(16, ' ');
      string strOldValue;
      if (Extract::instance()->getRecord(strRecord.c_str(), strOldValue) == true)
      {
         strOldValue = strRecord;
         strOldValue.append(m_strDocPath);
         Extract::instance()->setRecord(strRecord.c_str(), strOldValue);
      }
      else
      {
         strRecord.append(m_strDocPath);
         Extract::instance()->addRecord(strRecord);
      }

      if (!createDocumentFolder(m_strCustomer + "DO1", strSource))
         return false;
   }
   //moves files to complete folder and tries to execute FTP script
   if (!finalizeNonVisaFiles (cStatus))
   {
      Trace::put("Unable to move files to complete folder");
      return false;
   }
   cStatus='S';
   Trace::put("MSTR File has successfully processed");
   return true;
  //## end DownloadFile::processMSTR%535E9CC2015E.body
}

bool DownloadFile::processSTAR (char& cStatus)
{
  //## begin DownloadFile::processSTAR%63D6948B031D.body preserve=yes
   Trace::put("VX01::processSTAR");
   FlatFile hSTARFile(m_strCustomer.c_str());
   hSTARFile.setMember("ImageOut*");  //setting zip file to open
   if (!hSTARFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find STAR file");
      return false;
   }
   hSTARFile.getBaseName(m_strMainFile,true);
   hSTARFile.setMember(m_strMainFile.c_str());
   size_t nPos = hSTARFile.getName().find_last_of("\\");
   string strLocation(hSTARFile.getName(),0,nPos + 1);
   hSTARFile.close();
   if (!hSTARFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      Trace::put("Cannot access ImageOut zip file");
      return false;
   }
   m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length() - 1)); //Setting STAR as EntityFolder
   ImportReportAuditSegment::instance()->setFILE(m_strMainFile);
   if (!hSTARFile.unzip())  // unzip the archive file
   {
      Trace::put("Unable to exratract MSTR file");
      return false;
   }
   //taking backing up of inbound zip file
   if (!hSTARFile.move(m_strCustomer.c_str(),("original_" + m_strMainFile).c_str()))
   {
      Trace::put("Unable rename STAR file to: original_");
      return false;
   }
   hSTARFile.close();
   string strTempOutFileName;
   hSTARFile.setMember("*-outbound.xml"); //setting pattern to open inbound file 
   if (!hSTARFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find outbound xml file");
      return false;
   }
   hSTARFile.getBaseName(strTempOutFileName,true);
   hSTARFile.setMember(strTempOutFileName.c_str());
   strTempOutFileName.assign("new" + strTempOutFileName);
   hSTARFile.move(m_strCustomer.c_str(),strTempOutFileName.c_str());
   hSTARFile.close();
   //creating new xml file
   string strCustDoc(m_strCustomer + "DOC");
   if (!createFolder(strCustDoc.c_str()))
      return false;
   FlatFile hOutFile(m_strCustomer.c_str());
   hOutFile.setMember(strTempOutFileName.c_str());
   hOutFile.setOwner(m_strEntityFolder);
   if (!hOutFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find STAR file");
      return false;
   }
   m_strMainFile = strTempOutFileName.substr(3);
   rebuildXML(hOutFile,false);
   hOutFile.remove();
   FlatFile hDocFile(m_strCustomer.c_str());
   if (!m_hDocFileNames.empty())
   {
      for (int i = 0; i < m_hDocFileNames.size(); i++)
      {
         hDocFile.setName(m_strCustomer.c_str());
         hDocFile.setMember(m_hDocFileNames[i].c_str());
         if (!hDocFile.open(FlatFile::CX_OPEN_INPUT))
         {
            cStatus = 'N';
            Trace::put("Cannot find STAR file");
            return false;
         }
         hDocFile.move(strCustDoc.c_str());
         hDocFile.close();
      }      
      string strFolderName(hDocFile.getName(), 0, hDocFile.getName().find_last_of("\\"));
      if (strFolderName[2] == '\\')
      {
         m_strFolderName = "\\\\";
         m_strFolderName.append(Extract::instance()->getHost());
         m_strFolderName.append(strFolderName.substr(2));
      }
      else
         m_strFolderName = strFolderName;
   }
   m_strHeaderFile = m_strEntityFolder + "IN"; // destination folder name STRIN CPPIN CPYIN
   m_strMainFile = strTempOutFileName.substr(3);
   if (!finalizeNonVisaFiles(cStatus))
   {
      Trace::put("Unsuccessful execution of the FTP script");
      return false;
   }
   Trace::put("STAR documents have been processed successfully");
   cStatus = 'S';
   return true;
  //## end DownloadFile::processSTAR%63D6948B031D.body
}

bool DownloadFile::processVRDM (char& cStatus)
{
  //## begin DownloadFile::processVRDM%4C695A250075.body preserve=yes
   Trace::put("VX01::processVROL");
   //restoreFiles();
   FlatFile hVRDMFile(m_strCustomer.c_str());
   hVRDMFile.setMember("*.zip");
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'N';
      Trace::put("Cannot find VRDM file");
      return false;
   }
   hVRDMFile.getBaseName(m_strMainFile,true);
   hVRDMFile.setMember(m_strMainFile.c_str());
   hVRDMFile.close();
   //reopens specifically named VRDM file
   if (!hVRDMFile.open(FlatFile::CX_OPEN_INPUT))
   {
      cStatus = 'F';
      Trace::put("Cannot access VRDM file");
      return false;
   }
   if (m_strMainFile.find("original_") != string::npos)
   {
      string strTemp = m_strMainFile+".cleanup";
      hVRDMFile.move(m_strCustomer.c_str(),strTemp.c_str());
      Trace::put("Renamed a file for cleanup");
      return false;
   }
   Trace::put("VX01: Going to unzip the file"); 
   hVRDMFile.getBaseName(m_strMainFile,true);
   m_strEntityFolder = m_strCustomer.substr(1,(m_strCustomer.length()-1));
   ImportReportAuditSegment::instance()->setFILE(m_strMainFile);
   //Unzips the VRDM zip and moves it to complete with original_ prefix.
   if (!hVRDMFile.unzip())
   {
      Trace::put("Unable to exratract VRDM file");
      return false;
   }
   if (!hVRDMFile.move(m_strCustomer.c_str(),("original_"+m_strMainFile).c_str()))
   {
      Trace::put("Unable rename VRDM file to: original_zip");
      return false;
   }
   hVRDMFile.close();
   //process BDM
   if (!processDocument("BDM*"))
   {
      Trace::put("Unable to process BDM file");
      return false;
   }
   //process RDM
   if (m_hBodyFiles.size()!=0)
   {
      vector<string>::iterator pItr;
      for(pItr = m_hBodyFiles.begin(); pItr != m_hBodyFiles.end(); pItr++)
      {
         if ((*pItr).compare(4,2,m_strHeaderFile,4,2)!=0)
         {
            Trace::put("BDM file references an incorrect RDM file name");
            return false;
         }
         if (!processDocument(*pItr))
         {
            Trace::put("Unable to process RDM file:");
            Trace::put((*pItr).c_str());
            return false;
         }
      }
   }
   //process DDM
   if (m_strDocFile.size()!=0)
   {
      FlatFile hDocFile(m_strCustomer.c_str(),m_strDocFile.c_str());
      hDocFile.setOwner(m_strEntityFolder);
      hDocFile.setFolder(m_strHeaderFile);
      if (!hDocFile.open(FlatFile::CX_OPEN_INPUT))
      {
         Trace::put("The documentation file does not exist");
         return false;
      }
      if (m_strDocFile.compare(4,2,m_strHeaderFile,4,2)!=0)
      {
         Trace::put("BDM file references an incorrect DDM file name");
         return false;
      }
      string strTemp;
      string strTemp1("DFILES  DVROLDOC");
      strTemp1.replace(8,5,m_strCustomer);
      if (Extract::instance()->getRecord(strTemp1.c_str(),strTemp))
      {
         string strRecord("DFILES  ");
         strRecord.append(m_strCustomer);
         strRecord.append("DO1");
         strRecord.resize(16, ' ');
         string strOldValue;
         if (Extract::instance()->getRecord(strRecord.c_str(), strOldValue) == true)
         {
            strOldValue = strRecord;
            strOldValue.append(m_strDocPath);
            Extract::instance()->setRecord(strRecord.c_str(), strOldValue);
         }
         else
         {
            strRecord.append(m_strDocPath);
            Extract::instance()->addRecord(strRecord);
         }
         if (!createFolder(m_strCustomer + "DO1"))
            return false;
         m_strDocFile.append(".zip");
         hDocFile.move((m_strCustomer + "DO1").c_str(),m_strDocFile.c_str());
         hDocFile.close();
         FlatFile hDocFile1((m_strCustomer + "DO1").c_str(),m_strDocFile.c_str());
         hDocFile1.setOwner(m_strEntityFolder);
         hDocFile1.setFolder(m_strHeaderFile);
         if (hDocFile1.open(FlatFile::CX_OPEN_INPUT))
         {
            size_t pos = hDocFile1.getDatasetName().find_last_of('\\');
            if (pos != string::npos)
            {
               string strFolderName(hDocFile1.getDatasetName().data(),0,pos);
               if (strFolderName[2] == '\\')
               {
                  m_strFolderName = "\\\\";
                  m_strFolderName.append(Extract::instance()->getHost());
                  m_strFolderName.append(strFolderName.substr(2));
                }
               else
                  m_strFolderName = strFolderName;
            }
            if (!hDocFile1.unzip())
            {
               cStatus = 'F';
               Trace::put("Unable to exratract DOCUMENT file");
               return false;
            }
            string strFileLocation = hDocFile1.getName();
            hDocFile1.close();
            string strCommand;
            string strSource;
            string strSource1;
            if (Extract::instance()->find(("DFILES  "+m_strCustomer + "DO1").c_str(),strTemp))
            {
               if ((strTemp[16] != '.')
               && (strTemp[18] != '\\')
               && (memcmp(strTemp.data()+16,"\\\\",2) != 0))
               {
                  strSource = Extract::instance()->getNode001();
                  strSource += "\\";
               }
            }
            if (!m_hInvalidFiles.empty())
            {
               for (int i=0;i<m_hInvalidFiles.size();i++)
               {
                  strSource1 = strSource;
                  size_t nPos = strFileLocation.find_last_of("\\");
                  strFileLocation.erase(nPos+1);
                  strFileLocation.append(m_hInvalidFiles[i]);
                  strCommand = "del ";
                  strSource1.append(strFileLocation);
                  strCommand.append(strSource1);
                  Trace::put(strCommand.c_str());
                  system(strCommand.c_str());
               }
            }
            if (!m_hDocFileNames.empty())
            {
               for (int i=0;i<m_hDocFileNames.size();i++)
               {
                  strSource1 = strSource;
                  size_t nPos = strFileLocation.find_last_of("\\");
                  strFileLocation.erase(nPos+1);
                  nPos = m_hDocFileNames[i].find_last_of(".");
                  strFileLocation.append(m_hDocFileNames[i].substr(0,nPos));
                  strSource1.append(strFileLocation);
                  strSource1.append(" ");
                  strSource1.append(m_hDocFileNames[i]);
                  strCommand = "ren ";
                  strCommand.append(strSource1);
                  Trace::put(strCommand.c_str());
                  system(strCommand.c_str());
               }
            }
            strSource1 = strSource;
            strCommand = "del ";
            size_t nPos = strFileLocation.find_last_of("\\");
            strFileLocation.erase(nPos+1);
            strSource1.append(strFileLocation);
            strSource1.append(m_strDocFile);
            strCommand.append(strSource1);
            Trace::put(strCommand.c_str());
            system(strCommand.c_str());
         }
      }
      else
         hDocFile.close();
   }
   Trace::put("VX01::All documents have been processed");
   //moves files to complete folder and tries to execute FTP script
   if (!finalizeFiles())
   {
      Trace::put("Unable to move files to complete folder");
      return false;
   }
   m_hFTPScriptFile1.setName("DCOMPLET");
   m_hFTPScriptFile1.setFolder(m_strHeaderFile);
   m_hFTPScriptFile1.setOwner(m_strEntityFolder);
   m_hFTPScriptFile1.setMember((m_strMainFile+".ftp").c_str());
   if (Extract::instance()->getCustomCode() == "DGMC")
   {
      if (setupDGMCFTP())
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
   if (!setupFTP())
   {
      Trace::put("Unable to setup FTP file");
      return false;
   }
   if (finishFTP()==true)
   {
      cStatus='S';
      ImportReportAuditSegment::instance()->setFILE(m_strMainFile+".ftp");
      Trace::put("Successfully Uploaded");
      return true;
   }
   Trace::put("Unsuccessful execution of the FTP script");
   return false;
  //## end DownloadFile::processVRDM%4C695A250075.body
}
bool DownloadFile::processZIP (const string& strFilename)
{
   return true;
}
bool DownloadFile::readExtract ()
{
  //## begin DownloadFile::readExtract%4C697E39022E.body preserve=yes
   string strDaysUntilDelete, strErrorsBetweenEmails;
   string strTemp;
   if (!(Extract::instance()->getSpec("FTPIBMH",m_strFTPIbmHost)
      && Extract::instance()->getSpec("FTPUSRID",m_strFTPUsername)
      && Extract::instance()->getSpec("FTPPSWRD",m_strFTPPassword)
      && Extract::instance()->getSpec("DDELDAY",strDaysUntilDelete)
      && Extract::instance()->getSpec("EMAILADR",m_strContactEmailAddress)
      && Extract::instance()->getSpec("ERMAILNM",strErrorsBetweenEmails)
      && Extract::instance()->getSpec("UNZIPCOM",strTemp)
      && Extract::instance()->getSpec("ZIPCOM",strTemp)
      && Extract::instance()->find("DFILES  DCOMPLET",strTemp)
      && Extract::instance()->find("DFILES  DDOC    ",strTemp)))
      return false;
   AdvancedEncryptionStandard::decrypt(m_strFTPUsername);
   AdvancedEncryptionStandard::decrypt(m_strFTPPassword);
   //If cannot convert DSPEC values from strings to integers
   if ((m_iDaysUntilDelete = atoi(strDaysUntilDelete.c_str()))==0
      || (m_iErrorsBetweenEmails = atoi(strErrorsBetweenEmails.c_str()))==0)
      return false;
   return true;
  //## end DownloadFile::readExtract%4C697E39022E.body
}

bool DownloadFile::rebuildXML (IF::FlatFile& hInFile, const bool& bIsHeader)
{
  //## begin DownloadFile::rebuildXML%4C587F0301E9.body preserve=yes
   string strFileName;
   hInFile.getBaseName(strFileName);
   //removes the "_unprocessed" from the xml file name
   strFileName.erase(8);
   if (m_strEntityFolder == "BAMS")
      strFileName.assign("chargebacks",0,11);
   if (m_strEntityFolder == "MSTR")
   {
      strFileName.assign(m_strMainFile,0,8);
      strFileName.append(Clock::instance()->getYYYYMMDDHHMMSS(),0,8);
      strFileName.append(".T");
      strFileName.append(Clock::instance()->getYYYYMMDDHHMMSS(),8,6);
      strFileName.append(".xml");
      m_strMainFile = strFileName;
   }
   else if (m_strEntityFolder == "STR" || m_strEntityFolder == "CPP" || m_strEntityFolder == "CPY")
      strFileName = m_strMainFile;

   FlatFile hOutFile(m_strCustomer.c_str(),strFileName.c_str());
   hOutFile.setOwner(m_strEntityFolder);
   if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
      return false;
   if (m_strEntityFolder == "MSTR")
   {
      string strTemp("<Wrapper>");
      hOutFile.write((char*)strTemp.data(), strTemp.length());
      string strTemp2("DFILES  DMSTRDOC");
      strTemp2.replace(8, 5, m_strCustomer);
      string strTemp3;
      if (Extract::instance()->getRecord(strTemp2.c_str(), m_strDocPath))
      {
         //m_strDocPath.erase(0, 16);
         string strTemp4("<DocumentationPath>");
         //m_strDocPath will now have %date and %time in it.
         //Replace %date with first 8 characters of Transaction::instance()->getTimeStamp()
         int nPos = m_strDocPath.find("%date");
         if (nPos != string::npos)
            m_strDocPath.replace(nPos, 5, Transaction::instance()->getTimeStamp().substr(0, 8));
         //Replace %time with next 6 characters of Transaction::instance()->getTimeStamp()
         nPos = m_strDocPath.find("%time");
         if (nPos != string::npos)
            m_strDocPath.replace(nPos, 5, Transaction::instance()->getTimeStamp().substr(8, 6));
         string strDest;
         if ((m_strDocPath[16] != '.')
            && (m_strDocPath[18] != '\\')
            && (memcmp(m_strDocPath.data() + 16, "\\\\", 2) != 0))
         {
            strDest.append(Extract::instance()->getNode001());
            strDest += "\\";
         }
         strDest.append(m_strDocPath.substr(16));
         m_strDocPath = strDest;
         strTemp4.append(m_strDocPath);
         nPos = strTemp4.find("%member");
         if (nPos != string::npos)
            strTemp4.erase(nPos);
         strTemp4.append("</DocumentationPath>");
         hOutFile.write((char*)strTemp4.data(), strTemp4.length());
      }
   }
   string strLine;
   string strskipLine;
   string strTempTag;
   bool bWithinPackageTag=false;
   //Creates buffer for reading chunks of file
   char szTempLine[BUFFER_SIZE1 +1];
   size_t iReadSize = BUFFER_SIZE1;
   while (hInFile.read(szTempLine,BUFFER_SIZE1+1,&iReadSize)==true )
   {
      // Remove xml line for mastercard file
      strskipLine = szTempLine; 
      if (m_strEntityFolder == "MSTR"
      && strskipLine.find("xml version") != string::npos) 
         continue;
	  string strTempLine = szTempLine;
	  size_t p = 0;
	  size_t q = 0;
	  size_t r = 0;
	  while ((p = strTempLine.find("&")) != string::npos)
	  {
		  if ((q = strTempLine.find("amp;")) != string::npos)
			  strTempLine.erase(q,4);
		  else 
		  if ((r = strTempLine.find("apos;")) != string::npos ||
			  ((r = strTempLine.find("quot;")) != string::npos))
			  strTempLine.erase(r,5);
		  else
			  strTempLine.erase(p,1);
	  }
      //Adds buffer and leaves residue from last cycle
	  strLine += strTempLine;
      //Loops through strLine and prints tags untill there is less than 2 tags
      //or it is the end of the file and the last tag needs to be processed
      while(strLine.find_first_of('>')!= strLine.find_last_of('>'))
      {
         //Formats the output into a single tag or a pair of tags.
         if ( strLine.find("<")!=strLine.find("</")    //If the first tag is not a close tag
            && strLine.find("<",strLine.find("<")+1)==strLine.find("</"))  //and the second tag is a close tag
         {
            strTempTag.assign(strLine,0,strLine.find(">",strLine.find(">")+1)+1);
         }
         else
         {
            if (strLine.find(">")!=string::npos)
               strTempTag.assign(strLine,0,strLine.find(">")+1);
            else
               strTempTag = strLine;
         }
         if (m_strEntityFolder == "STR" || m_strEntityFolder == "CPP" || m_strEntityFolder == "CPY")
         {
            string strImgFileNameTag("<image-file-name>");
            if (strTempTag.find(strImgFileNameTag) != string::npos)
            {
               int i = strTempTag.find(strImgFileNameTag) + strImgFileNameTag.length();
               int j = strTempTag.find('<',i);
               m_hDocFileNames.push_back(strTempTag.substr(i,j-i));
            }
         }
         else if (bIsHeader==true)
         {
            if (strTempTag.find("<Package ")!=string::npos)
            {
               int i = strTempTag.find("name=\"")+6;
               int j = strTempTag.find("\"",i);
               m_hBodyFiles.push_back(strTempTag.substr(i,j-i));
            }
            int i;
            if (bWithinPackageTag == true
               && (i = strTempTag.find("<Name>"))!=string::npos)
            {
               i+=6;
               int j = strTempTag.find("<",i);
               m_strDocFile.assign(strTempTag,i,j-i);
               string strTemp("<DocNetId>");
               strTemp.append(m_strEntityFolder);
               strTemp.append("</DocNetId>");
               string strTemp2("DFILES  DVROLDOC");
               strTemp2.replace(8, 5, m_strCustomer);
               string strTemp3;
               if (Extract::instance()->getRecord(strTemp2.c_str(), m_strDocPath))
               {
                  //m_strDocPath.erase(0, 16);
                  string strTemp4("<DocumentationPath>");
                  //m_strDocPath will now have %date and %time in it.
                  //Replace %date with first 8 characters of Transaction::instance()->getTimeStamp()
                  int nPos = m_strDocPath.find("%date");
                  if (nPos != string::npos)
                     m_strDocPath.replace(nPos, 5, Transaction::instance()->getTimeStamp().substr(0,8));
                  //Replace %time with next 6 characters of Transaction::instance()->getTimeStamp()
                  nPos = m_strDocPath.find("%YYYY");
                  if (nPos != string::npos)
                     m_strDocPath.replace(nPos, 5, Transaction::instance()->getTimeStamp().substr(0, 4));
                  nPos = m_strDocPath.find("%MM");
                  if (nPos != string::npos)
                     m_strDocPath.replace(nPos, 3, Transaction::instance()->getTimeStamp().substr(4, 2));
                  nPos = m_strDocPath.find("%time");
                  if (nPos != string::npos)
                  m_strDocPath.replace(nPos, 5, Transaction::instance()->getTimeStamp().substr(8, 6));
                  string strDest;
                  if ((m_strDocPath[16] != '.')
                     && (m_strDocPath[18] != '\\')
                     && (memcmp(m_strDocPath.data() + 16, "\\\\", 2) != 0))
                  {
                    strDest.append(Extract::instance()->getNode001());
                    strDest += "\\";
                  }
               strDest.append(m_strDocPath.substr(16));
               m_strDocPath = strDest;
               strTemp4.append(m_strDocPath);
               nPos = strTemp4.find("%member");
               if (nPos != string::npos)
                  strTemp4.erase(nPos);
               strTemp4.append("</DocumentationPath>");
               hOutFile.write((char*)strTemp4.data(), strTemp4.length());
               }
               hOutFile.write((char*)strTemp.data(),strTemp.length());
            }
            if (strTempTag.find("<PackageFile ")!=string::npos)
               bWithinPackageTag = true;
            if (strTempTag.find("</PackageFile>")!=string::npos)
               bWithinPackageTag = false;
         }
         int iDeleteLen = strTempTag.length();
         if (strTempTag.find("<RemoteFileName>") != string::npos
            && strTempTag.find("?xml") == string::npos)
            if (!checkDocExtension(strTempTag))
               strTempTag = "<RemoteFileName>INVALIDFILE</RemoteFileName>";
         //If the output is under 513 characters they are printed to the file
         //If the output is over 512 characters they are split without breaking the tags
         if (iDeleteLen <513)
         {
            hOutFile.write((char*)strTempTag.data(),strTempTag.length());
            strLine.erase(0, iDeleteLen);
         }
         else
         {
            int i = strTempTag.rfind("<",512);
            int j = strTempTag.rfind(">",512);
            if (i>j)
            {
               //prevents tags from being split by a newline
               hOutFile.write((char*)strLine.data(),i);
               strLine.erase(0,i);
            }
            else
            {
               hOutFile.write((char*)strLine.data(),512);
               strLine.erase(0,512);
            }
         }
      }     //ends read tag(s) while loop
   }     //ends readline while loop
   //outputs last buffer residue from after the inFile has been fully read
   size_t pos = strLine.find_last_of('>');
   if (pos != string::npos)
      hOutFile.write((char*)strLine.data(),pos + 1);
   if (m_strEntityFolder == "MSTR")
   {      
      string strTemp("</Wrapper>");
      hOutFile.write((char*)strTemp.data(), strTemp.length());
   }
   hOutFile.close();
   return true;
  //## end DownloadFile::rebuildXML%4C587F0301E9.body
}

void DownloadFile::resetVars ()
{
  //## begin DownloadFile::resetVars%4C6959A603A7.body preserve=yes
   m_strHeaderFile.erase();
   m_strDocFile.erase();
   m_strEntityFolder.erase();
   m_hBodyFiles.clear();
   m_hInvalidFiles.clear();
   m_hDocFileNames.clear();
   ImportReportAuditSegment::instance()->setREJECT_CODES("");
   ImportReportAuditSegment::instance()->setFILE("");
   //ImportReportAuditSegment::instance()->setREJECT_CODES("");
  //## end DownloadFile::resetVars%4C6959A603A7.body
}

void DownloadFile::restoreFiles ()
{
  //## begin DownloadFile::restoreFiles%4C5AD32B0242.body preserve=yes
   Trace::put("VX01::Restoring original VR files");
   //cleans up unfinished files from last unsuccessful run
   FlatFile hRestoreFile("");
   hRestoreFile.setMember("BDM*");
   hRestoreFile.setName("DPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("RDM*");
   hRestoreFile.setName("DPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("DDM*");
   hRestoreFile.setName("DPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("*.ftp");
   hRestoreFile.setName("DPENDING");
   hRestoreFile.remove();
   hRestoreFile.setName("DPENDING");
   hRestoreFile.setMember("original_*");
   while(hRestoreFile.open())
   {
      string strOriginalName;
      hRestoreFile.getBaseName(strOriginalName,true);
      //removes the "original_" prefix from the file
      strOriginalName.erase(0,9);
      hRestoreFile.move("DPENDING",strOriginalName.c_str());
      hRestoreFile.close();
      hRestoreFile.setName("DPENDING");
   }
  //## end DownloadFile::restoreFiles%4C5AD32B0242.body
}

void DownloadFile::sendStatus (char& cStatus, const string& strReason)
{
  //## begin DownloadFile::sendStatus%517586A90334.body preserve=yes
   if (cStatus == 'F')
   {
      if (strReason != m_strPreviousError)
         m_iConsecutiveErrorCount=0;
      m_iConsecutiveErrorCount ++;
      m_strPreviousError = strReason;
   }
   if (cStatus == 'S'
      || m_iConsecutiveErrorCount >= m_iErrorsBetweenEmails)
         m_iConsecutiveErrorCount = 0;
   if (cStatus == 'S'
      || m_iConsecutiveErrorCount == 1)
   {
      email();
      m_pEmail->report(cStatus);
      m_pEmail->getFlatFile().close();
      m_pEmail->complete();
      delete m_pEmail;
      m_pEmail = 0;
   }
  //## end DownloadFile::sendStatus%517586A90334.body
}

void DownloadFile::setSpaceParam ()
{
  //## begin DownloadFile::setSpaceParam%50AC73E20266.body preserve=yes
   string strValue;
   string strKey(m_strEntityFolder) ;
   if(strKey!="ECHIST")
   {
      strKey.append(m_strHeaderFile.substr(1,1));
      strKey.append(m_strHeaderFile.substr(3,1));
   }      
   strKey.append("PR");
   if(Extract::instance()->getSpec(strKey.c_str(),strValue) )
   {
      strValue.insert(0,"quote SITE PRIM=");
      m_hFTPScriptFile1.write((char*)strValue.data(),strValue.length());
   }
   strKey.replace(6,2,"SE");   
   if(Extract::instance()->getSpec(strKey.c_str(),strValue)) 
   {
      strValue.insert(0,"quote SITE SEC=");
      m_hFTPScriptFile1.write((char*)strValue.data(),strValue.length());
   } 

  //## end DownloadFile::setSpaceParam%50AC73E20266.body
}

bool DownloadFile::setupDGMCFTP ()
{
  //## begin DownloadFile::setupDGMCFTP%55CA3787015F.body preserve=yes
   FlatFile hFinishedFiles("DCOMPLET");
   hFinishedFiles.setOwner(m_strEntityFolder);
   hFinishedFiles.setFolder(m_strHeaderFile.c_str());
   string strFilename;
   string strCommand;
   string strTemp;
   string strTemp1;
   Resource::instance()->getText("SFTP_SEND", strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_HOST", strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_PORT", strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   string strCommand1(strCommand);
   if (m_strEntityFolder != "MSTR")
   {
      vector<string>::iterator pItr;
      int i = 0;
      char szTemp[4];
      for (pItr = m_hBodyFiles.begin(); pItr != m_hBodyFiles.end(); pItr++)
      {
         hFinishedFiles.setMember((*pItr).c_str());
         if (!hFinishedFiles.open())
            return false;
         strCommand1 = strCommand;
         strCommand1.append(hFinishedFiles.getDatasetName());
         strCommand1.append(" ");
         int nPos1 = hFinishedFiles.getDatasetName().find("DM3");
         if (nPos1 > 0)
            strFilename = "DM3";
         else if (nPos1 = hFinishedFiles.getDatasetName().find("DM5") > 0)
            strFilename = "DM5";
         strTemp1 = "SFTP_DEST_";
         strTemp1.append(m_strEntityFolder + "R");
         strTemp1.append(strFilename);
         Resource::instance()->getText(strTemp1, strTemp);
         strCommand1.append(strTemp);
         strCommand1.append(".D");
         strCommand1.append(Clock::instance()->getYYYYMMDDHHMMSSHN().substr(2, 6));
         strCommand1.append(".T");
         strCommand1.append(Clock::instance()->getYYYYMMDDHHMMSSHN().substr(8, 6));
         strCommand1.append(".A");
         snprintf(szTemp,sizeof(szTemp), "%03d", ++i);
         strCommand1.append(szTemp);
         strCommand1.append(" ");
         Resource::instance()->getText("SFTP_USER", strTemp);
         strCommand1.append(strTemp);
         strCommand1.append(" ");
         Resource::instance()->getText("SFTP_SSH_KEY", strTemp);
         strCommand1.append(strTemp);
         strCommand1.append(" ");
         Resource::instance()->getText("SFTP_CV_LABEL", strTemp);
         strCommand1.append(strTemp);
         Resource::instance()->getText("SFTP_PASS_PHRASE", strTemp);
         if (strTemp.length() > 0)
         {
            strCommand1.append(" ");
            strCommand1.append(strTemp);
         }
         Trace::put(strCommand1.c_str());
         system(strCommand1.c_str());
         hFinishedFiles.close();
      }
   }
   if (m_strEntityFolder == "MSTR")
      hFinishedFiles.setMember(m_strMainFile.c_str());
   else
      hFinishedFiles.setMember(m_strHeaderFile.c_str());
   if (!hFinishedFiles.open())
      return false;
   strCommand1 = strCommand;
   strCommand1.append(hFinishedFiles.getDatasetName());
   strCommand1.append(" ");
   strTemp1 = "SFTP_DEST_";
   int nPos1 = hFinishedFiles.getDatasetName().find("DM3");
   if (nPos1 > 0)
   {
      strFilename = "DM3";
      strTemp1.append(m_strEntityFolder + "B");
   }
   else if (hFinishedFiles.getDatasetName().find("DM5") != string::npos)
   {
      strFilename = "DM5";
      strTemp1.append(m_strEntityFolder + "B");
   }
   else if (hFinishedFiles.getDatasetName().find("MSTRIN") != string::npos)
      strFilename = m_strHeaderFile;
   strTemp1.append(strFilename);
   Resource::instance()->getText(strTemp1, strTemp);
   strCommand1.append(strTemp);
   if (m_strEntityFolder == "MSTR")
   {
      strCommand1.append("/");
      strCommand1.append(m_strHeaderFile);
   }
   strCommand1.append(".D");
   strCommand1.append(Clock::instance()->getYYYYMMDDHHMMSSHN().substr(2, 6));
   strCommand1.append(".T");
   strCommand1.append(Clock::instance()->getYYYYMMDDHHMMSSHN().substr(8, 6));
   strCommand1.append(".A001");
   strCommand1.append(" ");
   Resource::instance()->getText("SFTP_USER", strTemp);
   strCommand1.append(strTemp);
   strCommand1.append(" ");
   Resource::instance()->getText("SFTP_SSH_KEY", strTemp);
   strCommand1.append(strTemp);
   strCommand1.append(" ");
   Resource::instance()->getText("SFTP_CV_LABEL", strTemp);
   strCommand1.append(strTemp);
   Resource::instance()->getText("SFTP_PASS_PHRASE", strTemp);
   if (strTemp.length() > 0)
   {
      strCommand1.append(" ");
      strCommand1.append(strTemp);
   }
   Trace::put(strCommand1.c_str());
   system(strCommand1.c_str());
   hFinishedFiles.close();
   return true;
  //## end DownloadFile::setupDGMCFTP%55CA3787015F.body
}

bool DownloadFile::setupFTP ()
{
  //## begin DownloadFile::setupFTP%4C6959CA0010.body preserve=yes
   if (!m_hFTPScriptFile1.open(FlatFile::CX_OPEN_OUTPUT))
      return false;
   string strSSLFTP;
   string strPort;
   Extract::instance()->getSpec("SSLFTP",strSSLFTP);
   Extract::instance()->getSpec("PORT",strPort);
   if (strSSLFTP == "ON")
   {
      m_hFTPScriptFile1.write((char*)m_strFTPUsername.data(),m_strFTPUsername.length());			
      m_hFTPScriptFile1.write((char*)m_strFTPPassword.data(),m_strFTPPassword.length());
      m_hFTPScriptFile1.write((char*)strPort.data(),strPort.length());
   }
   string strFTPOutputLine("open ");
   strFTPOutputLine += m_strFTPIbmHost;
   m_hFTPScriptFile1.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
   if (strSSLFTP != "ON")
   {
      m_hFTPScriptFile1.write((char*)m_strFTPUsername.data(),m_strFTPUsername.length());			
      m_hFTPScriptFile1.write((char*)m_strFTPPassword.data(),m_strFTPPassword.length());
   }
   m_hFTPScriptFile1.write("quote SITE LRECL=512 BLKSIZE=27648 RECFM=FB",43);   
   setSpaceParam();
   FlatFile hFinishedFiles("DCOMPLET");
   hFinishedFiles.setOwner(m_strEntityFolder);
   hFinishedFiles.setFolder(m_strHeaderFile.c_str());
   hFinishedFiles.setMember(m_strHeaderFile.c_str());
   if (!hFinishedFiles.open())
      return false;
   string strTemp(m_strEntityFolder);
   strTemp.append("D5");
   if (!Extract::instance()->getSpec(strTemp.c_str(),m_strFTPIbmDsName))
      return false;
   if (Extract::instance()->getCustomCode() == "REGIONS")
   {
      if (m_strHeaderFile.find("DM5") != string::npos)
      {
         if (Extract::instance()->getSpec("FTPBDM5",m_strFTPIbmDsName)== false)
         {
            Trace::put("DM5 file set up is not available in extract");
            return false;
         }
      }
      else
      if (m_strHeaderFile.find("DM3") != string::npos)
      {
         if (Extract::instance()->getSpec("FTPBDM3",m_strFTPIbmDsName) == false)
         {
            Trace::put("DM3 file set up is not available in extract");
            return false;
         }
      }
      strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName +"(+1)'";
   }
   else
      strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName + m_strEntityFolder + "." + m_strHeaderFile +"'";
   m_hFTPScriptFile1.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
   hFinishedFiles.close();
   if (Extract::instance()->getCustomCode() == "REGIONS")
   {
      if (m_strHeaderFile.find("DM5") != string::npos)
      {
         if (Extract::instance()->getSpec("FTPRDM5",m_strFTPIbmDsName)== false)
         {
            Trace::put("DM5 file set up is not available in extract");
            return false;
         }
      }
      else
      if (m_strHeaderFile.find("DM3") != string::npos)
      {
         if (!Extract::instance()->getSpec("FTPRDM3",m_strFTPIbmDsName))
         {
            Trace::put("DM3 file set up is not available in extract");
            return false;
         }
      }
   }
   vector<string>::iterator pItr;
   for(pItr = m_hBodyFiles.begin(); pItr != m_hBodyFiles.end(); pItr++)
   {
      hFinishedFiles.setMember((*pItr).c_str());
      if (!hFinishedFiles.open())
         return false;
      if (Extract::instance()->getCustomCode() == "REGIONS")
         strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName +"(+1)'";
      else
         strFTPOutputLine = "put " + hFinishedFiles.getDatasetName() + " '" + m_strFTPIbmDsName + m_strEntityFolder + "." + *pItr + "." + m_strHeaderFile +"'";
      m_hFTPScriptFile1.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
      hFinishedFiles.close();
   }
   return true;
  //## end DownloadFile::setupFTP%4C6959CA0010.body
}

// Additional Declarations
  //## begin DownloadFile%4C2B622B026D.declarations preserve=yes
  //## end DownloadFile%4C2B622B026D.declarations

//## begin module%4C2B67DC0225.epilog preserve=yes
//## end module%4C2B67DC0225.epilog
