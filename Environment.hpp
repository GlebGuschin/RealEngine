#pragma once

#ifndef __ENV_HPP__
#define __ENV_HPP__


#include "DynamicArray.hpp"
#include "Name.hpp"
#include "Logger.hpp"
//#include "RenderModuler.hpp"




class EnvVarSection : public Referenced {


};

class EnvVarValue {

public:

	EnvVarValue() {}
	EnvVarValue(const String&) {}

};


class Environment : public Referenced {

public:

	virtual	Logger* getLogger() const=0; 


	virtual  bool getVar(const Name& section, const Name& name, String& value) const;
	virtual  void setVar(const Name& section, const Name& name, const String& value);

	static Environment* Get();

};

Environment* GetEnvironment();


#endif