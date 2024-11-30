struct hFeeSegment
{
   char sRecordType[2];
   char sRecordSeqNum[10];
   struct
   {
      char sFee1Type[20];
      char sFee1Value[19];
      char sFee1Cur[3];
      char sFee1AmtInd[2];
      char cFee1AmtImpactType;
   }sFeeCount[2];
};

 m_iFeecount = (pFeeSegment->sFeeCount[0].sFee1Type, 2);
         for (int i = 0; i < m_iFeecount; i++)
         {
            string strInterChangeFee;

         }