#pragma once

#include "frameInterface.h"

class renderInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t open() = 0;
	virtual int32_t push(comPtr<frameInterface> framePtr) = 0;
	virtual int32_t synchronize(syncpos pos) = 0;
	virtual int32_t close() = 0;
};