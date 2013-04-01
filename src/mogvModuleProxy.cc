#include "mogvModuleProxy.h"
#include <iostream>

mogvModuleProxy::mogvModuleProxy() {
}

void mogvModuleProxy::registerProxy(coder_info * info) {
	this->info = info;
	this->whoAmI();
	// Registration with the singularity goes here
}


// These should be overriden
decoder* mogvModuleProxy::createDecoder() { return NULL; }
encoder* mogvModuleProxy::createEncoder() { return NULL; }

void mogvModuleProxy::whoAmI() { // TODO Remove this in favour of a test module with assertions
	    std::cout << "I'm " << this->info->longname << " file suffix; \"" << this->info->suffix << "\"" << std::endl; // worst concat ever
}

coder_info * mogvModuleProxy::getModuleInfo() {
	return this->info;
}
