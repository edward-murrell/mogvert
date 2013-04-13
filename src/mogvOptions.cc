#include "mogvOptions.h"

using namespace mogvert;

void OptionsHandler::registerOption(
    const char * name,
    const char * description,
    mogv_opt_type type,
    void (OptionsHandler::*method)(mogv_option * opt)) {
    
}
void OptionsHandler::setOption(mogv_option * opt) {
    
}
void OptionsHandler::setOptionStack(mogv_option_stack * opts) {
}

mogv_module_options * OptionsHandler::getOptions() {
    return this->options_list;
}
