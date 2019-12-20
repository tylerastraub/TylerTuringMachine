#ifndef TYLERTURINGMACHINE_INPUTTAPE_H
#define TYLERTURINGMACHINE_INPUTTAPE_H

#include <vector>
#include <iostream>
#include <cmath>

class InputTape {
public:
    InputTape() = default;
    explicit InputTape(std::string input);

    char get_value_at_head();

    void set_input(std::string input);
    void write_to_head(char value);
    void erase_at_head();
    void move_head_right();
    void move_head_left();
    void display_tape();

private:
    // since tape is infinite, we have two unbound vectors to account for all
    // positive and negative indexes, where 0 is the index where the head starts
    std::vector<char> right_tape; // contains all "positive" indexes on tape
    std::vector<char> left_tape; // contains all "negative" indexes on tape
    int head_index = 0;
};

#endif //TYLERTURINGMACHINE_INPUTTAPE_H
