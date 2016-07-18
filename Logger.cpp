#include "stdafx.h"
#include "Logger.hpp"


//std::wfstream  Logger::FileStream;

void Logger::start(const String& fileName) {

	fileStream.open(fileName.w_str(), std::ios_base::out);
}

void Logger::stop() {
	fileStream.close();
}

void Logger::writeMessage(const String& type, const String& system, const String& message) {

	std::wstring outputString;

	outputString += L"[";
	outputString += system.w_str();
	outputString += L"]:";

	outputString += type.w_str();
	outputString += TEXT(":");

	outputString += message.w_str();


	fileStream << outputString << std::endl;

	OutputDebugStringW(outputString.c_str());
	OutputDebugStringW(L"\n");

}

void Logger::warning(const String& system, const String& message) {

	writeMessage(L"Warning", system, message);
}

void Logger::error(const String& system, const String& message) {
	writeMessage(L"Error", system, message);
}

void Logger::info(const String& system, const String& message) {
	writeMessage(L"Info", system, message);
}

