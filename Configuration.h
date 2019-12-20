#ifndef TYLERTURINGMACHINE_CONFIGURATION_H
#define TYLERTURINGMACHINE_CONFIGURATION_H

#include <iostream>

enum Direction
{
    L,
    R,
    N
};

struct Configuration
{
    Configuration(char read_symbol, char write_symbol, Direction move_tape,
                  std::string next_state) : read_symbol(read_symbol),
                                            write_symbol(write_symbol),
                                            move_tape(move_tape),
                                            next_state(next_state) {}

    void display_config()
    {
        std::cout << read_symbol << " " << write_symbol << " " << move_tape
            << " " << next_state << std::endl;
    }

    char read_symbol;
    char write_symbol;
    Direction move_tape;
    std::string next_state;
};

#endif //TYLERTURINGMACHINE_CONFIGURATION_H
