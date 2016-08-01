#include "stdafx.h"
#include "ModuleManager.hpp"
#include "DynamicArray.hpp"


class BaseModuleManager : public ModuleManager {

	DynamicArray<SharedPtr<Module>> modules;

public:

	Module* loadModule(const String&);
	void unloadModule(Module*);

};


Module* BaseModuleManager::loadModule(const String&) {
	return NULL;
}

void BaseModuleManager::unloadModule(Module*) {

}



ModuleManager* CreateModuleManager() { return new BaseModuleManager; }
