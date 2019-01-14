#pragma once

#include "baseInterface.h"
#include "type_player.h"

class speedInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t speed(shiftrate r) = 0;
};