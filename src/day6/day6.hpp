#pragma once

#include <string>
#include <vector>

namespace day6 {
    class CustomsGroup {
        private:
            std::vector<std::string> member_questions_answered;
        public:
            CustomsGroup(std::vector<std::string> member_answers);
            int check_yes_answers();
            int number_unanimous_yes_answers();
    };

    int sum_yes_custom_form_answers_by_group();
    int sum_unanimous_form_answers_by_group();
}