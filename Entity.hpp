#pragma once

#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "Component.hpp"
#include "DynamicArray.hpp"

class Entity : public EntityListener {

	//DECLARE_CLASS(Entity,Object)

	/*
	DynamicArray<SharedPtr<Component>> components;
	DynamicArray<SharedPtr<Entity>> children;
	SharedPtr<Entity> parent;

	Name name;

	std::vector<EntityListener*> listeners;	

	World* world;

	void setParent(Entity* parent);

	friend class World;
	Transform transform;
	*/

public:

	Entity();
	~Entity();

	virtual World* getWorld() const = 0;

	//void setName( Name name_) { name = name_; }
	//Name getName() const { return name; }

	//void dump();
	//Entity* clone() const;
	//void destroy();

	virtual unsigned getNumComponents() const;
	virtual Component* getComponent(unsigned index) const;
	virtual void addComponent(Component*);
	virtual void removeComponent(Component*);
	//virtual void removeAllComponents();
	//virtual bool findComponent(Component*);
	//virtual void replaceComponent(Component*, Component*);


	
	virtual Entity* getParent() const = 0;
	//bool isBase() const;

	void addChild(Entity*);
	void removeChild(Entity*);
	bool isChild(Entity*) const;
	bool findRecursive(Entity*) const;

	virtual size_t getNumChildren() const = 0;
	virtual Entity* getChild(size_t index) const = 0;

	//void collectAllChildren(Entities&);


	// Entity listener
	void onAddComponent( Entity*, Component* ) {}
	void onRemoveComponent( Entity*, Component* ){}
	void onUpdateComponent( Entity*, Component*) {}
	void onAddChild(Entity*) {}
	void onRemoveChild(Entity*) {}


	void addListener( EntityListener* );
	void removeListener( EntityListener* );


	//void setTransform(const Transform& transform_) { transform = transform_; }
	//const Transform& getTransform() const { return transform; };
	

protected:

	void setWorld(World* world_);

public:

	static Entity* Create();
};



Entity* CreateEntity();

typedef SharedPtr<Entity> EntityRef;


class EntityManager : public Referenced {

public:

	virtual Entity* createEntity() = 0;

};


#endif