// Your First C++ Program

#include <iostream>
#include <sstream>

#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"
#include "day8.hpp"
#include "day9.hpp"
#include "day10.hpp"
#include "day11.hpp"
#include "day12.hpp"
#include "day13.hpp"

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
                answer = day5::get_your_seat_assignment();
                std::cout << "Your seat assignment is: " << answer << std::endl;
            }
            break;
            case 6:
            {
                std::cout << "Executing day 6" << std::endl;
                int answer = day6::sum_yes_custom_form_answers_by_group();
                std::cout << "The number of each group's customs answers is " << answer << std::endl;
                answer = day6::sum_unanimous_form_answers_by_group();
                std::cout << "The number of each group's unanimous customs answers is " << answer << std::endl;
            }
            break;
            case 7:
            {
                std::cout << "Executing day 7" << std::endl;
                int answer = day7::find_bags_that_contain_shiny_golden_bags();
                std::cout << "The number of bags which can contain shiny gold bags eventually is " << answer << std::endl;
                answer = day7::find_bags_required_for_shiny_gold_bag();
                std::cout << "The number of bags required for purchase in a shiny gold bag is " << answer << std::endl;
            }
            break;
            case 8:
            {
                std::cout << "Executing day 8" << std::endl;
                int answer = day8::detect_last_accumulator_value_before_loop();
                std::cout << "The accumulator contained this value before repeating: " << answer << std::endl;
                answer = day8::fix_program_and_get_final_accumulator_value();
                std::cout << "The final accumulator value is " << answer << std::endl;
            }
            break;
            case 9:
            {
                std::cout << "Executing day 9" << std::endl;
                int answer = day9::get_bad_coded_number();
                std::cout << "The number that is badly coded is: " << answer << std::endl;
                answer = day9::get_sum_of_highest_and_lowest_numbers_in_contiguous_set_adding_to_part_1();
                std::cout << "The sum of the highest and lowest number that contiguously adds to 1930745883 is: " << answer << std::endl;
            }
            break;
            case 10:
            {
                std::cout << "Executing day 10" << std::endl;
                int answer = day10::get_product_of_single_and_triple_jolt_adapter_value_counts();
                std::cout << "The product of 3 and 1 jolt adapter differentials is: " << answer << std::endl;
                long answer2 = day10::get_permutations_of_adapters();
                std::cout << "The number of permutations of adapters to plug in your computer is " << answer2 << std::endl;
            }
            break;
            case 11:
            {
                std::cout << "Executing day 11" << std::endl;
                int answer = day11::count_occupied_seats();
                std::cout << "The number of occupied seats on the plane is: " << answer << std::endl;
                answer = day11::count_occupied_seats_sightline();
                std::cout << "The number of people occupied by sight is: " << answer << std::endl;
            }
            break;
            case 12:
            {
                std::cout << "Executing day 12" << std::endl;
                int answer = day12::get_manhattan_distance_traveled();
                std::cout << "The manhattan distance the boat has traveled is: " << answer << std::endl;
                answer = day12::get_manhattan_ship_distance_traveled();
                std::cout << "The manhattan distance the waypoint boat has traveled is: " << answer << std::endl;
            }
            break;
            case 13:
            {
                std::cout << "Executing day 13" << std::endl;
                int answer = day13::get_soonest_bus_id_times_waittime();
                std::cout << "The bus id times soonest arrival time delta is: " << answer << std::endl;
                unsigned long answer2 = day13::get_first_sequential_bus_departure_timestanp();
                std::cout << "The first timestamp that all buses depart sequentially is: " << answer2 << std::endl;
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