enable_testing()

include_directories(
    "${PROJECT_SOURCE_DIR}/tests/MosquitoNet/cpp/single-include"
    )

add_executable(${MAIN_EXECUTABLE} tests.cpp)

# Turn on C++14 support
set_property(TARGET ${MAIN_EXECUTABLE} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${MAIN_EXECUTABLE} PROPERTY CXX_STANDARD 14)

add_test(NAME ${MAIN_EXECUTABLE} COMMAND ${MAIN_EXECUTABLE})