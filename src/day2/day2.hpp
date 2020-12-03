#pragma once

#include <memory>
#include <string> 

namespace day2 {
    class Rule {
        public:
            char target_char;
            int lower_bound;
            int upper_bound;
            Rule(char target_char, int lower_bound, int upper_bound);
            bool apply_rule(std::string target);
    };

    class PasswordEntry {
        private:
            std::unique_ptr<Rule> rule;
            std::string password;
            PasswordEntry(std::unique_ptr<Rule> rule, std::string password);
        public:
            static std::unique_ptr<PasswordEntry> construct_from_line(std::string line);
            bool is_valid();
    };

    int count_valid_passwords();
}