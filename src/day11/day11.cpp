#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace day11 {
    int count_occupied_adjacent_seats(std::vector<std::string> seat_map, int row, int seat) {
        int occupied_spaces = 0;
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = seat - 1; j <= seat + 1; j++) {
                // skip the current seat because that doesn't count in the rules
                if ((i == row) && (j == seat)) {
                    continue;
                }

                // do a bounds check for both indicies (above 0 and less than the length of the string)
                bool row_valid = i >= 0 && i < seat_map.size();
                bool seat_valid = j >= 0; j < seat_map[row].length();

                if (row_valid && seat_valid && (seat_map[i][j] == '#')) {
                    occupied_spaces++;
                }
            }
        }

        return occupied_spaces;
    }

    int count_occupied_adjacent_seats_by_sight(std::vector<std::string> seat_map, int row, int seat) {
        int occupied_spaces = 0;

        // north west
        int row_scroll = row - 1;
        int seat_scroll = seat - 1;
        while (row_scroll >= 0 && seat_scroll >= 0) {
            if (seat_map[row_scroll][seat_scroll] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[row_scroll][seat_scroll] == 'L') {
                break;
            }

            row_scroll--;
            seat_scroll--;
        }

        // North
        for (int i = row - 1; i >= 0; i--) {
            if (seat_map[i][seat] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[i][seat] == 'L') {
                break;
            }
        }

        // North East
        row_scroll = row - 1;
        seat_scroll = seat + 1;
        while (row_scroll >= 0 && seat_scroll < seat_map[row].length()) {
            if (seat_map[row_scroll][seat_scroll] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[row_scroll][seat_scroll] == 'L') {
                break;
            }

            row_scroll--;
            seat_scroll++;
        }

        // East
        for (int i = seat + 1; i < seat_map[row].size(); i++) {
            if (seat_map[row][i] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[row][i] == 'L') {
                break;
            }
        }

        // South East
        row_scroll = row + 1;
        seat_scroll = seat + 1;
        while (row_scroll < seat_map.size() && seat_scroll < seat_map[row].length()) {
            if (seat_map[row_scroll][seat_scroll] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[row_scroll][seat_scroll] == 'L') {
                break;
            }

            row_scroll++;
            seat_scroll++;
        }

        // South
        for (int i = row + 1; i < seat_map.size(); i++) {
            if (seat_map[i][seat] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[i][seat] == 'L') {
                break;
            }
        }

        // South West
        row_scroll = row + 1;
        seat_scroll = seat - 1;
        while (row_scroll < seat_map.size() && seat_scroll >= 0) {
            if (seat_map[row_scroll][seat_scroll] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[row_scroll][seat_scroll] == 'L') {
                break;
            }

            row_scroll++;
            seat_scroll--;
        }

        // West
        for (int i = seat - 1; i >= 0; i--) {
            if (seat_map[row][i] == '#') {
                occupied_spaces++;
                break;
            }

            if (seat_map[row][i] == 'L') {
                break;
            }
        }

        return occupied_spaces;
    }

    bool apply_rules(std::vector<std::string> current_seat_map, std::vector<std::string> &next_map) {
        bool modified = false;

        // Copy over the map to ensure we are talking about the most recent map
        next_map = current_seat_map;

        // iterate through each index and apply the rules
        for (int row = 0; row < current_seat_map.size(); row++) {
            for (int seat = 0; seat < current_seat_map[row].length(); seat++) {
                if (current_seat_map[row][seat] == '.') {
                    // The floor does nothing
                    continue;
                }

                int occupied_neighbors = count_occupied_adjacent_seats(current_seat_map, row, seat);

                // Apply occupancy rules
                if (current_seat_map[row][seat] == 'L' && (occupied_neighbors == 0)) {
                    // switch new seat to be occupied
                    next_map[row][seat] = '#';
                    modified = true;
                }

                if (current_seat_map[row][seat] == '#' && (occupied_neighbors >= 4)) {
                    // Occupied seat becomes empty
                    next_map[row][seat] = 'L';
                    modified = true;
                }
            }
        }

        return modified;
    }

    bool apply_sight_rules(std::vector<std::string> current_seat_map, std::vector<std::string> &next_map) {
        bool modified = false;

        // Copy over the map to ensure we are talking about the most recent map
        next_map = current_seat_map;

        // iterate through each index and apply the rules
        for (int row = 0; row < current_seat_map.size(); row++) {
            for (int seat = 0; seat < current_seat_map[row].length(); seat++) {
                if (current_seat_map[row][seat] == '.') {
                    // The floor does nothing
                    continue;
                }

                int occupied_neighbors = count_occupied_adjacent_seats_by_sight(current_seat_map, row, seat);

                // Apply occupancy rules
                if (current_seat_map[row][seat] == 'L' && (occupied_neighbors == 0)) {
                    // switch new seat to be occupied
                    next_map[row][seat] = '#';
                    modified = true;
                }

                if (current_seat_map[row][seat] == '#' && (occupied_neighbors >= 5)) {
                    // Occupied seat becomes empty
                    next_map[row][seat] = 'L';
                    modified = true;
                }
            }
        }

        return modified;
    }

    int count_occupied_seats(std::vector<std::string> seat_map) {
        int seats_occupied = 0;
        for (auto row : seat_map) {
            for (int i = 0; i < row.length(); i++) {
                if (row[i] == '#') {
                    seats_occupied++;
                }
            }
        }

        return seats_occupied;
    }

    std::vector<std::string> parse_file_into_string_list() {
        std::fstream infile("/examples/day11.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int count_occupied_seats() {
        auto seatmap = parse_file_into_string_list();

        std::vector<std::string> next_cycle = seatmap;

        while(apply_rules(seatmap, next_cycle)) {
            seatmap = next_cycle;
        }

        return count_occupied_seats(seatmap);
    }

    int count_occupied_seats_sightline() {
        auto seatmap = parse_file_into_string_list();

        std::vector<std::string> next_cycle = seatmap;

        while(apply_sight_rules(seatmap, next_cycle)) {
            seatmap = next_cycle;
        }

        return count_occupied_seats(seatmap);
    }
}