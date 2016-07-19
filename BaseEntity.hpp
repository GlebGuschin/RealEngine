#pragma once

#ifndef __BASE_ENTITY_HPP__
#define __BASE_ENTITY_HPP__

#include "Entity.hpp"

class BaseEntity;

class BaseEntityManager : public EntityManager {

	DynamicArray<Entity*> entities;

public:

	Entity* createEntity();
	void releaseEntity(Entity*entity);

};






class BaseEntity : public Entity {
		
	SharedPtr<BaseEntityManager> manager;

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

	BaseEntity(BaseEntityManager* manager_) : manager(manager_) {}
	~BaseEntity(){ manager->releaseEntity(this); }

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




#endif