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

bool BaseWorld::spawnEntity(Entity* entity, Entity* owner_) {

	Entity* owner = owner_ ? owner_ : getRoot();

	if (owner) {
	} else {	
	}

	entities.add(entity);

	for(unsigned i =0; i < listeners.size(); i++) listeners[i]->onSpawnEntity(entity);

	return true;

}

void BaseWorld::destroyEntity(Entity* entity) {

	for(unsigned i =0; i < listeners.size(); i++) listeners[i]->onDestroyEntity(entity);
	entities.remove(entity);

}



World* CreateWorld() { return new BaseWorld; }