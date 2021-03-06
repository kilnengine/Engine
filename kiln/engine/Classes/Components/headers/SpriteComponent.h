#pragma once

#include "Component.h"
#include "kiln/engine/Utils/headers/Dim.h"

class SpriteComponent : public Component {
public:
  SpriteComponent();
  SpriteComponent(Entity* owner, class Texture* texture);
  SpriteComponent(Entity* owner);
  SpriteComponent(class Texture* texture);

  virtual ~SpriteComponent() {}

  virtual void start() override;
  virtual void tick(float deltaTime) override;

  void setShouldRender(const bool shouldRender);
  bool checkShouldRender() const;
  void setWidth(unsigned int width);
  void setHeight(unsigned int height);
  void setScale(float scale);
  void setRotation(float degrees);
  void setTexture(class Texture* texture);

protected:
  void setTexture(struct SDL_Texture* texture);

public:
  FCoordinate getWorldPosition() const;
  Dim getDimensions() const;
  float getScale() const;
  float getRotationDegrees() const;
  struct SDL_Texture* getTexture();

  virtual void render(struct SDL_Renderer*);
  virtual void clear();

private:
  bool shouldRender = true;
  Dim originalDim;
  Dim renderDim;
  float rotationDegrees = 0.f;
  float scale = 1.f;
  struct SDL_Texture* texture = nullptr;
};
