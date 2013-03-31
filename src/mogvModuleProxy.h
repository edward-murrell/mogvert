#include "mogconvert.h"
#include "decoder_objects.h"
#include "encoder_objects.h"

class mogvModuleProxy {
	// components, autoregister logic
	// static? coder_info
	// Create coder instance class
	public:
		mogvModuleProxy();
		mogvModuleProxy(coder_info * info);
		decoder* createDecoder();
		encoder* createEncoder();
		coder_info * getModuleInfo();
		void whoAmI();
	private:
		coder_info * info;
};
