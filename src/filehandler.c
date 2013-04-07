#include "mogconvert.h"
#include "error.h"
#include <unistd.h>
#include <stdlib.h>
//#include <getopt.h> // the standard getopt call is in unistd.h
#include <stdio.h>
#include <strings.h>



const char * get_ext(const char *arg) {
	const char* suffix = strrchr ( arg , '.'); // TODO, seperate out finding the extensions into it's own function
	if (suffix == NULL) // strrchr: http://www.cplusplus.com/reference/clibrary/cstring/strrchr/
		suffix = arg; // It's not a file extension
	if (suffix[0] == '.'){
		suffix++;
	}
    return suffix;
}

// TODO: Get the length of string to be passed in, too
// TODO: More importantly, fix the code that passes in an uninitialised value for string
//	and causes a segfault.
int get_code(const char *arg) {
	const char* suffix = strrchr ( arg , '.'); // TODO, seperate out finding the extensions into it's own function
	if (suffix == NULL) // strrchr: http://www.cplusplus.com/reference/clibrary/cstring/strrchr/
		suffix = arg; // It's not a file extension
	if (suffix[0] == '.'){
		suffix++;
	}

	if (strcasecmp("WAV",suffix) == 0)
		return FORMAT_WAV;
	else if (strcasecmp("MP3",suffix) == 0)
		return FORMAT_MP3;
	else if (strcasecmp("OGG",suffix) == 0)
		return FORMAT_OGG;
	else if (strcasecmp("FLAC",suffix) == 0)
		return FORMAT_FLAC;
	else if (strcasecmp("AO",suffix) == 0)
		return FORMAT_AO;

	return FORMAT_UNDEFINED; // Default return code;
}

char get_letter() {
	char input[1024];
	char c = 0;
	int  i = 0;
	for(i = 0; i < 1024; i++)
		input[i] = 0;
	scanf("%s",input);
	c = input[0];
	return c;
}

int check_encoder(const char *encoder) {
	const char *encoders[] = { "mp3","ao" };
	int i = 0;
	for(i = 0; i < NUM_ENCODERS; i++) {
		if(strcasecmp(encoder,encoders[i])==0) break;
		if(i == NUM_ENCODERS-1 && strcasecmp(encoder,encoders[i]) != 0) invalid_encoder(encoder); // <-- WTF Does this do?
	}
	return get_code(encoder);
}


int check_decoder(const char *decoder) {
	const char *decoders[] = { "ogg","flac" };
	int i = 0;
	for(i = 0; i < NUM_DECODERS; i++) {
		if(strcasecmp(decoder,decoders[i])==0) break;
		if(i == NUM_DECODERS-1 && strcasecmp(decoder,decoders[i]) != 0) invalid_encoder(decoder); // <-- WTF Does this do?
	}
	return 1;
}

