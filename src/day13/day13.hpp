#pragma once

namespace day13 {
    struct BusOffset {
        int bus_id;
        int offset;
    };

    int get_soonest_bus_id_times_waittime();
    unsigned long get_first_sequential_bus_departure_timestanp(); 
}