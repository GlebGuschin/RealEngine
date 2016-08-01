#pragma once

#ifndef __MODULE_MANAGER_HPP__
#define __MODULE_MANAGER_HPP__

#include "Module.hpp"

class ModuleManager : public Referenced {

public:

	Module* loadModule(const String&) { return NULL; }
	void unloadModule(Module*) {  }

};


ModuleManager* CreateModuleManager();

#endif