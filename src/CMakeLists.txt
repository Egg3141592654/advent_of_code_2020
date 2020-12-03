add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)

add_executable(main main.cpp)
target_link_libraries(main day1 day2 day3)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(day1 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/day1"
                          "${PROJECT_SOURCE_DIR}/src/day2"
                          "${PROJECT_SOURCE_DIR}/src/day3"
                          )