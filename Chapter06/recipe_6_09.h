#pragma once

#include <type_traits>
#include <string>

namespace recipe_6_09
{
   using namespace std::string_literals;

   template <typename T,
             typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
   T multiply(T const t1, T const t2)
   {
      return t1 * t2;
   }

   template <typename T>
   struct pod_wrapper
   {
      static_assert(std::is_pod<T>::value, "Type is not a POD!");
      T value;
   };

   template <typename T>
   struct const_wrapper
   {
      typedef typename std::conditional<
         std::is_const<T>::value,
         T,
         typename std::add_const<T>::type>::type
         const_type;
   };

   template <typename T>
   auto process(T arg)
   {
#ifdef CONSTEXPR_IF_AVAILABLE
      if constexpr (std::is_same<T, bool>::value)
         return !arg;
      else if constexpr (std::is_integral<T>::value) 
         return -arg;
      else if constexpr (std::is_floating_point<T>::value) 
         return std::abs(arg);
      else 
#endif
         return arg;
   }

   void execute()
   {
      {
         auto v1 = multiply(42.0, 1.5);     // OK
         //auto v2 = multiply("42"s, "1.5"s); // error
      }

      {
         pod_wrapper<int> i{ 42 };            // OK
         //pod_wrapper<std::string> s{ "42"s }; // error
      }

      {
         static_assert(std::is_const<const_wrapper<int>::const_type>::value);
         static_assert(std::is_const<const_wrapper<int const>::const_type>::value);
      }

      {
         auto v1 = process(false);  // true
         auto v2 = process(42);     // -42
         auto v3 = process(-42.0);  // 42.0
         auto v4 = process("42"s);  // "42"
      }
   }
}