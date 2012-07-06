#ifndef _MOGDECODEOBJECTS_H_
#define _MOGDECODEOBJECTS_H_

#include "mogconvert.h"
#include <stdio.h>

class decoder {
protected:
    coder_info local_coder_info;
public:
	virtual bool test(FILE *inputfile)=0;
	virtual bool init(FILE *inputfile)=0;
	// it'd be nice if this function was actually
	// virtual struct generic_file_info& getgfi();
    virtual coder_info* get_coder_info() { return &this->local_coder_info; };
	virtual void getgfi(struct generic_file_info &gfi)=0;
	virtual int decode(unsigned char &wave_buffer)=0 ;		// This function returns number of BYTES
	virtual int close(unsigned char &wave_buffer)=0 ;
	//virtual ~decoder();
};
#include "decoders/flac.h"
#include "decoders/ogg.h"
//#include "decoders/cdda.h"

#endif /* _MOGDECODEOBJECTS_H_ */

