#include <fstream>
#include <iostream>

#include "day8.hpp"

namespace day8 {
    int parse_command_affect(std::string line) {
        std::string affected_string = line.substr(line.find_first_of(' ') + 1);

        int affect = std::stoi(affected_string.substr(1));

        return affected_string[0] == '+' ? affect : -affect;
    }

    Command determine_line_command(std::string line) {
        auto selector = line.substr(0, 3);
        if (selector.compare("jmp") == 0) {
            return Command::JUMP;
        }
        else if (selector.compare("acc") == 0) {
            return Command::ACCUMULATE;
        }
        else {
            return Command::NOP;
        }
    }

    int execute_program_from_state(std::vector<std::string> program, ProgramState state, std::set<int> precharge) {
        std::set<int> extra_set = precharge;
        int accumulator = state.accumulator;
        int program_line = state.line_number;
        while (program_line < program.size()) {
            std::cout << "Executing line " << program_line << " with accumulator looking like: " << accumulator << std::endl;
            auto attempt = extra_set.insert(program_line);
            if (!attempt.second) {
                return -1;
            }

            auto command_type = determine_line_command(program[program_line]);

            switch (command_type) {
                case Command::JUMP:
                program_line += parse_command_affect(program[program_line]);
                break;
                case Command::ACCUMULATE:
                accumulator += parse_command_affect(program[program_line]);
                default:
                program_line++;
            }
        }

        return accumulator;
    }

    std::vector<std::string> parse_file_into_lines() {
        std::fstream infile("/examples/day8.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int detect_last_accumulator_value_before_loop() {
        auto program = parse_file_into_lines();

        int accumulator = 0;
        int program_line = 0;
        std::set<int> lines_hit;
        while (true) {
            std::cout << "Executing line " << program_line << " with accumulator looking like: " << accumulator << std::endl;
            auto attempt = lines_hit.insert(program_line);
            if (!attempt.second) {
                return accumulator;
            }

            auto command_type = determine_line_command(program[program_line]);

            switch (command_type) {
                case Command::JUMP:
                program_line += parse_command_affect(program[program_line]);
                break;
                case Command::ACCUMULATE:
                accumulator += parse_command_affect(program[program_line]);
                default:
                program_line++;
            }
        }
    }

    int fix_program_and_get_final_accumulator_value() {
        auto program = parse_file_into_lines();

        int accumulator = 0;
        int program_line = 0;
        std::set<int> lines_hit;
        std::vector<ProgramState> executed_program;
        while (true) {
            auto attempt = lines_hit.insert(program_line);
            if (!attempt.second) {
                break;
            }
            auto command_type = determine_line_command(program[program_line]);
            int affect = parse_command_affect(program[program_line]);

            switch (command_type) {
                case Command::JUMP:
                program_line +=affect;
                break;
                case Command::ACCUMULATE:
                accumulator += affect;
                default:
                program_line++;
            }

            executed_program.push_back(ProgramState{accumulator, program_line, affect, command_type});
        }

        // starting from the last command, iterate back and pop off the set all the values that we hit
        for (int i = executed_program.size() - 1; i >= 0; i--) {
            int assumed_value = -1;
            lines_hit.erase(executed_program[i].line_number);
            if (executed_program[i].command == Command::NOP) {
                assumed_value = execute_program_from_state(
                    program,
                    ProgramState{executed_program[i].accumulator, executed_program[i].line_number + executed_program[i].affected_value - 1, executed_program[i].affected_value, Command::JUMP},
                    lines_hit
                );
            }

            if (executed_program[i].command == Command::JUMP) {
                assumed_value = execute_program_from_state(
                    program,
                    ProgramState{executed_program[i].accumulator, executed_program[i].line_number - executed_program[i].affected_value + 1, executed_program[i].affected_value, Command::JUMP},
                    lines_hit
                );
            }

            if (assumed_value != -1) {
                return assumed_value;
            }
        }

        return accumulator;
    }
}