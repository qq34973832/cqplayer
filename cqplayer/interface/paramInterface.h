#pragma once

#include "baseInterface.h"
#include "type_player.h"

class paramInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t getParamCount(int32_t& cnt) = 0;
	virtual int32_t getParam(int32_t idx) = 0;
	virtual int32_t setParam(int32_t idx) = 0;
};
