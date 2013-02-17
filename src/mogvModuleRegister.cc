#include "mogvModuleRegister.h"
#include <iostream>

mogvModuleRegister::mogvModuleRegister() {
}

void mogvModuleRegister::registerModule(mogvModuleProxy * proxy) { // TODO, proxy should have it's own damn module_info reference, possible overload?
	coder_info * module_info = proxy->getModuleInfo(); // coder/module
	if ((module_info->type && MOGV_OBJECT_DECODER) == MOGV_OBJECT_DECODER) {
		std::cerr << "Adding decoder; " << module_info->longname << " (." << module_info->suffix << ")" << std::endl;
		this->decoder_list_name [std::string(module_info->shortname)] = proxy; // TODO, add test at compile time that strings are lowercase
		this->decoder_list_exts [std::string(module_info->suffix)]    = proxy; 
		this->decoder_list_magic[std::string(module_info->magic)]     = proxy; // This would be a really good time to get the maximum length of the magic for look ahead purposes
	}
	// Repeat all this for the encoder types
}

decoder * mogvModuleRegister::getDecoderByExt  (const char *ext) {
	std::cout << "Looking for suffix |" << ext << "| in list - count: " << this->decoder_list_exts.count(ext) << std::endl;
	std::string search_string = std::string(ext);
	mogProxyMapIter result = this->decoder_list_exts.find (search_string);
	if (result == decoder_list_exts.end()) {
		std::cout << "nope" << std::endl; // Debug, remove
		return NULL;
	}
	else {
		std::cout << "found" << std::endl; // Debug, remove
		result->second->whoAmI();
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

// This whole thing is to debug
int main (int arc, char* argv[]) { 
	mogvModuleRegister* reg = new mogvModuleRegister();
	mogvModuleProxy * proxy = new mogvModuleProxy();
	reg->registerModule(proxy);
	decoder * samewise = reg->getDecoderByExt("fo1");
	return 5;
}
