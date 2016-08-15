#pragma once

#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "Entity.hpp"
#include "LinearMap.hpp"
#include "DynamicArray.hpp"
#include "Referenced.hpp"

#include "RenderScene.hpp"
#include "AudioScene.hpp"

class Entity;
class Component;

#include "Component.hpp"

//class RenderScene : public Object {};
//class AudioScene : public Object {};

/*
struct TimerInfo {
	float duration;
	Name name;
	SharedPtr<Component> component;
};


class EntityPSmartPtrab : public Object {

public:

};

struct EntitySpawnInfo {
	//Entity* owner;
	Vector3 position;
	Quaternion rotation;
};

struct EntityDestroyInfo {
	int i;
};

struct ComponentTimer {
	SharedPtr<Component> component;
	Name name;
	float time, currentTime;
	bool looped : 1;
	bool active : 1;
	ComponentTimer() : time(0.0f), currentTime(0.0f), looped(false), active(true) {}
};

struct ComponentUpdateQueueItem {
	SharedPtr<Component> component;
	uint8 flags;	
	ComponentUpdateQueueItem() : flags(0) {}
};

class WorldInterface {

	virtual bool spawnEntity(Entity* entity, Entity* parentEntity) =0;
	virtual bool destroyEnitity(Entity* entity)=0;

};
*/

//class World : public Object, public EntityListener {

class World : public Referenced {
	
	//std::vector<ComponentUpdateQueueItem> componentUpdateQueue;
	//DynamicArray<ComponentSmartPtr> components;


	/*
	struct WorldListenerInfo {
		SharedPtr<WorldListener> listener;
		//WorldListener* listener;
		unsigned priority;
		WorldListenerInfo() : priority(0) {}
		bool operator <(const WorldListenerInfo& info) const { return priority < info.priority; }
	};
	*/

	/*
	typedef LinearMap<SharedPtr<WorldListener>,unsigned> ListenerStorage;
	ListenerStorage listenerStorage;
	
	typedef std::vector<ComponentTimer> ComponentTimerVector;
	ComponentTimerVector  componentTimers;
	*/

protected:

	/*
	void addEntity(Entity* entity, Entity* parent = NULL);
	void removeEntity(Entity* entity);

	void cleanNonActiveTimers();
	void updateTimers(float timeDelta);

	virtual void onCreate();
	virtual void onDestroy();

	// Entity listener
	void onAddComponent(Entity*, Component*) {}
	void onRemoveComponent(Entity*, Component*){}
	void onUpdateComponent(Entity*, Component*) {}
	void onAddChild(Entity*) {}
	void onRemoveChild(Entity*) {}

	void addToUpdateQueue(Component*);
	void removeFromUpdateQueue(Component*);

	// timers 
	void addTimer(Component*, Name name, float time, bool loop = false);
	void removeTimer(Component*, Name name);
	void removeAllTimers(Component*);

	//update
	void addUpdate(Component*, uint8 flags);
	void removeUpdate(Component*);
	*/

public:

	World() {}
	~World() {}

	virtual Entity* getRoot() const { return NULL; }

	virtual RenderScene* getRenderScene() const { return NULL; }
	virtual AudioScene* getAudioScene() const { return NULL; }

	//RenderScene* getRenderScene() const { return renderScene; }
	//AudioScene* getAudioScene() const { return audioScene; }

	

	virtual void addListener(WorldListener*, unsigned priority = 0) {}
	virtual void removeListener(WorldListener*) {}


	virtual bool spawnEntity(Entity* entity, Entity* owner = NULL) = 0;
	virtual void destroyEntity(Entity* entity)=0;

	//Entity* spawnEntity( const EntitySpawnInfo&, Entity* owner = NULL );
	//void destroyEntity(Entity* entity, const EntityDestroyInfo&);

	//void registerComponent(Component*);
	//void unregisterComponent(Component*); 
	
	
	/*
	template<typename T>
	bool findComponents(DynamicArray<Component*>& array ) const {
	
		bool found = false;
		array.clear();

		for (size_t i = 0; i < components.size(); i++) {
			Component* component = components[i];
			if (dynamic_cast<T*>(component)) {
				array.add(component);
			}
		}
	
		return false;
	}
	*/
	
	
};

//class ServerWorld : public World {};
//class ClientWorld : public World {};




#endif