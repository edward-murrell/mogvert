#include "mp3.h"

decoder* mp3_encoder_proxy::createDecoder() {
    return new mp3_encoder();
}

mp3_encoder_proxy::mp3_encoder_proxy() {
	coder_info * info = new coder_info;
	info->type      = MOGV_OBJECT_ENCODER;
	info->shortname = "MP3";
    info->longname  = "LAME MP3 Encoder";
	info->suffix    = "mp3";
	info->magic		= "ID3";
	this->info = info;
}

mp3_encoder::mp3_encoder() {
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

    id3tag_set_title  (lamehandle, gfi.title);
    id3tag_set_artist (lamehandle, gfi.artist);
    id3tag_set_album  (lamehandle, gfi.album);
    id3tag_set_genre  (lamehandle, gfi.genre);
    id3tag_set_year   (lamehandle, gfi.year);
    id3tag_set_track  (lamehandle, gfi.track);
    id3tag_set_comment(lamehandle, gfi.comment);
    
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
