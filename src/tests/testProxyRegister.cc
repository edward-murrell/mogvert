#include "mogvModuleRegister.h"
#include <iostream>
#include <assert.h>

int main (int arc, char* argv[]) { 
	coder_info * info = new coder_info;
	info->shortname = "foobar"; // The argument name
	info->longname = "Foobar4000 fileformat";
    info->suffix = "fo1"; // Because they thought there would be a version two.
    info->magic = "F00v1";
    info->type = MOGV_OBJECT_ENCODER + MOGV_OBJECT_DECODER;

	mogvModuleRegister* reg = new mogvModuleRegister();
	mogvModuleProxy * proxy = new mogvModuleProxy(info);
	
	reg->registerModule(proxy);
	
	decoder * samewise = reg->getDecoderByExt("fo1");
	encoder * boom     = reg->getEncoderByExt("fo1");

	// TODO: Add asserts into this
	proxy.whoAmI();
}
