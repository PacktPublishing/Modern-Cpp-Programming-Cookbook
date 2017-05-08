#pragma once

#include "string_view.h"

namespace recipe_2_12
{
   std::string get_filename(std::string const & str)
   {
      auto const pos1{ str.find_last_of('\\') };
      auto const pos2{ str.find_last_of('.') };
      return str.substr(pos1 + 1, pos2 - pos1 - 1);
   }

   std::experimental::string_view get_filename_view(std::experimental::string_view str)
   {
      auto const pos1{ str.find_last_of('\\') };
      auto const pos2{ str.find_last_of('.') };
      return str.substr(pos1 + 1, pos2 - pos1 - 1);
   }

   std::experimental::string_view trim_view(std::experimental::string_view str)
   {
      auto const pos1{ str.find_first_not_of(" ") };
      auto const pos2{ str.find_last_not_of(" ") };
      str.remove_suffix(str.length() - pos2 - 1);
      str.remove_prefix(pos1);

      return str;
   }

   void execute()
   {
      {
         auto name1 = get_filename(R"(c:\test\example1.doc)"); // example1
         auto name2 = get_filename(R"(c:\test\example2)");     // example2
         if (get_filename(R"(c:\test\_sample_.tmp)").front() == '_')
         {
            std::cout << "underscore" << std::endl;
         }
      }

      {
         char const file1[] { R"(c:\test\example1.doc)" };
         auto name1 = get_filename_view(file1);
         auto sname1 = name1.to_string();

         std::string file2{ R"(c:\test\example2)" };
         auto name2 = get_filename_view(file2);
         auto sname2 = name2.to_string();

         auto name3 = get_filename_view(std::experimental::string_view(file1, 16));
         auto sname3 = name3.to_string();
      }

      {
         auto sv1{ trim_view("sample") };
         auto sv2{ trim_view("  sample") };
         auto sv3{ trim_view("sample  ") };
         auto sv4{ trim_view("  sample  ") };

         auto s1{ sv1.to_string() };
         auto s2{ sv2.to_string() };
         auto s3{ sv3.to_string() };
         auto s4{ sv4.to_string() };
      }
   }
}