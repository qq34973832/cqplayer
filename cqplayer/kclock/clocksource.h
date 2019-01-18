#pragma once

#include "clockInterface.h"

#include <chrono>
#include <atomic>

class clocksource
	: public baseInterfaceImpl
	, public clockInterface {
public:
	clocksource(baseInterface* pOuter);
	virtual ~clocksource();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// clockInterface
	virtual syncpos now() override;
	virtual syncpos reset(syncpos pos) override;
	virtual syncpos pause() override;
	virtual syncpos resume() override;

private:
	syncpos _pos;

	std::atomic<bool> _paused;
	std::chrono::high_resolution_clock::time_point _lastTimepoint;
};
