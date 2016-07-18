#include "stdafx.h"
#include "BaseEntity.hpp"

//unsigned BaseEntity::getNumComponents() const { }
//Component* BaseEntity::getComponent(unsigned index) const;

void BaseEntity::addComponent(Component* component) {

	components.add(component);

}


void BaseEntity::removeComponent(Component* component) {

	components.remove(component);

}



/*

template<typename T>  T* findComponent() {
for (uint32 i = 0; i < components.size(); i++) {
Component* ptr = components[i];
if (dynamic_cast<T*>(ptr)) return (T*)ptr;
}
return (T*)NULL;
}

template<typename T>  T* findComponent(const Name& name) {
for (uint32 i = 0; i < components.size(); i++) {
Component* ptr = components[i];
if (dynamic_cast<T*>(ptr) && ptr->getName() == name) return (T*)ptr;
}
return (T*)NULL;
}

/*
template<typename T>  T* findComponentInChildren() {
Entities entities;
collectAllChildren( entities );
for (uint32 i = 0; i < entities.getNumEntities(); i++) {
T* ptr = entities[ i ]->findComponent<T>();
if (ptr) return ptr;
}

return (T*)NULL;
}
*/

/*
template<typename T>  Components<T> findComponents() {

Components<T> container;
for (uint32 i = 0; i < components.size(); i++) {
Component* ptr = components[i];
if (dynamic_cast<T*>(ptr)) container.addComponent( (T*)ptr );
}

return container;

}

template<typename T>  void findComponents( Components<T>& container ) {
for (uint32 i = 0; i < components.size(); i++) {
Component* ptr = components[i];
if (dynamic_cast<T*>(ptr)) container.addComponent( (T*)ptr );
}
}



template<typename T>   Components<T> findComponentsInChildren() {

Components<T> container;
Entities entities;
collectAllChildren(entities);

for (uint32 i = 0; i < entities.getNumEntities(); i++) {
Components<T> container2 = entities[i]->findComponents<T>();
for (size_t i2 = 0; i2 < container2.getNumComponents(); i2++) {
container.addComponent(container2[ i2 ] );
}
}

return container;

}
*/




