#include "InputTape.h"

InputTape::InputTape(std::string input)
{
    set_input(input);
    left_tape.push_back(' ');
}

char InputTape::get_value_at_head()
{
    if(head_index < 0)
    {
        int temp_index = std::abs(head_index + 1);
        while(temp_index >= left_tape.size())
        {
            left_tape.push_back(' ');
        }

        return left_tape[temp_index];
    }

    while(head_index >= right_tape.size())
    {
        right_tape.push_back(' ');
    }

    return right_tape[head_index];
}

void InputTape::set_input(std::string input)
{
    for(char i : input)
    {
        right_tape.push_back(i);
    }
}

void InputTape::write_to_head(char value)
{
    if(head_index < 0)
    {
        left_tape[std::abs(head_index + 1)] = value;
    }
    else
    {
        right_tape[head_index] = value;
    }
}

void InputTape::erase_at_head()
{
    if(head_index < 0)
    {
        left_tape[std::abs(head_index + 1)] = ' ';
    }
    else
    {
        right_tape[head_index] = ' ';
    }
}

void InputTape::move_head_right()
{
    ++head_index;
    if(head_index == right_tape.size())
    {
        right_tape.push_back(' ');
    }
}

void InputTape::move_head_left()
{
    --head_index;
    if(std::abs(head_index) == left_tape.size())
    {
        left_tape.push_back(' ');
    }
}

void InputTape::display_tape()
{
    for(int i = left_tape.size() - 1; i >= 0; --i)
    {
        std::cout << left_tape[i];
    }

    for(int i = 0; i  < right_tape.size(); ++i)
    {
        std::cout << right_tape[i];
    }

    std::cout << std::endl;

    // display arrow
    for(int i = 0; i < head_index + left_tape.size(); ++i)
    {
        std::cout << " ";
    }
    std::cout << "^" << std::endl;
}
