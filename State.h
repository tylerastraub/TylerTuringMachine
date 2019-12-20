#ifndef TYLERTURINGMACHINE_STATE_H
#define TYLERTURINGMACHINE_STATE_H

#include "Configuration.h"

#include <string>
#include <vector>

class State {
public:
    State() = default;
    explicit State(const std::vector<Configuration> &configurations);

    void add_configuration(const Configuration &c);

    std::vector<Configuration> get_configurations();

private:
    std::vector<Configuration> configurations;
};

#endif //TYLERTURINGMACHINE_STATE_H
