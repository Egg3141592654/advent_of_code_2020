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

    bool Rule::apply_rule(std::string target) {
        return false;
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

    bool PasswordEntry::is_valid() {
        // Take the nested rule and apply to the password
        int char_instances = 0;
        for (int i = 0; i < this->password.length(); ++i) {
            if (this->password[i] == this->rule->target_char) {
                char_instances++;
            }
        }

        return (char_instances >= this->rule->lower_bound) && (char_instances <= this->rule->upper_bound);
    }

    int count_valid_passwords() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day2.txt");

        std::string line;
        int valid_passwords = 0;
        int passwords_detected = 0;
        while (std::getline(infile, line))
        {
            std::unique_ptr<PasswordEntry> dummy = PasswordEntry::construct_from_line(line);
            if (dummy->is_valid()) {
                valid_passwords++;
            }

            passwords_detected++;
        }

        std::cout << "Sifted through " << passwords_detected << " passwords!" << std::endl;

        return valid_passwords;
    }
}