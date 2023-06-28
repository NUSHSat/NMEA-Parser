#ifndef INC_NMEA_GPRMC_H
#define INC_NMEA_GPRMC_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <nmea.h>

typedef struct {
	nmea_s base;
	struct tm date_time;
	nmea_position longitude;
	nmea_position latitude;
} nmea_gprmc_s;

/* Value indexes */
#define NMEA_GPRMC_TIME			0
#define NMEA_GPRMC_LATITUDE		1
#define NMEA_GPRMC_LATITUDE_CARDINAL	2
#define NMEA_GPRMC_LONGITUDE		3
#define NMEA_GPRMC_LONGITUDE_CARDINAL	4
#define NMEA_GPRMC_DATE			5
#endif  /* INC_NMEA_GPRMC_H */
