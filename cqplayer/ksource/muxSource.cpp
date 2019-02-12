
#include "muxSource.h"

#include "dummyframe.h"

#include "coCreate.h"

#include <algorithm>
#include <future>

muxSource::muxSource(baseInterface* pOuter)
	: baseInterfaceImpl(pOuter) {

}

muxSource::~muxSource() {

}

int32_t muxSource::queryInterface(const int32_t riid, void** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(muxInterface)
		query_interface_item(sourceInterface)
		query_interface_item(ctrlInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

int32_t muxSource::addSource(comPtr<sourceInterface> source) {
	std::unique_lock<std::mutex> lck(_muxMutex);
	auto found_source = std::find(_sources.begin(), _sources.end(), source);
	if (found_source == _sources.end()) {
		_sources.emplace(source);
	}
	return ok;
}

int32_t muxSource::delSource(comPtr<sourceInterface> source) {
	std::unique_lock<std::mutex> lck(_muxMutex);
	auto found_source = std::find(_sources.begin(), _sources.end(), source);
	if (found_source != _sources.end()) {
		_sources.erase(source);
	}
	return ok;
}

framerate muxSource::fps() {
	static const framerate _25fps = { 25, 1 };
	return _25fps;
}

length muxSource::len() {
	return 0;
}

int32_t muxSource::open() {

	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		v->open();
	}
	return ok;
}

int32_t muxSource::preroll(bool reversePlay) {
	std::vector<std::future<int32_t>> fut;

	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		fut.emplace(std::async(std::launch::async, [v, reversePlay]() {
			return v->preroll(reversePlay);
		}));
	}

	for (auto& v : fut) {
		v.get();
	}
	return ok;
}

comPtr<frameInterface> muxSource::pop(int32_t waitms) {
	comPtr<frameInterface> ret;

	std::unique_lock<std::mutex> lck(_muxMutex);

	if (_sources.size() > 0) {
		if (_currentSourceIdx >= _sources.size()) {
			_currentSourceIdx = 0;
		}
		ret = _sources[_currentSourceIdx]->pop(waitms);
		_currentSourceIdx++;
	}

	return ret;
}

int32_t muxSource::close() {
	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		v->close();
	}
	return ok;
}

int32_t muxSource::rewind() {
	std::vector<std::future<int32_t>> fut;

	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		fut.emplace(std::async(std::launch::async, [v]() {
			comPtr<ctrlInterface> ctrl;
			v->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);

			return ctrl->rewind();
		}));
	}

	for (auto& v : fut) {
		v.get();
	}
	return ok;
}

int32_t muxSource::seek(syncpos pos) {
	std::vector<std::future<int32_t>> fut;

	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		fut.emplace(std::async(std::launch::async, [v, pos]() {
			comPtr<ctrlInterface> ctrl;
			v->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);

			return ctrl->seek(pos);
		}));
	}

	for (auto& v : fut) {
		v.get();
	}
	return ok;
}

int32_t muxSource::forward() {
	std::vector<std::future<int32_t>> fut;

	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		fut.emplace(std::async(std::launch::async, [v]() {
			comPtr<ctrlInterface> ctrl;
			v->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);

			return ctrl->forward();
		}));
	}

	for (auto& v : fut) {
		v.get();
	}
	return ok;
}

int32_t muxSource::backward() {
	std::vector<std::future<int32_t>> fut;

	std::unique_lock<std::mutex> lck(_muxMutex);
	for (auto& v : _sources) {
		fut.emplace(std::async(std::launch::async, [v]() {
			comPtr<ctrlInterface> ctrl;
			v->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);

			return ctrl->backward();
		}));
	}

	for (auto& v : fut) {
		v.get();
	}
	return ok;
}
