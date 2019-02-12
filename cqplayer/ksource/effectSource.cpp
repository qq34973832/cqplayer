
#include "effectSource.h"

#include "dummyframe.h"

#include "coCreate.h"

effectSource::effectSource(baseInterface* pOuter)
	: baseInterfaceImpl(pOuter) {

}

effectSource::~effectSource() {

}

int32_t effectSource::queryInterface(const int32_t riid, void** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(sourceInterface)
		query_interface_item(ctrlInterface)
		query_interface_item(effectInterface)
	query_interface_end

	return baseInterfaceImpl::queryInterface(riid, ppv);
}

framerate effectSource::fps() {
	return _source->fps();
}

length effectSource::len() {
	return 0;
}

int32_t effectSource::open() {
	return _source->open();
}

int32_t effectSource::preroll(bool reversePlay) {
	return _source->preroll(reversePlay);
}

comPtr<frameInterface> effectSource::pop(int32_t waitms) {
	comPtr<frameInterface> ret = _source->pop(waitms);

	{
		// do effect here
	}

	return ret;
}

int32_t effectSource::close() {
	return _source->close();
}

int32_t effectSource::rewind() {
	comPtr<ctrlInterface> ctrl;
	_source->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);
	return ctrl->rewind();
}

int32_t effectSource::seek(syncpos pos) {
	comPtr<ctrlInterface> ctrl;
	_source->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);
	return ctrl->seek(pos);
}

int32_t effectSource::forward() {
	comPtr<ctrlInterface> ctrl;
	_source->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);
	return ctrl->forward();
}

int32_t effectSource::backward() {
	comPtr<ctrlInterface> ctrl;
	_source->queryInterface(interface_id(ctrlInterface), (void**)&ctrl);
	return ctrl->backward();
}

int32_t effectSource::attachSource(comPtr<sourceInterface> source) {
	_source = source;
	return ok;
}

int32_t effectSource::detachSource() {
	_source = nullptr;
	return ok;
}
