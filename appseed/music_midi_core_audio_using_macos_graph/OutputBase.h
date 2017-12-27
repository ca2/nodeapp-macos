//
//  OutputBase.hpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//


/*
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once


/**
 * @ingroup midi.players
 *
 * The base class for OSX output classes
 */
class OutputBase
{
public:
   MIDIClientRef m_client;
   int m_last_note;
   int m_last_channel;
   bool m_playing;
   
   OutputBase();
   virtual ~OutputBase();
   
   void playNote(int pitchID, int volume, int duration, int channel, int instrument);
   void stopNote();
   
   virtual void note_on(const int note, const int volume, const int channel) = 0;
   virtual void note_off(const int note, const int channel) = 0;
   virtual void prog_change(const int instrument, const int channel) = 0;
   virtual void controlchange(const int controller, const int value, const int channel) = 0;
   virtual void pitch_bend(const int value, const int channel) = 0;
   
   void reset_all_controllers();
};

