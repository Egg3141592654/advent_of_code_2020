#include <fstream>
#include <iostream>
#include <vector>

#include "day3.hpp"

namespace day3 {
    int number_trees_hit() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day3.txt");

        std::string line;
        std::vector<std::string> slope;
        while (std::getline(infile, line))
        {
            slope.push_back(line);
        }

        int slope_scroll = 0;
        int trees_hit = 0;
        for(int height = 0; height < slope.size(); ++height) {
            // Detect the current state and add if its a tree
            if (slope[height][slope_scroll] == '#') {
                trees_hit++;
            }

            // increment slope scroll by 3, check for wrapping
            slope_scroll += 3;
            if (slope_scroll >= slope[height].length()) {
                slope_scroll -= slope[height].length();
            }
        }

        return trees_hit;
    }

    void number_trees_hit_multiple_paths() {
        // Get source file and read it entirely
        std::fstream infile("/examples/day3.txt");

        std::string line;
        std::vector<std::string> slope;
        while (std::getline(infile, line))
        {
            slope.push_back(line);
        }

        int path_scrolls[5] = {0, 0, 0, 0, 0};
        int path_scroll_rules[5] = {1, 3, 5, 7, 1};
        int path_height_rules[5] = {1, 1, 1, 1, 2};
        int trees_hit[5] = {0, 0, 0, 0, 0};
        for(int height = 0; height < slope.size(); ++height) {
            for (int path_index = 0; path_index < 5; path_index++) {
                // Check if we are allowed to process this line or if we are skipping
                if (height % path_height_rules[path_index] != 0) {
                    continue;
                }

                // Detect the current state and add if its a tree
                if (slope[height][path_scrolls[path_index]] == '#') {
                    trees_hit[path_index]++;
                }

                // increment slope scroll by 3, check for wrapping
                path_scrolls[path_index] += path_scroll_rules[path_index];
                if (path_scrolls[path_index] >= slope[height].length()) {
                    path_scrolls[path_index] -= slope[height].length();
                }
            }
        }

        std::cout << "The number of trees hit for every path is as follows:";
        for (int i = 0; i < 5; i++) {
            std::cout << trees_hit[i] << " ";
        }
        
        std::cout << std::endl;
    }
}