#include "TuringMachine.h"

TuringMachine::TuringMachine(const std::string &filename)
{
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Input: ";
    std::cin >> input;
    std::cout << std::endl;

    tm_code_filename = filename;
    init();
}

TuringMachine::TuringMachine(const std::string &filename, std::string input) :
    input(input)
{
    tm_code_filename = filename;
    init();
}

void TuringMachine::init()
{
    State s; // placeholder state with no configurations
    state_map.emplace("halt_accept", s);
    state_map.emplace("halt_reject", s);
    state_map.emplace("halt_error", s);
    if(!build_state_map())
    {
        return;
    }
    input_tape.set_input(input);
    run();
    input_tape.display_tape();
    std::cout << final_state << std::endl;
}

void TuringMachine::run()
{
    if(!state_map.count("0"))
    {
        std::cout << "Error: No initial state (state 0)" << std::endl;
        return;
    }

    State current_state = state_map["0"];
    std::string current_state_key = "0";
    int step_counter = 0;
    while(current_state_key != "halt_accept" &&
          current_state_key != "halt_reject" &&
          current_state_key != "halt_error")
    {
        input_tape.display_tape();
        ++step_counter;

        std::vector<Configuration> configs = current_state.get_configurations();
        char current_char = input_tape.get_value_at_head();
        if(current_char == ' ') current_char = '_';
        Configuration instruction('*', '*', R, "halt_error");
        Configuration final_config('a','a', N, "a"); // use this for if a config reads *
        for(const Configuration c : configs)
        {
            // by default will read the first config that reads the right symbol
            if(current_char == c.read_symbol)
            {
                instruction = c;
                break;
            }

            if(c.read_symbol == '*')
            {
                final_config = c;
            }
        }

        if(final_config.read_symbol == '*' &&
           instruction.next_state == "halt_error")
        {
            instruction = final_config;
        }

        // if no configs read the current_char, we end the program
        if(instruction.next_state == "halt_error")
        {
            std::cout << "Error: Unhandled case for symbol " << current_char
                << " in state " << current_state_key << std::endl;
            return;
        }

        // valid config, now we follow its instructions
        switch(instruction.write_symbol)
        {
            case '_':
                input_tape.erase_at_head();
                break;
            case '*':
                break;
            default:
                input_tape.write_to_head(instruction.write_symbol);
                break;
        }

        if(instruction.move_tape == L)
        {
            input_tape.move_head_left();
        }
        else if(instruction.move_tape == R)
        {
            input_tape.move_head_right();
        }

        if(!state_map.count(instruction.next_state))
        {
            std::cout << "Error: Invalid next state in state "
                << current_state_key << ". Invalid state: "
                << instruction.next_state << std::endl;
            final_state = "halt_error";
            return;
        }

        current_state = state_map[instruction.next_state];
        current_state_key = instruction.next_state;
    }

    final_state = current_state_key;
    std::cout << std::endl << "Steps: " << step_counter << std::endl;
}

// takes file and translates all states into the state_map member
// returns true if no errors in building state map
bool TuringMachine::build_state_map() {
    std::ifstream tm_code_file;
    std::string current_line;

    tm_code_file.open(tm_code_filename);
    if(tm_code_file)
    {
        int line_count = 1;
        while(std::getline(tm_code_file, current_line))
        {
            if(!current_line.empty() && current_line[0] != ';')
            {
                int index = 0; // our place in the line
                std::string state;
                char read_symbol, write_symbol;
                Direction dir;
                std::string next_state; // string because we store it in map
                // skip possible spaces at start
                advance_past_spaces(index, current_line, line_count);
                // determine state
                while(current_line[index] != ' ')
                {
                    state += current_line[index];
                    ++index;
                }
                advance_past_spaces(index, current_line, line_count);

                // determine read/write symbols
                read_symbol = current_line[index];
                ++index;
                advance_past_spaces(index, current_line, line_count);
                write_symbol = current_line[index];
                ++index;
                advance_past_spaces(index, current_line, line_count);

                // determine direction to move head
                if(current_line[index] == 'L' ||
                   current_line[index] == 'l')
                {
                    dir = L;
                    ++index;
                }
                else if(current_line[index] == 'R' ||
                        current_line[index] == 'r')
                {
                    dir = R;
                    ++index;
                }
                else if(current_line[index] == '*')
                {
                    dir = N;
                    ++index;
                }
                else
                {
                    std::cout << "Error: Invalid direction for configuration on"
                              << " line " << line_count << std::endl;
                    return false;
                }
                advance_past_spaces(index, current_line, line_count);

                // determine next state
                while(current_line[index] != ' ' && index < current_line.size())
                {
                    next_state += current_line[index];
                    ++index;
                }

                // add configuration to state in state map
                Configuration c(read_symbol, write_symbol, dir, next_state);
                if(state_map.count(state))
                {
                    state_map[state].add_configuration(c);
                }
                else
                {
                    State s;
                    s.add_configuration(c);
                    state_map.emplace(state, s);
                }
            }

            ++line_count;
        }
    }
    else
    {
        std::cout << "Error: Could not open file or file does not exist"
            << std::endl;
        return false;
    }

    return true;
}

void TuringMachine::advance_past_spaces(int& index, std::string string, int line)
{
    while(string[index] == ' ')
    {
        ++index;
        if(index >= string.size())
        {
            std::cout << "Error: Invalid configuration on line " << line
                << std::endl;
        }
    }
}

// purely for debugging - prints all states and their configurations
void TuringMachine::print_states()
{
    std::cout << "CONFIGURATIONS:" << std::endl;
    for(auto it : state_map)
    {
        std::vector<Configuration> c = it.second.get_configurations();
        std::cout << "State " << it.first << ":" << std::endl;
        for(const auto ij : c)
        {
            std::cout << ij.read_symbol << " " << ij.write_symbol << " "
                      << ij.move_tape << " " << ij.next_state << std::endl;
        }
    }
}
