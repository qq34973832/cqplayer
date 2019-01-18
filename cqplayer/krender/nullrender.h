#pragma once

#include "renderInterface.h"

#include <list>

class nullrender
	: public baseInterfaceImpl
	, public renderInterface {
public:
	nullrender(baseInterface* pOuter);
	virtual ~nullrender();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// renderInterface
	virtual int32_t open() override;
	virtual int32_t push(comPtr<frameInterface> framePtr) override;
	virtual int32_t synchronize(syncpos pos) override;
	virtual int32_t close() override;

private:
	syncpos _pos;
	std::list<comPtr<frameInterface>> _frameList;
};
