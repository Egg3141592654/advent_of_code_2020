#pragma once

namespace day12 {

    class Ship {
        protected:
            int x_coord = 0;
            int y_coord = 0;
            int facing = 0;

        public:
            void move_distance(int x_coord, int y_coord);
            void move_forward(int spaces);
            void rotate_ship(int degrees);
            int get_distance_from_origin();
            void print_ship_statistics();
    };

    class WaypointShip: public Ship {
        protected:
            int waypoint_x = 10;
            int waypoint_y = 1;
        public:
            void move_waypoint_distance(int x_coord, int y_coord);
            void move_to_waypoint(int multiplier);
            void rotate_waypoint(int degrees);
            void print_ship_statistics();
    };

    int get_manhattan_distance_traveled();
    int get_manhattan_ship_distance_traveled();
}