#include "../mogvModuleRegister.h"
#include "../mogvModuleRegistery.h"
#include <iostream>
#include <assert.h>

/* Run from the src directory
 * g++ -Wall  -std=c++0x  -DHAVE_INTTYPES_H -o tests/testProxyRegister tests/testProxyRegister.cc mogvModuleProxy.cc mogvModuleRegistery.cc mogvModuleRegister.cc decoders/ogg.cc decoders/flac.cc encoders/mp3.cc encoders/ao.cc -lmp3lame -logg -lvorbisfile -lvorbis -lao -lFLAC -lFLAC++
 */

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
