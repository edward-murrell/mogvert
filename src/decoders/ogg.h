#ifndef _MOGDECODEOBJECTS_OGG_H_
#define _MOGDECODEOBJECTS_OGG_H_

#include "../mogconvert.h"
#include "../decoder_objects.h"
#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>
#include <string.h>

class ogg_decoder: public decoder {
  private:
void set_file_info(struct generic_file_info *gfi);
void ogg_id_extract(char *from[], char *output[], char test[]);
OggVorbis_File ogghandle;
  public:
bool test(FILE *inputfile);
bool init(FILE *inputfile);
char* get_decoder_name();
void getgfi(struct generic_file_info &gfi);
int decode(unsigned char &wave_buffer);
int close(unsigned char &wave_buffer);
};

#endif /* _MOGDECODEOBJECTS_OGG_H_ */

