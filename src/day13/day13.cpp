#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "day13.hpp"

namespace day13 {
    std::vector<int> parse_bus_list_into_bus_numbers(std::string bus_list) {
        std::vector<int> buses;
        std::stringstream ss (bus_list);
        std::string item;

        while (getline (ss, item, ',')) {
            if (item.compare("x") != 0) {
                buses.push_back (std::stoi(item));
            }
        }

        return buses;
    }

    std::vector<std::string> parse_file_into_string_list() {
        std::fstream infile("/examples/day13.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int get_soonest_bus_id_times_waittime() {
        auto input = parse_file_into_string_list();
        int soonest_departure = std::stoi(input[0]);
        auto buses = parse_bus_list_into_bus_numbers(input[1]);

        std::tuple<int, int> best_bus_departure{0, 0};

        for (auto bus_id : buses) {
            int time_to_arrival = bus_id - (soonest_departure % bus_id);

            if (std::get<0>(best_bus_departure) == 0) {
                best_bus_departure = std::make_tuple(bus_id, time_to_arrival);
            }

            if (std::get<1>(best_bus_departure) > time_to_arrival) {
                best_bus_departure = std::make_tuple(bus_id, time_to_arrival);
            }
        }

        return std::get<0>(best_bus_departure) * std::get<1>(best_bus_departure);
    }
}