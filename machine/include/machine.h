#pragma once

#include <stdint.h>
#include "errors.h"


errcode_t machineInit(size_t memSize);
errcode_t machineRun();
void machineDestroy();

