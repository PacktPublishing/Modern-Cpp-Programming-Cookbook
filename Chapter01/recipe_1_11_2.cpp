#include "recipe_1_11_2.h"
#include <string>
#include <iostream>

using namespace std::string_literals;

namespace
{
   void print(std::string message)
   {
      std::cout << "[file2] " << message << std::endl;
   }
}

namespace recipe_1_11
{
   void file2_run()
   {
      print("run"s);
   }
}