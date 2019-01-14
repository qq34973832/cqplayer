
#include "playerImpl.h"

static const int32_t qframes_limited = 5;

static int32_t q1frame(std::queue<comPtr<frameInterface>>& qframes, comPtr<sourceInterface> source, int32_t waitms) {
	int32_t ret = 0;
	if (qframes.size() < qframes_limited) {
		comPtr<frameInterface> framePtr = source->pop(waitms);
		if (framePtr != nullptr) {
			qframes.emplace(framePtr);
			ret = 1;
		}
	}
	return ret;
}

void playerImpl::_1step() {

	framerate fps = _source->fps();
	if (_state == playerState_paused) {
		q1frame(_qframes, _source, 0);
		return;
	} else if (_state != playerState_playing) {
		return;
	} else if (_qframes.size() <= 0) {
		q1frame(_qframes, _source, (int32_t)(1000 / fps.value()));
	}
	
	comPtr<frameInterface> framePtr = _qframes.front();
	if (framePtr != nullptr) {
		_render->push(framePtr);
		_qframes.pop();
	}

	syncpos pos = _clock->now();
	_render->synchronize(pos);
}
