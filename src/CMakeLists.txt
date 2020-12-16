add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)

add_executable(main main.cpp)
target_link_libraries(main day1 day2 day3 day4 day5 day6 day7 day8 day9 day10 day11 day12 day13 day14)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(day1 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/day1"
                          "${PROJECT_SOURCE_DIR}/src/day2"
                          "${PROJECT_SOURCE_DIR}/src/day3"
                          "${PROJECT_SOURCE_DIR}/src/day4"
                          "${PROJECT_SOURCE_DIR}/src/day5"
                          "${PROJECT_SOURCE_DIR}/src/day6"
                          "${PROJECT_SOURCE_DIR}/src/day7"
                          "${PROJECT_SOURCE_DIR}/src/day8"
                          "${PROJECT_SOURCE_DIR}/src/day9"
                          "${PROJECT_SOURCE_DIR}/src/day10"
                          "${PROJECT_SOURCE_DIR}/src/day11"
                          "${PROJECT_SOURCE_DIR}/src/day12"
                          "${PROJECT_SOURCE_DIR}/src/day13"
                          "${PROJECT_SOURCE_DIR}/src/day14"
                          )