#include "mogvOptions.h"
using namespace mogvert;

class mogvCliOptions: public mogvOptions {
  private:
  public:
mogvCliOptions(int argc,  char* argv[]);
mogv_options getOptions(mogv_opt_type option_type)=0;
};

