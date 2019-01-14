#pragma once

#include "baseInterface.h"
#include "type_player.h"

class ctrlInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t rewind() = 0;
	virtual int32_t seek(syncpos pos) = 0;
	virtual int32_t forward() = 0;
	virtual int32_t backward() = 0;
};