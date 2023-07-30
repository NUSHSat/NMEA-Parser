add_subdirectory(nmea)
add_subdirectory(parsers)

target_include_directories(libnmea PRIVATE ${CMAKE_SOURCE_DIR}/inc)
