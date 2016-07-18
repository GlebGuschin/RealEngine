#include "stdafx.h"
#include "Entity.hpp"
#include "World.hpp"

#if 0


Entity::Entity() {

	world = NULL;
	//addComponent( new TransformComponent() );

}

Entity::~Entity() {

	world = NULL;
	//TransformComponent* component = findComponent<TransformComponent>();
	//removeComponent( component );

}

void Entity::setParent(Entity*parent_) {

	parent = parent_;

	if (parent)
		
	setWorld( parent->getWorld() );

}

bool Entity::isBase() const { 

	if (world && getParent() == world->getRoot() ) return true;

	return false;

}

Entity* Entity::clone() const {

	Entity* entity = new Entity;

	/*
	for( unsigned i = 0; i < components.size(); i++ ) {			
				Component* component = components[ i ];
				entity->addComponent( component->clone() ); 		
	}

	for( unsigned i = 0; i < children.size(); i++ ) {			
				Entity* child = children[ i ];
				entity->addChild( child->clone() ); 		
	}
	*/

	return entity;

}

void Entity::destroy() {

	removeAllComponents();

	if (world) {
		//world->removeEntity(this);
	}

}

void Entity::setWorld(World* world_) { 

	if (world != world_) {

		world = world_;

		for( size_t i = 0; i < components.size(); i++ ) {			
				Component* component = components[ i ];
				component->setWorld( world_);				
		}

		for (size_t i = 0; i < children.size(); i++) {
				children[i]->setWorld(world_);			
		}

	}

}

bool Entity::findComponent( Component* component ) {

	for (size_t i = 0; i < components.size(); i++) {

		if( components.find( component) ) return true;
	}

	return false;

}

void Entity::addComponent( Component* component ) {

	check( component->getEntity() == NULL );

	
	for( unsigned i = 0; i < components.size(); i++ ) {			
			//if( strcmp( typeName, components[ i ]->getTypeName() ) == 0 ) return;
	}

	components.add( component );
	component->attachEntity( this );

	for( size_t i = 0; i < listeners.size(); i++ ) {
			listeners[i]->onAddComponent(this, component);
	}

	if(world) {
		component->setWorld(world);
	}

}

void Entity::removeComponent( Component* component ) {

	for( size_t i = 0; i < listeners.size(); i++ ) {
		listeners[i]->onRemoveComponent(this, component);
	}
	
	component->detachEntity( this );

	component->setWorld(NULL);

}

void Entity::removeAllComponents() {

	DynamicArray<ComponentRef> components2 = components;

	for( size_t i = 0; i < components2.size(); i++ ) {					
		removeComponent(components2[i]);

	}

	components.clear();

}

void Entity::addChild( Entity* child ) {

	check(child);

	children.add( child );

	for( size_t i = 0; i < listeners.size(); i++ ) {
		listeners[i]->onAddChild(child);
	}

	child->setParent(this);

}

void Entity::removeChild( Entity* child ) {

	const bool found = children.find(child);

	if (found) {
		
		children.remove( child );
		for( size_t i = 0; i < listeners.size(); i++ ) {
			listeners[i]->onRemoveChild(child);
		}
	}

	child->setParent(NULL);
}

bool Entity::isChild( Entity* child ) const {

	if (children.find(child)) return true;

	return false;

}

bool Entity::findRecursive(Entity* entity) const {

	if( isChild( entity ) ) return true;
	
	for( unsigned i = 0; i < children.size(); i++ ) {
		const Entity* child = children[i];
		if (child->findRecursive(entity)) return true;
	}

	return false;

}


/*
void Entity::collectAllChildren( Entities& entities ) {

	for (unsigned i = 0; i < children.size(); i++) {
			children[i]->collectAllChildren(entities);
	}

	entities.addEntity(this);

}
*/





void Entity::addListener( EntityListener* listener ) {

	std::vector<EntityListener*>::iterator it = std::find( listeners.begin(), listeners.end(), listener );

	if( it == listeners.end() ) {
			listeners.push_back( listener );
	}

}

void Entity::removeListener( EntityListener* listener ) {

	std::vector<EntityListener*>::iterator it = std::find( listeners.begin(), listeners.end(), listener );

	if( it != listeners.end() ) {
			listeners.erase( it );
	}

}


//void Entity::onComponentAdded(Component*) {}
//void Entity::onComponentRemoved(Component*) {}
//void Entity::onComponentUpdated(Component*) {}


Entity* Entity::Create() { return new Entity; }

Entity* CreateEntity() { return new Entity; }


void Entity::dump() {

	/*
	for (std::vector<ref<Entity>>::const_iterator cit = children.begin(); cit != children.end(); cit++) {

		Entity* child = *cit;
		if (child) {
			child->dump();
		}

	}
	*/

}

//void attachEntity(Entity*entity) { onEntityAttached(entity); }
///void detachEntity(Entity*entity) { onEntityDetached(entity); }

void Component::setWorld(World* newWorld) {

	if( world ) {
		onLeaveWorld();
		world->unregisterComponent(this);
	}

	world = newWorld;

	if(world) {
		world->registerComponent(this);
		onEnterWorld();
	}

}

void Component::attachEntity( Entity* entity_ ) {

	entity = entity_;
	onEntityAttached();

}

void Component::detachEntity( Entity* entity ) {

	onEntityDetached();
	entity = NULL;

}


/*
void Component::start() {

	onStart();
}

void Component::stop() {

	onStop();
}

void Component::resume() {

	onResume();
}

void Component::suspend() {

	onSuspend();
}

*/

void Component::setTimer(const Name name, float time, const bool repeat) {

	check(getEntity());
	check(getEntity()->getWorld());

	//getEntity()->getWorld()->addTimer( this, name, time, repeat );
	
}

void Component::killTimer(const Name) {

	check(getEntity());
	check(getEntity()->getWorld());

	//getEntity()->getWorld()->removeTimer(this, name);

}

void Component::killAllTimers() {

	check(getEntity());
	check(getEntity()->getWorld());

	//getEntity()->getWorld()->removeAllTimers(this);

}



void DoEntityTest() {

	ref<Entity> entity = new Entity();

}

#endif



