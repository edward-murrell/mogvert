#include "mogvOptions.h"

using namespace mogvert;

void OptionsHandler::registerOption(
    const char * name,
    const char * description,
    mogv_opt_type type,
    void (OptionsHandler::*method)(mogv_option * opt)) {
	
	// Create instance of mogv_option_listing
	
	// add to options_list
	
	// push name/method on to method_map
        
}
void OptionsHandler::setOption(mogv_option * opt) {
	// Get option from options_list
	// Check that handed opt matches the allowed type (remember, can be multiple types)
	// Get method from method_map
	// Call mapped method
}
void OptionsHandler::setOptionStack(mogv_option_stack * opts) {
	//for each opts as opt, call setOption
}

mogv_module_options * OptionsHandler::getOptions() {
    return this->options_list;
}
