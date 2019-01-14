#pragma once

#include "baseInterface.h"
#include "type_player.h"

class frameInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual void* data() = 0;
	virtual syncpos pos() = 0;
};