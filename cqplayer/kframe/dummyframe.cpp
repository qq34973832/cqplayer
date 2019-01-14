
#include "dummyframe.h"

dummyframe::dummyframe(baseInterface * pOuter)
	: baseInterfaceImpl(pOuter) {
}

dummyframe::~dummyframe() {
}

int32_t dummyframe::queryInterface(const int32_t riid, void ** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(frameInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

void * dummyframe::data() {
	return nullptr;
}

syncpos dummyframe::pos() {
	return int64_t();
}
