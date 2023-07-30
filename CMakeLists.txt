cmake_minimum_required (VERSION 3.20)
project(libnmea C)

set(LIBNMEA_MAJOR_VERSION 0)
set(LIBNMEA_MINOR_VERSION 1)
set(LIBNMEA_PATCH_VERSION 2)
set(LIBNMEA_VERSION
  ${LIBNMEA_MAJOR_VERSION}.${LIBNMEA_MINOR_VERSION}.${LIBNMEA_PATCH_VERSION})

add_library(libnmea STATIC src/nmea/nmea.c)
add_subdirectory(src)

add_executable(demo examples/parse_stdin.c)
target_include_directories(demo PRIVATE inc)
target_link_libraries(demo libnmea)
