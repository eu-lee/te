cmake_minimum_required(VERSION 3.20)

project(te LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v7.0.1
)

FetchContent_MakeAvailable(ftxui)

add_executable(te
    src/main.cpp
    src/document.cpp
)

target_link_libraries(te PRIVATE
    ftxui::ftxui
)
