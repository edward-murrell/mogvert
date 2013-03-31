#include "mogvModuleProxy.h"
#include <iostream>

mogvModuleProxy::mogvModuleProxy() {
}
mogvModuleProxy::mogvModuleProxy(coder_info * info) {
	this->info = info;
}

// These should be overriden
decoder* mogvModuleProxy::createDecoder() { return NULL; }
encoder* mogvModuleProxy::createEncoder() { return NULL; }

void mogvModuleProxy::whoAmI() {
	    std::cout << "I'm " << this->info->longname << " file suffix; \"" << this->info->suffix << "\"" << std::endl; // worst concat ever
}

coder_info * mogvModuleProxy::getModuleInfo() {
	return this->info;
}
