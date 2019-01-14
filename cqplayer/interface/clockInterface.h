#pragma once

#include "baseInterface.h"
#include "type_player.h"

class clockInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual syncpos now() = 0;
	virtual syncpos reset(syncpos pos) = 0;
	virtual syncpos pause() = 0;
	virtual syncpos resume() = 0;
};
