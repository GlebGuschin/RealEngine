#include "stdafx.h"
#include "BaseEntity.hpp"


Entity* BaseEntityManager::createEntity() {
	BaseEntity* entity = new BaseEntity(this);
	entities.add(entity);
	return entity;
}

void BaseEntityManager::releaseEntity(Entity*entity) {
	entities.remove(entity);
}






//unsigned BaseEntity::getNumComponents() const { }
//Component* BaseEntity::getComponent(unsigned index) const;

void BaseEntity::addComponent(Component* component) {
	components.add(component);
}

void BaseEntity::removeComponent(Component* component) {
	components.remove(component);
}

void BaseEntity::addChild(Entity* child) { children.add(child); }
void BaseEntity::removeChild(Entity* child) { children.add(child); }
bool BaseEntity::isChild(Entity* child) const{ return children.find(child); }
bool BaseEntity::findRecursive(Entity*)  const { return false; }

