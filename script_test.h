#pragma once
#include "Commons.h"
#include "ScriptBase.h"
#include "EntityEnums.h"

#define D2C(x) x & 0x000000ff, (x & 0x0000ff00) >> 8, (x & 0x00ff0000) >> 16, (x & 0xff000000) >> 24

static constant testingaaa[] {
	PUSHC, 20.0f
};
