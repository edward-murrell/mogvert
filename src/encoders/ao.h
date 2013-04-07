#ifndef _MOGENCODEOBJECTS_AO_H_
#define _MOGENCODEOBJECTS_AO_H_

#include "../mogconvert.h"
#include "../encoder_objects.h"
#include "../mogvModuleProxy.h"
#include <ao/ao.h>

class ao_encoder: public encoder {
  private:
    int out_driver_id;
    ao_device *out_device;
  public:
ao_encoder();
int init(struct generic_file_info &gfi, struct encoding_options &encodeop);
int encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer);
int close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer);
};

class ao_encoder_proxy: public mogvModuleProxy {
  public:
    ao_encoder_proxy();
    decoder * createDecoder();
    encoder * createEncoder();
};


#endif /* _MOGENCODEOBJECTS_AO_H_ */

