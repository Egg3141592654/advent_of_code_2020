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

    int execute() {
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
}