//
//  audio_core_audio_toolbox.h
//  audio_core_audio
//
//  Created by Thomas Borregaard Sørensen on 11/10/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


namespace multimedia
{
   
   
   namespace audio_core_audio
   {
      
      
      class  CLASS_DECL_AUDIO_CORE_AUDIO toolbox :
         virtual public ::multimedia::audio::wave_base
      {
      public:
   
         
//         aligned < AudioStreamBasicDescription >             m_pdataformat;
//         aligned_pointer < AudioQueueRef >                   m_Queue;
         AudioStreamBasicDescription                           m_dataformat;
         AudioQueueRef                                         m_Queue;
         comparable_raw_array < AudioQueueBufferRef >::type    m_Buffers;
         SInt64                                                m_CurrentPacket;
         CFRunLoopRef                                          m_runloop;
         CFStringRef                                           m_runmode;
   
         
         
         toolbox(sp(base_application) papp);
         virtual ~toolbox();
         

         virtual void * wave_allocate_buffer_data(::primitive::memory_size len);
         virtual void wave_free_buffer_data(void * pdata);
         
         
         virtual bool initialize_instance();
         virtual int32_t exit_instance();
         
         
         virtual void free_buffers();
         
         
         AudioStreamBasicDescription * wave_format();
         AudioQueueBufferRef audio_buffer(int iBuffer);
         
         
         
      } ; 
      
   
   } // namespace multimedia
   
   
} // namespace multimedia
