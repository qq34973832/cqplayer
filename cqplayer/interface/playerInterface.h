#pragma once

#include "sourceInterface.h"
#include "renderInterface.h"

class playerInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t open(comPtr<sourceInterface> source, comPtr<renderInterface> render) = 0;
	virtual int32_t play(bool reversePlay) = 0;
	virtual int32_t pause() = 0;
	virtual int32_t stop() = 0;
	virtual int32_t close() = 0;
};