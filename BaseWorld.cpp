#include "stdafx.h"
#include "BaseWorld.hpp"

BaseWorld::BaseWorld() {}
BaseWorld::~BaseWorld() {}

void BaseWorld::addListener(WorldListener* worldListener, unsigned priority) {
	listeners.add(worldListener);
}
 
void BaseWorld::removeListener(WorldListener* worldListener) {
	listeners.remove(worldListener);
}

bool BaseWorld::spawnEntity(Entity* entity, Entity* owner) {

	if (owner) {

	} else {
	
	}

	entities.add(entity);

	return true;

}

void BaseWorld::destroyEntity(Entity* entity) {

	entities.remove(entity);

}

