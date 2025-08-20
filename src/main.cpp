#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "eval.hpp"
#include "reader.hpp"
#include "types.hpp"

int main()
{
    std::string chars;
    std::getline(std::cin, chars);

    std::vector<Instruction> instructions = readStr(chars);

    // for (auto i : instructions)
    // {
    //     i.print(i);
    // }

    uint8_t data[30] = {};
    uint32_t cellPointer = 0;

    eval(instructions, data, cellPointer, 0, instructions.size());

    printf("----- data [1..30] -----\n");

    for (int i = 0; i < 30; i++)
    {
        printf("%d; ", data[i]);
    }

    return 0;
}
