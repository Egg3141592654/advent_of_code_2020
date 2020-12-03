#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

#include "day1.hpp"

namespace day1 {
    void detect_pairs(std::vector<int> numbers, std::tuple<int, int> &values, int starting_index = 0) {
        // I know that this isn't optimal, but we are going to scan starting at starting index + 1 for pairs that may match 2020
        for (int i = starting_index + 1; i < numbers.size(); ++i) {
            if (numbers[starting_index] + numbers[i] == 2020) {
                values = std::tuple<int, int>{numbers[starting_index], numbers[i]};
                break;
            }
        }
    }

    std::tuple<int, int, int> detect_triples(std::vector<int> numbers) {
        for (int i = 0; i < numbers.size(); ++i) {
            for (int j = i + 1; j < numbers.size(); ++j) {
                for (int k = j + 1; k < numbers.size(); ++k) {
                    if ((numbers[i] + numbers[j] + numbers[k]) == 2020) {
                        return std::tuple<int, int, int>{numbers[i], numbers[j], numbers[k]};
                    }
                }
            }
        }

        return std::tuple<int, int, int>();
    }

    int execute_part_1() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day1.txt");

        std::vector<int> numbers;
        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            int dummy;
            if(!(iss >> dummy)) {
                std::cout << "ERROR PARSING nuMBER, BREAKING" << std::endl;
                 break;
            }
            numbers.push_back(dummy);
        }

        std::cout << "Detected " <<  numbers.size() << " numbers to parse, parsing now!" << std::endl;

        std::tuple<int, int> pair{-1, -1};
        for (int i = 0; i < numbers.size() - 1; ++i) {
            detect_pairs(numbers, pair, i);

            if (std::get<0>(pair) != -1 && std::get<1>(pair) != -1) {
                // identified pair, return product
                std::cout << "PAIR DETECTED! VALUES: " << std::get<0>(pair) << " and " << std::get<1>(pair) << std::endl;
                return std::get<0>(pair) * std::get<1>(pair);
            }
        }
        return 42;
    }

    int execute_part_2() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day1.txt");

        std::vector<int> numbers;
        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            int dummy;
            if(!(iss >> dummy)) {
                std::cout << "ERROR PARSING nuMBER, BREAKING" << std::endl;
                 break;
            }
            numbers.push_back(dummy);
        }

        std::cout << "Detected " <<  numbers.size() << " numbers to parse, parsing now!" << std::endl;

        std::tuple<int, int, int> result = detect_triples(numbers);

        std::cout << "Detected triples " << std::get<0>(result) << ", " << std::get<1>(result) << ", " << std::get<2>(result) << std::endl;

        return std::get<0>(result) * std::get<1>(result) * std::get<2>(result);
    }
}