#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>
#include <iomanip>
#include <chrono>

namespace fs = std::experimental::filesystem;

namespace recipe_7_10
{
   void execute()
   {
      auto path = fs::current_path() / "main.cpp";
      auto err = std::error_code{};

      // file exists
      {
         auto exists = fs::exists(path, err);
         std::cout << "file exists: " << std::boolalpha
            << exists << std::endl;
      }

      // paths equivalent
      {
         auto same = fs::equivalent(
            path, 
            fs::current_path() / "." / "main.cpp");

         std::cout << "equivalent: " << same << std::endl;
      }

      // file size
      {
         auto size = fs::file_size(path, err);
         std::cout << "file size: " << size << std::endl;
      }

      // number of hard links
      {
         auto links = fs::hard_link_count(path, err);
         if(links != static_cast<uintmax_t>(-1))
            std::cout << "hard links: " << links << std::endl;
         else
            std::cout << "hard links: error" << std::endl;
      }

      // last write time
      {
         auto lwt = fs::last_write_time(path, err);
         auto time = decltype(lwt)::clock::to_time_t(lwt);
         auto localtime = std::localtime(&time);

         std::cout << "last write time: " 
            << std::put_time(localtime, "%c") << std::endl;

         // modify last write time
         {
            using namespace std::chrono_literals;

            fs::last_write_time(path, lwt - 30min);

            lwt = fs::last_write_time(path, err);
            time = decltype(lwt)::clock::to_time_t(lwt);
            localtime = std::localtime(&time);

            std::cout << "last write time: "
               << std::put_time(localtime, "%c") << std::endl;
         }
      }

      // status
      {
         auto print_perm = [](fs::perms p)
         {
            std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
               << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
               << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
               << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
               << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
               << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
               << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
               << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
               << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
               << std::endl;
         };

         auto status = fs::status(path, err);
         std::cout << "type: " << static_cast<int>(status.type()) << std::endl;
         std::cout << "permissions: ";
         print_perm(status.permissions());
      }

      // file types
      {
         std::cout << "regular file? " <<
            fs::is_regular_file(path, err) << std::endl;
         std::cout << "directory? " <<
            fs::is_directory(path, err) << std::endl;
         std::cout << "char file? " <<
            fs::is_character_file(path, err) << std::endl;
         std::cout << "symlink? " <<
            fs::is_symlink(path, err) << std::endl;

      }
   }
}