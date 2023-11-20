m_strRole.assign(pMainSegment->cISSACQFlag, sizeof(pMainSegment->cISSACQFlag));


reusable::string& string::assign (size_t n, char c)
{
  //## begin reusable::string::assign%5BA950AB01A2.body preserve=yes
   assert(n <= max_size());
   if (n > max_size())
      return *this;
   if (m_lCapacity < n)
   {
      delete [] m_pBuffer;
      m_lLength = n;
      m_pBuffer = new char[m_lLength + 1];
      m_lCapacity = m_lLength;
   }
   else
      m_lLength = n;
   memset(m_pBuffer,c,m_lLength);
   m_pBuffer[m_lLength] = '\0';
   return *this;
  //## end reusable::string::assign%5BA950AB01A2.body
}
