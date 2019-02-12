#pragma once

#include "demuxInterface.h"
#include "renderInterface.h"

#include <vector>
#include <mutex>

class demuxRender
	: public baseInterfaceImpl
	, public demuxInterface
	, public renderInterface {
public:
	demuxRender(baseInterface* pOuter);
	virtual ~demuxRender();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// demuxInterface
	virtual int32_t addRender(comPtr<renderInterface> render) override;
	virtual int32_t delRender(comPtr<renderInterface> render) override;

private:
	// renderInterface
	virtual int32_t open() override;
	virtual int32_t push(comPtr<frameInterface> framePtr) override;
	virtual int32_t synchronize(syncpos pos) override;
	virtual int32_t close() override;

private:
	std::mutex _demuxMutex;
	std::vector<comPtr<renderInterface>> _renders;
};
