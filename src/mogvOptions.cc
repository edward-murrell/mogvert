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
void OptionsHandler::setOptionStack(mogv_options * opts) {}

mogv_options * OptionsHandler::getOptions() {
    return this->options;
}