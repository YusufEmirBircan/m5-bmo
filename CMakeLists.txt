cmake_minimum_required(VERSION 3.16)

file (STRINGS version.txt BUILD_NUMBER)
set(PROJECT_VER ${BUILD_NUMBER})
add_compile_options(-Wno-missing-field-initializers -Wno-error -Wno-format -Wno-format-security)
add_compile_definitions(BUILD_NUMBER="${BUILD_NUMBER}")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

idf_build_set_property(COMPILE_OPTIONS "-Wno-error" APPEND)
idf_build_set_property(COMPILE_OPTIONS "-Wno-format" APPEND)
idf_build_set_property(MINIMAL_BUILD ON)
project(M5Gemini)
