#pragma once

#include <map>

namespace day14 {
    class Mask {
        protected:
            std::map<int, int> forced_mask;
        public:
            void set_mask(std::string new_mask);
            unsigned long apply_number(unsigned long to_apply);
    };

    unsigned long sum_bitmask();
}