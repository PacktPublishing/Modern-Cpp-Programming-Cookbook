#pragma once

#include <typeinfo>
#include <memory>
#include <map>
#include <functional>
#include <string>
#include <string_view>

namespace recipe_10_01
{
   using namespace std::string_literals;

   class Image {};

   class BitmapImage : public Image {};
   class PngImage : public Image {};
   class JpgImage : public Image {};

   struct IImageFactory
   {
      virtual std::shared_ptr<Image> Create(std::string_view type) = 0;
   };

   struct ImageFactoryClassic : public IImageFactory
   {
      virtual std::shared_ptr<Image> Create(std::string_view type) override
      {
         if (type == "bmp")
            return std::make_shared<BitmapImage>();
         else if (type == "png")
            return std::make_shared<PngImage>();
         else if (type == "jpg")
            return std::make_shared<JpgImage>();

         return nullptr;
      }
   };

   struct ImageFactory : public IImageFactory
   {
      virtual std::shared_ptr<Image> Create(std::string_view type) override
      {
         static std::map<
            std::string,
            std::function<std::shared_ptr<Image>()>> mapping
         {
            { "bmp", []() {return std::make_shared<BitmapImage>(); } },
            { "png", []() {return std::make_shared<PngImage>(); } },
            { "jpg", []() {return std::make_shared<JpgImage>(); } }
         };

         auto it = mapping.find(type.data());
         if (it != mapping.end())
            return it->second();

         return nullptr;
      }
   };

   struct IImageFactoryByType
   {
      virtual std::shared_ptr<Image> Create(std::type_info const & type) = 0;
   };
   
   struct ImageFactoryByType : public IImageFactoryByType
   {
      virtual std::shared_ptr<Image> Create(std::type_info const & type) override
      {
         auto it = mapping.find(&type);
         if (it != mapping.end())
            return it->second();

         return nullptr;
      }

   private:
      static std::map<
         std::type_info const *,
         std::function<std::shared_ptr<Image>()>> mapping;
   };

   std::map<
      std::type_info const *,
      std::function<std::shared_ptr<Image>()>> ImageFactoryByType::mapping
   {
      { &typeid(BitmapImage), []() {return std::make_shared<BitmapImage>(); } },
      { &typeid(PngImage),    []() {return std::make_shared<PngImage>(); } },
      { &typeid(JpgImage),    []() {return std::make_shared<JpgImage>(); } }
   };

   void execute()
   {
      {
         auto factory = ImageFactoryClassic{};
         auto image = factory.Create("png");
      }

      {
         auto factory = ImageFactory{};
         auto image = factory.Create("png");
      }

      {
         auto factory = ImageFactoryByType{};
         auto movie = factory.Create(typeid(PngImage));
      }
   }
}