#include "mogconvert.h"
#include "decoder_objects.h"
#include "encoder_objects.h"
#include "init.h"
#include "filehandler.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>

int main(int argc,  char* argv[])
{
	mog_info info;	// struct for cmdline args
    struct encoding_options encodeop;
	FILE *inputfile;
	FILE *outputfile;
	int decode_format = 0;	// TODO - Should really make these part of a struct
	int encode_format = 0;

    decoder *decoder_ob;
    encoder *encoder_ob;

	// Holds the wave output from the decode, and the encoded output
	unsigned char		wave_buffer[WAVE_BUFFER_SIZE];
	unsigned char		encoded_buffer[OUTPUT_BUFFER_SIZE];

	printf("MAIN() wave_buffer addr: %p\n",&wave_buffer);

	struct generic_file_info gfi;

	info           = mog_initmog(argc,argv); 	// parse comandline arguments
	inputfile      = fopen(info.input_file,"rb");	// open inputfile
	outputfile     = fopen(info.output_file,"wb");	// open outputfile

	printf("inputfile ptr: %p\n",inputfile);

    encodeop.bitrate = info.bitrate;

// expand on this to setup multiple file formats, add the tests for their validity to filehandler.c
// ======================================================

// == Init the decoder

    if (info.dec_module == NULL)    
        decode_format = get_code(info.input_file);
	else if(check_decoder(info.dec_module))
    {
		decode_format = get_code(info.dec_module);
	}
	else
	{
		fprintf(stderr,"Failed to detect input format.\n");
		exit(1); // TODO - Need proper (and documented) exit codes
	}
    
	fprintf(stderr,"\nInitilizing decoding engine... %d\n",decode_format);
    
	switch (decode_format) {
	case FORMAT_OGG:
		decoder_ob = new ogg_decoder(); break;
	case FORMAT_FLAC:
		decoder_ob = new flac_decoder(); break;
	default: // ideally this case would be caught and thrown earlier in the piece
		fprintf(stderr, "Invalid decoder.\n");
		exit(1);
	}

	if (! decoder_ob->init(inputfile))
	{
		fprintf(stderr,"Failed to open input file.\n");
		exit(1); // TODO - Need proper (and documented) exit codes
	}
	decoder_ob->getgfi(gfi);
	

// == Init the encoder

	// check if the encoder is supported
    if (info.dec_module == NULL)    
        encode_format = get_code(info.output_file);
	else if(check_encoder(info.enc_module)) {
		encode_format = get_code(info.enc_module);
	} else {
   		fprintf(stderr,"Unknown output format.\n");
    }

	switch (encode_format) {
	case FORMAT_MP3:
		encoder_ob = new mp3_encoder(); break;
	case FORMAT_AO:
		encoder_ob = new ao_encoder(); break;
	default: // *should* never execute, since input should get caught above
		fprintf(stderr, "Invalid encoder. This is a bug!\n");
		exit(1);
	}
	fprintf(stderr,"\nInitilizing encoding engine...\n");
	encoder_ob->init(gfi, encodeop);

// DECODING STARTS HERE ======================================================



	int decoding_status = 0;
	int encoding_status = 0;
	int position_bytes = 0;
	int start_time = 0;
	int end_time = 0;
	int ptime = 0;
	int otime = 0;

	start_time = time(NULL);
	do 
	{
		decoding_status = decoder_ob->decode(*wave_buffer);	//This is supposed to get BYTES
		if (decoding_status>0)
		{
			encoding_status = encoder_ob->encode(gfi, *wave_buffer, decoding_status, *encoded_buffer);
		}

		if (encoding_status>0)
		{
			fwrite(encoded_buffer, 1, encoding_status,outputfile);
		}

		position_bytes = position_bytes + decoding_status;

		ptime = time(NULL) - start_time;
		if (ptime == otime + 1) {
			fprintf(stderr,"Recoding %s... %6.4lf mbytes completed in %d seconds...\r",
			        gfi.title,(double)position_bytes/1048576,ptime);
			otime = ptime;
		} 
		if(ptime == info.reencode_time) break;
	}
	while (decoding_status >= 0);
	encoding_status = encoder_ob->close(gfi, *wave_buffer, decoding_status, *encoded_buffer);

	end_time = time(NULL);

	fwrite(encoded_buffer, 1, encoding_status,outputfile);
	int total_time = end_time-start_time;
	fprintf(stderr,"\nRecode finished in %d minute(s) and %d second(s), average recode speed %4.4lf kilobytes/second.\n",total_time/60,total_time % 60,(double)position_bytes/(ptime*1024));

	// clean up
	fclose(inputfile);
	fclose(outputfile);

return 0;
}
