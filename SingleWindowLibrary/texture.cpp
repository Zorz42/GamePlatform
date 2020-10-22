//
//  texture.cpp
//  SingleWindowLibrary
//
//  Created by Jakob Zorz on 12/09/2020.
//

#include "swl.h"
#include "SDL2_image/SDL_image.h"

Swl::texture::~texture() {
    _free();
}

void Swl::texture::_free() {
    if(_texture)
        SDL_DestroyTexture(_texture);
}

void Swl::draw(texture& obj) {
    SDL_Rect temp_rect = {obj.x, obj.y, obj.w, obj.h};
    SDL_RenderCopy(_renderer, obj._texture, nullptr, &temp_rect);
}

void Swl::texture::_loadFromSurface(SDL_Surface *temp_surface) {
    _free();
    if_dev(!temp_surface) std::cout << "[Swl::texture::_loadFromSurface] Surface is not loaded!" << std::endl;
    
    w = temp_surface->w;
    h = temp_surface->h;
    
    _texture = SDL_CreateTextureFromSurface(swl._renderer, temp_surface);
    if_dev(!_texture) std::cout << "[Swl::texture::_loadFromSurface] Surface did not convert to texture!" << std::endl;
    
    SDL_FreeSurface(temp_surface);
}

void Swl::texture::loadFromImage(const std::string path) {
    _loadFromSurface(IMG_Load(path.c_str()));
}

void Swl::texture::loadFromText(const std::string text, color c) {
    if_dev(!swl._font) std::cout << "[Swl::texture::loadFromText] Font is not even loaded while trying to render !" << std::endl;
    _loadFromSurface(TTF_RenderText_Solid(swl._font, text.c_str(), {c.r, c.g, c.b}));
}
