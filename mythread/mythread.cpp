
#include "mythread.h"

#include "errorDef.h"

#include <assert.h>
#include <functional>
#include <chrono>

#define SUSPENDED_INTERVALS	5000

mythread::mythread()
	: _mutex()
	, _cond()
	, _stop(false)
	, _suspended(true) {
	this->swap(std::thread(std::bind(&mythread::threadProc, this)));
}

mythread::~mythread() {
	assert(_stop && !_suspended);
}

int32_t mythread::resume() {
	std::unique_lock<std::mutex> lck(_mutex);
	_suspended = false;
	_cond.notify_one();
	return ok;
}

int32_t mythread::suspend() {
	std::unique_lock<std::mutex> lck(_mutex);
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

bool mythread::is_suspended() {
	std::unique_lock<std::mutex> lck(_mutex);
	return _suspended;
}

void mythread::threadProc() {
	while (true) {
		std::unique_lock<std::mutex> lck(_mutex);
		_cond.wait_for(lck, std::chrono::milliseconds(SUSPENDED_INTERVALS), [this]() {
			return _stop || (!_suspended && this->_nowait());
		});

		if (_stop) {
			break;
		} else if (_suspended) {
			continue;
		} else if (!this->_nowait()) {
			continue;
		}

		this->_1step();
	}
}
