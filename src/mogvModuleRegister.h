#include "mogvOptions.h"

using namespace mogvert;
class mogvModuleRegister {
	public:
       static mogvModuleRegister* getInstance(); // I think this should be private
       ~mogvModuleRegister();
   private:
       mogvModuleRegister();
       static mogvModuleRegister* instance;
   }
}
