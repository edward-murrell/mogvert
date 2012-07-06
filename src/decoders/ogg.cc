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
	inputcomment = ov_comment(&ogghandle,-1);	// produces warning because ov_comment is C++ and handles by 
	char cut_string[STRINGS_SIZE];
	char *test_string;

	int i = 0;
	for(i=0;i<inputcomment->comments;i++)
	{
		fprintf(stderr,"%d: ",i);
		fprintf(stderr,"%s",inputcomment->user_comments[i]);
		fprintf(stderr,"\n");

		// FIXME - This is kinda ugly, can we clean this up some?
		strcpy(cut_string,"title=");
		test_string = gfi->title;
		if ( strncmp( inputcomment->user_comments[i], cut_string, 6) == 0 )
			ogg_id_extract(&inputcomment->user_comments[i],&test_string,cut_string);

		strcpy(cut_string,"artist=");
		test_string = gfi->artist;
		if ( strncmp(inputcomment->user_comments[i], "artist=", 7) == 0 )
			ogg_id_extract(&inputcomment->user_comments[i],&test_string,cut_string);

		strcpy(cut_string,"album=");
		test_string = gfi->album;
		if ( strncmp(inputcomment->user_comments[i], "album=", 6) == 0 )
			ogg_id_extract(&inputcomment->user_comments[i],&test_string,cut_string);
	}
	fprintf(stderr,"Tag detection completed...\n\n");
}

// Tests if test makes up the first part of scan, and if so, copies the rest to output
// Could cause major issues if some Oggs don't properly null terminate their strings.
// Probably need to tack on some string lengths vars somewhere.
// Yes, the language (from, output, test) sucks, suggest something better.
void ogg_decoder::ogg_id_extract(char *from[], char *output[], char test[])
{
	int test_length = strlen(test);
	int from_length = strlen(*from);
	if (from_length > test_length)		// Eg, if the ogg string is longer than what we're testing for...
		if (strncmp(test,*from,test_length) == 0)	// If the first n (size of test) chars of scan and test match...
		{	// strncpy(dest, source, #_of_chars);
			strncpy(*output, *from+test_length,from_length-test_length);
		}
}
