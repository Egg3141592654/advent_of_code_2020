#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "day5.hpp"

namespace day5 {
    int get_row_from_boarding_pass(std::string boarding_pass, int parse_index = 0, int lower_possible_row = 0, int highest_possible_row = 127) {
        int range = (highest_possible_row - lower_possible_row + 1) / 2;

        if (range == 0) {
            //base case, return one of these numbers
            return lower_possible_row;
        } else {
            //recurse through another time
            return boarding_pass[parse_index] == 'F' ? get_row_from_boarding_pass(boarding_pass, parse_index + 1, lower_possible_row, highest_possible_row - range) :
                get_row_from_boarding_pass(boarding_pass, parse_index + 1, lower_possible_row + range, highest_possible_row);
        }
    }

    int get_seat_from_boarding_pass(std::string boarding_pass, int parse_index = 7, int lower_possible_seat = 0, int highest_possible_seat = 7) {
        int range = (highest_possible_seat - lower_possible_seat + 1) / 2;

        if (highest_possible_seat - lower_possible_seat == 1) {
            //base case, return one of these numbers
            return boarding_pass[parse_index] == 'L' ? lower_possible_seat : highest_possible_seat;
        } else {
            // recurse through another time
            return boarding_pass[parse_index] == 'L' ? get_seat_from_boarding_pass(boarding_pass, parse_index + 1, lower_possible_seat, highest_possible_seat - range) :
                get_seat_from_boarding_pass(boarding_pass, parse_index + 1, lower_possible_seat + range, highest_possible_seat);
        }
    }

    SeatAssignment parse_boarding_pass(std::string boarding_pass) {
        return SeatAssignment{get_row_from_boarding_pass(boarding_pass), get_seat_from_boarding_pass(boarding_pass)};
    }

    std::vector<std::string> parse_file_into_lines() {
        std::fstream infile("/examples/day5.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int get_highest_detected_seat_number() {
        std::vector<std::string> boarding_passes;
        boarding_passes = parse_file_into_lines();

        int highest_value_seat_id = 0;
        for (int i = 0; i < boarding_passes.size(); i++) {
            SeatAssignment seat = parse_boarding_pass(boarding_passes[i]);

            std::cout << "DEBUG assignment row: " << seat.row << ", seat: " << seat.seat << std::endl;

            int detected_seat_id = seat.row * 8 + seat.seat;
            if (detected_seat_id > highest_value_seat_id)
                highest_value_seat_id = detected_seat_id;
        }
        return highest_value_seat_id;
    }
}