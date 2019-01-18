#pragma once

#include "ctrlInterface.h"
#include "sourceInterface.h"

class colorbar
	: public baseInterfaceImpl
	, public sourceInterface
	, public ctrlInterface {
public:
	colorbar(baseInterface* pOuter);
	virtual ~colorbar();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// sourceInterface
	virtual framerate fps() override;
	virtual length len() override;

	virtual int32_t open() override;
	virtual int32_t preroll(bool reversePlay) override;
	virtual comPtr<frameInterface> pop(int32_t waitms) override;
	virtual int32_t close() override;

private:
	// ctrlInterface
	virtual int32_t rewind() override;
	virtual int32_t seek(syncpos pos) override;
	virtual int32_t forward() override;
	virtual int32_t backward() override;

private:
	comPtr<frameInterface> generateFrame();
	int32_t fillFrame(comPtr<frameInterface> frame);

private:
	const framerate _fps = 25;
	syncpos _pos;
};
