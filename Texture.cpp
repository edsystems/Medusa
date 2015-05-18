//********************************************************************************
// Medusa, a distributed embedded system to apply filters on image files.
// Copyright (C) 2015  Gorka Suárez García, Dan Cristian Rotaru
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//********************************************************************************

#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "Texture.hpp"

#include <iostream>
#include <boost/gil/image.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
//#include <boost/gil/extension/io/png_io.hpp>
#include <Utility.hpp>

//********************************************************************************
// [Texture] InnerData:
//********************************************************************************

class Texture::InnerData {
protected:
    // Methods:
    template <typename T> inline
    bool loadPNG(const std::string & path, T & victim) {
        //try {
        //    boost::gil::png_read_image(path, victim);
        //    return true;
        //} catch (std::exception & e) {
        //    std::cerr << "[Texture::InnerData::loadPNG] catch => std::exception" << std::endl;
        //    std::cerr << "+ WHAT: " << e.what() << std::endl;
        //    return false;
        //}
        return false;
    }

    template <typename T> inline
    bool loadJPG(const std::string & path, T & victim) {
        try {
            boost::gil::jpeg_read_image(path, victim);
            return true;
        } catch (std::exception & e) {
            std::cerr << "[Texture::InnerData::loadJPG] catch => std::exception" << std::endl;
            std::cerr << "+ WHAT: " << e.what() << std::endl;
            return false;
        }
    }

    template <typename T> inline
    bool savePNG(const std::string & path, T & victim) const {
        //try {
        //    boost::gil::png_write_view(path, boost::gil::const_view(victim));
        //    return true;
        //} catch (std::exception & e) {
        //    std::cerr << "[Texture::InnerData::savePNG] catch => std::exception" << std::endl;
        //    std::cerr << "+ WHAT: " << e.what() << std::endl;
        //    return false;
        //}
        return false;
    }

    template <typename T> inline
    bool saveJPG(const std::string & path, T & victim) const {
        try {
            boost::gil::jpeg_write_view(path, boost::gil::const_view(victim));
            return true;
        } catch (std::exception & e) {
            std::cerr << "[Texture::InnerData::saveJPG] catch => std::exception" << std::endl;
            std::cerr << "+ WHAT: " << e.what() << std::endl;
            return false;
        }
    }

    template <typename T> inline
    uint32_t getWidth(T & victim) const {
        return victim.width();
    }

    template <typename T> inline
    uint32_t getHeight(T & victim) const {
        return victim.height();
    }

public:
    // Constructors:
    InnerData() {}
    virtual ~InnerData() {}
    // Methods:
    virtual bool LoadPNG(const std::string & path) = 0;
    virtual bool LoadJPG(const std::string & path) = 0;
    virtual bool SavePNG(const std::string & path) const = 0;
    virtual bool SaveJPG(const std::string & path) const = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    //virtual Pixel GetPixel(uint32_t x, uint32_t y) const = 0;
    //virtual void SetPixel(uint32_t x, uint32_t y, const Pixel & value) = 0;
};

//--------------------------------------------------------------------------------

class PngInnerData : public Texture::InnerData {
private:
    boost::gil::rgba8_image_t img_;
public:
    // Constructors:
    PngInnerData() {}
    virtual ~PngInnerData() {}
    // Methods:
    virtual bool LoadPNG(const std::string & path) { return loadPNG(path, img_); }
    virtual bool LoadJPG(const std::string & path) { return false; }
    virtual bool SavePNG(const std::string & path) const { return savePNG(path, img_); }
    virtual bool SaveJPG(const std::string & path) const { return false; }
    virtual uint32_t GetWidth() const { return getWidth(img_); }
    virtual uint32_t GetHeight() const { return getHeight(img_); }

    void foo() {
        auto p = boost::gil::view(img_)(0, 0);
        auto r = p[0];
    }
    //virtual Pixel GetPixel(uint32_t x, uint32_t y) const {
    //    auto & imgView = boost::gil::view(img_);
    //    return Pixel();
    //}
    //virtual void SetPixel(uint32_t x, uint32_t y, const Pixel & value) {
    //}
};

//--------------------------------------------------------------------------------

class JpgInnerData : public Texture::InnerData {
private:
    boost::gil::rgb8_image_t img_;
public:
    // Constructors:
    JpgInnerData() {}
    virtual ~JpgInnerData() {}
    // Methods:
    virtual bool LoadPNG(const std::string & path) { return false; }
    virtual bool LoadJPG(const std::string & path) { return loadJPG(path, img_); }
    virtual bool SavePNG(const std::string & path) const { return false; }
    virtual bool SaveJPG(const std::string & path) const { return saveJPG(path, img_); }
    virtual uint32_t GetWidth() const { return getWidth(img_); }
    virtual uint32_t GetHeight() const { return getHeight(img_); }
};

//********************************************************************************
// [Texture] Constructors:
//********************************************************************************

Texture::Texture() : data_(nullptr) {}

//--------------------------------------------------------------------------------

Texture::~Texture() {}

//********************************************************************************
// [Texture] Properties:
//********************************************************************************

uint32_t Texture::GetWidth() const {
    return data_ ? data_->GetWidth() : 0;
}

//--------------------------------------------------------------------------------

uint32_t Texture::GetHeight() const {
    return data_ ? data_->GetHeight() : 0;
}

//********************************************************************************
// [Texture] Methods:
//********************************************************************************

bool Texture::Load(const std::string & path) {
    std::string extension = GetPathExtension(path);
    //if (extension == "png") {
    //    data_.reset(new PngInnerData());
    //    return data_->LoadPNG(path);
    //}
    if (extension == "jpg" || extension == "jpeg") {
        data_.reset(new JpgInnerData());
        return data_->LoadJPG(path);
    }
    return false;
}

//--------------------------------------------------------------------------------

bool Texture::Save(const std::string & path) const {
    std::string extension = GetPathExtension(path);
    //if (extension == "png") {
    //    return data_->SavePNG(path);
    //}
    if (extension == "jpg" || extension == "jpeg") {
        return data_->SaveJPG(path);
    } 
    return false;
}

//--------------------------------------------------------------------------------

void Texture::Unload() {
    data_.reset();
}

//--------------------------------------------------------------------------------

Pixel Texture::GetPixel(uint32_t x, uint32_t y) const {
    //return data_ ? data_->GetPixel(x, y) : Pixel();
    //...
    return Pixel();
}

//--------------------------------------------------------------------------------

void Texture::SetPixel(uint32_t x, uint32_t y, const Pixel & value) {
    if (data_) {
        //data_->SetPixel(x, y, value);
        //...
    }
}

//--------------------------------------------------------------------------------

void Texture::InvertFilter(const Rect & area) {
    //TODO: Complete this method...
    //...
}

//--------------------------------------------------------------------------------

void Texture::GrayFilter(const Rect & area) {
    //TODO: Complete this method...
    //...
}
