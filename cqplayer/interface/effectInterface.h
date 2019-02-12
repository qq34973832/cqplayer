#pragma once

#include "sourceInterface.h"
#include "type_player.h"

class effectInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t attachSource(comPtr<sourceInterface> source) = 0;
	virtual int32_t detachSource() = 0;
};