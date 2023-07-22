#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <nmea.h>

#include <nmea/gpgga.h>
#include <nmea/gprmc.h>
#include <nmea/gpgsa.h>
#include <nmea/gpgsv.h>

char buffer[4096];
int gps_fd;

/**
 * Callback function when receiving SIGINT signal. Frees memory and quits
 * the application.
 *
 * signum The current signal invoked, always SIGINT.
 */
// void
// sig_quit(int signum)
// {
// 	close(gps_fd);
// 	exit(EXIT_SUCCESS);
// }

// /**
//  * Register the signal callback function.
//  *
//  * Returns RETURN_SUCCESS on success and RETURN_FAILURE on error.
//  */
// int
// register_signals()
// {
// 	struct sigaction kill_action;
// 	kill_action.sa_handler = sig_quit;

// 	if (-1 == sigemptyset(&kill_action.sa_mask)) {
// 		perror("sigemptyset");
// 		return -1;
// 	}
// 	kill_action.sa_flags = 0;
// 	if (-1 == sigaction(SIGINT, &kill_action, NULL)) {
// 		perror("sigaction");
// 		return -1;
// 	}

// 	return 0;
// }

// int geofenceShape(nmea_gpgga_s * loc, nmea_position latitude, nmea_position longitude, float radius, char type) { 

// 	float centerLat = latitude.degrees + (latitude.minutes / 60);
// 	float centerLong = longitude.degrees + (longitude.minutes / 60);
// 	float currentLat;
// 	float currentLong;

// 	if (longitude.cardinal == 'W') {
// 		centerLong = -centerLong;
// 	} 

// 	if (latitude.cardinal == 'S') {
// 		centerLat = -centerLat;
// 	}	

// 	currentLat = loc->latitude.degrees + (loc->latitude.minutes / 60);
// 	currentLong = loc->longitude.degrees + (loc->longitude.minutes / 60);	
// 	if (loc->longitude.cardinal == 'W') {
// 		currentLong = -currentLong;
// 	} 

// 	if (loc->latitude.cardinal == 'S') {
// 		currentLat = -currentLat;
// 	}

// 	if (type == 'c') {
// 		if ((currentLat - centerLat) * (currentLat - centerLat) + (currentLong - centerLong) * (currentLong - centerLong) <= radius * radius) {
// 			return 1;
// 		} else {
// 			return 0;
// 		}
// 	} else if (type == 's') {
// 		if (currentLat <= centerLat + radius && currentLat >= centerLat - radius && currentLong <= centerLong + radius && currentLong >= centerLong - radius) {
// 			return 1;
// 		} else {
// 			return 0;
// 		}
// 	}

// 	return 0;
// }

// int geofenceShape2(nmea_gpgga_s * loc, float centerLat, float centerLong, float radius, char type) { 
// 	float currentLat;
// 	float currentLong;

// 	currentLat = loc->latitude.degrees + (loc->latitude.minutes / 60);
// 	currentLong = loc->longitude.degrees + (loc->longitude.minutes / 60);	
// 	if (loc->longitude.cardinal == 'W') {
// 		currentLong = -currentLong;
// 	} 

// 	if (loc->latitude.cardinal == 'S') {
// 		currentLat = -currentLat;
// 	}

// 	if (type == 'c') {
// 		if ((currentLat - centerLat) * (currentLat - centerLat) + (currentLong - centerLong) * (currentLong - centerLong) <= radius * radius) {
// 			return 1;
// 		} else {
// 			return 0;
// 		}
// 	} else if (type == 's') {
// 		if (currentLat <= centerLat + radius && currentLat >= centerLat - radius && currentLong <= centerLong + radius && currentLong >= centerLong - radius) {
// 			return 1;
// 		} else {
// 			return 0;
// 		}
// 	}

// 	return 0;
// }



int
main(int argc, char **argv)
{
	// int read_bytes, total_bytes = 0;
	// char *start, *end;
	// sigset_t block_mask;


	// gps_fd = STDIN_FILENO;

	// /* Register signal handler for SIGINT */
	// if (-1 == register_signals()) {
	// 	exit(EXIT_FAILURE);
	// }

	// /* Prepare signal blocking */
	// if (-1 == sigemptyset(&block_mask) || -1 == sigaddset(&block_mask, SIGINT)) {
	// 	perror("prepare signal blocking");
	// 	exit(EXIT_FAILURE);
	// }

	// while (1) {
	// 	// char buf[255];
	// 	// nmea_s *data;

	// 	// /* Unlock signal */
	// 	// sigprocmask(SIG_UNBLOCK, &block_mask, NULL);

	// 	// read_bytes = read(gps_fd, buffer + total_bytes, 20);
	// 	// if (-1 == read_bytes) {
	// 	// 	perror("read stdin");
	// 	// 	exit(EXIT_FAILURE);
	// 	// }
	// 	// if (0 == read_bytes) {
	// 	// 	sig_quit(SIGINT);
	// 	// }

	// 	// total_bytes += read_bytes;

	// 	// /* Block signal */
	// 	// sigprocmask(SIG_BLOCK, &block_mask, NULL);

	// 	// /* find start (a dollar $ign) */
	// 	// start = memchr(buffer, '$', total_bytes);
	// 	// if (NULL == start) {
	// 	// 	total_bytes = 0;
	// 	// 	continue;
	// 	// }

	// 	// /* find end of line */
	// 	// end = memchr(start, NMEA_END_CHAR_1, total_bytes - (start - buffer));
	// 	// if (NULL == end || NMEA_END_CHAR_2 != *(++end)) {
	// 	// 	continue;
	// 	// }


	// 	/* buffer empty? */
	// 	if (end == buffer + total_bytes) {
	// 		total_bytes = 0;
	// 		continue;
	// 	}

	// 	/* copy rest of buffer to beginning */
	// 	if (buffer != memmove(buffer, end, total_bytes - (end - buffer))) {
	// 		total_bytes = 0;
	// 		continue;
	// 	}

	// 	total_bytes -= end - buffer;
	// }

	// close(gps_fd);
	if (argc != 2) {
		printf("Usage: %s <nmea_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char buf[255];
	printf("Parsing NMEA sentence: %s\n", argv[1]);
	nmea_s * data = nmea_parse(argv[1], strlen(argv[1]), 0);
	if (NULL != data) {
		if (0 < data->errors) {
			printf("WARN: The sentence struct contains parse errors!\n");
		}
		nmea_t type = nmea_get_type(argv[1]);
		printf("Sentence type: %d\n", type);
		if (NMEA_GPGGA == type) {
			printf("GPGGA sentence\n");
			nmea_gpgga_s *gpgga = (nmea_gpgga_s *) data;
			printf("Longitude:\n");
			printf("  Degrees: %d\n", gpgga->longitude.degrees);
			printf("  Minutes: %f\n", gpgga->longitude.minutes);
			printf("  Cardinal: %c\n", (char) gpgga->longitude.cardinal);
			printf("Latitude:\n");
			printf("  Degrees: %d\n", gpgga->latitude.degrees);
			printf("  Minutes: %f\n", gpgga->latitude.minutes);
			printf("  Cardinal: %c\n", (char) gpgga->latitude.cardinal);
			printf("Altitude: %f %c\n", gpgga->altitude, gpgga->altitude_unit);
			printf("Satellites: %d\n", gpgga->n_satellites);

			printf("%d",gpgga->geofenceShape2(data, 11.307264055356438, 103.76941931859459, 1.0, 'c'));
		}

	
		if (NMEA_GPRMC == type) {
			printf("GPRMC sentence\n");
			nmea_gprmc_s *pos = (nmea_gprmc_s *) data;
			strftime(buf, sizeof(buf), "%d %b %T %Y", &pos->date_time);
			printf("Date & Time: %s\n", buf);

		}

		if (NMEA_GPGSA == type) {
				nmea_gpgsa_s *gpgsa = (nmea_gpgsa_s *) data;

				printf("GPGSA Sentence:\n");
				printf("  Mode: %c\n", gpgsa->mode);
				printf("  Fix:  %d\n", gpgsa->fixtype);
				printf("  PDOP: %.2lf\n", gpgsa->pdop);
				printf("  HDOP: %.2lf\n", gpgsa->hdop);
				printf("  VDOP: %.2lf\n", gpgsa->vdop);
			}

		if (NMEA_GPGSV == type) {
			nmea_gpgsv_s *gpgsv = (nmea_gpgsv_s *) data;

			printf("GPGSV Sentence:\n");
			printf("  Num: %d\n", gpgsv->sentences);
			printf("  ID:  %d\n", gpgsv->sentence_number);
			printf("  SV:  %d\n", gpgsv->satellites);
			printf("  #1:  %d %d %d %d\n", gpgsv->sat[0].prn, gpgsv->sat[0].elevation, gpgsv->sat[0].azimuth, gpgsv->sat[0].snr);
			printf("  #2:  %d %d %d %d\n", gpgsv->sat[1].prn, gpgsv->sat[1].elevation, gpgsv->sat[1].azimuth, gpgsv->sat[1].snr);
			printf("  #3:  %d %d %d %d\n", gpgsv->sat[2].prn, gpgsv->sat[2].elevation, gpgsv->sat[2].azimuth, gpgsv->sat[2].snr);
			printf("  #4:  %d %d %d %d\n", gpgsv->sat[3].prn, gpgsv->sat[3].elevation, gpgsv->sat[3].azimuth, gpgsv->sat[3].snr);
		}
		nmea_free(data);
	} else {
		printf("ERROR: Failed to parse NMEA sentence!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
