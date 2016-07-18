#pragma once

#ifndef __HIB_HPP__
#define __HIB_HPP__

#include "RenderCommon.hpp"

enum INDEX_TYPE { INDEX_16, INDEX_32 };

struct HardwareIndexBufferInfo {
	INDEX_TYPE type;
	size_t size;
};


class HardwareIndexBuffer : public Referenced {
	HardwareIndexBufferInfo info;	
public:
	HardwareIndexBuffer(const HardwareIndexBufferInfo& info_) : info(info_) {}
	virtual void update( unsigned startIndex, unsigned count, MemoryBuffer* ) {}
};

inline size_t GetSize(INDEX_TYPE type ) { return type == INDEX_16 ? 2 :4; }

#endif