#include "../headers/LayerManager.h"

LayerManager::LayerManager() {
  this->layers = new std::vector<std::unique_ptr<std::vector<class Entity*>>>();
  this->entityMap = new std::unordered_map<Entity*, size_t>();
  this->requestedUpdates = new std::queue<std::pair<class Entity*, size_t>>();
}

LayerManager::~LayerManager() {
  delete this->layers;
  delete this->entityMap;
  delete this->requestedUpdates;
}

void LayerManager::add(class Entity* entity) {
  if (!entity) { return; }

  if (this->entityMap->find(entity) == this->entityMap->end()) {
    if (this->layers->empty()) { this->createLayer(); }
    this->requestedUpdates->push({entity, 0});
  }

  printf("Entity %p was added to LM %p.\n", entity, this);
}

void LayerManager::moveUpLayer(class Entity* entity) {
  this->adjustLayer(entity, 1);
}

void LayerManager::moveDownLayer(class Entity* entity) {
  this->adjustLayer(entity, -1);
}

void LayerManager::moveToTop(class Entity* entity) {
  this->requestedUpdates->push({entity, this->getLayerCount() - 1});
}

void LayerManager::moveToNewTop(class Entity* entity) {
  this->createLayer();
  this->moveToTop(entity);
}

void LayerManager::moveToBottom(class Entity* entity) {
  this->requestedUpdates->push({entity, 0});
}

void LayerManager::remove(class Entity* entity) {
  if (this->entityMap->find(entity) != this->entityMap->end()) {
    this->removeFromLayer(entity);
    this->entityMap->erase(entity);
  }
}

void LayerManager::moveToLayer(class Entity* entity, size_t layer) {
  this->requestedUpdates->push({entity, layer});
}

void LayerManager::update() {
  while(!this->requestedUpdates->empty()) {
    std::pair<class Entity*, size_t> update = this->requestedUpdates->front();
    this->requestedUpdates->pop();
    this->removeFromLayer(update.first);
    
    this->insertToLayer(update.first, update.second);

    for (size_t i = 0; i < this->getLayerCount(); ++i) {
      printf("Layer %d\n", (int)i);
      for (Entity* ent : *this->getLayer(i)) {
        printf("\tEntity: %p\n", ent);
      }
    }
  }
}

size_t LayerManager::getLayerCount() const {
  return this->layers->size();
}

const std::vector<Entity*>* LayerManager::getLayer(size_t layer) const {
  return this->layers->at(layer).get();
}

void LayerManager::adjustLayer(Entity* entity, int direction) {
  size_t current = this->entityMap->at(entity);
  size_t requested = current + direction;

  if (requested < this->layers->size()) {
    this->requestedUpdates->push({entity, requested});
  }
}

void LayerManager::createLayer() {
  this->layers->push_back(std::make_unique<std::vector<Entity*>>());
}

void LayerManager::insertToLayer(Entity* entity, size_t layer) {
  if (this->getLayerCount() == 0) { this->createLayer(); }
  
  size_t _layer = layer%this->getLayerCount();
  this->layers->at(_layer)->push_back(entity);

  if (this->entityMap->find(entity) == this->entityMap->end()) {
    this->entityMap->insert({entity, _layer});
  } else {
    this->entityMap->at(entity) = _layer;
  }
}

void LayerManager::removeFromLayer(Entity* entity) {
  if (this->entityMap->find(entity) == this->entityMap->end()) {
    return;
  }

  int currentLayer = this->entityMap->at(entity);
  auto it = this->layers->at(currentLayer)->begin();

  while (it < this->layers->at(currentLayer)->end()) {
    if (*it == entity) {
      this->layers->at(currentLayer)->erase(it);
      break;
    }

    ++it;
  }

  if (this->layers->at(currentLayer)->empty()) {
    this->layers->erase(this->layers->begin() + currentLayer);
  }
}