#include "mogvModuleProxy.h"
#include <iostream>
// TODO, delete this file -- this is a test class, don't use it

mogvModuleProxy::mogvModuleProxy() {
	// This should be pulled from a given coders static info function
	coder_info * info = new coder_info;
	info->shortname = "foobar"; // The argument name
	info->longname = "Foobar4000 fileformat";
    info->suffix = "fo1"; // Because they thought there would be a version two.
    info->magic = "F00v1";
    info->type = MOGV_OBJECT_ENCODER + MOGV_OBJECT_DECODER;
    this->info = info;
}

decoder* mogvModuleProxy::createDecoder() { return NULL; }
encoder* mogvModuleProxy::createEncoder() { return NULL; }

void mogvModuleProxy::whoAmI() {
	    std::cout << "I'm " << this->info->longname << " file suffix; \"" << this->info->suffix << "\"" << std::endl; // worst concat ever
}

coder_info * mogvModuleProxy::getModuleInfo() {
	return this->info;
}
