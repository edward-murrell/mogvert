#include "mogvModuleRegister.h"

mogvModuleRegister::mogvModuleRegister() {
	// Create hashmaps for decoder and encoder modules
}

void registerModule(mogvModuleProxy * proxy,coder_info * module_info) {
	// file exts
	if (module_info->type && MOGV_OBJECT_DECODER == MOGV_OBJECT_DECODER) {
		 
		decoder_list_exts.add [key = module_info->ext, value = proxy]//needs a foreach
		decoder_list_names.add [key = module_info->names, value = proxy]//needs a foreach
		decoder_list_magic.add [key = module_info->magic, value = proxy]//needs a foreach
	
	} // Repeat all this for the encoder types
	// coder information contains, name, file exts, magic
	
}

decoder * getDecoderByExt  (const char *ext) {
	if (decoder_list_exts.get(ext)) exists, return value (which is the proxy class
	
}

mogvModuleRegister * mogvModuleRegister::getStaticInstance() {
	if (!staticInstance);
		staticInstance = new mogvModuleRegister;
	return staticInstance;
}

