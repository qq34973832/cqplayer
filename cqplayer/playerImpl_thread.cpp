
#include "playerImpl.h"

void playerImpl::_1step() {

	framerate fps = _source->fps();
	comPtr<frameInterface> framePtr = _source->pop((int32_t)(1000 / fps.value()));
	if (framePtr != nullptr) {
		_render->push(framePtr);
	}

	if (_state == playerState_paused) {
		return;
	}

	syncpos pos = _clock->now();
	_render->synchronize(pos);
}
