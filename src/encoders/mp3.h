#ifndef _MOGENCODEOBJECTS_MP3_H_
#define _MOGENCODEOBJECTS_MP3_H_

#include "../mogconvert.h"
#include "../encoder_objects.h"
#include "../mogvModuleProxy.h"
#include <lame/lame.h>

class mp3_encoder: public encoder {
  private:
    lame_global_flags *lamehandle;
  public:
mp3_encoder();  
int init(struct generic_file_info &gfi, struct encoding_options &encodeop);
int encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer);
int close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer);
};

class mp3_encoder_proxy: public mogvModuleProxy {
  public:
    mp3_encoder_proxy();
    decoder * createDecoder();
};


#endif /* _MOGENCODEOBJECTS_MP3_H_ */

