#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "day9.hpp"

namespace day9 {
    bool is_number_coded_correctly(int coded_length, std::deque<long> numbers) {
        if (numbers.size() - 1  < coded_length) {
            // not enough numbers, still the preamble
            return true;
        }

        // The last number in the deque is the number we need to add to
        auto target_number = numbers.back();

        for (int i = 0; i < numbers.size() - 1; i++) {
            // ignore last number because that is what we need to add to
            for (int j = i + 1; j < numbers.size() - 1; j++) {
                if (numbers[i] + numbers[j] == target_number) {
                    return true;
                }
            }
        }

        return false;
    }

    bool find_contiguous_pair_adding_to_number(long target, std::vector<long> numbers, int starting_index, std::tuple<long, long> &result) {
        int accumulation = 0;
        long lowest_num = numbers[starting_index];
        long highest_num = numbers[starting_index];
        for (int i = starting_index; i < numbers.size(); i++) {
            accumulation += numbers[i];
            if (accumulation > target) {
                return false;
            }

            if (lowest_num > numbers[i]) {
                lowest_num = numbers[i];
            }

            if (highest_num < numbers[i]) {
                highest_num = numbers[i];
            }

            if (accumulation == target) {
                result = std::make_tuple(lowest_num, highest_num);
                return true;
            }
        }

        return false;
    }

    std::vector<std::string> parse_file_into_lines() {
        std::fstream infile("/examples/day9.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int get_bad_coded_number() {
        auto numbers_raw = parse_file_into_lines();
        int cypher_length = 25;

        std::deque<long> cypher;
        for (int i = 0; i < numbers_raw.size(); i++) {
            auto current_number = std::stol(numbers_raw[i]);
            cypher.push_back(current_number);

            if (!is_number_coded_correctly(cypher_length, cypher)) {
                return current_number;
            }

            // Keep the list pruned to exactly the length it needs to be
            if (cypher.size() > cypher_length) {
                cypher.pop_front();
            }
        }

        return -1;
    }

    long get_sum_of_highest_and_lowest_numbers_in_contiguous_set_adding_to_part_1() {
        auto numbers_raw = parse_file_into_lines();
        long target_number = 1930745883;
        std::tuple<long, long> answer;

        // convert list of strings to numbers
        std::vector<long> numbers;
        for (int i = 0; i < numbers_raw.size(); i++) {
            numbers.push_back(std::stol(numbers_raw[i]));
        }

        // loop one more time to get the numbers that add to target
        for (int i = 0; i < numbers.size(); i++) {
            if (find_contiguous_pair_adding_to_number(target_number, numbers, i, answer)) {
                std::cout << "got the high and low index that adds to " << target_number << " of " << std::get<0>(answer) << " " << std::get<1>(answer) << std::endl;
                return std::get<0>(answer) + std::get<1>(answer);
            }
        }

        return -1;
    }
}