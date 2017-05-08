#pragma once

namespace recipe_1_06
{   
   /*
   enum Status { Unknown, Created, Connected };

   enum Codes 
   { 
      OK, 
      Failure, 
      // Unknown redefinition
   };
   */

   /*
   namespace Status
   {
      enum Status { Unknown, Created, Connected };
   }

   namespace Codes
   {
      enum Codes { OK, Failure, Unknown };
   }
   */

   enum class Status { Unknown, Created, Connected };

   enum class Codes { OK, Failure, Unknown };


   enum class Codes2 : unsigned int;

   void print_code(Codes2 const code) {}

   enum class Codes2 : unsigned int
   {
      OK = 0,
      Failure = 1,
      Unknown = 0xFFFF0000U
   };


   void execute()
   {
      Codes code = Codes::Unknown;

      Codes c1 = Codes::OK;					      // OK
      //int c2 = Codes::Failure;   				   // error
      int c3 = static_cast<int>(Codes::Failure);// OK
   }
}