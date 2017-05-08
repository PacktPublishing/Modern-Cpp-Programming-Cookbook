#pragma once

#include <cstdlib>
#include <iostream>

namespace recipe_6_08
{
   void exit_handler_1()
   {
      std::cout << "exit handler 1" << std::endl;
   }

   void exit_handler_2()
   {
      std::cout << "exit handler 2" << std::endl;
   }

   void quick_exit_handler_1()
   {
      std::cout << "quick exit handler 1" << std::endl;
   }

   void quick_exit_handler_2()
   {
      std::cout << "quick exit handler 2" << std::endl;
   }

   struct static_foo
   {
      ~static_foo() { std::cout << "static foo destroyed!" << std::endl; }
      static static_foo* instance() 
      {
         static static_foo obj;
         return &obj; 
      }
   };

   void execute()
   {
      {
         std::atexit(exit_handler_1);
         static_foo::instance();
         std::atexit(exit_handler_2);
         std::atexit([]() {std::cout << "exit handler 3" << std::endl; });
         
         // std::exit(42);    // exit handlers are invoked
         // std::terminate(); // exit handlers are not invoked
      }

      {
         std::at_quick_exit(quick_exit_handler_1);
         std::at_quick_exit(quick_exit_handler_2);
         std::at_quick_exit([]() {std::cout << "quick exit handler 3" << std::endl; });

         // std::quick_exit(42); // exit handlers are invoked
         // std::terminate();    // exit handlers are not invoked
      }
   }
}