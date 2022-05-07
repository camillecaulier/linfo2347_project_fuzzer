cmake_minimum_required(VERSION 3.16)
project(project C)

set(CMAKE_C_STANDARD 11)

add_executable(project
        src/fuzzer.c help.c help_new.c archive_creator.c corporate_espionage.c test_shit.c)
