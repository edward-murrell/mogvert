#include "mogconvert.h"
#include "mogvOptions.h"

using namespace mogvert;
class mogvModuleRegister {
	public:
		mogvModuleRegister();
		// TODO, change these to getModuleByXyz with MOGV_OBJECT_X when modules are subclassed
		void registerModule(mogvModuleProxy * proxy, coder_info * module_info);
		decoder * getDecoderByExt  (const char *ext); // TODO, Change return type to proxy, maybe possible to add ident type to getDecoder
		decoder * getDecoderByMagic(const char *magic);
		decoder * getDecoderByName (const char *name);
		encoder * getEncoderByExt  (const char *ext);
		encoder * getEncoderByMagic(const char *magic);
		encoder * getEncoderByName (const char *name);
		~mogvModuleRegister();
		
		static mogvModuleRegister* getStaticInstance(); // Used for self registering classes		
	private:
		static mogvModuleRegister * staticInstance;
};

