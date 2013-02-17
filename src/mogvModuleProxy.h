#include "mogconvert.h"
#include "decoder_objects.h"
#include "encoder_objects.h"

class mogvModuleProxy {
	// components, autoregister logic
	// static? coder_info
	// Create coder instance class
	public:
		mogvModuleProxy();
		decoder* createDecoder();
		encoder* createEncoder();
		coder_info * getModuleInfo();
		void whoAmI(); // Debug function, to be removed
	private:
		coder_info * info;
};
