#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace day7 {
    struct BagRelationship;
    class Bag;
    class BagRules;

    struct BagRelationship {
        int quantity;
        std::shared_ptr<Bag> bag;
    };

    class Bag {
        private:
            std::string bag_color;
            std::vector<BagRelationship> bags_contained;
            std::vector<std::shared_ptr<Bag>> contained_in;
        public:
            Bag(std::string bag_color);
            std::string get_bag_color();
            void add_contained_in_relationship(std::shared_ptr<Bag> parent_bag);
            void set_bags_contained(std::vector<BagRelationship> bags_contained);
            int get_num_bags_containing_this_bag(std::set<std::string> &bags_passed);
            int find_num_bags_in_bag();
    };

    class BagRules {
        private:
            std::map<std::string, std::shared_ptr<Bag>> graph;
        public:
            void add_bag_to_map(std::string rule_raw);
            int find_bags_that_contain_bag(std::string bag_color);
            int find_num_nested_bags(std::string bag_color);
    };

    int find_bags_that_contain_shiny_golden_bags();
    int find_bags_required_for_shiny_gold_bag();
}