#include "mogvModuleRegister.h"

mogvModuleRegister::mogvModuleRegister() {
	// Create hashmaps for decoder and encoder modules
  // hash_map<Key, Data, HashFcn, EqualKey, Alloc>
  // hash_map<const char*, int, hash<const char*>, eqstr> months;
  hash_map<const char*, mogvModuleProxy*, hash<const char*>, strcasecmp> decoder_list_exts;
}

void registerModule(mogvModuleProxy * proxy,coder_info * module_info) {
	// file exts
	/*
	if (module_info->type && MOGV_OBJECT_DECODER == MOGV_OBJECT_DECODER) {
		 // want to add support for multiple iterations at some point
		decoder_list_exts.add [key = module_info->ext, value = proxy]
		decoder_list_name.add [key = module_info->name, value = proxy]
		decoder_list_magic.add [key = module_info->magic, value = proxy]
	*/
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

