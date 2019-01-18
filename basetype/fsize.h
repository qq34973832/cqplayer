#pragma once

#include <stdint.h>
#include <assert.h>

template<typename t0, typename vt>
class fsize {
public:
	fsize() : _w(0), _h(0) {
	}
	fsize(t0 v) : _w(v), _h(v) {
	}
	fsize(t0 w, t0 h) : _w(w), _h(h) {
	}
	fsize(const fsize& v) : _w(v._w), _h(v._h) {
	}
	virtual ~fsize() {
		_w = 0; _h = 0;
	}

public:
	t0 w() const {
		return _w;
	}

	t0 h() const {
		return _h;
	}

#define x w
#define y h

	vt value() {
		return _w * _h;
	}

public:
	fsize operator+(const t0 v) {
		fsize ret(*this);
		ret._w += v;
		ret._h += v;
		return ret;
	}
	fsize operator+(const fsize& v) {
		fsize ret(*this);
		ret._w += v._w;
		ret._h += v._h;
		return ret;
	}
	fsize operator++() {
		_w += 1;
		_h += 1;
		return *this;
	}
	fsize operator-(const t0 v) {
		fsize ret(*this);
		ret._w -= v;
		ret._h -= v;
		return ret;
	}
	fsize operator-(const fsize& v) {
		fsize ret(*this);
		ret._w -= v._w;
		ret._h -= v._h;
		return ret;
	}
	fsize operator--() {
		_w -= 1;
		_h -= 1;
		return *this;
	}
	fsize operator*(const t0 v) {
		fsize ret(*this);
		ret._w *= v;
		ret._h *= v;
		return ret;
	}
	fsize operator*(const fsize& v) {
		fsize ret(*this);
		ret._w *= v._w;
		ret._h *= v._h;
		return ret;
	}
	fsize operator/(const t0 v) {
		fsize ret(*this);
		ret._w /= v;
		ret._h /= v;
		return ret;
	}
	fsize operator/(const fsize& v) {
		fsize ret(*this);
		ret._w /= v._w;
		ret._h /= v._h;
		return ret;
	}
	fsize operator+=(const t0 v) {
		_w += v;
		_h += v;
		return *this;
	}
	fsize operator+=(const fsize& v) {
		_w += v._w;
		_h += v._h;
		return *this;
	}
	fsize operator-=(const t0 v) {
		_w -= v;
		_h -= v;
		return *this;
	}
	fsize operator-=(const fsize& v) {
		_w -= v._w;
		_h -= v._h;
		return *this;
	}
	fsize operator*=(const t0 v) {
		_w *= v;
		_h *= v;
		return *this;
	}
	fsize operator*=(const fsize& v) {
		_w *= v._w;
		_h *= v._h;
		return *this;
	}
	fsize operator/=(const t0 v) {
		_w /= v;
		_h /= v;
		return *this;
	}
	fsize operator/=(const fsize& v) {
		_w /= v._w;
		_h /= v._h;
		return *this;
	}
	fsize operator=(const t0 v) {
		_w = v;
		_h = v;
		return *this;
	}
	fsize operator=(const fsize& v) {
		_w = v._w;
		_h = v._h;
		return *this;
	}

public:
	bool operator==(const t0 v) {
		return _w == v && _h == v;
	}
	bool operator==(const fsize& v) {
		return _w * v._w == _h * v._h;
	}
	bool operator!=(const t0 v) {
		return _w != v || _h != v;
	}
	bool operator!=(const fsize& v) {
		return _w != v._w || _h != v._h;
	}
	bool operator>(const t0 v) {
		return _w * _h > v;
	}
	bool operator>(const fratio& v) {
		return _w * _h > v._w * v._h;
	}
	bool operator>=(const t0 v) {
		return _w * _h >= v;
	}
	bool operator>=(const fratio& v) {
		return _w * _h >= v._w * v._h;
	}
	bool operator<(const t0 v) {
		return _w * _h < v;
	}
	bool operator<(const fratio& v) {
		return _w * _h < v._w * v._h;
	}
	bool operator<=(const t0 v) {
		return _w * _h <= v;
	}
	bool operator<=(const fratio& v) {
		return _w * _h <= v._w * v._h;
	}

private:
	t0 _w, _h;
};
