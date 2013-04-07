#include "../mogvModuleRegister.h"
#include "../mogvModuleRegistery.h"
#include <iostream>
#include <assert.h>

int main (int arc, char* argv[]) { 
	mogv_register_modules();
	mogvModuleRegister * reg = mogvModuleRegister::getStaticInstance();
	mogvModuleProxy * proxy = reg->getDecoderProxyByExt("flac");
	// TODO: Add asserts into this
	proxy->whoAmI();
	proxy = reg->getEncoderProxyByExt("mp3");
	proxy->whoAmI();
	exit(0);
}
