#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "day16.hpp"

namespace day16 {
    void Rule::print_debug_information() {
        std::cout << "RULE: " << this->rule_name << "Bounds {" << std::endl;

        for (int i = 0; i < this->valid_values.size(); i++) {
            std::cout << valid_values[i].lower << " -> " << valid_values[i].upper << std::endl;
        }

        std::cout << "}" << std::endl;
    }

    std::vector<Bounds> construct_bounds_from_string(std::string bounds_string) {
        // split string from or and parse the numbers between - deliniations
        std::vector<Bounds> to_return;
        int or_index = bounds_string.find("or");
        auto first_bound = bounds_string.substr(0, or_index - 1);
        auto second_bound = bounds_string.substr(or_index + 3);

        // do first bound first
        Bounds bound1;
        Bounds bound2;
        int dash_index = first_bound.find_first_of('-');
        bound1.lower = std::stoi(first_bound.substr(0, dash_index));
        bound1.upper = std::stoi(first_bound.substr(dash_index + 1));
        dash_index = second_bound.find_first_of('-');
        bound2.lower = std::stoi(second_bound.substr(0, dash_index));
        bound2.upper = std::stoi(second_bound.substr(dash_index + 1));
        to_return.push_back(bound1);
        to_return.push_back(bound2);
        return to_return;
    }

    unsigned int is_field_compliant(unsigned long field, std::vector<Rule> rules) {
        bool in_bounds = false;
        for (int i = 0; i < rules.size(); i++) {
            auto bounds = rules[i].get_bounds();
            for (int j = 0; j < bounds.size(); j++) {
                if (field >= bounds[j].lower && field <= bounds[j].upper) {
                    in_bounds = true;
                }
            }
        }

        return in_bounds ? 0 : field;
    }

    Rule line_to_rule(std::string line) {
        int colon_index = line.find_first_of(':');
        auto rule_name = line.substr(0, colon_index);
        auto rule_bounds_string = line.substr(colon_index + 2);
        return Rule(rule_name, construct_bounds_from_string(rule_bounds_string));
    }

    std::vector<std::string> parse_file_into_string_list() {
        std::fstream infile("/examples/day16.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    std::vector<int> split_string_by_commas(std::string bus_list) {
        std::vector<int> to_return;
        std::stringstream ss (bus_list);
        std::string item;

        while (getline (ss, item, ',')) {
            to_return.push_back(std::stoi(item));
        }

        return to_return;
    }

    unsigned int get_ticket_error_rate() {
        auto file_read = parse_file_into_string_list();

        int file_index = 0;
        std::vector<Rule> rules;
        while (file_read[file_index].length() > 0) {
            // The first inputs are going to be the rules. The first empty line is going to be the delimiter
            rules.push_back(line_to_rule(file_read[file_index]));
            file_index++;
        }

        for (int i = 0; i < rules.size(); i++) {
            rules[i].print_debug_information();
        }

        // next input is _your_ ticket, but for part 1 lets just fastforward a few lines
        file_index += 5;

        //Parse each ticket and add the outlier to an accumulator
        unsigned int error_value = 0;
        while (file_index < file_read.size()) {
            std::vector<int> ticket_fields = split_string_by_commas(file_read[file_index]);
            for (int field_index = 0; field_index < ticket_fields.size(); field_index++) {
                auto error_detected = is_field_compliant(ticket_fields[field_index], rules);

                if (error_detected != 0) {
                    error_value += ticket_fields[field_index];
                    std::cout << "DEBUG DETECTED Out OF COMPLiant FIELD: " << ticket_fields[field_index] << std::endl;
                    break;
                }
            }

            file_index++;
        }

        // Index is 
        return error_value;
    }
}