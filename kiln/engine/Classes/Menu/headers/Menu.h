#pragma once
#include "kiln/engine/Module/SubModule.h"
#include "kiln/engine/Kiln.h"
#include <vector>

class Menu : public SubModule {
public:
  Menu(class KilnModule* module);
  
  virtual void handleEvent(SDL_Event* event) override;
  virtual void tick(float deltaTime) override;
  virtual void render(SDL_Renderer* renderer);

protected:
  void createButton(class Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  void createButton(class Texture* texture);
  void createButton(class Button* button);

  void createStatic(class Entity* sprite);
private:
  std::vector<class Entity*> staticElements;
  std::vector<class Button*> buttons;
  SDL_Color backgroundColor;

  float runTime = 0.f;
};