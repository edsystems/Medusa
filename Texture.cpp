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

#include "Texture.hpp"

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
    //...
    return 0;
}

//--------------------------------------------------------------------------------

uint32_t Texture::GetHeight() const {
    //...
    return 0;
}

//********************************************************************************
// [Texture] Methods:
//********************************************************************************

bool Texture::Load(const std::string & path) {
    //...
    return false;
}

//--------------------------------------------------------------------------------

bool Texture::Save(const std::string & path) {
    //...
    return false;
}

//--------------------------------------------------------------------------------

void Texture::Unload() {
    //...
}

//--------------------------------------------------------------------------------

Pixel Texture::GetPixel(uint32_t x, uint32_t y) const {
    //...
    return Pixel();
}

//--------------------------------------------------------------------------------

void Texture::SetPixel(uint32_t x, uint32_t y, const Pixel & value) {
    //...
}

//--------------------------------------------------------------------------------

void Texture::InvertFilter(const Rectangle & area) {
    //...
}

//--------------------------------------------------------------------------------

void Texture::GrayFilter(const Rectangle & area) {
    //...
}
