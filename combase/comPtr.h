#pragma once

#define safe_release(p) \
	if ((p) != nullptr) { (p)->release(); (p) = nullptr; }

#define safe_assign(dst, src) \
	if ((src) != nullptr) { (src)->addRef(); (dst) = (src); }


template <class T>
class comPtr {
public:
	comPtr() : _ptr(nullptr) {
	}

	comPtr(const comPtr& v) : _ptr(nullptr) {
		safe_assign(_ptr, v._ptr);
	}

	comPtr(T* ptr) : _ptr(nullptr) {
		safe_assign(_ptr, ptr);
	}

	virtual ~comPtr() {
		safe_release(_ptr);
	}

public:
	int32_t release() {
		if (_ptr != nullptr) {
			return _ptr->release();
		}
		return 0;
	}

public:
	T** operator&() {
		return &_ptr;
	}

	T* operator->() {
		return _ptr;
	}

	comPtr<T> operator=(const comPtr& v) {
		return this->operator=(v._ptr);
	}

	comPtr<T> operator=(T* ptr) {

		safe_release(_ptr);
		safe_assign(_ptr, ptr);

		return comPtr<T>(_ptr);
	}

	bool operator==(const comPtr& v) const {
		return this->operator==(v._ptr);
	}

	bool operator==(const T* ptr) const {
		return _ptr == ptr;
	}

	bool operator!=(const comPtr& v) const {
		return this->operator!=(v._ptr);
	}

	bool operator!=(const T* ptr) const {
		return _ptr != ptr;
	}

private:
	T* _ptr;
};
