#ifndef INC_NMEA_GPGGA_H
#define INC_NMEA_GPGGA_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <nmea.h>

typedef struct {
	nmea_s base;
	// struct tm time;
	nmea_position longitude;
	nmea_position latitude;
	int n_satellites;
	double altitude;
	char altitude_unit;
} nmea_gpgga_s;

int geofenceShape(nmea_s * data, nmea_position latitude, nmea_position longitude, float radius, char type) { 
	
	nmea_gpgga_s * loc = (nmea_gpgga_s *) data;

	float centerLat = latitude.degrees + (latitude.minutes / 60);
	float centerLong = longitude.degrees + (longitude.minutes / 60);
	float currentLat;
	float currentLong;

	if (longitude.cardinal == 'W') {
		centerLong = -centerLong;
	} 

	if (latitude.cardinal == 'S') {
		centerLat = -centerLat;
	}	

	currentLat = loc->latitude.degrees + (loc->latitude.minutes / 60);
	currentLong = loc->longitude.degrees + (loc->longitude.minutes / 60);	
	if (loc->longitude.cardinal == 'W') {
		currentLong = -currentLong;
	} 

	if (loc->latitude.cardinal == 'S') {
		currentLat = -currentLat;
	}

	if (type == 'c') {
		if ((currentLat - centerLat) * (currentLat - centerLat) + (currentLong - centerLong) * (currentLong - centerLong) <= radius * radius) {
			return 1;
		} else {
			return 0;
		}
	} else if (type == 's') {
		if (currentLat <= centerLat + radius && currentLat >= centerLat - radius && currentLong <= centerLong + radius && currentLong >= centerLong - radius) {
			return 1;
		} else {
			return 0;
		}
	}

	return 0;
}

int geofenceShape2(nmea_s * data, float centerLat, float centerLong, float radius, char type) { 

	nmea_gpgga_s * loc = (nmea_gpgga_s *) data;
	float currentLat;
	float currentLong;

	currentLat = loc->latitude.degrees + (loc->latitude.minutes / 60);
	currentLong = loc->longitude.degrees + (loc->longitude.minutes / 60);	
	if (loc->longitude.cardinal == 'W') {
		currentLong = -currentLong;
	} 

	if (loc->latitude.cardinal == 'S') {
		currentLat = -currentLat;
	}

	if (type == 'c') {
		if ((currentLat - centerLat) * (currentLat - centerLat) + (currentLong - centerLong) * (currentLong - centerLong) <= radius * radius) {
			return 1;
		} else {
			return 0;
		}
	} else if (type == 's') {
		if (currentLat <= centerLat + radius && currentLat >= centerLat - radius && currentLong <= centerLong + radius && currentLong >= centerLong - radius) {
			return 1;
		} else {
			return 0;
		}
	}

	return 0;
}

/* Value indexes */
// #define NMEA_GPGGA_TIME			0
#define NMEA_GPGGA_LATITUDE		1
#define NMEA_GPGGA_LATITUDE_CARDINAL	2
#define NMEA_GPGGA_LONGITUDE		3
#define NMEA_GPGGA_LONGITUDE_CARDINAL	4
#define NMEA_GPGGA_N_SATELLITES		6
#define NMEA_GPGGA_ALTITUDE		8
#define NMEA_GPGGA_ALTITUDE_UNIT	9

#endif  /* INC_NMEA_GPGGA_H */
