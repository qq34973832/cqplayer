#pragma once

#include "fratio.h"
#include "fsize.h"

typedef int32_t playerState;
enum {
	playerState_loaded,
	playerState_playing,
	playerState_paused,
	playerState_stopped,
	playerState_closed,
};

typedef fratio<int64_t, double> framerate;
typedef fratio<int64_t, double> shiftrate;
typedef fratio<int64_t, double> fraction;
typedef fratio<int64_t, double> syncpos;
typedef fratio<int64_t, double> length;

typedef fsize<int32_t, int64_t> resolution;

#define SECOND_100_NS	10000000

__inline syncpos ns_to_100ns(syncpos v) {
	return v / 100;
}

__inline syncpos ns_from_100ns(syncpos v) {
	return v * 100;
}

__inline syncpos s_to_100ns(syncpos v) {
	return v * SECOND_100_NS;
}

__inline syncpos s_from_100ns(syncpos v) {
	return v / SECOND_100_NS;
}
