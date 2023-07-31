add_subdirectory(nmea)
add_subdirectory(parsers)

target_include_directories(libnmea PRIVATE ../inc)
target_include_directories(libnmea PRIVATE ../inc/nmea)
