#include "ao.h"

ao_encoder::ao_encoder() {
}

coder_info * ao_encoder::get_coder_info() {
	coder_info * info = new coder_info;
	info->type      = MOGV_OBJECT_ENCODER;
	info->shortname = "AO";
    info->longname  = "Libao Audio Output library";
	info->suffix    = "";
	info->magic		= "";
	return info;
}

int ao_encoder::init(struct generic_file_info &gfi, struct encoding_options &encodeop)
{
	printf("Playing %s by %s (%s)...\n",gfi.title,gfi.artist,gfi.album);
	ao_initialize();
	out_driver_id = ao_default_driver_id();
    //out_driver_id = ao_driver_id("pulse"); // To force a drive, do this

	ao_sample_format out_format;
		out_format.bits        = 16;
		out_format.channels    = 2;
		out_format.rate        = 44100;
#ifdef _BIG_ENDIAN
		out_format.byte_format = AO_FMT_BIG;
#else
		out_format.byte_format = AO_FMT_LITTLE;
#endif
	out_device = ao_open_live(out_driver_id, &out_format,NULL);
	return 0; // TODO - Again, this should actually return an error if something is borked
}

int ao_encoder::encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)
{
	if(out_device==NULL) {
		fprintf(stderr,"Could not open audio device... ");
		fprintf(stderr,"Exiting!\n");
		exit(1);	// TODO - This is such a bad way to do this.
	}
	ao_play(out_device, (char*) &wave_buffer, wave_buffer_size);
	return 0;
}


int ao_encoder::close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)
{
	ao_shutdown();
	return 0;
}

