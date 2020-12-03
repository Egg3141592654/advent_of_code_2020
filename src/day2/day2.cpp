#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "day2.hpp"

namespace day2 {

    Rule::Rule(char target_char, int lower_bound, int upper_bound) {
        this->target_char = target_char;
        this->lower_bound = lower_bound;
        this->upper_bound = upper_bound;
    }

    bool Rule::apply_rule_old(std::string target) {
        // Take the nested rule and apply to the password
        int char_instances = 0;
        for (int i = 0; i < target.length(); ++i) {
            if (target[i] == this->target_char) {
                char_instances++;
            }
        }

        return (char_instances >= this->lower_bound) && (char_instances <= this->upper_bound);
    }

    bool Rule::apply_rule_new(std::string target) {
        // lower bound must have target and upper bound must not have target char
        // this is 1 indexed, so always subtract 1!
        if (upper_bound > target.length()) {
            return false;
        }

        bool position1_valid = target[this->lower_bound] == this->target_char;
        bool position2_valid = target[this->upper_bound] == this->target_char;

        return !(position1_valid) != !(position2_valid);
    }

    PasswordEntry::PasswordEntry(std::unique_ptr<Rule> rule, std::string password) {
        this->rule = std::move(rule);
        this->password = password;
    }

    std::unique_ptr<PasswordEntry> PasswordEntry::construct_from_line(std::string line) {
        // Example string: 4-5 t: ftttttrvts
        // loop through string to get substring of lower bound
        // loop through string to get second bound (stop at ' ')
        // get next character to get character rule
        // after space complete string for password
        int dash_index = line.find_first_of('-');
        int first_space_index = line.find_first_of(' ');
        int colon_index = line.find_first_of(':');

        int lower_bound = std::stoi(line.substr(0, dash_index));
        int upper_bound = std::stoi(line.substr(dash_index + 1, first_space_index));
        char target_character = line[first_space_index + 1];
        std::string password = line.substr(colon_index + 1);

        std::unique_ptr<PasswordEntry> to_return{new PasswordEntry(std::make_unique<Rule>(target_character, lower_bound, upper_bound), password)}; 
        return to_return;
    }

    bool PasswordEntry::is_valid_old() {
        return this->rule->apply_rule_old(this->password);
    }

    bool PasswordEntry::is_valid_new() {
        return this->rule->apply_rule_new(this->password);
    }

    int count_valid_passwords_part_1() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day2.txt");

        std::string line;
        int valid_passwords = 0;
        int passwords_detected = 0;
        while (std::getline(infile, line))
        {
            std::unique_ptr<PasswordEntry> dummy = PasswordEntry::construct_from_line(line);
            if (dummy->is_valid_old()) {
                valid_passwords++;
            }

            passwords_detected++;
        }

        std::cout << "Sifted through " << passwords_detected << " passwords!" << std::endl;

        return valid_passwords;
    }

    int count_valid_passwords_part_2() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day2.txt");

        std::string line;
        int valid_passwords = 0;
        int passwords_detected = 0;
        while (std::getline(infile, line))
        {
            std::unique_ptr<PasswordEntry> dummy = PasswordEntry::construct_from_line(line);
            if (dummy->is_valid_new()) {
                valid_passwords++;
            }

            passwords_detected++;
        }

        std::cout << "Sifted through " << passwords_detected << " passwords!" << std::endl;

        return valid_passwords;
    }
}