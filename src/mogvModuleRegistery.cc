#include "mogvModuleRegistery.h"
#include "decoders/ogg.h"
#include "decoders/flac.h"

void mogv_register_modules() {
	mogvModuleRegister * reg = mogvModuleRegister::getStaticInstance();
	reg->registerModule(new ogg_decoder_proxy);
	reg->registerModule(new flac_decoder_proxy);
}
