#pragma once

#include "errorDef.h"
#include "comPtr.h"

#include <atomic>

const int32_t genInterfaceId();

#define declare_interface_id \
	static const int32_t interface_id

#define implement_interface_id(interface_class) \
	const int32_t interface_class::interface_id = genInterfaceId()

#define interface_id(interface_class) \
	interface_class::interface_id

#define query_interface_start(riid, ppv) \
	{ \
		const int32_t& _riid = riid; \
		void**& _ppv = ppv;

#define query_interface_item(interface_class) \
		if (interface_id(interface_class) == _riid) { \
			((interface_class*)this)->addRef(); \
			*_ppv = static_cast<interface_class*>(this); \
			return ok; \
		}

#define query_interface_item_obj(interface_class, obj) \
		if (interface_id(interface_class) == _riid) { \
			return obj->queryInterface(_riid, _ppv); \
		}

#define query_interface_end \
	}

class baseInterface {
public:
	declare_interface_id;

public:
	virtual int32_t addRef() = 0;
	virtual int32_t queryInterface(const int32_t riid, void** ppv) = 0;
	virtual int32_t release() = 0;
};

#define declare_ref_op(base_class) \
	virtual int32_t addRef() override { \
		return base_class::addRef(); \
	} \
	virtual int32_t release() override { \
		return base_class::release(); \
	}

class baseInterfaceImpl : public baseInterface {
public:
	baseInterfaceImpl(baseInterface* pOuter);
	virtual ~baseInterfaceImpl();

public:
	virtual int32_t addRef() override;
	virtual int32_t queryInterface(const int32_t riid, void** ppv) override;
	virtual int32_t release() override;

private:
	std::atomic<int32_t> m_nRef;
	baseInterface* m_pOuter;
};
