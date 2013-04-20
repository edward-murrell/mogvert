#include "mogvOptions.h"

using namespace mogvert;

void OptionsHandler::registerOption(
    const char * name,
    const char * description,
    mogv_opt_type type,
    options_set_method method) {
	
	std::string std_name = std::string(name);
	
	// Create instance of mogv_option_listing
	mogv_option_listing * opt = new mogv_option_listing;
	opt->name        = name;
	opt->description = description;
	opt->type        = type;
	
	// add to options_list
	this->options_list->insert(std::make_pair(std_name,opt));
	
	// push name/method on to method_map
	this->method_map->insert(std::make_pair(std_name,method));	
}
void OptionsHandler::setOption(mogv_option * opt) {
	std::string name = std::string(opt->name);

    // Get option from options_list
    // Check that handed opt matches the allowed type (remember, can be multiple types)

	// Get method from method_map
	mogv_opt_handler_map_iter result = this->method_map->find(name);
	if (result == this->method_map->end())
		return;
	else {
		options_set_method method = result->second;
		// Call mapped method
		(this->*method)(opt);
	}

}
void OptionsHandler::setOptionStack(mogv_option_stack * opts) {
	//for each opts as opt, call setOption
}

mogv_module_options * OptionsHandler::getOptions() {
    return this->options_list;
}
