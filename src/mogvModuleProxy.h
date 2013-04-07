#ifndef _MOGDECODEOBJECTS_MOGVMODULEPROXY_H_
#define _MOGDECODEOBJECTS_MOGVMODULEPROXY_H_

#include "mogconvert.h"
#include "decoder_objects.h"
#include "encoder_objects.h"

class mogvModuleProxy {
	// components, autoregister logic
	// static? coder_info
	// Create coder instance class
	public:
		//mogvModuleProxy();
		virtual decoder* createDecoder() =0;
		virtual encoder* createEncoder() =0;
		coder_info * getModuleInfo();
		void whoAmI();
	protected:
		coder_info * info;
};
#endif /* _MOGDECODEOBJECTS_MOGVMODULEPROXY_H_ */
