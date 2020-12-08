#pragma once

#include <map>
#include <memory>
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
            std::vector<std::shared_ptr<Bag>> bags_contained;
            std::vector<std::unique_ptr<Bag>> contained_in;
        public:
            Bag(std::string bag_color);
            void add_contained_in_relationship(BagRelationship new_relationship);
            void add_bags_contained(std::vector<BagRelationship> bags_contained);
            int get_num_bags_containing_this_bag();
    };

    class BagRules {
        private:
            std::map<std::string, std::shared_ptr<Bag>> graph;
        public:
            void add_bag_to_map(std::string rule_raw);
            int find_bags_that_contain_bag(std::string bag_color);
    };

    int find_bags_that_contain_shiny_golden_bags();
}