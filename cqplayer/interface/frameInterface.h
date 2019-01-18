#pragma once

#include "baseInterface.h"
#include "type_player.h"

class frameInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual void* data() = 0;
	virtual syncpos pos() = 0;
	virtual length len() = 0;
	virtual int32_t copyfrom(frameInterface* framePtr) = 0;
};

class frameConfInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t setPos(syncpos pos) = 0;
	virtual int32_t setLen(length len) = 0;
};
