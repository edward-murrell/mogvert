#include "ogg.h"

ogg_decoder::ogg_decoder() {
    coder_info local_coder_init = {"Ogg","Xiph Ogg Vorbis decoder","ogg"};
    local_coder_info = local_coder_init;
}

bool ogg_decoder::test(FILE *inputfile)	// This should be a static method.
{
	if (ov_test(inputfile,&ogghandle,NULL,0) == 0)
        return true;
    else return false;
}

bool ogg_decoder::init(FILE *inputfile)
{
	if (ov_test(inputfile,&ogghandle,NULL,0) == 0)
		if (ov_test_open(&ogghandle) == 0)
	        return true;
	    else return false;
    else return false;
}

void ogg_decoder::getgfi(struct generic_file_info &gfi)
{
	set_file_info(&gfi); // This is one of those horrible left over bits of code that we have to fix.
}

int ogg_decoder::decode(unsigned char &wave_buffer)
{
	int returnvar = 0;

//e xtern long ov_read(OggVorbis_File *vf,char *buffer,int length,int bigendianp,int word,int sgned,int *bitstream)
    // TODO - explain what the various options passed to ov_read are
	/* According to the API, arg 7 should be a 0 (unsigned char) - Don't, bad things happen */
    #ifdef _BIG_ENDIAN
		returnvar = ov_read(&ogghandle, (char *) &wave_buffer, WAVE_BUFFER_SIZE, 1, 2, 1, bitstream);
    #else
		returnvar = ov_read(&ogghandle, (char *) &wave_buffer, WAVE_BUFFER_SIZE, 0, 2, 1, bitstream);
    #endif

	// TODO, ugly, but working hack.
	return returnvar ? returnvar : -1;
}

int ogg_decoder::close(unsigned char &wave_buffer)
{	// TODO Holy crap, this needs to be fixed.
	return ov_clear(&ogghandle);
}

// Private methods for handling tags here

void ogg_decoder::set_file_info(struct generic_file_info *gfi)
{	// Don't forget to clean this up, most of it isn't needed except for debugging.
	fprintf(stderr,"\nStarting tag detection...\n");

	vorbis_comment *inputcomment;
	inputcomment = ov_comment(&ogghandle,-1);

	for(int i=0;i<inputcomment->comments;i++) // title, artist, album = 
	{
		fprintf(stderr,"\n%s\n",inputcomment->user_comments[i]);
		char * tag_delim = strchr(inputcomment->user_comments[i],'=');
		int tag_key_l = (int)(tag_delim - inputcomment->user_comments[i]);
		char * tag_key = new char[tag_key_l];
		tag_key[tag_key_l] = '\0';
		strncpy(tag_key,inputcomment->user_comments[i],tag_key_l);
        tag_delim++;
        int tag_value_l = strlen(tag_delim);
        printf("{%s}(%i) => {%s}(%i)\n",tag_key,tag_key_l,tag_delim,tag_value_l);

		       if (strcmp(tag_key,"title")) {
            strncpy(gfi->title,tag_delim,tag_value_l);
            gfi->title[tag_value_l] = '\0';
        } else if (strcmp(tag_key,"arist")) {
            strncpy(gfi->artist,tag_delim,tag_value_l);
            gfi->artist[tag_value_l] = '\0';
        } else if (strcmp(tag_key,"album")) {
            strncpy(gfi->album,tag_delim,tag_value_l);
            gfi->album[tag_value_l] = '\0';
        } else if (strcmp(tag_key,"comment")) {
            strncpy(gfi->comment,tag_delim,tag_value_l);
            gfi->comment[tag_value_l] = '\0';
        }        
	}
    fprintf(stderr,"{%s} by {%s} from {%s}\n",gfi->title,gfi->artist,gfi->album);
    fprintf(stderr,"User comment {%s}\n",gfi->comment);
	fprintf(stderr,"Tag detection completed...\n\n");
}

