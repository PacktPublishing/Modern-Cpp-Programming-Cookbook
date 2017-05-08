#pragma once

#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <string>
#include <stack>

namespace recipe_5_01
{
   using namespace std::string_literals;

   void process(int const * const arr, int const size)
   {
      for (int i = 0; i < size; ++i)
         std::cout << arr[i] << std::endl;
      std::cout << std::endl;
   }

   struct foo
   {
      int a;
      double b;
      std::string c;

      foo(int a, double b, std::string const & c) :
         a(a), b(b), c(c) 
      {}
   };

   void execute()
   {
      {
         std::vector<int> v1{ 1, 2, 3, 4, 5 };

         int arr[] = { 1, 2, 3, 4, 5 };
         std::vector<int> v2(arr, arr + 5);

         std::list<int> l{ 1, 2, 3, 4, 5 };
         std::vector<int> v3(l.begin(), l.end());

         std::vector<int> v4(5, 1);
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 5 };
         v1.push_back(6);
         v1.pop_back();

         int arr[] = { 1, 2, 3, 4, 5 };
         std::vector<int> v2;
         v2.insert(v2.begin(), arr, arr + 5);

         std::vector<foo> v3;
         v3.emplace_back(1, 1.0, "one"s);
         v3.emplace(v3.begin(), 2, 2.0, "two"s);    
      }

      {
         std::vector<int> v1{ 1, 2, 3, 4, 5 };
         std::vector<int> v2{ 10, 20, 30 };
         v2 = v1;
      
         int arr[] = { 1, 2, 3, 4, 5 };
         std::vector<int> v3;
         v3.assign(arr, arr + 5);

         std::vector<int> v4{ 1, 2, 3, 4, 5 };
         std::vector<int> v5{ 10, 20, 30 };
         v4.swap(v5);

         std::vector<int> v6{ 1, 2, 3, 4, 5 };
         v6.clear();

         std::vector<int> v7{ 1, 2, 3, 4, 5 };
         v7.erase(v7.begin() + 2, v7.begin() + 4);
      }

      {
         std::vector<int> v{ 1, 2, 3, 4, 5 };
         
         process(v.data(), static_cast<int>(v.size()));
         process(&v[0], static_cast<int>(v.size()));
         process(&v.front(), static_cast<int>(v.size()));
         process(&*v.begin(), static_cast<int>(v.size()));
      }

      {
         std::list<int> l { 1, 2, 3, 4, 5 };
         std::vector<int> v(l.begin(), l.end());
         process(v.data(), static_cast<int>(v.size()));
      }

      {
         std::vector<int> v{ 1, 2, 3, 4, 5 };
         std::vector<int>().swap(v);
      }
   }
}