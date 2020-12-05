#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "day4.hpp"

namespace day4 {
    Passport::Passport(std::string passport_data) {
        // need to parse string stopping at each space to determine the key/value to write
        std::string key_value_string;
        for (int i = 0; i < passport_data.length(); ++i) {
            if (passport_data[i] != ' ') {
                key_value_string += passport_data[i];
            } else {
                auto key_value_tuple = this->extract_key_value(key_value_string);
                this->populate_passport_field(std::get<0>(key_value_tuple), std::get<1>(key_value_tuple));
                key_value_string.clear();
            }
        }

        // need to get the last value's field
        auto key_value_tuple = this->extract_key_value(key_value_string);
        this->populate_passport_field(std::get<0>(key_value_tuple), std::get<1>(key_value_tuple));
    }

    void Passport::populate_passport_field(std::string key, std::string value) {
        if (key.compare("byr") == 0) {
            this->byr = value;
        }
        else if (key.compare("iyr") == 0) {
            this->iyr = value;
        }
        else if (key.compare("eyr") == 0) {
            this->eyr = value;
        }
        else if (key.compare("hgt") == 0) {
            this->hgt = value;
        }
        else if (key.compare("hcl") == 0) {
            this->hcl = value;
        }
        else if (key.compare("ecl") == 0) {
            this->ecl = value;
        }
        else if (key.compare("pid") == 0) {
            this->pid = value;
        }
        else if (key.compare("cid") == 0) {
            this->cid = value;
        }
        else {
            std::cout << "DETECTED BAD PASSPORT KEY, VALUE: " << key << ", " << value << std::endl;
        }
    }

    std::tuple<std::string, std::string> Passport::extract_key_value(std::string kvp) {
        // find the colon and then splice the string into parts
        int colon = kvp.find_first_of(':');
        return std::tuple<std::string, std::string>{kvp.substr(0, colon), kvp.substr(colon + 1)};
    }

    bool Passport::passport_valid() {
        bool all_required_fields_exist = this->byr.length() &&
            this->iyr.length() &&
            this->eyr.length() &&
            this->hgt.length() &&
            this->hcl.length() &&
            this->ecl.length() &&
            this->pid.length();

        return all_required_fields_exist; 
    }

    bool Passport::deep_validate() {
        if (!this->passport_valid()) {
            return false;
        }

        // All fields expected are here now, let's validate each field one by one
        // byr (Birth Year) - four digits; at least 1920 and at most 2002.
        int byr = std::stoi(this->byr);
        if (byr < 1920 || 2002 < byr) {
            return false;
        }

        // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
        int iyr = std::stoi(this->iyr);
        if (iyr < 2010 || 2020 < iyr) {
            return false;
        }

        // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
        int eyr = std::stoi(this->eyr);
        if (eyr < 2020 || 2030 < eyr) {
            return false;
        }

        // hgt (Height) - a number followed by either cm or in:
        // If cm, the number must be at least 150 and at most 193.
        // If in, the number must be at least 59 and at most 76.
        bool contins_cm = this->hgt.find_first_of("cm") != std::string::npos;
        bool contins_in = this->hgt.find_first_of("in") != std::string::npos;

        if (!(contins_cm || contins_in)) {
            return false;
        }

        int hgt = std::stoi(this->hgt.substr(0, this->hgt.length() - 2));

        if (contins_cm && (hgt < 150 || 193 < hgt)) {
            return false;
        }

        if (contins_in && (hgt < 59 || 76 < hgt)) {
            return false;
        }


        // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
        if (this->hcl[0] != '#' || this->hcl.length() != 7) {
            return false;
        }

        for (int i = 1; i < this->hcl.length(); ++i) {
            if (!std::isalnum((int)this->hcl[i])) {
                return false;
            }
        }

        // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
        if (
            this->ecl.compare("amb") != 0 &&
            this->ecl.compare("blu") != 0 &&
            this->ecl.compare("brn") != 0 &&
            this->ecl.compare("gry") != 0 &&
            this->ecl.compare("grn") != 0 &&
            this->ecl.compare("hzl") != 0 &&
            this->ecl.compare("oth") != 0
        ) {
            return false;
        }
        
        // pid (Passport ID) - a nine-digit number, including leading zeroes.
        if (this->pid.length() != 9) {
            return false;
        }

        for (int i = 0; i < this->pid.length(); ++i) {
            if (!std::isdigit((int)this->pid[i])) {
                return false;
            }
        }

        // cid (Country ID) - ignored, missing or not.
        return true;
    }

    std::vector<std::string> parse_file_into_lines() {
        std::fstream infile("/examples/day4.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int get_valid_passports() {
        std::vector<std::string> file_by_lines = parse_file_into_lines();

        std::string passport_raw_string = "";
        int num_valid_passports = 0;
        for (int i = 0; i < file_by_lines.size(); ++i) {
            if (file_by_lines[i].length() == 0) {
                // This is the end of a passport
                Passport to_check(passport_raw_string);
                if (to_check.passport_valid()) {
                    num_valid_passports++;
                }
                passport_raw_string.clear();
            }
            else {
                if (passport_raw_string.length() == 0) {
                    passport_raw_string = file_by_lines[i];

                } else {
                    passport_raw_string += " " + file_by_lines[i];
                }
            }
        }
        
        if (passport_raw_string.length()) {
            // This is the end of a passport
            Passport to_check(passport_raw_string);
            if (to_check.passport_valid()) {
                num_valid_passports++;
            }
        }

        return num_valid_passports;
    }

    int get_valid_detailed_passports() {
        std::vector<std::string> file_by_lines = parse_file_into_lines();

        std::string passport_raw_string = "";
        int num_valid_passports = 0;
        for (int i = 0; i < file_by_lines.size(); ++i) {
            if (file_by_lines[i].length() == 0) {
                // This is the end of a passport
                Passport to_check(passport_raw_string);
                if (to_check.deep_validate()) {
                    num_valid_passports++;
                }
                passport_raw_string.clear();
            }
            else {
                if (passport_raw_string.length() == 0) {
                    passport_raw_string = file_by_lines[i];

                } else {
                    passport_raw_string += " " + file_by_lines[i];
                }
            }
        }
        
        if (passport_raw_string.length()) {
            // This is the end of a passport
            Passport to_check(passport_raw_string);
            if (to_check.passport_valid()) {
                num_valid_passports++;
            }
        }

        return num_valid_passports;
    }
}