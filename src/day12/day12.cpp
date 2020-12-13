#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "day12.hpp"

namespace day12 {
    void Ship::move_distance(int x_coord, int y_coord) {
        this->x_coord += x_coord;
        this->y_coord += y_coord;
    }

    void Ship::rotate_ship(int degrees) {
        // Degrees is probably a modulo of 90, divide by 90
        int rotations = degrees / 90;

        this->facing += rotations;

        // wrap to make sure that we aren't facing someplace we shouldn't be
        if (this->facing < 0) {
            this->facing += 4;
        }
        
        if (this->facing > 3) {
            this->facing -= 4;
        }
    }

    void Ship::move_forward(int spaces) {
        switch (this->facing) {
            case 0:
                // East
                this->x_coord += spaces;
                break;
            case 1:
                // South
                this->y_coord -= spaces;
                break;
            case 2:
                // West
                this->x_coord -= spaces;
                break;
            default:
                // North
                this->y_coord += spaces;

        }
    }

    int Ship::get_distance_from_origin() {
        return std::abs(this->x_coord) + std::abs(this->y_coord);
    }

    void Ship::print_ship_statistics() {
        std::cout << "DEBUG SHIP STATISTICS: x: " << this->x_coord << " y: " << this->y_coord << " heading: " << this->facing << std::endl;
    }

    void WaypointShip::move_waypoint_distance(int x_coord, int y_coord) {
        this->waypoint_x += x_coord;
        this->waypoint_y += y_coord;
    }

    void WaypointShip::move_to_waypoint(int multiplier) {
        this->x_coord += multiplier * this->waypoint_x;
        this->y_coord += multiplier * this->waypoint_y;
    }
    
    void WaypointShip::rotate_waypoint(int degrees) {
        // Degrees is probably a modulo of 90, divide by 90
        int rotations = degrees / 90;

        // wrap to make sure that we aren't facing someplace we shouldn't be
        if (rotations < -2) {
            rotations += 4;
        }
        
        if (rotations > 2) {
            rotations -= 4;
        }

        // std::cout << "DEBUG ROTATIONS FROM INPUT: " << degrees << " is " << rotations << std::endl;

        switch (rotations) {
            case -1:
            {
                // Rotate right 90
                int orig_x = this->waypoint_x;
                int orig_y = this->waypoint_y;
                this->waypoint_x = orig_y;
                this->waypoint_y = -orig_x;
            }
            break;
            case 1: 
            {
                // rotate left 90
                int orig_x = this->waypoint_x;
                int orig_y = this->waypoint_y;
                this->waypoint_x = -orig_y;
                this->waypoint_y = orig_x;
            }
            break;
            case 2:
            case -2:
            // flip coordinates
            this->waypoint_y = -this->waypoint_y;
            this->waypoint_x = -this->waypoint_x;
            break;
            default:
            break;
        }
    }

    void WaypointShip::print_ship_statistics() {
        std::cout << "DEBUG SHIP STATISTICS: x: " << this->x_coord << " y: " << this->y_coord << " waypoint statistics: x:" << this->waypoint_x << " y: " << this->waypoint_y << std::endl;
    }

    std::vector<std::string> parse_file_into_string_list() {
        std::fstream infile("/examples/day12.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int get_manhattan_distance_traveled() {
        auto directions = parse_file_into_string_list();

        Ship ship;
        for (auto instruction : directions) {
            char direction = instruction[0];
            int number = std::stoi(instruction.substr(1));
            switch (direction) {
                case 'N':
                    ship.move_distance(0, number);
                    break;
                case 'S':
                    ship.move_distance(0, -number);
                    break;
                case 'E':
                    ship.move_distance(number, 0);
                    break;
                case 'W':
                    ship.move_distance(-number, 0);
                    break;
                case 'L':
                    ship.rotate_ship(-number);
                    break;
                case 'R':
                    ship.rotate_ship(number);
                    break;
                default:
                    ship.move_forward(number);
            }
        }

        return ship.get_distance_from_origin();
    }

    int get_manhattan_ship_distance_traveled() {
        auto directions = parse_file_into_string_list();

        WaypointShip ship;
        for (auto instruction : directions) {
            char direction = instruction[0];
            int number = std::stoi(instruction.substr(1));
            switch (direction) {
                case 'N':
                    ship.move_waypoint_distance(0, number);
                    break;
                case 'S':
                    ship.move_waypoint_distance(0, -number);
                    break;
                case 'E':
                    ship.move_waypoint_distance(number, 0);
                    break;
                case 'W':
                    ship.move_waypoint_distance(-number, 0);
                    break;
                case 'L':
                    ship.rotate_waypoint(number);
                    break;
                case 'R':
                    ship.rotate_waypoint(-number);
                    break;
                default:
                    ship.move_to_waypoint(number);
            }

            ship.print_ship_statistics();
        }

        return ship.get_distance_from_origin();
    }
}