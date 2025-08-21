#include <cstdint>
#include <cstdio>
#include <vector>

#include "types.hpp"

void eval(std::vector<Instruction> instructions, uint8_t data[],
          uint32_t& cellPointer, uint32_t sliceBegin, uint32_t sliceEnd)
{
    for (uint32_t i = sliceBegin; i < sliceEnd; i++)
    {
        // printf("eval: ");
        // instructions[i].print(instructions[i]);

        switch (instructions[i].ast)
        {
            case Add:
            {
                data[cellPointer] += instructions[i].repeat;
                break;
            }
            case Sub:
            {
                data[cellPointer] -= instructions[i].repeat;
                break;
            }
            case Next:
            {
                cellPointer += instructions[i].repeat;
                break;
            }
            case Prev:
            {
                cellPointer -= instructions[i].repeat;
                break;
            }
            case LoopBegin:
            {
                int looplen = instructions[i].loopLen;
                const uint32_t loop_start_cell_pointer = cellPointer;

                // std::printf("inside loop: data = %d             \r",
                // data[loop_start_cell_pointer]);

                while (data[loop_start_cell_pointer] != 0)
                {
                    eval(instructions, data, cellPointer, i + 1, i + looplen);
                }

                // printf("exited loop\n");

                // Skip over items inside loop
                // -1 because the for loop already adds 1
                i += looplen - 1;

                break;
            }
            case Print:
            {
                // std::printf("found print!\n");
                for (int p = 0; p < instructions[i].repeat; p++)
                {
                    putchar(data[cellPointer]);
                }
                break;
            }
            case Input:
            {
                data[cellPointer] = getchar();
                break;
            }
        }
    }
}
