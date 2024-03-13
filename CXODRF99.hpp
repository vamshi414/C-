#ifndef CXODRF99_HPP
#define CXODRF99_HPP

struct hFileHeader
{ 
   char sRecordType[2];            //0000
   char sRecordSeqNum[10];         //0002
   char sRecipientID[6];           //0012
   char sSettleDate[8];            //0018
   char sCreateTime[20];           //0026
   char sVersion[3];               //0046

};

struct hMainTransactionSegment
{
   char sRecordType[2];                          //0000          
   char sRecordSeqNum[10];                       //0002
   char cISSACQFlag;                             //0012
   char sAcqSettleProcBusinessID[16];            //0013
   char sIssSettleProcBusinessID[16];            //0029
   char sExtTimeStamp[20];                       //0045
   char sSysOwnerBusinessDate[8];                //0065
   char sACT_ID1[28];                            //0073
   char sACT_ID2[28];                            //0101
   char sProcCode[6];                            //0129
   char sAcqInstID[9];                           //0135
   char sAcqNetID[3];                            //0144
   char sActionCode[4];                          //0147
   char sCardAcptLocAddress[23];                 //0151
   char sCardAcptCity[13];                       //0174
   char sCardAcptState[2];                       //0187
   char sCardAcptCountryCode[3];                 //0189
   char sCardAcptName[25];                       //0192
   char sCardAcptIDCode[15];                     //0217
   char sCardAcptTermID[16];                     //0232
   char sCardSeqNum[3];                          //0248
   char sCountryCodeAcq[3];                      //0251
   char sDateExp[4];                             //0254
   char sPAN[19];                                //0258
   char sIssInstID[9];                           //0277
   char sIssNetID[3];                            //0286
   char sLocalTimeStamp[16];                     //0289
   char sMerchantCategoryCode[4];                //0305
   char sNetTermID[6];                           //0309
   char sRRN[16];                                //0315
   char cRevFlag;                                //0331
   char sSTAN[12];                               //0332
   char sSettleAmount[19];                       //0344
   char sSettleCur[3];                           //0363
   char sTranAmountInd[2];                       //0366
   char cTranAmountImpactType;                   //0368
   char sTranSourceInd[4];                       //0369
   char cStandinProcInd;                         //0373
   char Filler1[79];                             //0374
                                                 //0453
};

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



struct hAdditionalAmountSegment
{
   char  sRecordType[2];                          
   char  sRecordSeqNum[10];                       
   struct
   {
    char  sAmount1Name[20];
    char  sAmount1Value[19];
    char  sAmount1CurCode[3];
    char  sAmount1ConvRate[19];
    char  sAmount1ConvRateTimeStamp[20];
   }sAmountCnt[2];
};

struct hFeeSegment
{
   char sRecordType[2];
   char sRecordSeqNum[10];
   char sFeecnt[2];
   struct
   {
      char sType[20];
      char sValue[19];
      char sCur[3];
      char sAmtInd[2];
      char cAmtImpactType;
   }hFee[6];
};

struct hDisputeSegment
{ 
   char sRecordType[2];                         //0000
   char sRecordSeqNum[10];                      //0002
   char sTxnCode[4];                            //0010
   char sTxnCodeExt[6];                         //0014
   char cMerchantRefType;                       //0020
   char sDisputeReasonCode[4];                  //0021
   char sAcqProcID[6];                          //0025
   char sAdjAddTimestamp[12];                   //0031
   char sAdjAddUser[16];                        //0043
   char sAdjCaseNo[8];                          //0059
   char cAdjSettleInd;                          //0067
   char sAdjLocalSeqNo[8];                      //0068
   char sAdjReqType[4];                         //0076
   char sAdjSettleDate[6];                      //0080
   char sAdjStatus[2];                          //0086
   char sAdjSubCode[4];                         //0088
   char sAdjTraceNo[14];                        //0092
   char sIssProcID[6];                          //0106
   char sAdjcomment[140];                       //0112
};

struct hTokenSegment
{
   char sRecordType[2];                         //0000
   char sRecordSeqNum[10];                      //0002
   char sTokenPAN[19];                          //0012
   char sTokenAssurancelvl[2];                  //0031
   char sTokenReqID[11];                        //0033
   char sTokenPANAcntRange[19];                 //0044
   char sTokenTranIdentifier[2];                //0063
   char sTokenExpDate[4];                       //0065
   char sPANRefNum[64];                         //0069
   char sTokenLookupTranID[15];                 //0133
};

struct hCurrencyTrailer
{
   char sRecordType[2];                         //0000
   char sRecordSeqNum[10];                      //0002
   char sLocalCurCode[3];                       //0012
   char sLocalCurTxnCnt[8];                     //0015
   char sLocalCurAmt[20];                       //0023
   char cLocalCurAmtInd;                        //0043
   char sSettleCurCode[3];                      //0044
   char sSettleCurAmt[20];                      //0047
   char cSettleCurAmtInd;                       //0067
};

struct hFileTrailer
{

    char sRecordType[2];                        //0000
    char sRecordSeqNum[10];                     //0002
    char sRecipientID[6];                       //0012
    char sCreateTime[20];                       //0018
    char sTotalnumofTran[10];                   //0038
    char sTotalnumofRecords[10];                //0048
                                                //0058
};

#endif