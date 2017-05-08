#pragma once

#include <map>
#include <iostream>

namespace recipe_1_13
{
   std::tuple<int, std::string, double> find()
   {
      return std::make_tuple(1, "marius", 1234.5);
   }

   void execute()
   {
      {
         std::map<int, std::string> m;

         auto result = m.insert({ 1, "one" });
         std::cout << "inserted = " << result.second << std::endl
            << "value = " << result.first->second << std::endl;
      }

      {
         std::map<int, std::string> m;
         std::map<int, std::string>::iterator it;
         bool inserted;

         std::tie(it, inserted) = m.insert({ 1, "one" });
         std::cout << "inserted = " << inserted << std::endl
            << "value = " << it->second << std::endl;

         std::tie(it, inserted) = m.insert({ 1, "two" });
         std::cout << "inserted = " << inserted << std::endl
            << "value = " << it->second << std::endl;
      }

      {
         int id;
         std::string name;
         double score;

         std::tie(id, name, score) = find();

         std::cout << "id=" << id
            << " name=" << name
            << " score=" << score << std::endl;
      }

      // C++17 only
#ifdef STRUCTURED_BINDINGS
      {
         std::map<int, std::string> m;
         if (auto[it, inserted] = m.insert({ 1, "two" }); inserted)
         {
            std::cout << it->second << std::endl;
         }

         {
            auto[it, inserted] = m.insert({ 1, "one" });
            std::cout << "inserted = " << inserted << std::endl
                      << "value = " << it->second << std::endl;
         }

         {
            auto[it, inserted] = m.insert({ 1, "two" });
            std::cout << "inserted = " << inserted << std::endl
                      << "value = " << it->second << std::endl;
         }

         auto[id, name, score] = find();

         if (auto[id, name, score] = find(); score > 1000)
         {
            std::cout << name << std::endl;
         }
      }
#endif
   }
}