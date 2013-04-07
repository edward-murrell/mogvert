#include "mogconvert.h"
#include "decoder_objects.h"
#include "decoders/ogg.h"
#include "decoders/flac.h"
#include "encoder_objects.h"
#include "init.h"
#include "filehandler.h"
#include "mogvModuleRegister.h"
#include "mogvModuleRegistery.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
const char* audiotype[] = {"undefined", "wav", "mp3", "ogg", "flac", "ao"};

int main(int argc,  char* argv[])
{
    mogv_register_modules();
    mogvModuleRegister * reg = mogvModuleRegister::getStaticInstance();
    
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

	struct generic_file_info gfi;

	info           = mog_initmog(argc,argv); 	// parse comandline arguments
	inputfile      = fopen(info.input_file,"rb");	// open inputfile
	outputfile     = fopen(info.output_file,"wb");	// open outputfile

    encodeop.bitrate = info.bitrate;

	coder_info* dec_info, *enc_info;
    
    mogvModuleProxy * dec_proxy = reg->getDecoderProxyByExt ( info.dec_module );
    mogvModuleProxy * enc_proxy = reg->getEncoderProxyByExt ( info.enc_module );

	if (dec_proxy == NULL) {
		fprintf(stderr,"Failed to detect input format.\n");
		exit(1);
	}
	if (enc_proxy == NULL) {
		fprintf(stderr,"Failed to detect output format.\n");
		exit(1);
	}    

// == Init the decoder
    
    fprintf(stderr,"\nInitilizing decoding engine... %s\n",dec_proxy->getModuleInfo()->longname);
    decoder_ob = dec_proxy->createDecoder();
    
	if (! decoder_ob->init(inputfile)) {
		fprintf(stderr,"Failed to open input file.\n");
		exit(1); // TODO - Need proper (and documented) exit codes
	}

	decoder_ob->getgfi(gfi); // todo, change to return pointer

// == Init the encoder

    fprintf(stderr,"\nInitilizing Encoding engine... %s\n",enc_proxy->getModuleInfo()->longname);
    encoder_ob = enc_proxy->createEncoder();
	
    if (! encoder_ob->init(gfi, encodeop)) {
		fprintf(stderr,"Failed to open output file.\n");
		exit(1); // TODO - Need proper (and documented) exit codes
	}


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
