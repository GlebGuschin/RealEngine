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

	Entity() {}
	~Entity() {}

	//void setName( Name name_) { name = name_; }
	//Name getName() const { return name; }

	//void dump();
	//Entity* clone() const;
	//void destroy();

	virtual unsigned getNumComponents() const = 0;
	virtual Component* getComponent(unsigned index) const=0;
	virtual void addComponent(Component*)=0;
	virtual void removeComponent(Component*)=0;
	//virtual void removeAllComponents();
	//virtual bool findComponent(Component*);
	//virtual void replaceComponent(Component*, Component*);

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
			if (dynamic_cast<T*>(ptr) && ptr->getName() == name ) return (T*)ptr;
		}
		return (T*)NULL;
	}
	*/
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
	
	//virtual Entity* getParent() const { return parent; }
	//bool isBase() const;

	virtual void addChild(Entity*) =0;
	virtual void removeChild(Entity*) = 0;
	virtual bool isChild(Entity*) const = 0;
	virtual bool findRecursive(Entity*) const = 0;

	virtual size_t getNumChildren() const = 0;
	virtual Entity* getChild(unsigned index) const = 0;

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

	
	/*
	void setLocation(const Vector3&);
	Vector3& getLocation() const;
	void setRotation(const Quaternion&);
	Quaternion& getRotation() const;
	*/


	//World* getWorld() const { return world; }

protected:

	void setWorld(World* world_);

public:

	static Entity* Create();
};

Entity* CreateEntity();

typedef SharedPtr<Entity> EntityRef;


class EntityManager : public Referenced {

public:
	virtual Entity* createEntity() { return NULL; }
	virtual void releaseEntity(Entity*) {}
};

template<typename T>  T* FindComponent(Entity*entity) {
		for (uint32 i = 0; i < entity->getNumComponents(); i++) {
			Component* ptr = entity->getComponent(i);
			if (dynamic_cast<T*>(ptr)) return (T*)ptr;
		}
		return (T*)NULL;
}



#endif