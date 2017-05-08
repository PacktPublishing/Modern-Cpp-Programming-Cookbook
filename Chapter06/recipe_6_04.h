#pragma once

#include <any>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace recipe_6_04
{
   using namespace std::string_literals;

   void log(std::any const & value)
   {
      if (value.has_value())
      {
         auto const & tv = value.type();
         if (tv == typeid(int))
         {
            std::cout << std::any_cast<int>(value) << std::endl;
         }
         else if (tv == typeid(std::string))
         {
            std::cout << std::any_cast<std::string>(value) << std::endl;
         }
         else if (tv == typeid(std::chrono::time_point<std::chrono::system_clock>))
         {
            auto t = std::any_cast<std::chrono::time_point<std::chrono::system_clock>>(value);
            auto now = std::chrono::system_clock::to_time_t(t);
            std::cout << std::put_time(std::localtime(&now), "%F %T") << std::endl;
         }
         else
         {
            std::cout << "unexpected value type" << std::endl;
         }
      }
      else
      {
         std::cout << "(empty)" << std::endl;
      }
   }

   inline bool is_integer(std::any const & a)
   {
      return a.type() == typeid(int);
   }

   void execute()
   {
      {
         std::any value(42);  // integer     12
         value = 42.0;        // double      12.0
         value = "42"s;       // std::string "12"
      }

      {
         auto ltest = [](std::any const & a) {
            if (a.has_value())
               std::cout << "has value" << std::endl;
            else
               std::cout << "no value" << std::endl;
         };

         std::any value;
         ltest(value);   // no value
         value = 42;
         ltest(value);   // has value
         value.reset();
         ltest(value);   // no value
      }

      {
         std::any value = 42.0;

         try
         {
            auto d = std::any_cast<double>(value);
            std::cout << d << std::endl;
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << std::endl;
         }

         try
         {
            auto pd = std::any_cast<double>(&value);
            std::cout << *pd << std::endl;
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << std::endl;
         }

         try
         {
            auto i = std::any_cast<int>(value);
            std::cout << i << std::endl;
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << std::endl;
         }


         value = "sample"s;
         try
         {
            auto s = std::any_cast<std::string>(value);
            std::cout << s << std::endl;
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << std::endl;
         }

         value = std::vector<int>{ 1, 1, 2, 3, 5, 8 };
         try
         {
            auto v = std::any_cast<std::vector<int>>(value);
            for (auto e : v)
               std::cout << e << std::endl;
         }
         catch (std::bad_any_cast const & e)
         {
            std::cout << e.what() << std::endl;
         }
      }

      {
         log(std::any{});// (empty)
         log(12);        // 12
         log("12"s);     // 12
         log(12.0);      // unexpected value type
         log(std::chrono::system_clock::now());  // 2016-10-30 22:42:57
      }

      {
         std::vector<std::any> values;
         values.push_back(std::any{});
         values.push_back(12);
         values.push_back("12"s);
         values.push_back(12.0);
         values.push_back(std::chrono::system_clock::now());

         for (auto const v : values)
            log(v);
      }

      {
         struct foo
         {
            foo() = default;
            foo(foo const&) = delete;
         };

         foo f;
         // std::any value = f; // error
      }
   }
}