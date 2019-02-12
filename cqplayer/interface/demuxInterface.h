#pragma once

#include "renderInterface.h"
#include "type_player.h"

class demuxInterface : public baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t addRender(comPtr<renderInterface> render) = 0;
	virtual int32_t delRender(comPtr<renderInterface> render) = 0;
};
