#pragma once

#include "fpga.h"

#ifdef __cplusplus
extern "C" {
#endif


inline uint32_t GetMs() {
    return MPS2_FPGAIO->COUNTER / 25000;
}

inline uint32_t GetUs() {
    return MPS2_FPGAIO->COUNTER / 25;
}

#ifdef __cplusplus
}
#endif