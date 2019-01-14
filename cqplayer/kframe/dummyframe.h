#pragma once

#include "frameInterface.h"

class dummyframe
	: public baseInterfaceImpl
	, public frameInterface {
public:
	dummyframe(baseInterface* pOuter);
	virtual ~dummyframe();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

public:
	// frameInterface
	virtual void* data() override;
	virtual syncpos pos() override;

private:
	int64_t _pos;
};
