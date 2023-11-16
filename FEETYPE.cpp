if (memcmp(pFeeSegment->sRecordType, "09", 2) == 0)
      {

         int m_iFeecount;
         //m_iFeecount = (pFeeSegment->sFeeCount[0].sFee1Type, 2);
         m_iFeecount = sizeof(pFeeSegment->sFeeCount) / sizeof(pFeeSegment->sFeeCount[0]);
         for (int i = 0; i < m_iFeecount; i++)
         {
            string strInterChangeFee;
            if (memcmp(pFeeSegment->sFeeCount[i].sFee1Type, "Interchange Fee Ty  ", 20) == 0)
            {
               formatAmount(pFeeSegment->sFeeCount[i].sFee1Value, sizeof(pFeeSegment->sFeeCount[i].sFee1Value) - 1);
               strInterChangeFee.append(pFeeSegment->sFeeCount[i].sFee1Value, 19);
               setColumn(ADL_RQST_AMT0, strInterChangeFee.c_str(), strInterChangeFee.length());
            }
         }

      }
