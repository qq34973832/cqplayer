#pragma once

#include "baseInterface.h"
#include "type_player.h"

class stateInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual playerState state() = 0;
	virtual fraction progress() = 0;
};