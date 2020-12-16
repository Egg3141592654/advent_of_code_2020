#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "day15.hpp"

namespace day15 {
    std::vector<std::string> parse_file_into_string_list() {
        std::fstream infile("/examples/day15.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int get_2020_turn() {
        std::string input = parse_file_into_string_list()[0];
        std::map<int, std::tuple<int, int>> memory;
        int last_number = 0;
        int current_turn = 1;

        // Seed the input string
        while (input.length() > 0) {
            int comma_index = input.find_first_of(',');
            int value = std::stoi(input.substr(0, comma_index));
            memory[value] = std::make_pair(current_turn, current_turn);
            last_number = value;
            current_turn++;
            if (comma_index == std::string::npos) {
                break;
            }
            
            input = input.substr(comma_index + 1);
        }

        // Iterate until turn is 2020
        while (current_turn <= 2020) {
            auto last_number_results = memory[last_number];

            if (std::get<1>(last_number_results) - std::get<0>(last_number_results) == 0) {
                last_number = 0;
                memory[0] = std::make_pair(std::get<1>(memory[0]), current_turn);
            }
            else {
                last_number = std::get<1>(last_number_results) - std::get<0>(last_number_results);

                auto search = memory.find(last_number);
                if (search == memory.end()) {
                    memory[last_number] = std::make_pair(current_turn, current_turn);
                }
                else {
                    memory[last_number] = std::make_pair(std::get<1>(memory[last_number]), current_turn);
                }
            }

            current_turn++;
        }

        for (auto const& x : memory)
        {
            std::cout << "DEBUG integer " << x.first
                    << " contains last known indicies of {" << std::get<0>(x.second) << ", " << std::get<1>(x.second) << "}" << std::endl; 
        }

        return last_number;
    }

    unsigned long get_30000000th_step() {
        std::string input = parse_file_into_string_list()[0];
        std::map<int, std::tuple<unsigned long, unsigned long>> memory;
        unsigned long last_number = 0;
        unsigned long current_turn = 1;

        // Seed the input string
        while (input.length() > 0) {
            int comma_index = input.find_first_of(',');
            unsigned long value = std::stol(input.substr(0, comma_index));
            memory[value] = std::make_pair(current_turn, current_turn);
            last_number = value;
            current_turn++;
            if (comma_index == std::string::npos) {
                break;
            }
            
            input = input.substr(comma_index + 1);
        }

        // Iterate until turn is 30000000
        while (current_turn <= 30000000) {
            auto last_number_results = memory[last_number];

            if (std::get<1>(last_number_results) - std::get<0>(last_number_results) == 0) {
                last_number = 0;
                memory[0] = std::make_pair(std::get<1>(memory[0]), current_turn);
            }
            else {
                last_number = std::get<1>(last_number_results) - std::get<0>(last_number_results);

                auto search = memory.find(last_number);
                if (search == memory.end()) {
                    memory[last_number] = std::make_pair(current_turn, current_turn);
                }
                else {
                    memory[last_number] = std::make_pair(std::get<1>(memory[last_number]), current_turn);
                }
            }

            current_turn++;
        }

        for (auto const& x : memory)
        {
            std::cout << "DEBUG integer " << x.first
                    << " contains last known indicies of {" << std::get<0>(x.second) << ", " << std::get<1>(x.second) << "}" << std::endl; 
        }

        return last_number;
    }
}