#pragma once

#include "frameInterface.h"

class sourceInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual framerate fps() = 0;
	virtual length len() = 0;

	virtual int32_t open() = 0;
	virtual int32_t preroll(bool reversePlay) = 0;
	virtual comPtr<frameInterface> pop(int32_t waitms) = 0;
	virtual int32_t close() = 0;
};