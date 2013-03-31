#ifndef _MOGENCODEOBJECTS_H_
#define _MOGENCODEOBJECTS_H_

#include "mogconvert.h"

class encoder {
  private:
  public:
    static coder_info * get_coder_info() {
        coder_info * info = new coder_info;
        info->type      = 0;
        info->shortname = "Unreal encoder";
        info->longname  = "Unreal encoder";
        info->suffix    = 0;
        return info;
    }  
virtual int init(struct generic_file_info  &gfi, struct encoding_options &encodeop) =0 ;
virtual int encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)=0 ;
virtual int close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)=0 ;

  };

#include "encoders/mp3.h"
#include "encoders/ao.h"
// TODO - Spin this out into dynamically loaded libraries at some point

#endif /* _MOGENCODEOBJECTS_H_ */

