#pragma once

#include <string>
#include <vector>

namespace day16 {
    struct Bounds {
        unsigned int upper;
        unsigned int lower;
    };

    class Rule {
        protected:
            std::vector<Bounds> valid_values;
            std::string rule_name;
        public:
            Rule(std::string rule_name, std::vector<Bounds> bounds) { this->rule_name = rule_name; this->valid_values = bounds; }
            std::vector<Bounds> get_bounds() { return this->valid_values; }
            std::string get_rule_name() { return this->rule_name; }
            void print_debug_information();
    };

    unsigned int get_ticket_error_rate();
}