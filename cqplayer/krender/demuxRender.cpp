
#include "demuxRender.h"

static const int32_t qframes_limited = 5;

demuxRender::demuxRender(baseInterface* pOuter)
	: baseInterfaceImpl(pOuter) {

}

demuxRender::~demuxRender() {

}

int32_t demuxRender::queryInterface(const int32_t riid, void** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(demuxInterface)
		query_interface_item(renderInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

int32_t demuxRender::addRender(comPtr<renderInterface> render) {
	std::unique_lock<std::mutex> lck(_demuxMutex);
	auto found_render = std::find(_renders.begin(), _renders.end(), render);
	if (found_render == _renders.end()) {
		_renders.emplace(render);
	}
	return ok;
}

int32_t demuxRender::delRender(comPtr<renderInterface> render) {
	std::unique_lock<std::mutex> lck(_demuxMutex);
	auto found_render = std::find(_renders.begin(), _renders.end(), render);
	if (found_render != _renders.end()) {
		_renders.erase(found_render);
	}
	return ok;
}

int32_t demuxRender::open() {
	std::unique_lock<std::mutex> lck(_demuxMutex);
	for (auto& v : _renders) {
		v->open();
	}
	return ok;
}

int32_t demuxRender::push(comPtr<frameInterface> framePtr) {
	std::unique_lock<std::mutex> lck(_demuxMutex);
	auto found_render = std::find(_renders.begin(), _renders.end(), [0](comPtr<renderInterface>& v) {
		return true;
	});
	if (found_render != _render.end()) {
		(*found_render)->push(framePtr);
	}
	return ok;
}

int32_t demuxRender::synchronize(syncpos pos) {
	std::unique_lock<std::mutex> lck(_demuxMutex);
	for (auto& v : _renders) {
		v->synchronize(pos);
	}
	return ok;
}

int32_t demuxRender::close() {
	std::unique_lock<std::mutex> lck(_demuxMutex);
	for (auto& v : _renders) {
		v->close();
	}
	return ok;
}
