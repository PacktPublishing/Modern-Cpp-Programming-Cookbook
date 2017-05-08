#pragma once

#include <iostream>

namespace recipe_4_01
{

#if !defined(_UNIQUE_NAME_)
#define _UNIQUE_NAME_

   class foo
   {
   };

#endif

   void show_compiler()
   {
#if defined _MSC_VER
      std::cout << "Visual C++" << std::endl;
#elif defined __clang__
      std::cout << "Clang" << std::endl;
#elif defined __GNUG__
      std::cout << "GCC" << std::endl;
#else
      std::cout << "Unknown compiler" << std::endl;
#endif
   }

   void show_compiler_version()
   {
#if defined _MSC_VER

      std::cout <<
#if (_MSC_VER >= 1900)
         "Visual C++ 2015 or newer"
#else 
         "Visual C++ " << _MSC_FULL_VER
#endif
         << std::endl;

#elif defined __clang__

      std::cout <<
#if (__clang_major__ == 3) && (__clang_minor__ >= 9)
         "Clang 3.9 or newer"
#else
         "Clang " << __clang_version__
#endif
         << std::endl;

#elif defined __GNUG__

      std::cout <<
#if __GNUC__ >= 5 && __GNUC_MINOR__ > 0
         "GCC 5.0 or newer"
#else
         "GCC " << __VERSION__
#endif
         << std::endl;

#else
      std::cout << "Unknown compiler" << std::endl;
#endif
   }

   void show_architecture()
   {
#if defined _MSC_VER

      std::cout <<
#if defined _M_X64
         "AMD64"
#elif defined _M_IX86
         "INTEL x86"
#elif defined _M_ARM
         "ARM"
#else
         "unknown"
#endif
         << std::endl;

#elif defined __clang__ || __GNUG__

      std::cout <<
#if defined __amd64__
         "AMD64"
#elif defined __i386__
         "INTEL x86"
#elif defined __arm__
         "ARM"
#else
         "unknown"
#endif
         << std::endl;

#else
#error Unknown compiler
#endif
   }

   void show_configuration()
   {
      std::cout <<
#ifdef _DEBUG
         "debug"
#else
         "release"
#endif
         << std::endl;
   }

   void execute()
   {
      show_compiler();

      show_compiler_version();

      show_architecture();

      show_configuration();
   }
}