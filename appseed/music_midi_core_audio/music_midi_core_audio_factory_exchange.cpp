#include "framework.h"


namespace music
{


   namespace midi
   {
      
      namespace port
      {


      factory_exchange::factory_exchange(::aura::application * papp) :
      ::object(papp)
      {

         System.factory().cloneable_large < sequence               >  (System.type_info < ::music::midi::sequence                  > ());
         System.factory().cloneable_large < buffer              >  (System.type_info < ::music::midi::file::buffer                 > ());
         System.factory().cloneable_large < sequence_thread              >  (System.type_info < ::music::midi::sequence_thread                 > ());
         System.factory().cloneable_large < ::music::midi::port::player::player              >  (System.type_info < ::music::midi::player::player                 > ());
         System.factory().cloneable_large < ::music::midi::port::player:: player              >  (System.type_info < ::music::midi::player::player                 > ());
         System.factory().cloneable_large < ::music::midi::port::midi              >  (System.type_info < ::music::midi::midi               > ());

      }


      factory_exchange::~factory_exchange()
      {
      }

      } // namespace port

   } // namespace midi


} // namespace music


extern "C"
void ca2_factory_exchange(::aura::application * papp)
{

   ::music::midi::port::factory_exchange factoryexchange(papp);

}









