#include <cstdio>
#include <string>
#include <vector>

#include "types.hpp"

std::vector<Instruction> readStr(std::string str)
{
    std::string chars = str;
    chars.push_back(0);

    std::vector<Instruction> instructions;

    char lastChar = 0;
    int rep = 0;

    std::vector<Loop> pendingLoops;
    int pendingLoopOffset = 0;

    for (int i = 0; i <= chars.length(); i++)
    {
        char currentChar = chars[i];

        if (i == 0)
        {
            lastChar = currentChar;
            continue;
        }

        if (chars[i] == lastChar && i < chars.length() - 1)
        {
            rep++;
            lastChar = currentChar;
            continue;
        }

        rep++;
        Instruction tmp;

        switch (lastChar)
        {
            case '+':
            {
                tmp.ast = Ast::Add;
                break;
            }
            case '-':
            {
                tmp.ast = Ast::Sub;
                break;
            }
            case '<':
            {
                tmp.ast = Ast::Prev;
                break;
            }
            case '>':
            {
                tmp.ast = Ast::Next;
                break;
            }
            case '.':
            {
                tmp.ast = Ast::Print;
                break;
            }
            case ',':
            {
                tmp.ast = Ast::Input;
                break;
            }
            case '[':
            {
                pendingLoops.push_back(
                    {static_cast<int>(instructions.size()), 0});

                rep = 0;
                lastChar = currentChar;

                for (int i = 0; i < pendingLoops.size(); i++)
                {
                    pendingLoops[i].len++;
                }
                continue;
            }
            case ']':
            {
                Loop l = pendingLoops.front();
                // pop oldest
                pendingLoops.erase(pendingLoops.begin());

                tmp.ast = Ast::LoopBegin;
                tmp.loopLen = l.len;

                rep = 0;
                lastChar = currentChar;

                instructions.insert(
                    instructions.begin() + l.pos + pendingLoopOffset, tmp);
                pendingLoopOffset++;

                continue;
            }
            default:
            {
                rep = 0;
                lastChar = currentChar;
                continue;
            }
        }

        for (int i = 0; i < pendingLoops.size(); i++)
        {
            pendingLoops[i].len++;
        }

        tmp.repeat = rep;

        lastChar = currentChar;
        rep = 0;
        instructions.push_back(tmp);
    }

    return instructions;
}
