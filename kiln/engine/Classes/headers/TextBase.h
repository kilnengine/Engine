#pragma once
#include "kiln/engine/Classes/headers/SpriteBase.h"
#include "SDL_ttf.h"

class TextBase : public SpriteBase {
public:
  TextBase(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  ~TextBase();

  void draw(SDL_Renderer* renderer);
  void setText(std::string TextBaseBase);
  void setFont(TTF_Font* font);
  void setColor(SDL_Color color);

  bool checkWasModified() const;

private:
  std::string text;
  TTF_Font* font;
  SDL_Color color;
  
  bool wasModified = false;
};