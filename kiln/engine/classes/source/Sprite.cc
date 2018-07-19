#include "../headers/Sprite.h"
#include <iostream>

Sprite::~Sprite() {
  delete this->texture;
}

void Sprite::fromTexture(Texture* texture) {
  if (texture) {
    std::cout << "ASSIGN" << std::endl;
    this->texture = texture;
    std::cout << "ASSIGNED" << std::endl;
  } else {
    std::cerr << "Bad texture!" << std::endl;
  }
}

void Sprite::fromText(std::string text, TTF_Font* font, SDL_Renderer* renderer) {
  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{0x88, 0x88, 0x88, 0xFF});
  this->texture = new Texture();
  this->texture->create(surface, renderer);

  SDL_FreeSurface(surface);
}

void Sprite::setWidth(int width) {
  this->texture->setWidth(width);
}

void Sprite::setHeight(int height) {
  this->texture->setHeight(height);
}

void Sprite::setPosition(int x, int y) {
  this->position.x = x;
  this->position.y = y;
}

void Sprite::render(SDL_Renderer* renderer) const {
  SDL_Rect container;
  container.w = this->texture->getWidth();
  container.h = this->texture->getHeight();
  container.x = this->position.x;
  container.y = this->position.y;

  SDL_RenderCopy(
    renderer,
    this->texture->getTexture(),
    NULL,
    &container  
  );
}