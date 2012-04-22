#ifndef _MOGENCODEOBJECTS_AO_H_
#define _MOGENCODEOBJECTS_AO_H_

#include "../mogconvert.h"
#include "../encoder_objects.h"
#include <ao/ao.h>

class ao_encoder: public encoder {
  private:
    int out_driver_id;
    ao_device *out_device;
  public:

int init(struct generic_file_info &gfi, struct encoding_options &encodeop);
int encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer);
int close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer);
};

#endif /* _MOGENCODEOBJECTS_AO_H_ */

