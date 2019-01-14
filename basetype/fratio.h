#pragma once

#include <stdint.h>
#include <assert.h>

template<typename t0, typename vt>
class fratio {
public:
	fratio() : _num(0), _den(1) {
	}
	fratio(t0 v) : _num(v), _den(1) {
	}
	fratio(t0 num, t0 den) : _num(num), _den(den) {
		assert(_den > 0);
	}
	fratio(const fratio& v) : _num(v._num), _den(v._den) {
		assert(_den > 0);
	}
	virtual ~fratio() {
		_num = 0; _den = 1;
	}

public:
	t0 num() const {
		return _num;
	}

	t0 den() const {
		return _den;
	}

	vt value() {
		return _num / (vt)_den;
	}

public:
	fratio operator+(const t0 v) {
		fratio ret(*this);
		ret._num += v * ret._den;
		return ret;
	}
	fratio operator+(const fratio& v) {
		fratio ret(*this);
		ret._den *= v._den;
		ret._num *= v._den;
		ret._num += v._num * _den;
		return ret;
	}
	fratio operator++() {
		_num += _den;
		return *this;
	}
	fratio operator-(const t0 v) {
		fratio ret(*this);
		ret._num -= v * ret._den;
		return ret;
	}
	fratio operator-(const fratio& v) {
		fratio ret(*this);
		ret._den *= v._den;
		ret._num *= v._den;
		ret._num -= v._num * _den;
		return ret;
	}
	fratio operator--() {
		_num -= _den;
		return *this;
	}
	fratio operator*(const t0 v) {
		fratio ret(*this);
		ret._num *= v;
		return ret;
	}
	fratio operator*(const fratio& v) {
		fratio ret(*this);
		ret._num *= v._num;
		ret._den *= v._den;
		return ret;
	}
	fratio operator/(const t0 v) {
		fratio ret(*this);
		ret._den *= v;
		return ret;
	}
	fratio operator/(const fratio& v) {
		fratio ret(*this);
		ret._num *= v._den;
		ret._den *= v._num;
		return ret;
	}
	fratio operator+=(const t0 v) {
		_num += v * _den;
		return *this;
	}
	fratio operator+=(const fratio& v) {
		t0 den = _den * v._den;
		_num *= v._den;
		_num += v._num * _den;
		return *this;
	}
	fratio operator-=(const t0 v) {
		_num -= v * _den;
		return *this;
	}
	fratio operator-=(const fratio& v) {
		t0 den = _den * v._den;
		_num *= v._den;
		_num -= v._num * _den;
		return *this;
	}
	fratio operator*=(const t0 v) {
		_num *= v;
		return *this;
	}
	fratio operator*=(const fratio& v) {
		_num *= v._num;
		_den *= v._den;
		return *this;
	}
	fratio operator/=(const t0 v) {
		_den *= v;
		return *this;
	}
	fratio operator/=(const fratio& v) {
		_num *= v._den;
		_den *= v._num;
		return *this;
	}
	fratio operator=(const t0 v) {
		_num = v;
		_den = 1;
		return *this;
	}
	fratio operator=(const fratio& v) {
		_num = v._num;
		_den = v._den;
		return *this;
	}
	bool operator==(const t0 v) {
		return _num == _den * v;
	}
	bool operator!=(const fratio& v) {
		return _num * v._den == _den * v._num;
	}
	bool operator!=(const t0 v) {
		return _num != _den * v;
	}
	bool operator==(const fratio& v) {
		return _num * v._den != _den * v._num;
	}

private:
	t0 _num, _den;
};
