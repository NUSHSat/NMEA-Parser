#include "../nmea/parser_types.h"
#include "gpgga.h"
#include "parse.h"

int
init(nmea_parser_s *parser)
{
	/* Declare what sentence type to parse */
	NMEA_PARSER_TYPE(parser, NMEA_GPGGA);
	NMEA_PARSER_PREFIX(parser, "GPGGA");
	return 0;
}

int
allocate_data(nmea_parser_s *parser)
{
	parser->data = malloc(sizeof (nmea_gpgga_s));
	if (NULL == parser->data) {
		return -1;
	}

	return 0;
}

int
set_default(nmea_parser_s *parser)
{
	memset(parser->data, 0, sizeof (nmea_gpgga_s));
	// Set the default undulation to an invalid value
	return 0;
}

int
free_data(nmea_s *data)
{
	free(data);
	return 0;
}

int
parse(nmea_parser_s *parser, char *value, int val_index)
{
	nmea_gpgga_s *data = (nmea_gpgga_s *) parser->data;

	switch (val_index) {
	case NMEA_GPGGA_TIME:
		/* Parse time */
		
		return nmea_time_parse(value, &data->time);
		
		break;

	case NMEA_GPGGA_LATITUDE:
		/* Parse latitude */
		
		return nmea_position_parse(value, &data->latitude);
		
		break;

	case NMEA_GPGGA_LATITUDE_CARDINAL:
		/* Parse cardinal direction */
		data->latitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == data->latitude.cardinal) {
			return -1;
		}
		break;

	case NMEA_GPGGA_LONGITUDE:
		/* Parse longitude */
		
		return nmea_position_parse(value, &data->longitude);
		
		break;

	case NMEA_GPGGA_LONGITUDE_CARDINAL:
		/* Parse cardinal direction */
		data->longitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == data->longitude.cardinal) {
			return -1;
		}
		break;

	case NMEA_GPGGA_ALTITUDE:
		/* Parse altitude */
		data->altitude = atof(value);
		break;

	case NMEA_GPGGA_ALTITUDE_UNIT:
		/* Parse altitude unit */
		data->altitude_unit = *value;
		break;

	default:
		break;
	}

	return 0;
}
