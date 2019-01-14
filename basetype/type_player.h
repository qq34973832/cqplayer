#pragma once

#include "fratio.h"

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
