#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace day10 {
    std::vector<int> parse_file_into_number_list() {
        std::fstream infile("/examples/day10.txt");
        std::vector<int> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(std::stoi(line));
        }

        return lines;
    }

    int get_product_of_single_and_triple_jolt_adapter_value_counts() {
        auto adapters = parse_file_into_number_list();

        // sort the list into ascending order
        std::sort(adapters.begin(), adapters.end());

        // add 0 (the socket) and 3 + max (the laptop)
        adapters.emplace(adapters.begin(), 0);
        adapters.push_back(adapters[adapters.size() - 1] + 3);

        int gaps_of_one = 0;
        int gaps_of_three = 0;

        // get the gaps for each adapter (and add to the corresponding value in each)
        for (int i = 0; i < adapters.size() - 1; i++) {
            auto gap = adapters[i + 1] - adapters[i];
            switch (gap) {
                case 1:
                gaps_of_one++;
                break;
                case 3:
                gaps_of_three++;
                break;
                default:
                continue;
            }
        }

        std::cout << "Gaps of 1 and three are: " << gaps_of_one << " and " << gaps_of_three << std::endl;

        return gaps_of_one * gaps_of_three;
    }
}