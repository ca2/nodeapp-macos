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

         ZERO(m_dataformat);
         
         m_Queue           = NULL;
         m_runloop         = NULL;
         m_CurrentPacket   = 0;
         
         
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
         
         return &m_dataformat;
         
      }
      
      
      AudioQueueBufferRef toolbox::audio_buffer(int iBuffer)
      {
         
         return m_Buffers[iBuffer];
         
      }
      
       bool toolbox::initialize_instance()
      {
         
         m_runloop = CFRunLoopGetCurrent();
         
         if(m_runloop != NULL)
         {

            CFRetain(m_runloop);
            
         }

         m_runmode = kCFRunLoopDefaultMode;

         if(m_runmode != NULL)
         {
            
            CFRetain(m_runmode);
            
         }
         
         return true;
      }
      
      
      int32_t toolbox::exit_instance()
      {

         if(m_runmode != NULL)
         {
            CFRelease(m_runmode);
            m_runmode = NULL;
         }
         
         if(m_runloop != NULL)
         {
            CFRelease(m_runloop);
            m_runloop = NULL;
         }
         
         return 0;
         
      }

      
      
   } // namespace multimedia
   
   
} // namespace multimedia
