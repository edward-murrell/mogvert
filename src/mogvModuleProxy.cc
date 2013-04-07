#include "mogvModuleProxy.h"
#include <iostream>

void mogvModuleProxy::whoAmI() { // TODO Remove this in favour of a test module with assertions
	    std::cout << "I'm " << this->info->longname << " file suffix; \"" << this->info->suffix << "\"" << std::endl; // worst concat ever
}

coder_info * mogvModuleProxy::getModuleInfo() {
	return this->info;
}

// Really, what we want is this;
// With some magic where by it pulls the ogg_decoders static info from... somewhere
// MogvModuleRegister::getInstance()->registerModule(mogvModuleProxy<ogg_decoder>);
//
// Since, it's not possible to put have static virtual methods required for getting
// the en/decoder information, it may as well go in it's own (non static) virtual
// method, and force the create[en|dec]coder methods to be overriden.
//
// MogvModuleRegister::getInstance()->registerModule(new ogg_decoder_proxy);
