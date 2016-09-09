//
//  CoreMIDIOutput.hpp
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



/**
 * @ingroup midi
 *
 * An OS X MIDI output port that uses CoreMIDI. This output device is used to send output
 * to external devices, not for playing with the built-in software synthesizer.
 */
class CoreMidiOutput : public OutputBase
{
public:
   MIDIPortRef m_port;
   //MIDIClientRef m_client;
   
   
   CoreMidiOutput(string driver);
   virtual ~CoreMidiOutput();
   
   struct Destination
   {
      MIDIEndpointRef m_ref;
      string m_name;
   };
   static const std::vector<Destination>& getDestinations();
   
   MIDIEndpointRef selectedOutput;
   
   
   virtual void note_on(const int note, const int volume, const int channel);
   virtual void note_off(const int note, const int channel);
   virtual void prog_change(const int instrument, const int channel);
   virtual void controlchange(const int controller, const int value, const int channel);
   virtual void pitch_bend(const int value, const int channel);
};

