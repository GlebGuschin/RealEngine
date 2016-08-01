#pragma once

#ifndef __BASE_WORLD_HPP__
#define __BASE_WORLD_HPP__

#include "World.hpp"


class BaseWorld : public World {

	SharedPtr<Entity> root;

	//std::vector<ComponentUpdateQueueItem> componentUpdateQueue;
	//DynamicArray<ComponentSmartPtr> components;

	DynamicArray<SharedPtr<Entity>> entities;

	SharedPtr<RenderScene> renderScene;
	SharedPtr<AudioScene> audioScene;

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

	DynamicArray<SharedPtr<WorldListener>> listeners;

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

	BaseWorld();
	~BaseWorld();

	Entity* getRoot() const { return root; }
	RenderScene* getRenderScene() const { return renderScene; }
	AudioScene* getAudioScene() const { return audioScene; }

	void addListener(WorldListener*, unsigned priority = 0);
	void removeListener(WorldListener*);


	bool spawnEntity(Entity* entity, Entity* owner = NULL);
	void destroyEntity(Entity* entity);

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