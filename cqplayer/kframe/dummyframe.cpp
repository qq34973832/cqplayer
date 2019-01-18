
#include "dummyframe.h"

dummyframe::dummyframe(baseInterface * pOuter)
	: baseInterfaceImpl(pOuter) {
}

dummyframe::~dummyframe() {
}

int32_t dummyframe::queryInterface(const int32_t riid, void ** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(frameInterface)
		query_interface_item(frameConfInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

void * dummyframe::data() {
	return nullptr;
}

syncpos dummyframe::pos() {
	return _pos;
}

length dummyframe::len() {
	return _len;
}

int32_t dummyframe::copyfrom(frameInterface * framePtr) {
	return int32_t();
}

int32_t dummyframe::setPos(syncpos pos) {
	_pos = pos;
	return ok;
}

int32_t dummyframe::setLen(length len) {
	_len = len;
	return ok;
}
