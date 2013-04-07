#include "mogconvert.h"
#include "mogvOptions.h"
#include "mogvModuleProxy.h"
#include <unordered_map>
#include <string> // should this be a C++ include?

typedef std::unordered_map<std::string, mogvModuleProxy*> mogProxyMap;
typedef std::unordered_map<std::string, mogvModuleProxy*>::const_iterator mogProxyMapIter;

using namespace mogvert;
class mogvModuleRegister {
	public:
		mogvModuleRegister();
		// TODO, change these to getModuleByXyz with MOGV_OBJECT_X when modules are subclassed
		void registerModule(mogvModuleProxy * proxy);
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
		mogProxyMap decoder_list_exts;
		mogProxyMap decoder_list_name;
		mogProxyMap decoder_list_magic;
		mogProxyMap encoder_list_exts;
		mogProxyMap encoder_list_name;
		mogProxyMap encoder_list_magic;		
};

