#pragma once

#include <stdint.h>
#include "errors.h"


_ERRNO_T machineInit(size_t memSize);
_ERRNO_T machineRun();
void machineDestroy();

