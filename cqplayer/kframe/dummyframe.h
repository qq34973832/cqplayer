#pragma once

#include "frameInterface.h"

class dummyframe
	: public baseInterfaceImpl
	, public frameInterface
	, public frameConfInterface {
public:
	dummyframe(baseInterface* pOuter);
	virtual ~dummyframe();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// frameInterface
	virtual void* data() override;
	virtual syncpos pos() override;
	virtual length len() override;
	virtual int32_t copyfrom(frameInterface* framePtr) override;

private:
	// frameConfInterface
	virtual int32_t setPos(syncpos pos) override;
	virtual int32_t setLen(length len) override;

private:
	syncpos _pos;
	length _len;
};
