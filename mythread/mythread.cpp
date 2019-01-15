
#include "mythread.h"

#include "errorDef.h"

#include <assert.h>
#include <functional>
#include <chrono>

#define DEFAULT_INTERVALS	2
#define SUSPENDED_INTERVALS	5000

mythread::mythread()
	: _mutex()
	, _cond()
	, _stop(false)
	, _suspended(true)
	, _intervals(SUSPENDED_INTERVALS) {
	this->swap(std::thread(std::bind(&mythread::threadProc, this)));
}

mythread::~mythread() {
	assert(_stop && !_suspended);
}

int32_t mythread::resume() {
	std::unique_lock<std::mutex> lck(_mutex);
	_intervals = DEFAULT_INTERVALS;
	_suspended = false;
	_cond.notify_one();
	return ok;
}

int32_t mythread::suspend() {
	std::unique_lock<std::mutex> lck(_mutex);
	_intervals = SUSPENDED_INTERVALS;
	_suspended = true;
	return ok;
}

int32_t mythread::finish() {

	if (this->joinable()) {
		{
			std::unique_lock<std::mutex> lck(_mutex);
			_suspended = false;
			_stop = true;
			_cond.notify_one();
		};
		this->join();
	}

	return int32_t();
}

bool mythread::is_suspended() const {
	return _suspended;
}

void mythread::threadProc() {
	while (true) {
		std::unique_lock<std::mutex> lck(_mutex);
		_cond.wait_for(lck, std::chrono::milliseconds(_intervals), [this]() {
			return _stop && !_suspended;
		});

		if (_stop) {
			break;
		} else if (_suspended) {
			continue;
		}

		this->_1step();
	}
}
