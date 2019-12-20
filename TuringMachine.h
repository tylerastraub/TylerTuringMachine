#ifndef TYLERTURINGMACHINE_TURINGMACHINE_H
#define TYLERTURINGMACHINE_TURINGMACHINE_H

#include "State.h"
#include "InputTape.h"

#include <iostream>
#include <fstream>
#include <map>

struct Configuration;

class TuringMachine {
public:
    // separate constructors for if you want to give predetermined input
    explicit TuringMachine(const std::string &filename);
    TuringMachine(const std::string &filename, std::string input);

    void init();
    void run();

    bool build_state_map();
    void advance_past_spaces(int &index, std::string string, int line);
    void print_states();

private:
    InputTape input_tape;
    std::string input;
    std::string tm_code_filename;
    std::string final_state = "halt_error";
    // states are in map in case they have non-integer names, i.e. 1a/1b
    std::map<std::string, State> state_map;
};

#endif //TYLERTURINGMACHINE_TURINGMACHINE_H
