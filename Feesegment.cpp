struct hFeeSegment
{
   char sRecordType[2];
   char sRecordSeqNum[10];
   char sFeecnt[2];
   struct
   {
     char sFeeType[20];
      char sFeeValue[19];
      char sFeeCur[3];
      char sFeeAmtInd[2];
      char cFeeAmtImpactType;
   }sFee[6];
};
