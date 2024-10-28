//## begin module%1.10%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.10%.codegen_version

//## begin module%4C2B683A0108.cm preserve=no
// $Date:   May 13 2020 13:17:26  $ $Author:   e1009510  $
// $Revision:   1.54  $
//## end module%4C2B683A0108.cm

//## begin module%4C2B683A0108.cp preserve=no
// Copyright (c) 1997 - 2012
// FIS
//## end module%4C2B683A0108.cp

//## Module: CXOSVX02%4C2B683A0108; Package body
//## Subsystem: VX%4C2B63AB026E
//## Source file: C:\bV02.5B.R003\Windows\Build\Dn\Server\Application\Vx\CXOSVX02.cpp

//## begin module%4C2B683A0108.additionalIncludes preserve=no
//## end module%4C2B683A0108.additionalIncludes

//## begin module%4C2B683A0108.includes preserve=yes
#include "CXODIF16.hpp"
#include "CXODIF48.hpp"
#include "CXODRU34.hpp"
#include "CXODBS07.hpp"
#include "CXODES36.hpp"
#include "CXODIF80.hpp"
//## end module%4C2B683A0108.includes

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
#ifndef CXOSNS10_h
#include "CXODNS10.hpp"
#endif
#ifndef CXOSBC25_h
#include "CXODBC25.hpp"
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
#ifndef CXOSIF11_h
#include "CXODIF11.hpp"
#endif
#ifndef CXOSVX05_h
#include "CXODVX05.hpp"
#endif
#ifndef CXOSVX04_h
#include "CXODVX04.hpp"
#endif
#ifndef CXOSVX09_h
#include "CXODVX09.hpp"
#endif
#ifndef CXOSVX10_h
#include "CXODVX10.hpp"
#endif
#ifndef CXOSVX11_h
#include "CXODVX11.hpp"
#endif
#ifndef CXOSVX02_h
#include "CXODVX02.hpp"
#endif


//## begin module%4C2B683A0108.declarations preserve=no
//## end module%4C2B683A0108.declarations

//## begin module%4C2B683A0108.additionalDeclarations preserve=yes
#define BUFFER_SIZE 32767
//## end module%4C2B683A0108.additionalDeclarations


// Class UploadFile

//## begin UploadFile::Status%55C51326007B.attr preserve=no  private: static bool {U} false
bool UploadFile::m_bStatus = false;
bool UploadFile::m_bDownloadFile = false;
string UploadFile::m_hFileName;
//## end UploadFile::Status%55C51326007B.attr

UploadFile::UploadFile()
  //## begin UploadFile::UploadFile%4C2B61EA001E_const.hasinit preserve=no
      : m_pDocumentInquiry(0)
  //## end UploadFile::UploadFile%4C2B61EA001E_const.hasinit
  //## begin UploadFile::UploadFile%4C2B61EA001E_const.initialization preserve=yes
   ,m_hFTPScriptFile("UFINISHE")
  //## end UploadFile::UploadFile%4C2B61EA001E_const.initialization
{
  //## begin UploadFile::UploadFile%4C2B61EA001E_const.body preserve=yes
   memcpy(m_sID,"VX02",4);
   m_iConsecutiveErrorCount=0;
   m_strPreviousError ="";
  //## end UploadFile::UploadFile%4C2B61EA001E_const.body
}


UploadFile::~UploadFile()
{
  //## begin UploadFile::~UploadFile%4C2B61EA001E_dest.body preserve=yes
  //## end UploadFile::~UploadFile%4C2B61EA001E_dest.body
}



//## Other Operations (implementation)
string UploadFile::buildFile (char& cStatus, const string& strFilename)
{
  //## begin UploadFile::buildFile%4C695FB0021C.body preserve=yes
  return "Succesfully processed";
  //## end UploadFile::buildFile%4C695FB0021C.body
}

void UploadFile::cleanup ()
{
  //## begin UploadFile::cleanup%4C6970AF01BE.body preserve=yes

   //get information on how many customers are set up
   string strBuffer;
   int i = 0;
   vector<string> hTokens;
   vector<string> hCustomers;
   while (IF::Extract::instance()->getRecord(i++,strBuffer))
   {
      if (strBuffer.length() > 16
         && strBuffer.substr(0,16) == "DSPEC   DFOLDER ")
      {
         // DSPEC  DFOLDER DVROL DUSPS DCARD DAFFN
         if (Buffer::parse(strBuffer," ",hTokens) >= 2)
         {
            for (int j = 2; j < hTokens.size(); ++j)
            {
               hTokens[j].erase(0,1);
               hCustomers.push_back(hTokens[j]);
            }
         }
      }
   }
   if (!(Extract::instance()->getRecord("DFILES  UFINISHE",strBuffer)
      && strBuffer.length()>24
      && strBuffer.find("%member")!=string::npos))
      return;
   strBuffer.erase(0,16);
   //get rid of %member in the string value
   int nPos = strBuffer.find("%member");
   if (nPos != string::npos)
      strBuffer.erase(nPos-1,8);
   //get rid of the %date also. It is added later.
   nPos = strBuffer.find("%date");
   if (nPos != string::npos)
      strBuffer.erase(nPos-1,6);
   for (int j = 0; j < hCustomers.size(); j++)
   {
      string strFolder(strBuffer);
      //replace %o with *
      nPos = strFolder.find("%o");
      if (nPos != string::npos)
      strFolder.replace(nPos,2,hCustomers[j]);
      Date hDate = Date::today()-m_iDaysUntilDelete;
      for (int i = 0; i < 60; i++)
      {
         hDate -=1;
         FlatFile::purgeFolder(strFolder.c_str(),hDate.asString("%Y-%m-%d"));
      }
   }
  //## end UploadFile::cleanup%4C6970AF01BE.body
}

bool UploadFile::email ()
{
  //## begin UploadFile::email%4C72ECFD0161.body preserve=yes
   string strDate(Date::today().asString("%Y%m%d"));
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
      "CSUBJECT:DataNavigator VROL Interface:Upload",
      "C",
      "CRun Time: ~Z.DATE_RECON. ~Z.SCHED_TIME.",
      "C",
      "SVRUA upload file has been successfully processed",
      "SFile: ~A.FILE",
      "FProcessing of the VRUA upload file was unsuccessful",
      "FFile: ~A.FILE",
      "F~A.REJECT_CODES",
       0
   };
   m_pEmail->setTemplate(&pszEmail[0]);
   m_pEmail->report('C');
   return true;
  //## end UploadFile::email%4C72ECFD0161.body
}

bool UploadFile::execute ()
{
  //## begin UploadFile::execute%556F58E9033D.body preserve=yes
   return true;
  //## end UploadFile::execute%556F58E9033D.body
}

bool UploadFile::executeDGMCFTPScript (string& strFTPDatasetName, string& strOwner, const string& strFilename)
{
  //## begin UploadFile::executeDGMCFTPScript%55CA38580148.body preserve=yes
   string strSource;
   if (strOwner == "BAMS"
   || strOwner == "MSTR")
      strSource=m_strBatchOrigName+".zip";
   else
      strSource="processed_"+m_strBatchOrigName+".zip";
   string strCommand;
   string strTemp;
   string strTemppath;
   Resource::instance()->getText("SFTP_SEND",strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_HOST",strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_PORT",strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   string strftpFilepath;
   if (m_hFTPScriptFile.open())
   {
      strTemppath = m_hFTPScriptFile.getName();
      if ((strTemppath[0] != '.')
         && (strTemppath[2] != '\\')
         && (memcmp(strTemppath.data(),"\\\\",2) != 0))
      {
         strftpFilepath.append(Extract::instance()->getNode001());
         strftpFilepath += "\\";
      }
   }
   int nPos1 = strTemppath.find_last_of("\\");
   strftpFilepath.append(strTemppath.substr(0,nPos1+1));
   strftpFilepath.append(strSource);
   m_hFTPScriptFile.close();
   strCommand.append(strftpFilepath);
   strCommand.append(" ");
   string strTemp1 = "SFTP_ZIP_" + strOwner;
   if (strOwner == "MSTR")
      strTemp1 = "SFTP_ZIP_";
   nPos1 = strFilename.find_last_of("*");
   strTemp1.append(strFilename.substr(0,nPos1));
   Resource::instance()->getText(strTemp1,strTemp);
   strCommand.append(strTemp);
   strCommand.append(".D");
   strCommand.append(Clock::instance()->getYYYYMMDDHHMMSSHN().substr(2,6));
   strCommand.append(".T");
   strCommand.append(Clock::instance()->getYYYYMMDDHHMMSSHN().substr(8,6));
   strCommand.append(".A001");
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_USER",strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_SSH_KEY",strTemp);
   strCommand.append(strTemp);
   strCommand.append(" ");
   Resource::instance()->getText("SFTP_CV_LABEL",strTemp);
   strCommand.append(strTemp);
   Resource::instance()->getText("SFTP_PASS_PHRASE",strTemp);
   if (strTemp.length() > 0)
   {
      strCommand.append(" ");
      strCommand.append(strTemp);
   }
   Trace::put(strCommand.c_str());
   system(strCommand.c_str());
   return true;
  //## end UploadFile::executeDGMCFTPScript%55CA38580148.body
}

bool UploadFile::executeFTPScript ()
{
  //## begin UploadFile::executeFTPScript%55CA383202B6.body preserve=yes
   string strSSLFTP;
   string strTemppath;
   Extract::instance()->getSpec("SSLFTP",strSSLFTP);
   if (strSSLFTP == "ON")
   {
      if (m_hFTPScriptFile.open())
      {
         string strftpFilepath;
         strTemppath = m_hFTPScriptFile.getName();
         if ((strTemppath[0] != '.')
            && (strTemppath[2] != '\\')
            && (memcmp(strTemppath.data(),"\\\\",2) != 0))
         {
            strftpFilepath.append(Extract::instance()->getNode001());
            strftpFilepath += "\\";
         }
         strftpFilepath.append(strTemppath);
         m_hFTPScriptFile.close();
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
      if (m_hFTPScriptFile.open()
         && m_hFTPScriptFile.executeFtp()
         && m_hFTPScriptFile.close())
      {
         ImportReportAuditSegment::instance()->setFILE("processed_"+m_strBatchOrigName+".zip");
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
  //## end UploadFile::executeFTPScript%55CA383202B6.body
}

bool UploadFile::finalizeFiles (string& strOwner)
{
  //## begin UploadFile::finalizeFiles%4C5B0F18010E.body preserve=yes
   //creates and deletes a file for the purpose of creating the complete directory.
   FlatFile hFinishedFolder("UFINISHE","foldercreator");
   hFinishedFolder.setOwner(strOwner);
   if(!(hFinishedFolder.open(FlatFile::CX_OPEN_OUTPUT)
      && hFinishedFolder.close()
      && hFinishedFolder.remove()))
      return false;
   //moves all files that include the batch base name to the complete folder
   FlatFile hCleanupFile("UPENDING");
   hCleanupFile.setOwner(strOwner);
   hCleanupFile.setMember(("*"+m_strBatchOrigName+"*").c_str());
   while(hCleanupFile.open())
   {
      if(!hCleanupFile.move("UFINISHE"))
      {
         if (strOwner == "MSTR")
         {
            Trace::put("MasterZIP is not deleted from prending");
            hCleanupFile.close();
            FlatFile hTestFile("UPENDING");
            hTestFile.setMember("*.zip");
            hTestFile.remove();
            return true;
         }
         return false;
      }
      hCleanupFile.close();
      hCleanupFile.setName("UPENDING");
   }
   hCleanupFile.setName("UPENDING");
   hCleanupFile.setMember(("*"+m_strBatchBaseName+"*").c_str());
   while(hCleanupFile.open())
   {
      if(!hCleanupFile.move("UFINISHE"))
         return false;
      hCleanupFile.close();
      hCleanupFile.setName("UPENDING");
   }
   return true;

  //## end UploadFile::finalizeFiles%4C5B0F18010E.body
}

bool UploadFile::isOnlyAlphaNum (const string& strContent, const size_t& pos, const size_t& n)
{
  //## begin UploadFile::isOnlyAlphaNum%4C6EAAA50383.body preserve=yes
   int x = pos;
   while(x < pos+n)
   {
      char c = strContent[x];
      if(!(isalnum(strContent[x]) || strContent[x]=='_'))
      {
         int iRemainingChars = pos + n - x;
         if (isspace(strContent[x]) && (iRemainingChars == 1) )
            break;
         if (isspace(strContent[x]) && (iRemainingChars >= 14) && (strncmp(strContent.data()+x+1,"currency",8) == 0))
            x=x+14;
         else
            return false;
      }
      x++;
   }
   return true;
  //## end UploadFile::isOnlyAlphaNum%4C6EAAA50383.body
}

bool UploadFile::packageZip ()
{
  //## begin UploadFile::packageZip%4C69602C022C.body preserve=yes
   FlatFile hFinishedFiles("");
   hFinishedFiles.setMember(("processed_"+m_strBatchOrigName+".zip").c_str());
   hFinishedFiles.setName("UPENDING");
   hFinishedFiles.remove();
   hFinishedFiles.setMember(("R"+m_strBatchOrigName).c_str());
   if(hFinishedFiles.open())
   {
      if(!hFinishedFiles.zip("processed_"+m_strBatchOrigName))
         return false;
      if(!hFinishedFiles.close())
         return false;
      if(!hFinishedFiles.remove())
         return false;
   }
   else if(m_strBatchOrigName.find("DM3") == string::npos)
      return false;
   hFinishedFiles.setMember(("B"+m_strBatchOrigName).c_str());
   if(!hFinishedFiles.open())
      return false;
   if(!hFinishedFiles.zip("processed_"+m_strBatchOrigName))
      return false;
   if(!hFinishedFiles.close())
      return false;
   if(!hFinishedFiles.remove())
      return false;
   if(m_hTifDocs.size()!=0)
   {
      hFinishedFiles.setMember(("D"+m_strBatchOrigName).c_str());
      if(!hFinishedFiles.open())
         return false;
      if(!hFinishedFiles.zip("processed_"+m_strBatchOrigName))
         return false;
      if(!hFinishedFiles.close())
         return false;
      if(!hFinishedFiles.remove())
         return false;
   }
   return true;
  //## end UploadFile::packageZip%4C69602C022C.body
}

bool UploadFile::post (string& strXMLText)
{
  //## begin UploadFile::post%55CD00F201BE.body preserve=yes
   m_strFolderName.erase();
   string strTemp;
   Extract::instance()->getSpec("WEBSER",strTemp);
   if (strTemp != "ON")
   {
      m_bStatus = false;
      return true;
   }
   if (!m_pDocumentInquiry)
      m_pDocumentInquiry = new DocumentInquiry;
   m_pDocumentInquiry->setxmlText(strXMLText);
   m_bStatus = true;
   if (!m_pDocumentInquiry->post("DOCL",this))
   {
      m_bStatus = false;
      Trace::put("Not able to connect to the server");
      return false;
   }
   return true;
  //## end UploadFile::post%55CD00F201BE.body
}
bool UploadFile::processMSTRZIP (const string& strFilename)
{
  //## begin UploadFile::processZIP%55C9FA7E0103.body preserve=yes
 //  if (strFilename.find("MCOUT") != string::npos)
 //  {
   string strOwner("MSTR");
   string strFTPDatasetName;
   if (finalizeFiles(strOwner))
   {
      if (writeFTPScript(strFTPDatasetName, strOwner))
      {
         if (Extract::instance()->getCustomCode() == "DGMC")
         {
            if (executeDGMCFTPScript(strFTPDatasetName, strOwner, strFilename))
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
         if (executeFTPScript())
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
      else
      {
         if (strFTPDatasetName.length() > 0)
         {
            Trace::put(" Dspec entry is not set up to FTP to IBM");
            return false;
         }
         else
         {
            Trace::put("File length downloaded to PC is less than 11 characters");
            return false;
         }
      }
   }
   else
   {
      Trace::put("MasterCard Finalize Files failed");
      return false;
   }
   return true;

  //## end UploadFile::processZIP%55C9FA7E0103.body
}

bool UploadFile::processZIP (const string& strFilename)
{
  //## begin UploadFile::processZIP%55C9FA7E0103.body preserve=yes
   if(!packageZip())
      return false;
   Trace::put("VX02::Packaged xml and document zip into UA zip");
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
            if(executeDGMCFTPScript(strFTPDatasetName, strOwner, strFilename))
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
   {
       Trace::put("Unsuccessful in moving files from Pending to Complete");
       return false;
   }

  //## end UploadFile::processZIP%55C9FA7E0103.body
}

bool UploadFile::readExtract ()
{
  //## begin UploadFile::readExtract%4C697EE80355.body preserve=yes
   string strMinimumTifError, strDaysUntilDelete, strErrorsBetweenEmails;
   string strTemp;
   if(!(Extract::instance()->getSpec("FTPIBMH",m_strFTPIbmHost)
      && Extract::instance()->getSpec("FTPUSRID",m_strFTPUsername)
      && Extract::instance()->getSpec("FTPPSWRD",m_strFTPPassword)
      && Extract::instance()->getSpec("EMAILADR",m_strContactEmailAddress)
      && Extract::instance()->getSpec("ERMAILNM",strErrorsBetweenEmails)
      && Extract::instance()->getSpec("MINTIFER",strMinimumTifError)
      && Extract::instance()->getSpec("UDELDAY",strDaysUntilDelete)
      && Extract::instance()->getSpec("UNZIPCOM",strTemp)
      && Extract::instance()->getSpec("ZIPCOM",strTemp)
      && Extract::instance()->find("DFILES  UPENDING",strTemp)
      && Extract::instance()->find("DFILES  UCOMPLET",strTemp)
      && Extract::instance()->find("DFILES  UFINISHE",strTemp))
      && Extract::instance()->find("DFILES  DCOMPLET",strTemp)
      && Extract::instance()->find("DFILES  DDOC    ",strTemp))
      return false;
   AdvancedEncryptionStandard::decrypt(m_strFTPUsername);
   AdvancedEncryptionStandard::decrypt(m_strFTPPassword);
   //If cannot convert DSPEC values from strings to integers
   if((m_iMinimumTifError = atoi(strMinimumTifError.c_str()))==0
      || (m_iDaysUntilDelete = atoi(strDaysUntilDelete.c_str()))==0
      || (m_iErrorsBetweenEmails = atoi(strErrorsBetweenEmails.c_str()))==0)
      return false;
   return true;
  //## end UploadFile::readExtract%4C697EE80355.body
}

bool UploadFile::rebuildBatchXML (IF::FlatFile& hInFile, const string& strOutputXMLFile)
{
  //## begin UploadFile::rebuildBatchXML%531DFB540349.body preserve=yes
   FlatFile hOutFile("UPENDING");
   hOutFile.setMember(strOutputXMLFile.c_str());
   if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
      return false;
   string strLine;
   string strRollOverTag;
   //Creates buffer for reading chunks of file
   char szTempLine[BUFFER_SIZE +1];
   size_t iReadSize = BUFFER_SIZE;
   bool bNoValidPrevLine = true, bEproutingidfetched = false;
   string strStartTag,strEndTag,strPrevLine,strEproutingid;
   int nPos,nPos1,nPos2,nPos3;
   while (hInFile.read(szTempLine,BUFFER_SIZE+1,&iReadSize)==true )
   {
      strStartTag.erase();
      strEndTag.erase();
      nPos = strLine.find_first_of("<");
      nPos1 = strLine.find_first_of(">");
      if(nPos != string::npos && nPos1 != string::npos)
         strStartTag = strLine.substr((nPos + 1),(nPos1-(nPos+1)));
      strLine = strRollOverTag + szTempLine;
      nPos2 = strLine.find("</");
      nPos3 = strLine.find_last_of(">");
      if(nPos2 != string::npos && nPos3 != string::npos)
         strEndTag = strLine.substr((nPos2 + 2),(nPos3 - (nPos2 + 2)));
      strRollOverTag.clear();
      //removes trailing whitespace
      strLine.erase(strLine.find_last_not_of(' ')+1,string::npos);
      int i,j;
      //removes leading 0's from ECMOTO tag
      if((i = strLine.find("<ECMOTO>"))!=string::npos
         && (j=strLine.find_first_not_of('0',i+8))!=string::npos)
         strLine.erase(i+8,j-i-8);
      //logs copy commands in vector<string> and excludes from xml revision
      if (!bEproutingidfetched && strLine.compare(0, 15, "<ep-routing-id>") == 0) 
      {
         m_strBatchOrigName.append(strLine);
         bEproutingidfetched = true;
      }
      if(strLine.compare(0,5,"copy ")== 0)
         m_hTifDocs.push_back(strLine.substr(strLine.find_first_not_of(' ',5)));
      else if(strLine.size()!=0
         && strLine.find_first_not_of(' ')!= string::npos)//if all characters in the line are not whitespaces
      {
         if(strLine.find_last_not_of(' ')==strLine.find_last_of('>')) //if last character in line is a >
         {
            removePatterns(strLine);
            if(bNoValidPrevLine)
            {
               strPrevLine = strLine;
               bNoValidPrevLine = false;
               continue;
            }
            if(strStartTag.length() && strStartTag == strEndTag && strRollOverTag.length() == 0)
            {
               strPrevLine += strLine;
               removePatterns(strPrevLine);
               bNoValidPrevLine = true;
            }
            if(strLine.find("<EFUNDS_") == string::npos
               && strLine.find("</EFUNDS_") == string::npos
               && strLine.size()!=0
               && strLine.find_first_not_of(' ')!= string::npos)
            {
               hOutFile.write((char*)strPrevLine.data(),strPrevLine.length());
               strPrevLine = strLine;
            }
            strRollOverTag="";
         }
         else
            strRollOverTag += strLine;
      }
   }
   hOutFile.write((char*)strPrevLine.data(),strPrevLine.length());
   hOutFile.close();
   return true;

  //## end UploadFile::rebuildBatchXML%531DFB540349.body
}

bool UploadFile::rebuildBatchText(IF::FlatFile& hInFile, const string& strOutputXMLFile)
{
   FlatFile hOutFile("UPENDING");
   hOutFile.setMember(strOutputXMLFile.c_str());
   if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
      return false;

   char szTempLine[BUFFER_SIZE + 1];
   size_t iReadSize = BUFFER_SIZE;
   string strLine;
   string strRollOverLine;

   bool  hdrWrite = false;
   const int extracStartPos = 600;
   const int extractLength = 36;

   while (hInFile.read(szTempLine, BUFFER_SIZE, &iReadSize))
   {
      szTempLine[iReadSize] = '\0';
      strLine = strRollOverLine + szTempLine;
      size_t pos;

      while ((pos = strLine.find('\n')) != string::npos)
      {
         string currentLine = strLine.substr(0, pos);
         strLine.erase(0, pos + 1);

         if (currentLine.compare(0, 3, "HDR") == 0)
         {
            if (!hdrWrite)
            {
               hOutFile.write((char*)currentLine.c_str(), currentLine.length());
               hOutFile.write("\n", 1);
               hdrWrite = true;
            }
         }
         else if (currentLine.compare(0, 3, "DTL") == 0 && currentLine.size() >= 636)
         {
            string extractField = currentLine.substr(extracStartPos, extractLength);

            extractField.erase(0, extractField.find_first_not_of(' '));
            extractField.erase(extractField.find_last_not_of(' ') + 1);

            if (!extractField.empty())
            {
               m_hTifDocs.push_back(extractField);
               hOutFile.write((char*)currentLine.c_str(), currentLine.length());
               hOutFile.write("\n", 1);
            }
         }
         else if (currentLine.compare(0, 3, "TRL") == 0)
         {
            hOutFile.write((char*)currentLine.c_str(), currentLine.length());
            hOutFile.write("\n", 1);
         }
      }
      strRollOverLine = strLine;
   }
   hOutFile.close();
   return true;
}

bool UploadFile::removePatterns (string& strLine)
{
  //## begin UploadFile::removePatterns%4C5880C903CE.body preserve=yes
   size_t pos;
   if ((pos=strLine.find('&'))!=string::npos)
   {
      char *q = 0;
      int m = strLine.length();
      char *psInputSource = new char[m + 1];
      memcpy(psInputSource,strLine.c_str(),strLine.length());
      char *p = psInputSource;
      *(p+m) = '\0';
      while (q = strchr(p,'&'))
      {
         if (memcmp(q,"&amp;",5) == 0)
            p = q + 5;
         else if (memcmp(q,"&gt;",4) == 0
                  || memcmp(q,"&gt;",4) == 0)
            p = q + 4;
         else if (memcmp(q,"&apos;",6) == 0
                  || memcmp(q,"&quot;",6) == 0)
            p = q + 6;
         else
            *q = ' ';
      }
      strLine = psInputSource;
      delete [] psInputSource;
   }
   string strTemp;
   int i,j,k,l;
   for(j=strLine.rfind("/>");j!=string::npos;j=strLine.rfind("/>",j-1))
   {
      i = strLine.find_last_of('<',j);
      if(i!=string::npos
         && isOnlyAlphaNum(strLine,i+1,j-i-1) )
         strLine.erase(i,j-i+2);
   }
   for(l=strLine.find_last_of('>');l!=string::npos;l=strLine.find_last_of('>',l-1))
   {
      k = strLine.find_last_of('<',l);
      j = strLine.find_last_of('>',k);
      i = strLine.find_last_of('<',j);
      if(i!=string::npos
         && j!=string::npos
         && k!=string::npos
         && strLine[k+1]=='/'
         && strLine[i+1]!='/')
      {
         strTemp = strLine.substr(j+1,k-j-1);
         if (strLine.find("MerchantCity") != string::npos
            || strLine.find("MerchantName") != string::npos)
         {
            for (int a=0;a < strTemp.length(); a++)
            {
               if (!(isalnum(strLine[j+1+a])))
               {
                  if (strLine[j+1+a] == '&')
                  {
                     if (memcmp(&strLine[j+1+a],"&amp;",5) == 0)
                        a += 5;
                     else if (memcmp(&strLine[j+1+a],"&gt;",4) == 0
                              || memcmp(&strLine[j+1+a],"&gt;",4) == 0)
                        a += 4;
                     else if (memcmp(&strLine[j+1+a],"&apos;",6) == 0
                              || memcmp(&strLine[j+1+a],"&quot;",6) == 0)
                        a += 6;
                     else
                        strLine[j+1+a] = ' ';
                  }
                  else if (strLine[j+1+a] != ' ')
                     strLine[j+1+a] = ' ';
               }
            }
         }
         else if(strTemp.find_first_not_of(' ')==string::npos
               && isOnlyAlphaNum(strLine,i+1,j-i-1))
            strLine.erase(i,l-i+1);
      }
   }
   return true;
  //## end UploadFile::removePatterns%4C5880C903CE.body
}

int UploadFile::reply ()
{
  //## begin UploadFile::reply%55A7FC7A03E2.body preserve=yes
   if (m_bStatus == false)
      return 0;
   if (m_lInfoIDNumber != 0)
   {
      Trace::put(m_pDocumentInquiry->getText().c_str());
      return 1;
   }
   if (memcmp(m_sID,m_hFileName.data(),4) == 0)
   {
      m_bStatus = false;
      if (m_hFileName == "VX10" || m_hFileName == "VX14")
         processZIP(m_strFilename);
      else if (m_hFileName == "VX09")
         processMSTRZIP(m_strFilename);
   }
   return 0;
  //## end UploadFile::reply%55A7FC7A03E2.body
}

void UploadFile::resetVars ()
{
  //## begin UploadFile::resetVars%4C69605C0132.body preserve=yes
   m_strBatchBaseName.erase();
   m_strDocFile.erase();
   m_strFilename.erase();
   m_hTifDocs.clear();
   m_hTifCommands.clear();
   m_bStatus = false;
   ImportReportAuditSegment::instance()->setREJECT_CODES("");
   ImportReportAuditSegment::instance()->setFILE("");
  //## end UploadFile::resetVars%4C69605C0132.body
}

void UploadFile::restoreFiles ()
{
  //## begin UploadFile::restoreFiles%4C5B0EDD03B4.body preserve=yes
   Trace::put("VX02::Restoring original VR files");
   FlatFile hRestoreFile("");
   hRestoreFile.setMember("DUA*");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("TUA*");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("DDM*");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("TDM*");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("*.ftp");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("*.zip");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setMember("*.xml");
   hRestoreFile.setName("UPENDING");
   hRestoreFile.remove();
   hRestoreFile.setName("UPENDING");
   hRestoreFile.setMember("original_*");
   while(hRestoreFile.open())
   {
      string strOriginalName;
      hRestoreFile.getBaseName(strOriginalName,true);
      //removes the "original_" prefix from the file
      strOriginalName.erase(0,9);
      hRestoreFile.move("UPENDING",strOriginalName.c_str());
      hRestoreFile.close();
      hRestoreFile.setName("UPENDING");
   }
  //## end UploadFile::restoreFiles%4C5B0EDD03B4.body
}

void UploadFile::sendStatus (char& cStatus, const string& strReason)
{
  //## begin UploadFile::sendStatus%5166D73101A7.body preserve=yes
   ImportReportAuditSegment::instance()->setREJECT_CODES(strReason);
   if(cStatus == 'F')
   {
      //If this is a different error from the last
      //then reset the error count so a new Email alert will be sent
      if(strReason != m_strPreviousError)
         m_iConsecutiveErrorCount=0;
      m_iConsecutiveErrorCount ++;
      m_strPreviousError = strReason;
   }
   if(cStatus == 'S'
      || m_iConsecutiveErrorCount >= m_iErrorsBetweenEmails)
      m_iConsecutiveErrorCount = 0;
   if(cStatus == 'S'
      || m_iConsecutiveErrorCount == 1)
   {
      email();
      m_pEmail->report(cStatus);
      m_pEmail->getFlatFile().close();
      m_pEmail->complete();
      delete m_pEmail;
      m_pEmail = 0;
   }
  //## end UploadFile::sendStatus%5166D73101A7.body
}

void UploadFile::setSpaceParam ()
{
  //## begin UploadFile::setSpaceParam%5D49D6B403A9.body preserve=yes
   string strValue;
   string strKey(m_strOwner);
   string strTemp("MGMTCLAS");
   if (Extract::instance()->getSpec(strTemp.c_str(), strValue))
   {
      strValue.insert(0, "quote SITE MGMTCLAS=");
      m_hFTPScriptFile.write((char*)strValue.data(), strValue.length());
   }
   strTemp = "UNIT";
   if (Extract::instance()->getSpec(strTemp.c_str(), strValue))
   {
      strValue.insert(0, "quote SITE UNIT=");
      m_hFTPScriptFile.write((char*)strValue.data(), strValue.length());
   }
   strTemp = "AlloType";
   if (Extract::instance()->getSpec(strTemp.c_str(), strValue))
   {
      strValue.insert(0, "quote SITE ");
      m_hFTPScriptFile.write((char*)strValue.data(), strValue.length());
   }
   strKey.append("PR");
   if (Extract::instance()->getSpec(strKey.c_str(), strValue))
   {
      strValue.insert(0, "quote SITE PRI=");
      m_hFTPScriptFile.write((char*)strValue.data(), strValue.length());
   }
   strKey.replace(4, 2, "SE");
   if (Extract::instance()->getSpec(strKey.c_str(), strValue))
   {
      strValue.insert(0, "quote SITE SEC=");
      m_hFTPScriptFile.write((char*)strValue.data(), strValue.length());
   }
  //## end UploadFile::setSpaceParam%5D49D6B403A9.body
}

bool UploadFile::writeFTPScript (string& strFTPDatasetName, string& strOwner)
{
  //## begin UploadFile::writeFTPScript%4C69607101AF.body preserve=yes
   string strDataSetName;
   Trace::put("VX02: writeFTPSCript");
   FlatFile hFinalDoc("UFINISHE");
   if (strOwner == "BAMS"
   || strOwner == "MSTR")
      hFinalDoc.setMember((m_strBatchOrigName+".zip").c_str());
   else if (m_strBatchOrigName.find("ImageIn_") != string::npos)
   {
      hFinalDoc.setMember((m_strBatchOrigName + ".zip").c_str());
      strDataSetName = m_strFilename.substr(0,3) + "EXPI";
   }
   else
      hFinalDoc.setMember(("processed_"+m_strBatchOrigName+".zip").c_str());
   hFinalDoc.setOwner(strOwner);

   m_hFTPScriptFile.setName("UFINISHE");
   m_hFTPScriptFile.setOwner(strOwner);
   m_hFTPScriptFile.setMember((m_strBatchOrigName+".ftp").c_str());
   string strTestFileName = m_strBatchOrigName+".ftp";
   if (m_hFTPScriptFile.open(FlatFile::CX_OPEN_OUTPUT)
      && hFinalDoc.open(FlatFile::CX_OPEN_INPUT))
   {
      if (strOwner.length() > 0)
      {
         string strTemp = strOwner;
         strTemp.append("U5");
         if (!Extract::instance()->getSpec(strTemp.c_str(),m_strFTPIbmUADsName))
         {
            for (int i = 0; i < strTemp.length(); i++)
               strTemp[i] = toupper(strTemp[i]);
            if (!Extract::instance()->getSpec(strTemp.c_str(),m_strFTPIbmUADsName))
            {
               strFTPDatasetName = strTemp;
               Trace::put("VX02: Could not write the ftp file. Exiting with a false.");
               return false;
            }
         }
      }
      else
         return false;
      if (strOwner == "BAMS"
         || strOwner == "MSTR")
      {
         m_strFTPIbmUADsName.append("D");
         m_strFTPIbmUADsName.append(Clock::instance()->getYYYYMMDDHHMMSS().substr(2,6));
      }
      else if (strDataSetName.substr(3,4).find("EXPI") != string::npos)
         m_strFTPIbmUADsName.append(strDataSetName);
      else if (Extract::instance()->getCustomCode() != "REGIONS")
         m_strFTPIbmUADsName.append(m_strBatchOrigName);
      strFTPDatasetName = m_hFTPScriptFile.getDatasetName();
      string strTemp;
      string strTemp1;
      Extract::instance()->getSpec("SSLFTP",strTemp);
      Extract::instance()->getSpec("PORT",strTemp1);
      if (strTemp == "ON")
      {
         m_hFTPScriptFile.write((char*)m_strFTPUsername.data(),m_strFTPUsername.length());
         m_hFTPScriptFile.write((char*)m_strFTPPassword.data(),m_strFTPPassword.length());
         m_hFTPScriptFile.write((char*)strTemp1.data(),strTemp1.length());
      }
      string strFTPOutputLine("open ");
      strFTPOutputLine += m_strFTPIbmHost;
      m_hFTPScriptFile.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
      if (strTemp != "ON")
      {
         m_hFTPScriptFile.write((char*)m_strFTPUsername.data(),m_strFTPUsername.length());
         m_hFTPScriptFile.write((char*)m_strFTPPassword.data(),m_strFTPPassword.length());
      }
      m_hFTPScriptFile.write("binary",6);
      m_strOwner = strOwner;
      setSpaceParam();
      if (strOwner == "MSTR")
         m_hFTPScriptFile.write("quote SITE LRECL=0 BLKSIZE=1014 RECFM=U",39);
      else
         m_hFTPScriptFile.write("quote SITE LRECL=80 BLKSIZE=27920 RECFM=FB",42);
      if (Extract::instance()->getCustomCode() == "REGIONS")
         strFTPOutputLine = "put " + hFinalDoc.getDatasetName() + " '" + m_strFTPIbmUADsName+ "(+1)'";
      else
         strFTPOutputLine = "put " + hFinalDoc.getDatasetName() + " '" + m_strFTPIbmUADsName+ "'";
      m_hFTPScriptFile.write((char*)strFTPOutputLine.data(),strFTPOutputLine.length());
      m_hFTPScriptFile.write("bye",3);
      m_hFTPScriptFile.close();
      hFinalDoc.close();
      return true;
   }
   return false;
  //## end UploadFile::writeFTPScript%4C69607101AF.body
}

bool UploadFile::zipImages ()
{
  //## begin UploadFile::zipImages%4C5881080325.body preserve=yes
   string strFileLocation;
   string strFileDestinationName;
   string strTemp;
   FlatFile hImageFile("");
   FlatFile hLocalImageFiles("");
   Extract::instance()->getSpec("WEBSER",strTemp);
   if (strTemp == "ON")
   {
      string strLine;
      string strSearch1;
      string strSearch2;
      string strTemp("DECRYPT");
      strTemp.append(Clock::instance()->getYYYYMMDDHHMMSS());
      strTemp.append(".txt");
      FlatFile hOutFile("UCOMPLET");
      hOutFile.setMember(strTemp.c_str());
      hOutFile.setOwner("DECRYPT");
      if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
         return false;
      string strFile = hOutFile.getDatasetName();
      string strXMLText("<DocDecryptOsi>");
      strXMLText += "<Folder>";
      string strLETTER_STORAGE_LOCATION;
      if (Extract::instance()->getSpec("WEBDOC",strLETTER_STORAGE_LOCATION))
      {
         strSearch1.assign(m_strFolderName);
         transform (strSearch1.begin(),strSearch1.end(), strSearch1.begin(), ::toupper);
         strSearch2 = strLETTER_STORAGE_LOCATION;
         transform (strSearch2.begin(),strSearch2.end(), strSearch2.begin(), ::toupper);
         size_t pos = strSearch1.find(strSearch2);
         if (pos != string::npos)
         {
            m_strFolderName.erase(pos,strLETTER_STORAGE_LOCATION.length());
            strSearch1.assign(strFile);
            transform (strSearch1.begin(),strSearch1.end(), strSearch1.begin(), ::toupper);
            pos = strSearch1.find(strSearch2);
            if (pos != string::npos)
               strFile.erase(pos,strLETTER_STORAGE_LOCATION.length());
         }
      }
      strXMLText += m_strFolderName;
      strXMLText += "</Folder>";
      strXMLText += "<ZipName>";
      strXMLText += m_strDocFile;
      strXMLText += "</ZipName>";
      vector<string>::iterator pItr;
      for(pItr = m_hTifDocs.begin(); pItr != m_hTifDocs.end(); pItr++)
      {
         string strTemp = *pItr;
         for(int x = 0; x<strTemp.length(); x++)
            strTemp[x] = tolower(strTemp[x]);
         string strExtension(".tif ");
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".tiff ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".html ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".xps ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".pdf ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".jpg ";
         int n = strExtension.length();
         strFileLocation.assign(*pItr,0,strTemp.find(strExtension)+(n-1));
         strFileDestinationName.assign(*pItr, strTemp.find(strExtension)+n,strTemp.length());
         strLine = strFileLocation;
         strLine += " ";
         strLine += strFileDestinationName;
         if (Extract::instance()->getSpec("WEBDOC",strLETTER_STORAGE_LOCATION))
         {
            strSearch1.assign(strLine);
            transform (strSearch1.begin(),strSearch1.end(), strSearch1.begin(), ::toupper);
            size_t pos = strSearch1.find(strSearch2);
            if (pos != string::npos)
               strLine.erase(pos, strLETTER_STORAGE_LOCATION.length());
         }
         hOutFile.write((char*)strLine.data(),strLine.length());
      }
      hOutFile.close();
      strXMLText += "<FileName>";
      strXMLText += strFile;
      strXMLText += "</FileName>";
      strXMLText += "</DocDecryptOsi>";
      m_bStatus = true;
      if (!post(strXMLText))
      {
         m_bStatus = false;
         Trace::put("Not able to connect to the server");
         return false;
      }
   }
   else
   {
      int iErrorCount=0;
      FlatFile hImageFile("");
      FlatFile hLocalImageFiles("");
      vector<string>::iterator pItr;
      for(pItr = m_hTifDocs.begin(); pItr != m_hTifDocs.end(); pItr++)
      {
         string strTemp = *pItr;
         for(int x = 0; x<strTemp.length(); x++)
            strTemp[x] = tolower(strTemp[x]);
         string strExtension(".tif ");
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".tiff ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".html ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".xps ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".pdf ";
         if (strTemp.find(strExtension) == string::npos)
            strExtension = ".jpg ";
         int n = strExtension.length();
         strFileLocation.assign(*pItr,0,strTemp.find(strExtension)+(n-1));
         strFileDestinationName.assign(*pItr, strTemp.find(strExtension)+n,strTemp.length());
         hImageFile.setDatasetName(strFileLocation.c_str());
         if(!hImageFile.copy("UPENDING",strFileDestinationName.c_str()))
         {
            iErrorCount++;
            if(iErrorCount == m_iMinimumTifError)
               return false;
         }
      }
      if (m_strBatchBaseName.length() > 5 && m_strBatchBaseName.substr(0,6) == "ECHIST")

         hLocalImageFiles.setMember("DOCHIST*");
      if (m_strBatchBaseName.length() > 3 && m_strBatchBaseName.substr(0, 4) == "NYCE")
         hLocalImageFiles.setMember("DOCNYCE*");
      else if (m_strBatchBaseName.length() > 2 && m_strBatchBaseName.substr(0,3) == "UA5")
         hLocalImageFiles.setMember("TUA5*");
      else
         hLocalImageFiles.setMember("TDM5*");
      hLocalImageFiles.setName("UPENDING");
      if(!(hLocalImageFiles.zip(m_strDocFile)
         && hLocalImageFiles.remove()))
      return false;
      if (m_hFileName != "VX14")
      {
         FlatFile hFlatFile("UPENDING");
         hFlatFile.setMember((m_strDocFile + "*").c_str());
         if (!(hFlatFile.open()
            && hFlatFile.move("UPENDING", m_strDocFile.c_str())))
            return false;
         hFlatFile.close();
      }
      if (m_strBatchBaseName.length() > 5 && m_strBatchBaseName.substr(0,6) == "ECHIST")
      {
         FlatFile hOutFile("UPENDING");
         hOutFile.setMember(( "C" + m_strBatchBaseName).c_str());
         if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
            return false;
         vector<string>::iterator pItr;
         for(pItr = m_hTifCommands.begin(); pItr != m_hTifCommands.end(); pItr++)
         {
            string strTemp = *pItr;
            hOutFile.write((char*)strTemp.data(),strTemp.length());
         }
         hOutFile.close();
      }
      if (m_strBatchBaseName.length() > 3 && m_strBatchBaseName.substr(0, 4) == "NYCE")
      {
         FlatFile hOutFile("UPENDING");
         hOutFile.setMember(("C" + m_strBatchBaseName).c_str());
         if (!hOutFile.open(FlatFile::CX_OPEN_OUTPUT))
            return false;
         vector<string>::iterator pItr;
         for (pItr = m_hTifCommands.begin(); pItr != m_hTifCommands.end(); pItr++)
         {
            string strTemp = *pItr;
            hOutFile.write((char*)strTemp.data(), strTemp.length());
         }
         hOutFile.close();
      }
   }
   return true;
  //## end UploadFile::zipImages%4C5881080325.body
}

// Additional Declarations
  //## begin UploadFile%4C2B61EA001E.declarations preserve=yes
  //## end UploadFile%4C2B61EA001E.declarations

//## begin module%4C2B683A0108.epilog preserve=yes
//## end module%4C2B683A0108.epilog
