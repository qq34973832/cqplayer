#pragma once

#include "playerInterface.h"
#include "ctrlInterface.h"
#include "speedInterface.h"
#include "stateInterface.h"

#include "clockInterface.h"
#include "sourceInterface.h"
#include "renderInterface.h"

#include "mythread.h"

#include <atomic>
#include <queue>

class playerImpl
	: public baseInterfaceImpl
	, public mythread
	, public playerInterface
	, public ctrlInterface
	, public speedInterface
	, public stateInterface {
public:
	playerImpl(baseInterface* pOuter);
	virtual ~playerImpl();

public:
	// baseInterface
	declare_ref_op(baseInterfaceImpl);
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;

private:
	// mythread
	virtual void _1step();

private:
	// playerInterface
	virtual int32_t open(comPtr<sourceInterface> source, comPtr<renderInterface> render) override;
	virtual int32_t play(bool reversePlay) override;
	virtual int32_t pause() override;
	virtual int32_t stop() override;
	virtual int32_t close() override;

private:
	// ctrlInterface
	virtual int32_t rewind() override;
	virtual int32_t seek(syncpos pos) override;
	virtual int32_t forward() override;
	virtual int32_t backward() override;

private:
	// speedInterface
	virtual int32_t speed(shiftrate r) override;

private:
	// stateInterface
	virtual playerState state() override;
	virtual fraction progress() override;

private:
	int32_t initparams();
	void resetFrameQ();

	int32_t installSource(comPtr<sourceInterface> source);
	void uninstallSource();
	int32_t installRender(comPtr<renderInterface> render);
	void uninstallRender();

private:
	std::atomic<playerState> _state;
	bool _reversePlay;

	syncpos _offset;
	int64_t _steps;
	shiftrate _speed;

	std::queue<comPtr<frameInterface>> _qframes;

	comPtr<sourceInterface> _source;
	comPtr<renderInterface> _render;
	comPtr<clockInterface> _clock;
};