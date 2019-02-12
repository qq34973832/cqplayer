#pragma once

#include "muxInterface.h"
#include "ctrlInterface.h"
#include "sourceInterface.h"

#include <vector>
#include <mutex>

class muxSource
	: public baseInterfaceImpl
	, public muxInterface
	, public sourceInterface
	, public ctrlInterface {
public:
	muxSource(baseInterface* pOuter);
	virtual ~muxSource();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// muxInterface
	virtual int32_t addSource(comPtr<sourceInterface> source) override;
	virtual int32_t delSource(comPtr<sourceInterface> source) override;

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
	std::mutex _muxMutex;

	const framerate _fps = 25;

	int32_t _currentSourceIdx;
	std::vector<comPtr<sourceInterface>> _sources;
};
