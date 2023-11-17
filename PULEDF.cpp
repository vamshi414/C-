struct hAdditionalDataSegment
{
   char sRecordType[2];                          //0000
   char sRecordSeqNum[10];                       //0002
   char sAction[3];                              //0012
   char sFormat8TxnType[2];                      //0015
   char cTxnSettleAmountInd;                     //0017
   char sPosEntryMode[3];                        //0018
   char cPosPINCapCode;                          //0021
   char sAddDataNational[100];                   //0022
   char sAddAmounts[120];                        //0122
   char sReplaceAddFees[88];                     //0242
   char sAuthLifeCycle[3];                       //0330
   char sNationalPosCondCode[11];                //0333
   char sNationalPosGeoCode[17];                 //0344
   char sTranDesc[100];                          //0361
   char sAddDataPrivAcq[255];                    //0461
   char sAuthAgentInstIdCode[9];                 //0716
   char sCountryCodeAuthAgent[9];                //0725
   char sAcntQual[6];                            //0734
   char sSponsorBankID[9];                       //0740
   char sAVSAuthData[255];                       //0749
   char sIssTraceData[111];                      //1004
   char sAcqTraceData[111];                      //1115
   char sDowngradeInd[2];                        //1226
   char sApprovalCode[6];                        //1228 
};
