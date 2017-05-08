#pragma once

namespace recipe_4_06
{
#ifdef ATTRIBUTES_AVAILABLE
   [[nodiscard]] int get_value1()
   {
      return 42;
   }

   enum class[[nodiscard]] ReturnCodes{ OK, NoData, Error };

   ReturnCodes get_value2()
   {
      return ReturnCodes::OK;
   }

   struct[[nodiscard]] Item{};

   Item get_value3()
   {
      return Item{};
   }

   [[deprecated("Use func2()")]] void func()
   {
   }

   class[[deprecated]] foo
   {
   };

   double run([[maybe_unused]] int a, double b)
   {
      return 2 * b;
   }

   void option1() {}
   void option2() {}
#endif

   void execute()
   {
#ifdef ATTRIBUTES_AVAILABLE
      {
         // warning: ignoring return value of function declared with 'nodiscard' attribute
         get_value1();

         get_value2();

         get_value3();
      }

      {
         // warning: 'func' is deprecated : Use func2()
         func();

         // warning: 'foo' is deprecated
         foo f;
      }

      {
         run(2, 42.0);

         [[maybe_unused]] auto i = get_value1();
      }

      {
         int alternative = get_value1();
         switch (alternative)
         {
         case 1:
            option1();
            [[fallthrough]];
         case 2:
            option2();
         }
      }
#endif
   }
}