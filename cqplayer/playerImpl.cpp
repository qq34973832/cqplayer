
#include "playerImpl.h"

#include <assert.h>

playerImpl::playerImpl(baseInterface * pOuter)
	: baseInterfaceImpl(pOuter)
	, _state(playerState_closed)
	, _reversePlay(false)
	, _offset(0, 1)
	, _steps(0)
	, _speed(1) {
	this->initparams();
}

playerImpl::~playerImpl() {
	this->finish();
}

int32_t playerImpl::queryInterface(const int32_t riid, void ** ppv) {

	query_interface_start(riid, ppv)
		query_interface_item(playerInterface)
		query_interface_item(ctrlInterface)
		query_interface_item(speedInterface)
		query_interface_item(stateInterface)
	query_interface_end
	
	return baseInterfaceImpl::queryInterface(riid, ppv);
}

int32_t playerImpl::open(comPtr<sourceInterface> source, comPtr<renderInterface> render) {
	int32_t ret = ok;

	std::unique_lock<std::mutex> lck(_mutex);
	playerState prevState = _state.exchange(playerState_loaded);

	ret = this->installRender(render);
	ret = this->installSource(source);

	_clock->reset(0);

	return ret;
}

int32_t playerImpl::play(bool reversePlay) {
	int32_t ret = ok;

	{
		std::unique_lock<std::mutex> lck(_mutex);
		playerState prevState = _state.exchange(playerState_playing);
		assert(prevState != playerState_closed);

		_reversePlay = reversePlay;
		ret = _source->preroll(reversePlay);

		_clock->resume();
	};
	this->resume();

	return ret;
}

int32_t playerImpl::pause() {
	int32_t ret = ok;

	{
		std::unique_lock<std::mutex> lck(_mutex);
		playerState prevState = _state.exchange(playerState_paused);
		assert(prevState != playerState_closed);

		_clock->pause();
	};
	ret = this->resume();

	return ret;
}

int32_t playerImpl::stop() {
	int32_t ret = ok;

	ret = this->suspend();

	std::unique_lock<std::mutex> lck(_mutex);
	playerState prevState = _state.exchange(playerState_stopped);
	assert(prevState != playerState_closed);

	_clock->pause();

	return ret;
}

int32_t playerImpl::close() {
	int32_t ret = ok;

	ret = this->suspend();

	std::unique_lock<std::mutex> lck(_mutex);
	playerState prevState = _state.exchange(playerState_closed);

	_clock->pause();

	this->uninstallSource();
	this->uninstallRender();

	return ret;
}

int32_t playerImpl::rewind() {
	int32_t ret = ok;

	std::unique_lock<std::mutex> lck(_mutex);
	assert(_state != playerState_closed);

	_steps = 0;
	_offset = 0;

	_clock->reset(0);
	{
		comPtr<ctrlInterface> sourceCtrl;
		_source->queryInterface(interface_id(ctrlInterface), (void**)&sourceCtrl);
		assert(sourceCtrl != nullptr);

		sourceCtrl->rewind();
	}
	ret = _render->synchronize(0);

	return ret;
}

int32_t playerImpl::seek(syncpos pos) {
	int32_t ret = ok;

	std::unique_lock<std::mutex> lck(_mutex);
	assert(_state != playerState_closed);

	_steps = 0;
	_offset = pos;

	_clock->reset(pos);
	{
		comPtr<ctrlInterface> sourceCtrl;
		_source->queryInterface(interface_id(ctrlInterface), (void**)&sourceCtrl);
		assert(sourceCtrl != nullptr);

		sourceCtrl->seek(pos);
	}
	ret = _render->synchronize(pos);

	return ret;
}

int32_t playerImpl::forward() {
	int32_t ret = ok;

	ret = this->resume();

	std::unique_lock<std::mutex> lck(_mutex);
	playerState prevState = _state.exchange(playerState_paused);
	assert(prevState != playerState_stopped
		&& prevState != playerState_closed);

	_clock->pause();
	_clock->reset(0);

	_steps += 1;
	_offset += 1;
	{
		comPtr<ctrlInterface> sourceCtrl;
		_source->queryInterface(interface_id(ctrlInterface), (void**)&sourceCtrl);
		assert(sourceCtrl != nullptr);

		sourceCtrl->forward();
	}

	return ret;
}

int32_t playerImpl::backward() {
	int32_t ret = ok;

	ret = this->resume();

	std::unique_lock<std::mutex> lck(_mutex);
	playerState prevState = _state.exchange(playerState_paused);
	assert(prevState != playerState_stopped
		&& prevState != playerState_closed);

	_clock->pause();
	_clock->reset(0);

	_steps += 1;
	_offset -= 1;
	{
		comPtr<ctrlInterface> sourceCtrl;
		_source->queryInterface(interface_id(ctrlInterface), (void**)&sourceCtrl);
		assert(sourceCtrl != nullptr);

		sourceCtrl->backward();
	}

	return ret;
}

int32_t playerImpl::speed(shiftrate r) {
	int32_t ret = ok;

	std::unique_lock<std::mutex> lck(_mutex);
	_speed = r;

	return ret;
}

playerState playerImpl::state() {

	std::unique_lock<std::mutex> lck(_mutex);
	return _state;
}

fraction playerImpl::progress() {
	length len = _source->len();
	fraction ret(_offset / len);
	return ret;
}

