target_sources(libnmea PRIVATE
        gpgga.c
        gpgsa.c
        gpgsv.c
        gprmc.c
        parse.c
        )

target_include_directories(libnmea PRIVATE ${CMAKE_SOURCE_DIR}/inc/nmea)
