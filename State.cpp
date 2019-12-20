#include "State.h"

State::State(const std::vector<Configuration> &configurations)
{
    for(auto const &it : configurations)
    {
        this->configurations.push_back(it);
    }
}

void State::add_configuration(const Configuration &c)
{
    configurations.push_back(c);
}

std::vector<Configuration> State::get_configurations()
{
    return configurations;
}