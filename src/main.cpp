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
    // chars =
    // ">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++"
    //         "[<+++++++>-]<+ +.-- -- -- -- -- --.> ++ ++ ++[<++ ++ ++ ++ +> -
    //         ] "
    //         "< +.<.++ +.-- -- --.-- -- -- --.>>> ++ ++[<++ ++ ++ ++> - ] <
    //         +.";

    std::vector<Instruction> instructions = readStr(chars);

    for (auto i : instructions)
    {
        i.print(i);
    }

    uint8_t data[30000] = {};
    uint32_t cellPointer = 0;

    printf("evaluating\n");

    try
    {
        eval(instructions, data, cellPointer, 0, instructions.size());
    }
    catch (std::string err)
    {
        printf("catch");
        printf("%s", err.c_str());
        return 0;
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
