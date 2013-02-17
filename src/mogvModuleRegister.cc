#include "mogvModuleRegister.h"

mogvModuleRegister::mogvModuleRegister() {
}

void mogvModuleRegister::registerModule(mogvModuleProxy * proxy,coder_info * module_info) {
	// file exts
	if (module_info->type && MOGV_OBJECT_DECODER == MOGV_OBJECT_DECODER) {
		this->decoder_list_name [module_info->shortname] = proxy; // TODO, add test at compile time that strings are lowercase
		this->decoder_list_exts [module_info->suffix]    = proxy; // This would be a really good time to get the maximum length of the magic for look ahead purposes
		this->decoder_list_magic[module_info->magic]     = proxy;
	}
	// Repeat all this for the encoder types
}

decoder * mogvModuleRegister::getDecoderByExt  (const char *ext) {
	mogProxyMapIter result = decoder_list_exts.find (ext);
	if (result == decoder_list_exts.end())
		return NULL;
	else {
		return result->second->createDecoder();
	}
}
/*
mogvModuleRegister * mogvModuleRegister::getStaticInstance() {
	if (!mogvModuleRegister::staticInstance);
		mogvModuleRegister::staticInstance = new mogvModuleRegister;
	return mogvModuleRegister::staticInstance;
}
*/
