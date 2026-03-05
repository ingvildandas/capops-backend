cmake_minimum_required(VERSION 3.31)

project(capops
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(CTest) 

# ---- Find Qt6 ----
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# ---- Fetch Catch2 ----
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# ---- Fetch SQLite3 ----
include(FetchContent)
FetchContent_Declare(
    sqlite3 
    GIT_REPOSITORY https://github.com/sjinks/sqlite3-cmake.git 
    GIT_TAG v3.49.1
)
FetchContent_MakeAvailable(sqlite3)

# ---- Fetch hiredis (necessary redis-plus-plus dependency)
FetchContent_Declare(
    hiredis
    GIT_REPOSITORY https://github.com/redis/hiredis.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(hiredis)

# ---- Fetch redis-plus-plus ----
FetchContent_Declare(
    redis-plus-plus
    GIT_REPOSITORY https://github.com/sewenew/redis-plus-plus.git
    GIT_TAG v3.5.4
    FIND_PACKAGE_ARGS DISABLE_TESTS 
)
set(REDIS_PLUS_PLUS_BUILD_TEST OFF CACHE BOOL "Disable building redis-plus-plus tests" FORCE)
FetchContent_MakeAvailable(redis-plus-plus)

# ---- Library ----
target_include_directories(capops 
    PRIVATE 
        include
)

target_link_libraries(capops 
    PRIVATE 
        Qt6::Core 
        Qt6::Network
        Qt6::HttpServer
        Qt6::WebSocket
)

target_link_libraries(capops 
    PRIVATE
        SQLite::SQLite3
)

target_link_libraries(capops 
    PRIVATE 
        redis++::redis++
)

# ---- Executables ----
file(GLOB_RECURSE APP_SOURCES 
    app/main.cpp
    src/*.cpp
    include/*.hpp
    resources/*.qrc
)
add_executable(capops ${APP_SOURCES})

# ---- Tests ----
add_executable(tests
    tests/test.cpp
)

target_link_libraries(tests 
    PRIVATE 
    Catch2::Catch2WithMain 
    Qt6::Core Qt6::Widgets
)
