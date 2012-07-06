#ifndef _MOGENCODEOBJECTS_H_
#define _MOGENCODEOBJECTS_H_

#include "mogconvert.h"

class encoder {
  private:
  protected:
coder_info local_coder_info;
  public:
virtual coder_info* get_coder_info() { return &this->local_coder_info; }; // Can we spin this into a super class at some point? 
virtual int init(struct generic_file_info  &gfi, struct encoding_options &encodeop) =0 ;
virtual int encode(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)=0 ;
virtual int close(struct generic_file_info &gfi, unsigned char &wave_buffer, int wave_buffer_size, unsigned char &encoded_buffer)=0 ;

  };

#include "encoders/mp3.h"
#include "encoders/ao.h"
// You can all shut up, this works.

#endif /* _MOGENCODEOBJECTS_H_ */

