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
		printf("Type: %d\n", data->type);
		if (NMEA_GPGGA == data->type) {
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
			printf("Date & Time: %f:%f:%f\n", gpgga->time.tm_hour, gpgga->time.tm_min, gpgga->time.tm_sec);
		}

	
		if (NMEA_GPRMC == data->type) {
			printf("GPRMC sentence\n");
			nmea_gprmc_s *pos = (nmea_gprmc_s *) data;
			printf("Longitude:\n");
			printf("  Degrees: %d\n", pos->longitude.degrees);
			printf("  Minutes: %f\n", pos->longitude.minutes);
			printf("  Cardinal: %c\n", (char) pos->longitude.cardinal);
			printf("Latitude:\n");
			printf("  Degrees: %d\n", pos->latitude.degrees);
			printf("  Minutes: %f\n", pos->latitude.minutes);
			printf("  Cardinal: %c\n", (char) pos->latitude.cardinal);
			strftime(buf, sizeof(buf), "%d %b %T %Y", &pos->date_time);
			printf("Date & Time: %s\n", buf);

		}
		nmea_free(data);
	} else {
		printf("ERROR: Failed to parse NMEA sentence!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
