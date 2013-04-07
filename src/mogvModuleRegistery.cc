#include "mogvModuleRegistery.h"
#include "decoders/ogg.h"
#include "decoders/flac.h"
#include "encoders/mp3.h"
#include "encoders/ao.h"

void mogv_register_modules() {
	mogvModuleRegister * reg = mogvModuleRegister::getStaticInstance();
	reg->registerModule(new ogg_decoder_proxy);
	reg->registerModule(new flac_decoder_proxy);
	reg->registerModule(new mp3_encoder_proxy);
	reg->registerModule(new ao_encoder_proxy);	
}
