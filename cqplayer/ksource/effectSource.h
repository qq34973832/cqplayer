#pragma once

#include "ctrlInterface.h"
#include "sourceInterface.h"
#include "effectInterface.h"

class effectSource
	: public baseInterfaceImpl
	, public sourceInterface
	, public ctrlInterface
	, public effectInterface {
public:
	effectSource(baseInterface* pOuter);
	virtual ~effectSource();

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
	// effectInterface
	virtual int32_t attachSource(comPtr<sourceInterface> source) override;
	virtual int32_t detachSource() override;

private:
	comPtr<sourceInterface> _source;
};
