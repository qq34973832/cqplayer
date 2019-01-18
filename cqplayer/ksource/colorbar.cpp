
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
	comPtr<frameInterface> ret = coCreate<dummyframe, frameInterface>(nullptr, nullptr);;
	this->fillFrame(ret);

	comPtr<frameConfInterface> frameConfPtr;
	ret->queryInterface(interface_id(frameConfInterface), (void**)&frameConfPtr);

	syncpos dur = length(SECOND_100_NS) / this->fps();
	_pos += dur;
	frameConfPtr->setPos(_pos);
	frameConfPtr->setLen(dur);

	printf("colorbar::pop\n");

	return ret;
}

int32_t colorbar::close() {
	return ok;
}

int32_t colorbar::rewind() {
	int32_t ret = ok;
	_pos = 0;
	return ret;
}

int32_t colorbar::seek(syncpos pos) {
	int32_t ret = ok;
	_pos = pos;
	return ret;
}

int32_t colorbar::forward() {
	int32_t ret = ok;
	_pos += length(SECOND_100_NS) / _fps;
	return ret;
}

int32_t colorbar::backward() {
	int32_t ret = ok;
	_pos -= length(SECOND_100_NS) / _fps;
	return ret;
}

int32_t colorbar::fillFrame(comPtr<frameInterface> frame) {
	return ok;
}
