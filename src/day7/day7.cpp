#include "day7.hpp"

namespace day7 {
    void BagRules::add_bag_to_map(std::string rule_raw) {
        // get the indicies of the "bag", and "contains" keywords for string parsing.
        int bag_index = rule_raw.find("bag");
        int contain_index = rule_raw.find("contain");

        // bag index - 1 because there is a space there!
        std::string bag_color = rule_raw.substr(0, bag_index -1);
        graph[bag_color] = std::make_shared<Bag>(bag_color);

        // rules start after contain and the whitespace
        std::string containing_rules = rule_raw.substr(contain_index + 8);

        // start to create relationships based on rules.
        std::vector<BagRelationship> relationships;

        // First idiot check to see if "no" is in the string, if this is the case break since there are no relations
        if (containing_rules.find("no") != std::string::npos) {
            // iterate through the rules string with the following rule:
            // 1: first space indicates the end of the number of bags
            // 2: the next instance of the word "bag" - 1 indicates the bag color (need to strip the ' ')
            // 3: slice string at the first instance of ',' else, break (since we have hit the end of the string)
            while (containing_rules.length() != 0) {
                int first_space_index = containing_rules.find_first_of(' ');
                int bag_index = containing_rules.find("bag");
                
                int num_bags = std::stoi(containing_rules.substr(0, first_space_index));
                std::string nested_bag_color = containing_rules.substr(first_space_index + 1, bag_index - 2 - first_space_index);

                auto find = graph.find(nested_bag_color);
                if (find == graph.end()) {
                    graph[nested_bag_color] = std::make_shared<Bag>(nested_bag_color);
                }

                graph[nested_bag_color].add_contained_in_relationship(BagRelationship{nested_bag_color, graph[bag_color]});
        }
    }

    int find_bags_that_contain_bag(std::string bag_color) {
        auto find = graph.find(bag_color);

        if (find == graph.end()) {
            return -1;
        }

        return find->second->get_num_bags_containing_this_bag();
    }


    std::vector<std::string> parse_file_into_lines() {
        std::fstream infile("/examples/day7.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int find_bags_that_contain_shiny_golden_bags() {
        auto bag_rules_raw = parse_file_into_lines();
        BagRules bag_rules;

        for (int i = 0; i < bag_rules_raw.size(); ++i) {
            bag_rules.add_bag_to_map(bag_rules_raw[i]);
        }

        return bag_rules.find_bags_that_contain_bag("shiny gold")
    }
}