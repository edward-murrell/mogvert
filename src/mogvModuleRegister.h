#include "mogconvert.h"
#include "mogvOptions.h"

using namespace mogvert;
class mogvModuleRegister {
	public:
		mogvModuleRegister();
	
		// TODO, change these to getModuleByXyz with MOGV_OBJECT_X when modules are subclassed
		void static registerModule(coder_info * module_info);
		
		static decoder * getDecoderByExt  (const char *ext);
		static decoder * getDecoderByMagic(const char *magic);
		static decoder * getDecoderByName (const char *name);
		static encoder * getEncoderByExt  (const char *ext);
		static encoder * getEncoderByMagic(const char *magic);
		static encoder * getEncoderByName (const char *name);
		
       ~mogvModuleRegister();		
	private:
       static mogvModuleRegister* getStaticInstance(); // Used for self registering classes
       static mogvModuleRegister* staticInstance;
};

