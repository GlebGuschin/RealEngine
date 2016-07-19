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
