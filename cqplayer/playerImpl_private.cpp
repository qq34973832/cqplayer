
#include "playerImpl.h"

#include "nullrender.h"
#include "colorbar.h"
#include "clocksource.h"

#include "coCreate.h"

int32_t playerImpl::initparams() {
	int32_t ret = ok;

	_source = coCreate<colorbar, sourceInterface>(nullptr, &ret);
	_render = coCreate<nullrender, renderInterface>(nullptr, &ret);
	_clock = coCreate<clocksource, clockInterface>(nullptr, &ret);

	return ret;
}

void playerImpl::resetFrameQ() {
	_qframes = std::queue<comPtr<frameInterface>>();
}

int32_t playerImpl::installSource(comPtr<sourceInterface> source) {
	int32_t ret = ok;

	if (source != nullptr) {
		_source = source;
	}
	ret = _source->open();
	return ret;
}

void playerImpl::uninstallSource() {
	int32_t err = ok;
	_source->close();
	_source = coCreate<colorbar, sourceInterface>(nullptr, &err);
}

int32_t playerImpl::installRender(comPtr<renderInterface> render) {
	int32_t ret = ok;

	if (render != nullptr) {
		_render = render;
	}
	ret = _render->open();
	return ret;
}

void playerImpl::uninstallRender() {
	int32_t err = ok;
	_render->close();
	_render = coCreate<nullrender, renderInterface>(nullptr, &err);
}
