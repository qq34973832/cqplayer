#pragma once

#include <stdint.h>

#define succeeded(err)	((err) >= 0)
#define failed(err)		((err) < 0)


#define ok			0
#define error		0x80000000

#define invalidarg	0x80000001
#define notimpl		0x80000002

#define outofmem	0x80000003
