#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "day14.hpp"

namespace day14 {
    void Mask::set_mask(std::string new_mask) {
        this->forced_mask.clear();

        // iterate backwards through the list and increment the bit shifter (this is 1 based)
        int current_bit = 0;
        for (int index = new_mask.size() - 1; index >= 0; index--) {
            if (new_mask[index] == '0') {
                this->forced_mask[current_bit] = 0;
            }
            
            if (new_mask[index] == '1') {
                this->forced_mask[current_bit] = 1;
            }

            // Do nothing for X since we don't force bits that way
            current_bit++;
        }
    }

    unsigned long Mask::apply_number(unsigned long to_apply) {
        // iterate through the mask and force all bits to be what we expect them to be via 2s compliment
        unsigned long to_return = to_apply;
        for (auto kvp : this->forced_mask) {
            // first is going to be the amout to shift
            // second is going to be the value to set
            std::cout << "DEBUG fixing bit at position : value " << kvp.first << " : " << kvp.second << std::endl;
            to_return ^= (-((unsigned long)kvp.second) ^ to_return) & (1UL << kvp.first);
        }

        return to_return;
    }

    std::vector<std::string> parse_file_into_string_list() {
        std::fstream infile("/examples/day14.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    unsigned long sum_bitmask() {
        auto input = parse_file_into_string_list();

        std::map<int, unsigned long> memory;
        Mask mask;
        for (auto line : input) {
            // need to sus out what to do here
            if (line.find("mask") != std::string::npos) {
                // This is a mask reset operation, reset the mask per the substring of the line
                mask.set_mask(line.substr(7));
            }
            else {
                // We are trying to set a memory address
                int brace_index = line.find_first_of('[');
                int closing_index = line.find_first_of(']');
                int memory_address = std::stoi(line.substr(brace_index + 1, closing_index - brace_index));
                long number_to_apply = std::stol(line.substr(line.find_first_of('=') + 2));
                memory[memory_address] = mask.apply_number(number_to_apply);
            }
        }

        // sum over the memory addresses and get the return value
        unsigned long accumulator = 0;
        for (auto const& x : memory)
        {
            std::cout << "DEBUG MEMORY KEY : VALUE " << x.first
                    << ':' 
                    << x.second
                    << std::endl ;

            accumulator += x.second;
        }

        return accumulator;
    }
}