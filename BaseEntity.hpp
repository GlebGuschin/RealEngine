#pragma once

#ifndef __BASE_ENTITY_HPP__
#define __BASE_ENTITY_HPP__

#include "Entity.hpp"
#include "BaseWorld.hpp"


class BaseEntity : public Entity {
		
	DynamicArray<SharedPtr<Component>> components;
	DynamicArray<SharedPtr<Entity>> children;
	SharedPtr<Entity> parent;

	Name name;

	std::vector<EntityListener*> listeners;

	World* world;

	void setParent(Entity* parent);

	friend class World;
	Transform transform;
	
public:

	BaseEntity();
	~BaseEntity();

	void setName( Name name_) { name = name_; }
	Name getName() const { return name; }

	//void dump();
	//Entity* clone() const;
	//void destroy();

	unsigned getNumComponents() const { return components.size(); }
	Component* getComponent(unsigned index) const { return components[ index ]; }
	void addComponent(Component*);
	void removeComponent(Component*);
	//virtual void removeAllComponents();
	//virtual bool findComponent(Component*);
	//virtual void replaceComponent(Component*, Component*);


	virtual Entity* getParent() const { return parent; }
	//bool isBase() const;

	void addChild(Entity*);
	void removeChild(Entity*);
	bool isChild(Entity*) const;
	bool findRecursive(Entity*) const;

	size_t getNumChildren() const { return children.size(); }
	Entity* getChild(size_t index) const { return children[index]; }

	//void collectAllChildren(Entities&);


	// Entity listener
	void onAddComponent(Entity*, Component*) {}
	void onRemoveComponent(Entity*, Component*){}
	void onUpdateComponent(Entity*, Component*) {}
	void onAddChild(Entity*) {}
	void onRemoveChild(Entity*) {}


	void addListener(EntityListener*);
	void removeListener(EntityListener*);


	void setTransform(const Transform& transform_) { transform = transform_; }
	const Transform& getTransform() const { return transform; };


	/*
	void setLocation(const Vector3&);
	Vector3& getLocation() const;
	void setRotation(const Quaternion&);
	Quaternion& getRotation() const;
	*/


	World* getWorld() const { return world; }

protected:

	void setWorld(World* world_);

public:

	static Entity* Create();
};

Entity* CreateEntity();

typedef SharedPtr<Entity> EntityRef;


/*
class EntityManager : public Referenced {

public:
	virtual Entity* createEntity() { return NULL; }
};
*/


#endif