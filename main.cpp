#include "TuringMachine.h"

#include <iostream>

int main(int argc, char* argv[]) {
    std::string filename;

    switch(argc)
    {
        case 1:
            std::cout << "Turing Machine code file: ";
            std::cin >> filename;
            new TuringMachine(filename);
            break;
        case 2:
            new TuringMachine(argv[1]);
            break;
        case 3:
            new TuringMachine(argv[1], argv[2]);
        default:
            std::cout << "Error: Invalid arguments in command line"
                << std::endl;
            break;
    }

    return 0;
}

// TODO: start actually interacting with input tape based on states