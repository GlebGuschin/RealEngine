#pragma once

#ifndef __HARDWARE_BUFFER_HPP__
#define __HARDWARE_BUFFER_HPP__

#include "RenderCommon.hpp"
#include "MemoryBuffer.hpp"


enum BUFFER_TYPE { BUFFER_VERTEX, BUFFER_INDEX, BUFFER_MAX };
//enum INDEX_TYPE { INDEX_NONE = 0, INDEX_16, INDEX_32 };





struct HardwareBufferInfo {
	size_t size;
	BUFFER_TYPE type;
};


class HardwareBuffer : public Referenced {

	HardwareBufferInfo info;

public:

	HardwareBuffer(const HardwareBufferInfo& info_) : info(info_) {}

	const HardwareBufferInfo& getInfo() const { return info; }

	virtual void update(MemoryBuffer*, size_t size_, size_t offset_) {}

};



#endif