
#include "clocksource.h"

clocksource::clocksource(baseInterface * pOuter)
	: baseInterfaceImpl(pOuter) {
}

clocksource::~clocksource() {
}

int32_t clocksource::queryInterface(const int32_t riid, void ** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(clockInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

syncpos clocksource::now() {
	if (!_paused) {
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds diff = (now - _lastTimepoint);
		_lastTimepoint = now;
		_pos += diff.count();
	}
	return ns_to_100ns(_pos);
}

syncpos clocksource::reset(syncpos pos) {
	_lastTimepoint = std::chrono::high_resolution_clock::now();
	_pos = ns_from_100ns(pos);
	return pos;
}

syncpos clocksource::pause() {
	_pos += (std::chrono::high_resolution_clock::now() - _lastTimepoint).count();
	_paused.exchange(true);
	return ns_to_100ns(_pos);
}

syncpos clocksource::resume() {
	_lastTimepoint = std::chrono::high_resolution_clock::now();
	_paused.exchange(false);
	return ns_to_100ns(_pos);
}
