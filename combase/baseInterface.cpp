#include "baseInterface.h"

const int32_t genInterfaceId() {
	static std::atomic<int32_t> last_valid_interface_id = 0x00008000;
	return last_valid_interface_id++;
}

implement_interface_id(baseInterface);

baseInterfaceImpl::baseInterfaceImpl(baseInterface* pOuter)
	: m_nRef(0)
	, m_pOuter(pOuter) {
}

baseInterfaceImpl::~baseInterfaceImpl() {}

int32_t baseInterfaceImpl::addRef() {
	int ret = 0;

	if (m_pOuter != nullptr) {
		ret = m_pOuter->addRef();
	} else {
		ret = m_nRef.fetch_add(1) + 1;
	}
	return ret;
}

int32_t baseInterfaceImpl::queryInterface(const int32_t riid, void** ppv) {
	if (nullptr != m_pOuter) {
		return m_pOuter->queryInterface(interface_id, ppv);
	}

	query_interface_start(riid, ppv)
		query_interface_item(baseInterface)
	query_interface_end

	return notimpl;
}

int32_t baseInterfaceImpl::release() {
	int32_t ret = 0;

	if (nullptr != m_pOuter) {
		ret = m_pOuter->release();
	} else if (1 == m_nRef.fetch_sub(1)) {
		delete this;
		ret = 0;
	} else {
		ret = m_nRef;
	}
	return ret;
}
