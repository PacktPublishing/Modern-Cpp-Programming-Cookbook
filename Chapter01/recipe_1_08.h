#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

namespace recipe_1_08
{
   std::vector<int> getRates()
   {
      return std::vector<int> {1, 1, 2, 3, 5, 8, 13};
   }

   void print_rate(int const rate)
   {
      std::cout << rate << std::endl;
   }

   std::multimap<int, bool> getRates2()
   {
      return std::multimap<int, bool>
      {
         { 1, true },
         { 1, true },
         { 2, false },
         { 3, true },
         { 5, true },
         { 8, false },
         { 13, true }
      };
   }

   void execute()
   {
      {
         auto rates = getRates();

         // using iterators
         for (auto it = rates.begin(); it != rates.end(); ++it)
         {
            std::cout << *it << std::endl;
         }

         // using an index
         for (size_t i = 0; i < rates.size(); ++i)
         {
            std::cout << rates[i] << std::endl;
         }
      }

      {
         auto rates = getRates();

         std::for_each(rates.begin(), rates.end(), print_rate);

         std::for_each(rates.begin(), rates.end(), [](auto const rate) {std::cout << rate << std::endl; });
      }

      {
         auto rates = getRates();
         for (int rate : rates)
         {
            std::cout << rate << std::endl;
         }

         for(int& rate : rates)
         {
            rate *= 2;
         }

         for (auto&& rate : getRates())
         {
            std::cout << rate << std::endl;
         }

         for (auto & rate : rates)
         {
            rate *= 2;
         }

         for (auto const & rate : rates)
         {
            std::cout << rate << std::endl;
         }
      }

      {
         for (auto&& kvp : getRates2())
         {
            std::cout << kvp.first << std::endl;
         }

         for (auto&& kvp : getRates2())
         {
            bool flag;
            int rate;
            std::tie(rate, flag) = kvp;

            std::cout << rate << std::endl;
         }

#ifdef DECOMPOSITION_AVAILABLE 
         for (auto&&[rate, flag] : getRates())
         {
            std::cout << rate << std::endl;
         }
#endif
      }
   }
}