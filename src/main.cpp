// Your First C++ Program

#include <iostream>
#include <sstream>

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Incompatible run, please enter a day for the code advent to execute!" << std::endl;
        exit(1);
    }

    std::istringstream iss( argv[1] );
    int day;

    if (iss >> day)
    {
        switch (day) {
            case 1:
                {
                    std::cout << "Executing Day 1" << std::endl;
                    int answer = day1::execute_part_1();
                    std:: cout << "The answer to part 1 is: " << answer << "!" << std::endl;
                    answer = day1::execute_part_2();
                    std:: cout << "The answer to part 2 is: " << answer << "!" << std::endl;
                }
                break;
            case 2:
                {
                    std::cout << "Executing Day 2" << std::endl;
                    std::cout << "The number of old valid passwords from input set is " << day2::count_valid_passwords_part_1() << std::endl;
                    std::cout << "The number of new valid passwords from input set is " << day2::count_valid_passwords_part_2()  << std::endl;
                }
                break;
            case 3:
                {
                    std::cout << "Executing Day 3" << std::endl;
                    std::cout << "The number of trees hit is " << day3::number_trees_hit() << std::endl;
                    std::cout << "Executing part 2" << std::endl;
                    day3::number_trees_hit_multiple_paths();
                }
                break;
            case 4:
                {
                    std::cout << "Executing Day 4" << std::endl;
                    int answer = day4::get_valid_passports();
                    std::cout << "Part 1 has detected " << answer << " valid passports." << std::endl;
                    answer = day4::get_valid_detailed_passports();
                    std::cout << "Part 2 has detected " << answer << " valid passports." << std::endl;
                }
                break;
            case 5:
            {
                std::cout << "Executing day 5" << std::endl;
                int answer = day5::get_highest_detected_seat_number();
                std::cout << "Highest detected seat per formula in part 1 is: " << answer << std::endl;
            }
            break;
            default:
                std::cout << "Aborting since you selected a day that doesn't exist!" << std::endl;                
        }
    }
    else {
        std::cout << "Failed to convert first argument to integer. Bailing" << std::endl;
        exit(1);
    }
}