#pragma once

#ifndef __BASE_COMPONENT_HPP__
#define __BASE_COMPONENT_HPP__

#include "Component.hpp"
#include "Entity.hpp"
#include "World.hpp"


class BaseComponent : public Component {

	SharedPtr<World> world;
	SharedPtr<Entity> entity;

	bool enabled;
	bool unique;

	Name group;
	Name name;

	//friend class Entity;

protected:

public:

	BaseComponent() : world(NULL), entity(NULL) {}
	BaseComponent(const Name& group_) : world(NULL), entity(NULL), group(group_){}
	~BaseComponent() {}

	Entity* getEntity() const { return entity; }
	
	void setWorld(World* newWorld) { world = newWorld; }
	World* getWorld() const = 0 { return world; }

	void setName(const Name name_) { name = name_; }
	const Name& getName() const { return name; }

	const Name& getGroup() const { return group; }
	bool isUnique() const { return unique; }

	void enable() { enabled = true; }
	void disable() { enabled = false; }
	bool isEnabled() const { return enabled; }

	void update(const TimeUpdate&) {}

	//friend class Entity;

protected:

	virtual void onEnterWorld() {}
	virtual void onLeaveWorld() {}
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


#endif