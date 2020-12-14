#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "day13.hpp"

namespace day13 {
    std::vector<std::string> parse_bus_list_into_sequential_timetable(std::string bus_list) {
        std::vector<std::string> timetable;
        std::stringstream ss (bus_list);
        std::string item;

        while (getline(ss, item, ',')) {
            timetable.push_back(item);
        }

        return timetable;
    }

    auto win_contest(std::vector<std::string> buses) {
        /**
        WARNING: I CHEATED ON THIS PROBLEM! I didn't know about the chinese modulo therom.

        Credit for thi goes to: https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfpujtb?utm_source=share&utm_medium=web2x&context=3
        
        Now that I understand how the modulo theorm works, I can fully appreciate this code.
        **/
        std::vector<std::pair<int,int>> boffs;      // buses and offsets
        for (int i = 0; i < buses.size(); ++i)
            if (buses[i].compare("x") != 0)
                boffs.push_back(std::make_pair(i, std::stoi(buses[i])));
        
        auto it = std::begin(boffs);
        unsigned long mins = (*it).second;
        unsigned long stride = mins;
        for (it = std::next(it); it != std::end(boffs); ++it) {
            auto [off,val] = *it;
            while ((mins + off) % val != 0)
                mins += stride;
            stride *= val;
        }
        return mins;
    }

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

    unsigned long get_first_sequential_bus_departure_timestanp() {
        auto input = parse_file_into_string_list();
        auto timetable = parse_bus_list_into_sequential_timetable(input[1]);

        return win_contest(timetable);
        /*unsigned long multiplier = 0;
        bool sequence_broken = false;
        unsigned long current_starting_time = multiplier * timetable[0].bus_id;
        int i;

        // Need to keep this loop constant or else we will OOM
        while (true) {
            sequence_broken = false;
            current_starting_time = multiplier * timetable[0].bus_id;

            for (i = 1; i < timetable.size(); i++) {
                if ((current_starting_time + timetable[i].offset) % timetable[i].bus_id != 0) {
                    sequence_broken = true;
                    break;
                }
            }

            if (!sequence_broken) {
                return current_starting_time;
            }

            multiplier++;
        } */
    }
}