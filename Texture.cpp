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
#include <boost/gil/typedefs.hpp>
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
    virtual Pixel GetPixel(uint32_t x, uint32_t y) const = 0;
    virtual void SetPixel(uint32_t x, uint32_t y, const Pixel & value) = 0;
};

//--------------------------------------------------------------------------------

//class PngInnerData : public Texture::InnerData {
//private:
//    boost::gil::rgba8_image_t img_;
//public:
//    // Constructors:
//    PngInnerData() {}
//    virtual ~PngInnerData() {}
//    // Methods:
//    virtual bool LoadPNG(const std::string & path) { return loadPNG(path, img_); }
//    virtual bool LoadJPG(const std::string & path) { return false; }
//    virtual bool SavePNG(const std::string & path) const { return savePNG(path, img_); }
//    virtual bool SaveJPG(const std::string & path) const { return false; }
//    virtual uint32_t GetWidth() const { return getWidth(img_); }
//    virtual uint32_t GetHeight() const { return getHeight(img_); }
//};

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

    virtual Pixel GetPixel(uint32_t x, uint32_t y) const {
        try {
            auto & iv = boost::gil::const_view(img_);
            auto & p = iv(x, y);
            return Pixel(p[0], p[1], p[2]);
        } catch (std::exception & e) {
            std::cerr << "[JpgInnerData::GetPixel] catch => std::exception" << std::endl;
            std::cerr << "+ WHAT: " << e.what() << std::endl;
            return Pixel();
        }
    }

    virtual void SetPixel(uint32_t x, uint32_t y, const Pixel & value) {
        try {
            auto & iv = boost::gil::view(img_);
            auto & p = iv(x, y);
            p[0] = value.Red;
            p[1] = value.Green;
            p[2] = value.Blue;
        } catch (std::exception & e) {
            std::cerr << "[JpgInnerData::SetPixel] catch => std::exception" << std::endl;
            std::cerr << "+ WHAT: " << e.what() << std::endl;
        }
    }
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
    return data_ ? data_->GetPixel(x, y) : Pixel();
}

//--------------------------------------------------------------------------------

void Texture::SetPixel(uint32_t x, uint32_t y, const Pixel & value) {
    if (data_) { data_->SetPixel(x, y, value); }
}

//--------------------------------------------------------------------------------

void Texture::InvertFilter(const Rect & area) {
    for (uint32_t i = 0; i < area.Height; ++i) {
        for (uint32_t j = 0; j < area.Width; ++j) {
            auto p = GetPixel(area.X + j, area.Y + i);
            p.Red = ~p.Red;
            p.Green = ~p.Green;
            p.Blue = ~p.Blue;
            SetPixel(area.X + j, area.Y + i, p);
        }
    }
}

//--------------------------------------------------------------------------------

void Texture::GrayScaleFilter(const Rect & area) {
    for (uint32_t i = 0; i < area.Height; ++i) {
        for (uint32_t j = 0; j < area.Width; ++j) {
            auto p = GetPixel(area.X + j, area.Y + i);
            float gv = p.Red * 0.3f + p.Green * 0.6f + p.Blue * 0.11f;
            p.Red = p.Green = p.Blue = static_cast<uint8_t>(gv);
            SetPixel(area.X + j, area.Y + i, p);
        }
    }
}
