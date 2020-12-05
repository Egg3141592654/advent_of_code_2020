#pragma once

namespace day5 {
    struct SeatAssignment {
        int row;
        int seat;
    };

    int get_highest_detected_seat_number();
    int get_your_seat_assignment();
}