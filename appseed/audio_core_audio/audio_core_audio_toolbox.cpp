//
//  audio_core_audio_toolbox.cpp
//  audio_core_audio
//
//  Created by Thomas Borregaard Sørensen on 11/10/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"


namespace multimedia
{
   
   
   namespace audio_core_audio
   {
      
      
      toolbox::toolbox(sp(base_application) papp) :
         element(papp),
         ::thread(papp),
         wave_base(papp)
      {

         m_Queue           = NULL;
         
      }
      
      
      toolbox::~toolbox()
      {
         
      }
      
      
      void * toolbox::wave_allocate_buffer_data(::primitive::memory_size len)
      {
         
         AudioQueueBufferRef buf = NULL;
         
         if(0 != AudioQueueAllocateBuffer(m_Queue, (UInt32) len, &buf))
            return NULL;
         
         if(buf == NULL)
            return NULL;
         
         m_Buffers.add(buf);
         
         return (void *) buf->mAudioData;
         
      }
      
      
      void toolbox::wave_free_buffer_data(void * pdata)
      {
         
         for(int i = 0; i < m_Buffers.get_count(); i++)
         {

            
            if(m_Buffers[i]->mAudioData == pdata)
            {
            
               AudioQueueFreeBuffer(m_Queue, m_Buffers[i]);
               
               m_Buffers.remove_at(i);
               
               break;
               
            }
            
            
         }
         
         
      }
      
      
      void toolbox::free_buffers()
      {
         
         for(int i = 0; i < m_Buffers.get_count(); i++)
         {
            
            
            AudioQueueFreeBuffer(m_Queue, m_Buffers[i]);
            
         }
         
         m_Buffers.remove_all();
         
         
      }
      
      
      AudioStreamBasicDescription * toolbox::wave_format()
      {
         
         return &m_DataFormat;
         
      }
      
      
      AudioQueueBufferRef toolbox::audio_buffer(int iBuffer)
      {
         
         return m_Buffers[iBuffer];
         
      }
      
      
   } // namespace multimedia
   
   
} // namespace multimedia
