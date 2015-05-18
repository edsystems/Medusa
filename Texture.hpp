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

#ifndef __MEDUSA_TEXTURE__
#define __MEDUSA_TEXTURE__

#include <memory>
#include <string>

struct Rect {
    uint32_t X, Y, Width, Height;
    Rect(uint32_t x = 0, uint32_t y = 0, uint32_t w = 0, uint32_t h = 0) :
        X(x), Y(y), Width(w), Height(h) {}
    Rect(const Rect & o) : X(o.X), Y(o.Y), Width(o.Width), Height(o.Height) {}
};

struct Pixel {
    uint8_t Red, Green, Blue, Alpha;
    Pixel(uint8_t r = 0xFF, uint8_t g = 0xFF, uint8_t b = 0xFF, uint8_t a = 0xFF) :
        Red(r), Green(g), Blue(b), Alpha(a) {}
    Pixel(const Pixel & o) : Red(o.Red), Green(o.Green),Blue(o.Blue), Alpha(o.Alpha) {}
};

class Texture {
public:
    // Types:
    class InnerData;
private:
    // Fields:
    std::shared_ptr<InnerData> data_;
public:
    // Constructors:
    Texture();
    ~Texture();
    // Properties:
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    // Methods:
    bool Load(const std::string & path);
    bool Save(const std::string & path) const;
    void Unload();
    Pixel GetPixel(uint32_t x, uint32_t y) const;
    void SetPixel(uint32_t x, uint32_t y, const Pixel & value);
    void InvertFilter(const Rect & area);
    void GrayFilter(const Rect & area);
};

#endif
