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
int *bitstream;
  public:
ogg_decoder();
bool test(FILE *inputfile);
bool init(FILE *inputfile);
void getgfi(struct generic_file_info &gfi);
int decode(unsigned char &wave_buffer);
int close(unsigned char &wave_buffer);
static coder_info * get_coder_info();
};

#endif /* _MOGDECODEOBJECTS_OGG_H_ */

