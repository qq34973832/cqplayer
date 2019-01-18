
#include "nullrender.h"

static const int32_t qframes_limited = 5;

nullrender::nullrender(baseInterface* pOuter)
	: baseInterfaceImpl(pOuter) {

}

nullrender::~nullrender() {

}

int32_t nullrender::queryInterface(const int32_t riid, void** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(renderInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

int32_t nullrender::open() {
	return ok;
}

int32_t nullrender::push(comPtr<frameInterface> framePtr) {
	printf("nullrender::push\n");
	if (framePtr->pos() + framePtr->len() <= _pos) {
		return ok;
	}

	_frameList.push_back(framePtr);
	return ok;
}

int32_t nullrender::synchronize(syncpos pos) {
	printf("nullrender::synchronize: %f\n", pos.value());
	_pos = pos;
	return ok;
}

int32_t nullrender::close() {
	return ok;
}
