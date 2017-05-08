#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>

namespace recipe_3_02
{
   using namespace std::string_literals;

   inline bool is_positive(int const n)
   {
      return n > 0;
   }

   class range_selector
   {
      int start_;
      int end_;
   public:
      explicit range_selector(int const start, int const end) :
         start_(start), end_(end)
      {
      }

      bool operator()(int const n)
      {
         return start_ <= n && n <= end_;
      }
   };

   struct __lambda_name__
   {
      bool operator()(int const n) const { return n > 0; }
   };

   class __lambda_name_2__
   {
      int start_;
      int end_;
   public:
      explicit __lambda_name_2__(int const start, int const end) :
         start_(start), end_(end)
      {}

      __lambda_name_2__(const __lambda_name_2__&) = default;
      __lambda_name_2__(__lambda_name_2__&&) = default;
      __lambda_name_2__& operator=(const __lambda_name_2__&) = delete;
      ~__lambda_name_2__() = default;

      bool operator() (int const n) const
      {
         return start_ <= n && n <= end_;
      }
   };

   void execute()
   {
      auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };

      {
         auto positives = std::count_if(std::begin(numbers), std::end(numbers),
            is_positive);

         std::cout << "positives: " << positives << std::endl;

         auto start{ 5 }; // could be an input params
         auto end{ 10 };
         auto inrange = std::count_if(std::begin(numbers), std::end(numbers),
            range_selector(start, end));

         std::cout << "inrange(5, 10): " << inrange << std::endl;
      }

      {
         auto positives = std::count_if(std::begin(numbers), std::end(numbers),
            [](int const n) {return n > 0; });

         std::cout << "positives: " << positives << std::endl;

         auto start{ 5 };
         auto end{ 10 };
         auto inrange = std::count_if(
            std::begin(numbers), std::end(numbers),
            [start, end](int const n) {return start <= n && n <= end; });

         std::cout << "inrange(5, 10): " << inrange << std::endl;
      }

      {
         auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
            [](int const s, int const n) {return s + n; });

         std::cout << "sum: " << sum << std::endl;

         auto text = std::accumulate(std::begin(texts), std::end(texts), ""s,
            [](std::string const s, std::string const n) {return s + n; });

         std::cout << "text: " << text << std::endl;
      }
   }
}
