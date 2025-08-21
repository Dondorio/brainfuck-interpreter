#pragma once

#include <cstdint>
#include <vector>

#include "types.hpp"

void eval(std::vector<Instruction> instructions, uint8_t data[],
          uint32_t &cellPointer, uint32_t sliceBegin, uint32_t sliceEnd);
