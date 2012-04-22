#include "filehandler.h"

// TODO: Get the length of string to be passed in, too
// TODO: More importantly, fix the code that passes in an uninitialised value for string
//	and causes a segfault.
int get_code(char *string) {
	int code = 2;
        if (strncasecmp("WAV",string,3) == 0)
                code = FORMAT_WAV;
        if (strncasecmp("MP3",string,3) == 0)
                code = FORMAT_MP3;
        if (strncasecmp("OGG",string,3) == 0)
                code = FORMAT_OGG;
        if (strncasecmp("FLAC",string,4) == 0)
                code = FORMAT_FLAC;
        if (strncasecmp("AO",string,2) == 0)
                code = FORMAT_AO;
	return code;
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

int check_encoder(char *encoder) {
	char *encoders[] = { "mp3","ao" };
	int i = 0;
	for(i = 0; i < NUM_ENCODERS; i++) {
		if(strcasecmp(encoder,encoders[i])==0) break;
		if(i == NUM_ENCODERS-1 && strcasecmp(encoder,encoders[i]) != 0) invalid_encoder(encoder); // <-- WTF Does this do?
	}
	return 1;
}


int check_decoder(char *decoder) {
	char *decoders[] = { "ogg","flac" };
	int i = 0;
	for(i = 0; i < NUM_DECODERS; i++) {
		if(strcasecmp(decoder,decoders[i])==0) break;
		if(i == NUM_DECODERS-1 && strcasecmp(decoder,decoders[i]) != 0) invalid_encoder(decoder); // <-- WTF Does this do?
	}
	return 1;
}

