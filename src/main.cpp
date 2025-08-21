#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "eval.hpp"
#include "globabs.hpp"
#include "reader.hpp"
#include "types.hpp"

int main(int argc, char* argv[])
{
    std::string chars;

    // TODO parse args properly
    if (argc == 1)
    {
        std::getline(std::cin, chars);
    }
    else
    {
        printf("argc = %d\n", argc);
        // TODO read file
    }

    std::vector<Instruction> instructions;

    try
    {
        instructions = reader::readStr(chars);
    }
    catch (reader::Error err)
    {
        switch (err)
        {
            case reader::BracketEof:
            {
                printf("expected ']', found EOF\n");
                break;
            }
            case reader::NoOpenBracket:
            {
                printf("found ']' without opening '['\n");
                break;
            }
        }
        return 0;
    }

    for (auto i : instructions)
    {
        i.print(i);
    }

    uint8_t data[DATA_SIZE] = {};
    uint32_t cellPointer = 0;

    try
    {
        eval(instructions, data, cellPointer, 0, instructions.size());
    }
    catch (...)
    {
        printf("out of bounds\n");
    }

    printf("\n");

    printf("----- data [1..30] -----\n");
    for (int i = 0; i < 30; i++)
    {
        printf("%d; ", data[i]);
    }

    std::cout << std::endl;

    return 0;
}
