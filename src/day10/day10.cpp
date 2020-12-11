#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace day10 {
    long recurse_combinations(std::vector<int> available_adapters, int current_adapter, std::set<int> visited, std::map<int, long> &hash) {
        std::cout << "Scanning element: " << current_adapter << std::endl;
        auto hash_check = hash.find(current_adapter);
        if (hash_check != hash.end()) {
            // we already solved this problem
            return hash[current_adapter];
        }

        visited.insert(current_adapter);

        std::vector<int> possible_moves;
        for (int i = 0; i < available_adapters.size(); i++) {
            auto search = visited.find(available_adapters[i]);
            if (search == visited.end() && 
                (available_adapters[i] - current_adapter <= 3) &&
                (available_adapters[i] - current_adapter >= 0)
            ) {
                possible_moves.push_back(available_adapters[i]);
            }
        }

        if (possible_moves.size() == 0) {
            // dead end, return 0
            return 0;
        }

        std::cout << "Determining current adapter: " << current_adapter << " with possible moves: " << std::endl << "{";
        for (auto el : possible_moves) {
            std::cout << el << ", ";
        }

        std::cout << "}" << std::endl;

        // we have some moves that we can make here, recurse over the list again for each possible move
        long combinations = 0;
        for (auto element : possible_moves) {
            combinations += recurse_combinations(available_adapters, element, visited, hash);
        }

        hash[current_adapter] = combinations;
        return combinations;
    }

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

    long get_permutations_of_adapters() {
        auto adapters = parse_file_into_number_list();

        // sort the list into ascending order
        std::sort(adapters.begin(), adapters.end());

        // add the laptop to list
        adapters.push_back(adapters[adapters.size() - 1] + 3);

        std::set<int> visited;
        std::map<int, long> hash;
        hash[adapters[adapters.size() - 1]] = 1;
        return recurse_combinations(adapters, 0, visited, hash);
    }
}