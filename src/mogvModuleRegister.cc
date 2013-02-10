#include "mogvModuleRegister.h"

mogvModuleRegister::mogvModuleRegister() {
	
}

class mogvModuleRegister {
	public:
       
	private:
       mogvModuleRegister();
       static mogvModuleRegister* getInstance(); // I think this should be private       
       static mogvModuleRegister* instance;
       ~mogvModuleRegister();
   }
}
