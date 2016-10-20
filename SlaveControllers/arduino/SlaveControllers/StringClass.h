#include <avr/pgmspace.h>

#ifndef _SIMULATOR_h
#define _SIMULATOR_h

class StringClass
{
   public:
   typedef struct Constants
   {
      char responseOn[15];
      char responseOff[15];
      char requestOn[15];
      char requestOff[15];
   } Constants;

   static const Constants Messages[8] PROGMEM;
};
#endif
