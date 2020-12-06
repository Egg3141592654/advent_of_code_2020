#include "day6.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <set>

namespace day6 {
    CustomsGroup::CustomsGroup(std::vector<std::string> member_answers) {
        member_questions_answered = member_answers;
    }

    int CustomsGroup::check_yes_answers() {
        int questions_answered_yes = 0;
        std::set<char> questions_fully_answered;

        for (int i = 0; i < member_questions_answered.size(); ++i) {
            // scroll through string and see what answers this person answered yes to
            for (int j = 0; j < member_questions_answered[i].length(); ++j) {
                auto insert_result = questions_fully_answered.insert(member_questions_answered[i][j]);
                if (insert_result.second) {
                    questions_answered_yes++;
                }
            }
        }

        return questions_answered_yes;
    }

    int CustomsGroup::number_unanimous_yes_answers() {
        int questions_answered_yes = 0;
        std::map<char, int> grouped_member_answers;

        for (int i = 0; i < member_questions_answered.size(); ++i) {
            // scroll through string and see what answers this person answered yes to
            for (int j = 0; j < member_questions_answered[i].length(); ++j) {
                char answered_question = member_questions_answered[i][j];

                if (grouped_member_answers.find(answered_question) == grouped_member_answers.end()) {
                    grouped_member_answers[answered_question] = 1;
                }
                else {
                    grouped_member_answers[answered_question]++;
                }
            }
        }

        // iterate though map and see which entries have an int value = the number of members in the group.
        for (auto it = grouped_member_answers.begin(); it != grouped_member_answers.end(); ++it) {
            if (it->second == member_questions_answered.size()) {
                questions_answered_yes++;
            }
        }

        return questions_answered_yes;
    }


    std::vector<std::string> parse_file_into_lines() {
        std::fstream infile("/examples/day6.txt");
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(infile, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    int sum_yes_custom_form_answers_by_group() {
        auto group_answers_list_raw = parse_file_into_lines();
        std::vector<std::string> group_aggregator;
        int summed_unanimous_answers = 0;

        for (int i = 0; i < group_answers_list_raw.size(); ++i) {
            if (group_answers_list_raw[i].length() > 0) {
                group_aggregator.push_back(group_answers_list_raw[i]);
            }
            else {
                CustomsGroup group(group_aggregator);
                summed_unanimous_answers += group.check_yes_answers();
                group_aggregator.clear();
            }
        }

        // be sure we got the last one
        if (group_aggregator.size()) {
            CustomsGroup group(group_aggregator);
            summed_unanimous_answers += group.check_yes_answers();
            group_aggregator.clear();
        }

        return summed_unanimous_answers;
    }

    int sum_unanimous_form_answers_by_group() {
        auto group_answers_list_raw = parse_file_into_lines();
        std::vector<std::string> group_aggregator;
        int summed_unanimous_answers = 0;

        for (int i = 0; i < group_answers_list_raw.size(); ++i) {
            if (group_answers_list_raw[i].length() > 0) {
                group_aggregator.push_back(group_answers_list_raw[i]);
            }
            else {
                CustomsGroup group(group_aggregator);
                summed_unanimous_answers += group.number_unanimous_yes_answers();
                group_aggregator.clear();
            }
        }

        // be sure we got the last one
        if (group_aggregator.size()) {
            CustomsGroup group(group_aggregator);
            summed_unanimous_answers += group.number_unanimous_yes_answers();
            group_aggregator.clear();
        }

        return summed_unanimous_answers;
    }
}