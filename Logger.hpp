#pragma once

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "Referenced.hpp"
#include "Common.hpp"
#include "String.hpp"

class Logger : public Referenced {

	std::wfstream  fileStream;

	void writeMessage(const String& type, const String& system, const String& message);

public:

	virtual void start(const String& fileName);
	virtual void stop();

	virtual void warning(const String& system, const String& message);
	virtual void error(const String& system, const String& message);
	virtual void info(const String& system, const String& message);

};

inline Logger* CreateLogger() { return new Logger; }


#endif






