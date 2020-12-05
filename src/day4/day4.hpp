#pragma once

#include <string>
#include <tuple>

namespace day4 {
    class Passport {
        private:
            std::string byr = "";
            std::string iyr = "";
            std::string eyr = "";
            std::string hgt = "";
            std::string hcl = "";
            std::string ecl = "";
            std::string pid = "";
            std::string cid = "";
            void populate_passport_field(std::string key, std::string value);
            std::tuple<std::string, std::string> extract_key_value(std::string kvp);
        public:
            Passport(std::string passport_data);
            bool passport_valid();
            bool deep_validate();
    };

    int get_valid_passports();
    int get_valid_detailed_passports();
}