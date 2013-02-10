#ifndef _MOGCONVERT_H_
#define _MOGCONVERT_H_

// Grab some default values
#include "defaults.h"

#define STRINGS_SIZE 1024

#define FORMAT_UNDEFINED 65536;
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

#define MOGV_OBJECT_DECODER 1
#define MOGV_OBJECT_ENCODER 2
#define MOGV_OBJECT_PCMFILTER 4
#define MOGV_OBJECT_NONE 127

#define mogv_obj_type int


//#define _BIG_ENDIAN

struct generic_file_info {
	char title[STRINGS_SIZE];
	char artist[STRINGS_SIZE];
	char album[STRINGS_SIZE];
	char genre[STRINGS_SIZE];
	char year[STRINGS_SIZE];
	char track[STRINGS_SIZE];
	char comment[STRINGS_SIZE];    
};

struct coder_info {
    mogv_obj_type type;
	const char * shortname;
	const char * longname;
    const char * suffix;
    bool decoder;
    bool encoder;
};

struct encoding_options {
	int bitrate;
};

#endif /* _MOGCONVERT_H_ */
