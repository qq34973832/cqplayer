
#include "colorbar.h"

#include "dummyframe.h"

#include "coCreate.h"

colorbar::colorbar(baseInterface* pOuter)
	: baseInterfaceImpl(pOuter) {

}

colorbar::~colorbar() {

}

int32_t colorbar::queryInterface(const int32_t riid, void** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(sourceInterface)
		query_interface_item(ctrlInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

framerate colorbar::fps() {
	static const framerate _25fps = { 25, 1 };
	return _25fps;
}

length colorbar::len() {
	return 0;
}

int32_t colorbar::open() {
	return ok;
}

int32_t colorbar::preroll(bool reversePlay) {
	return ok;
}

comPtr<frameInterface> colorbar::pop(int32_t waitms) {
	comPtr<frameInterface> ret(this->generateFrame());
	this->fillFrame(ret);

	printf("colorbar::pop\n");

	return ret;
}

int32_t colorbar::close() {
	return ok;
}

int32_t colorbar::rewind() {
	int32_t ret = ok;

	return ret;
}

int32_t colorbar::seek(syncpos pos) {
	int32_t ret = ok;

	return ret;
}

int32_t colorbar::forward() {
	int32_t ret = ok;

	return ret;
}

int32_t colorbar::backward() {
	int32_t ret = ok;

	return ret;
}

comPtr<frameInterface> colorbar::generateFrame() {
	comPtr<frameInterface> ret;

	if (_cbFrame == nullptr) {
		_cbFrame = coCreate<dummyframe, frameInterface>(nullptr, nullptr);
	}
	ret = _cbFrame;

	return ret;
}

int32_t colorbar::fillFrame(comPtr<frameInterface> frame) {
	return ok;
}
