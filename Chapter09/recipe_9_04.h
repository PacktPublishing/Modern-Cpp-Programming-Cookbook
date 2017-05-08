#pragma once

#include <iostream>


namespace recipe_9_04
{
   constexpr unsigned int factorial(unsigned int const n)
   {
      return n > 1 ? n * factorial(n - 1) : 1;
   }

   class point3d
   {
      double x_;
      double y_;
      double z_;
   public:
      constexpr point3d(double const x = 0,
         double const y = 0,
         double const z = 0)
         :x_{ x }, y_{ y }, z_{ z }
      {}

      constexpr double get_x() const { return x_; }
      constexpr double get_y() const { return y_; }
      constexpr double get_z() const { return z_; }
   };

   void execute()
   {
      {
         constexpr unsigned int size = factorial(6);
         char buffer[size]{ 0 };

         int n;
         std::cout << "enter factorial value: ";
         std::cin >> n;
         auto result = factorial(n);
      }

      {
         constexpr point3d p{ 0, 1, 2 };
         constexpr auto x = p.get_x();
      }

      {
         static constexpr int c = 42;
         constexpr int const * p = &c;

         static constexpr int const & r = c;
      }
   }
}