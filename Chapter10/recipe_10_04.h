#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace recipe_10_04
{
   class control
   {
   private:
      virtual void paint() = 0;

   protected:
      virtual void initialize_impl()
      {
         std::cout << "initializing control..." << std::endl;
      }

      virtual void erase_background()
      {
         std::cout << "erasing control background..." << std::endl;
      }

   public:
      void draw()
      {
         erase_background();
         paint();
      }

      void initialize()
      {
         initialize_impl();
      }

      virtual ~control()
      {
         std::cout << "destroying control..." << std::endl;
      }
   };

   class button : public control
   {
   private:
      virtual void paint() override
      {
         std::cout << "painting button..." << std::endl;
      }

   protected:
      virtual void initialize_impl()
      {
         control::initialize_impl();
         std::cout << "initializing button..." << std::endl;
      }

      virtual void erase_background() override
      {
         control::erase_background();
         std::cout << "erasing button background..." << std::endl;
      }

   public:
      ~button()
      {
         std::cout << "destroying button..." << std::endl;
      }
   };

   class checkbox : public button
   {
   private:
      virtual void paint() override
      {
         std::cout << "painting checkbox..." << std::endl;
      }

   protected:
      virtual void erase_background() override
      {
         button::erase_background();
         std::cout << "erasing checkbox background..." << std::endl;
      }

   public:
      ~checkbox()
      {
         std::cout << "destroying checkbox..." << std::endl;
      }
   };

   void execute()
   {
      {
         std::vector<std::shared_ptr<control>> controls;

         controls.push_back(std::make_shared<button>());
         controls.push_back(std::make_shared<checkbox>());

         for (auto& c : controls)
            c->draw();
      }

      {
         button b;
         b.initialize();
         b.draw();
      }
   }
}