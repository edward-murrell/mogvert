#include "mp3.h"

mp3_encoder::mp3_encoder() {
    coder_info local_coder_init = {"MP3","LAME MP3 Encoder","mp3",false,true};
    local_coder_info = local_coder_init;
}

int  mp3_encoder::init(struct generic_file_info &gfi, struct encoding_options &encodeop)
{
	fprintf(stderr,"Creating mp3 for %s by %s (%s)...\n",gfi.title,gfi.artist,gfi.album);// Remove this at some point?

	lamehandle = lame_init();
    if (lamehandle == NULL)
        return false;

	lame_set_brate(lamehandle, encodeop.bitrate);
	if (-1 == lame_init_params(lamehandle))
        return false;
	id3tag_init(lamehandle);
	id3tag_add_v2(lamehandle);

	id3tag_set_title(lamehandle, gfi.title);
	id3tag_set_artist(lamehandle, gfi.artist);
	id3tag_set_album(lamehandle, gfi.album);
	return true;
}

int  mp3_encoder::encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)
{
	return lame_encode_buffer_interleaved(
        lamehandle,
        (short int*) &wave_buffer,       // This is kinda ugly, but it should be ok
        (wave_buffer_size/4), // BUFFER_SIZE is for number of bytes, not short ints, and div/2 again for stereo
		&encoded_buffer,
		OUTPUT_BUFFER_SIZE);
}

int  mp3_encoder::close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)
{
	int encoding_status = lame_encode_flush(lamehandle,&encoded_buffer,OUTPUT_BUFFER_SIZE);
	lame_close(lamehandle);		// Return something of meaning here?
	return encoding_status;
}
