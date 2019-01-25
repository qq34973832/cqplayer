#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

class mythread : public std::thread {
public:
	mythread();
	virtual ~mythread();

public:
	int32_t resume();
	int32_t suspend();
	int32_t finish();

public:
	bool is_suspended();

private:
	void threadProc();

	virtual bool _nowait() = 0;
	virtual void _1step() = 0;

protected:
	std::mutex _mutex;
	std::condition_variable _cond;

private:
	bool _stop, _suspended;
};
