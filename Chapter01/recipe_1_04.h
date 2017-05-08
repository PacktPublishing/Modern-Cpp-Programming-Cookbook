#pragma once

#include <iostream>
#include <string>

namespace recipe_1_04
{
   struct Point
   {
      double X;
      double Y;

      Point(double const x = 0.0, double const y = 0.0) : X(x), Y(y) {}
   };

   struct foo
   {
      foo() { std::cout << "default constructor" << std::endl; }
      foo(std::string const & text) { std::cout << "constructor '" << text << "'" << std::endl; }
      foo(foo const & other) { std::cout << "copy constructor" << std::endl; }
      foo(foo&& other) { std::cout << "move constructor" << std::endl; };
      foo& operator=(foo const & other) { std::cout << "assignment" << std::endl; return *this; }
      foo& operator=(foo&& other) { std::cout << "move assignment" << std::endl; return *this; }
      ~foo() { std::cout << "destructor" << std::endl; }
   };

   enum class TextVerticalAligment { Top, Middle, Bottom };
   enum class TextHorizontalAligment { Left, Center, Right };

   struct Control
   {
      const int defaultHeigh = 14;
      const int defaultWidth = 80;
      
      std::string text;
      TextVerticalAligment valign = TextVerticalAligment::Middle;
      TextHorizontalAligment halign = TextHorizontalAligment::Left;

      Control(std::string const & t) : text(t) 
      {}
      Control(std::string const & t,
         TextVerticalAligment const va,
         TextHorizontalAligment const ha) : text(t), valign(va), halign(ha) 
      {}
   };

   void execute()
   {
      {
         struct bar
         {
            foo f;

            bar(foo const & value)
            {
               f = value;
            }
         };

         foo f;
         bar b(f);
      }

      {
         struct bar
         {
            foo f;

            bar(foo const & value) : f(value)
            {
            }
         };

         foo f;
         bar b(f);
      }

      {
         enum class TextFlow { LeftToRight, RightToLeft };

         struct Control
         {
            const int DefaultHeight = 20;
            const int DefaultWidth = 100;

            TextFlow textFlow = TextFlow::LeftToRight;
            std::string text;

            Control(std::string t) : text(t)
            {}
         };
      }

      {
         struct bar
         {
            foo f{ "default value" };

            bar() : f{ "constructor initializer" }
            {
            }
         };

         bar b;
      }
   }
}