#pragma once

#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Transform.hpp"

class Entity;
class Component;
class World;



class WorldListener : public Listener {

public:

	virtual void onSpawnEntity(Entity*) = 0;
	virtual void onDestroyEntity(Entity*) = 0;
	///virtual void onWorldTicked(float timeDelta) {}

};

class EntityListener : public Listener {

public:

	virtual void onAddComponent( Entity*, Component* ) = 0;
	virtual void onRemoveComponent( Entity*, Component* ) = 0;
	virtual void onUpdateComponent( Entity*, Component*) = 0;

	virtual void onAddChild(Entity*) = 0;
	virtual void onRemoveChild(Entity*) = 0;

	//virtual void onPreDestroy() {}

};

class ComponentListener : public Listener {
public:
	virtual void onUpdateComponent() = 0;
};








//class Component : public Object, public EntityListener, public WorldListener {

class Component : public Referenced {

	//CLASS(Component,Object)

	bool enabled;
	bool unique;

	Name group;
	Name name;

	friend class Entity;

protected:

public:

	Component() {}	
	//Component(const Name& group_) : world(NULL), entity(NULL), group(group_){}
	~Component() {}

	//virtual Entity* getEntity() const { return entity; }
	virtual Entity* getEntity() const = 0;

	virtual void setWorld(World* newWorld)=0;
	virtual World* getWorld() const=0;

	void setName(const Name name_) { name = name_; }
	const Name& getName() const { return name; }

	const Name& getGroup() const { return group; }
	bool isUnique() const { return unique; }

	virtual void enable() = 0;
	virtual void disable();
	virtual bool isEnabled() const;
	
	virtual void update(const TimeUpdate&) {}
	
	friend class Entity;

	
protected:

	/*
	void attachEntity(Entity*entity);
	void detachEntity(Entity*entity);

	void setTimer(const Name name, const float time, const bool repeat = false);
	void killTimer(const Name name);
	void killAllTimers();
	*/

	// entity listener 
	/*
	void onComponentAdded(Component*) {}
	void onComponentRemoved(Component*) {}
	void onComponentUpdated(Component*) {}
	void onChildAdded(Entity*) {}
	void onChildRemoved(Entity*) {}
	*/

	//world listener	
	/*
	void onSpawnEntity(Entity*) {};
	void onDestroyEntity(Entity*) {};
	*/
	
	//friend class Entity;
	//friend class World;

};

typedef SharedPtr<Component>  ComponentSmartPtr;



#endif