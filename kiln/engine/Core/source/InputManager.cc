#include "../headers/InputManager.h"
#include "kiln/engine/Classes/Components/headers/InputComponent.h"
#include <SDL.h>
#include <iostream>

std::queue<std::pair<SDL_Keycode, std::function<void()>>>* InputComponent::bindings = new std::queue<std::pair<SDL_Keycode, std::function<void()>>>();

InputManager::InputManager() {
  this->keyStates = SDL_GetKeyboardState(&this->keyCount);
}

InputManager::~InputManager() {
  delete InputComponent::bindings;
}

bool InputManager::poll() {
  if (SDL_PollEvent(&this->buffer) == 0) {
    return false;
  }

  switch(this->buffer.type) {
    case SDL_KEYDOWN:
    this->registerKeyDown();
    break;

    case SDL_KEYUP:
    this->registerKeyUp();
    break;
  }

  return true;
}

const SDL_Event* InputManager::getLastEvent() const {
  return &this->buffer;
}

void InputManager::bind(Sint32 keyCode, Action action) {
  std::cout << "Bound " << keyCode << "." << std::endl;
  this->bindings[keyCode] = action; 
}

void InputManager::bindInputComponents() {
  std::cout << "Binding components." << std::endl;
  while(!InputComponent::bindings->empty()) {
    std::pair<SDL_Keycode, Action> binding = InputComponent::bindings->front();
    InputComponent::bindings->pop();

    std::cout << "Binding " << binding.first << std::endl;

    this->bindings[binding.first] = binding.second;
  }
}

void InputManager::handleInputs() {
  this->handleKeys();
}

void InputManager::handleKeys() {
  for (SDL_Keycode key : this->pressedKeys) {
    auto binding = this->bindings.find(key);

    if (binding != this->bindings.end()) {
      std::cout << "\tEXEC: " << binding->first << std::endl;
      binding->second();
    }
  }
}

void InputManager::registerKeyDown() {
  this->pressedKeys.push_back(this->buffer.key.keysym.sym);
}

void InputManager::registerKeyUp() {
  for (auto itr = this->pressedKeys.begin(); itr != this->pressedKeys.end(); ++itr) {
    if (*itr == this->buffer.key.keysym.sym) {
      this->pressedKeys.erase(itr);
      break;
    }
  }
}