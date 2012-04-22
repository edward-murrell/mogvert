#ifndef _MOGCONVERT_H_
#define _MOGCONVERT_H_

// Grab some default values
#include "defaults.h"

#define STRINGS_SIZE 1024

#define FORMAT_WAV 1
#define FORMAT_MP3 2
#define FORMAT_OGG 3
#define FORMAT_FLAC 4
#define FORMAT_AO 5	// Audio out via libao

#define INPUT_BUFFER_SIZE 65536
#define WAVE_BUFFER_SIZE 65536
#define OUTPUT_BUFFER_SIZE 65536
#define NUM_DECODERS 2
#define NUM_ENCODERS 2

//#define _BIG_ENDIAN

struct generic_file_info {
	char title[STRINGS_SIZE];
	char artist[STRINGS_SIZE];
	char album[STRINGS_SIZE];
	char comment[STRINGS_SIZE];
	int year;
	int track;
	int total_tracks;
};

struct encoding_options {
	int bitrate;
};

#endif /* _MOGCONVERT_H_ */
