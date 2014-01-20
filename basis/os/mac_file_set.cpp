#include "framework.h"


namespace mac
{
   
   
   file_set::file_set(base_application * papp) :
   element(papp)
   {
      
   }
   
   
   file_set::~file_set()
   {
      
   }
   
   
   void file_set::add_search(stringa & stra, bool_array & baRecursive)
   {
      
      m_straSearch.add(stra);
      
      m_baRecursive.add(baRecursive);
      
      refresh();
      
   }
   
   
   void file_set::add_filter(stringa & stra)
   {
      
      m_straFilter.add(stra);
      
      refresh();
      
   }
   
   
   ::count file_set::get_file_count()
   {
      
      return m_straFile.get_size();
      
   }
   
   
   void file_set::file_at(::index i, string & str)
   {
      
      str = m_straFile[i];
      
   }
   
   
   ::index file_set::find_first_file(const char * lpcsz, ::index iStart)
   {
      
      return m_straFile.find_first_ci(lpcsz, iStart);
      
   }
   
   
   void file_set::clear_search()
   {
      
      m_straSearch.remove_all();
      
   }
   
   
   void file_set::clear_filter()
   {
      
      m_straFilter.remove_all();
      
   }
   
   
   void file_set::clear_file()
   {
      
      m_straFile.remove_all();
      
   }
   
   
   void file_set::refresh()
   {
      
      clear_file();
      
      string strFilter;
      
      int32_t i, j;
      
      string strFile;
      
      string str;
      
      for(i = 0; i < m_straSearch.get_size(); i++)
      {
         
         bool bRecursive = true;
         
         if(i < m_baRecursive.get_size())
         {
            
            bRecursive = m_baRecursive[i];
            
         }
         
         for(j = 0; j < m_straFilter.get_size(); j++)
         {
            
            string strFilter = m_straFilter.element_at(j);
            
            strFilter.trim("\\/");
            
            if(bRecursive)
            {
               
               Application.dir().rls_pattern(m_straSearch.element_at(i), strFilter, &m_straFile);
               
            }
            else
            {
               
               Application.dir().ls_pattern(m_straSearch.element_at(i), strFilter, &m_straFile);
               
            }
            
         }
         
      }
      
   }
   
   
} // namespace mac



