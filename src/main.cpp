// Your First C++ Program

#include <iostream>
#include <sstream>

#include "day1.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Incompatible run, please enter a day for the code advent to execute!" << std::endl;
        exit(1);
    }

    std::istringstream iss( argv[1] );
    int day;

    if (iss >> day)
    {
        switch (day) {
            case 1:
                {
                    std::cout << "Executing Day 1" << std::endl;
                    int answer = day1::execute();
                    std:: cout << "The answer to your question is: " << answer << "!" << std::endl;
                }
                break;
            default:
                std::cout << "Aborting since you selected a day that doesn't exist!" << std::endl;                
        }
    }
    else {
        std::cout << "Failed to convert first argument to integer. Bailing" << std::endl;
        exit(1);
    }
}