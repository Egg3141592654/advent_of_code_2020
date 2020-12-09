#pragma once

#include <set>
#include <string>
#include <vector>

namespace day8 {
    enum Command { JUMP, ACCUMULATE, NOP};

    struct ProgramState {
        int accumulator;
        int line_number;
        int affected_value;
        Command command;
    };

    int fix_program_and_get_final_accumulator_value();
    int detect_last_accumulator_value_before_loop();
}