#pragma once

namespace recipe_4_05
{
#ifdef CONSTEXPR_IF_AVAILABLE

   template <typename T>
   auto compute(T const a, T const b)
   {
      if constexpr (std::is_integral<T>::value)
         return a * b;
      else
         return a + b;
   }

   namespace binary
   {
      using byte8 = unsigned char;
      using byte16 = unsigned short;
      using byte32 = unsigned int;

      namespace binary_literals
      {
         namespace binary_literals_internals
         {
            template <typename CharT, char d, char... bits>
            constexpr CharT binary_eval()
            {
               if constexpr(sizeof...(bits) == 0)
                  return static_cast<CharT>(d - '0');
               else if constexpr(d == '0')
                  return binary_eval<CharT, bits...>();
               else if constexpr(d == '1')
                  return static_cast<CharT>((1 << sizeof...(bits)) | binary_eval<CharT, bits...>());
            }
         }

         template<char... bits>
         constexpr byte8 operator""_b8()
         {
            static_assert(
               sizeof...(bits) <= 8,
               "binary literal b8 must be up to 8 digits long");

            return binary_literals_internals::binary_eval<byte8, bits...>();
         }

         template<char... bits>
         constexpr byte16 operator""_b16()
         {
            static_assert(
               sizeof...(bits) <= 16,
               "binary literal b16 must be up to 16 digits long");

            return binary_literals_internals::binary_eval<byte16, bits...>();
         }

         template<char... bits>
         constexpr byte32 operator""_b32()
         {
            static_assert(
               sizeof...(bits) <= 32,
               "binary literal b32 must be up to 32 digits long");

            return binary_literals_internals::binary_eval<byte32, bits...>();
         }
      }
   }
}
#endif CONSTEXPR_IF_AVAILABLE

void execute()
{
#ifdef CONSTEXPR_IF_AVAILABLE
      {
         auto v1 = compute(1, 2);
         auto v2 = compute(1.0, 2.0);
      }

      {
         using namespace binary;
         using namespace binary_literals;

         auto b1 = 1010_b8;
         auto b2 = 101010101010_b16;
         auto b3 = 010101010101010101010101_b32;
      }
#endif
   }
}