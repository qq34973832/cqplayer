#pragma once

#include "baseInterface.h"

#define safe_set_value(p, v) \
	if ((p) != nullptr) { *(p) = v; }

#define safe_delete(p) \
	if ((p) != nullptr) { delete (p); (p) = nullptr; }

#define safe_delete_array(p) \
	if ((p) != nullptr) { delete[] (p); (p) = nullptr; }


template<class object_class, class interface_class>
comPtr<interface_class> coCreate(baseInterface* pOuter, int32_t* perr) {

	comPtr<interface_class> ret;
	int32_t err = ok;

	object_class* newObj = new object_class(pOuter);
	if (newObj != nullptr) {
		err = newObj->queryInterface(interface_id(interface_class), (void**)&ret);
	} else {
		err = outofmem;
	}

	if (failed(err)) {
		safe_delete(newObj);
	}

	safe_set_value(perr, err);

	return ret;
}
