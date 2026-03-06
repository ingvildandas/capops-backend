cmake_minimum_required(VERSION 3.5)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(capops
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---- Find Qt6 ----
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Network 
    HttpServer 
    WebSockets
)

# ---- Fetch Catch2 ----
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

# ---- Fetch SQLite3 ----
FetchContent_Declare(
    sqlite3 
    GIT_REPOSITORY https://github.com/sjinks/sqlite3-cmake.git 
    GIT_TAG v3.49.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(sqlite3)

if(TARGET SQLite3)
    target_compile_options(SQLite3 PRIVATE
        $<$<COMPILE_LANG_AND_ID:C,GNU,Clang>:-Wno-stringop-overread>
    )
endif()

# ---- Fetch hiredis (necessary redis-plus-plus dependency)
FetchContent_Declare(
    hiredis
    GIT_REPOSITORY https://github.com/redis/hiredis.git
    GIT_TAG v1.3.0
    GIT_SHALLOW TRUE
)

set(DISABLE_TESTS ON CACHE BOOL "Disable hiredis tests" FORCE)
set(ENABLE_EXAMPLES OFF CACHE BOOL "Disable hiredis examples/tests" FORCE)

FetchContent_MakeAvailable(hiredis)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/hiredis_include/hiredis)

file(COPY
    ${hiredis_SOURCE_DIR}/hiredis.h
    ${hiredis_SOURCE_DIR}/read.h
    ${hiredis_SOURCE_DIR}/sds.h
    ${hiredis_SOURCE_DIR}/async.h
    ${hiredis_SOURCE_DIR}/alloc.h
    DESTINATION ${CMAKE_BINARY_DIR}/hiredis_include/hiredis
)
set(HIREDIS_HEADER ${CMAKE_BINARY_DIR}/hiredis_include)
set(HIREDIS_LIB hiredis)

if(TARGET hiredis AND NOT TARGET hiredis::hiredis)
    add_library(hiredis::hiredis ALIAS hiredis)
endif()

# ---- Fetch redis-plus-plus ----
FetchContent_Declare(
    redis-plus-plus
    GIT_REPOSITORY https://github.com/sewenew/redis-plus-plus.git
    GIT_TAG 1.3.9
    GIT_SHALLOW TRUE
)
set(REDIS_PLUS_PLUS_BUILD_TEST OFF CACHE BOOL "Disable building redis-plus-plus tests" FORCE)
FetchContent_MakeAvailable(redis-plus-plus)

# ---- Executables ----
file(GLOB_RECURSE APP_SOURCES 
    app/main.cpp
    src/*.cpp
    include/*.hpp
    resources/*.qrc
)
add_executable(capops ${APP_SOURCES})

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
        Qt6::WebSockets
        SQLite::SQLite3
        redis++::redis++
)

# ---- Tests ----
option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
    include(CTest) 
    enable_testing()
    
    add_executable(tests
        tests/test.cpp
    )

    target_link_libraries(tests 
        PRIVATE 
            Catch2::Catch2WithMain 
    )

    include(Catch)
    catch_discover_tests(tests)
endif()
