#pragma once

#include "sourceInterface.h"
#include "type_player.h"

class muxInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t addSource(comPtr<sourceInterface> source) = 0;
	virtual int32_t delSource(comPtr<sourceInterface> source) = 0;
};
