#ifndef _MOGDECODEOBJECTS_MOGVOPTIONS_H_
#define _MOGDECODEOBJECTS_MOGVOPTIONS_H_

#define MOGV_OPT_TYPE_UINT 1
#define MOGV_OPT_TYPE_SINT 3
#define MOGV_OPT_TYPE_CHAR 4
#define MOGV_OPT_TYPE_UINT_ARRAY 129
#define MOGV_OPT_TYPE_SINT_ARRAY 131
#define MOGV_OPT_TYPE_CHAR_ARRAY 132
/* TODO: Add ranges, and arrays of ranges */
#define mogv_opt_type int

#include <inttypes.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>


#include "mogconvert.h"
#include "decoder_objects.h" // TODO, Not happy with having these here
#include "encoder_objects.h" 
#include "mogvModuleProxy.h"

/* Describes a single available option that can be set. */
typedef struct {
	const char * name;
	const char * description;
	mogv_opt_type type;
} mogv_option_listing;

/* List of options that can be set for a given module. */
typedef std::map<std::string,mogv_option_listing> mogv_module_options;

/* Describes a single option that has been set. */
typedef struct {
	const char * name;
	mogv_opt_type type;
    union {
       uint32_t		uint_value;	// MOGV_OPT_TYPE_UINT
        int32_t		sint_value;	// MOGV_OPT_TYPE_SINT
       const char	char_value;	// MOGV_OPT_TYPE_CHAR
       uint32_t   *	a_uint_value;	// MOGV_OPT_TYPE_UINT_ARRAY
        int32_t   *	a_sint_value;	// MOGV_OPT_TYPE_SINT_ARRAY
       const char *	a_char_value;	// MOGV_OPT_TYPE_CHAR_ARRAY
    } data;
} mogv_option;

/* A stack of options to be applied to a given module. */
typedef std::vector<mogv_option> mogv_option_stack;

/* A single pair of initalized encoder & decoder objects to be used in conjunction. */
typedef struct {
	FILE * inputfile; /* To be removed */
	FILE * outputfile; /* To be removed */
	decoder * decoder_obj;
	encoder * encoder_obj;
} mogv_iteration;

/* A pair of input and output stream/files, proxy objects predefined to initate processing modules, and option stacks to use against them. */
typedef struct {
	FILE * inputfile;
	FILE * outputfile;
	mogvModuleProxy * decoder_proxy;
	mogvModuleProxy * encoder_proxy;
	mogv_option_stack * decoder_options;
	mogv_option_stack * encoder_options;
} mogv_empty_iteration;

namespace mogvert
{

  
  /* Parse options by given method and pair of initalized encoder/decoder
   * objects [ getIteration() ] or struct of files, mogvProxy objects and
   * option struct vectors [ getEmptyIteration() ]
   */
  class OptionsParser
    {
	public:
	    virtual mogv_iteration * getIteration()=0;
	    virtual mogv_empty_iteration * getEmptyIteration()=0;
    };
    
  /* Add this to decoder/encoder/other classes
   * needs: register name/description/type/callback handler
   */
  class OptionsHandler {
	private:
	protected:
		/* Typedef of pointer-to-member for setting options. */
		typedef void (OptionsHandler::*options_set_method)(mogv_option *);
		
		/* Typedef Internal name->method mapper. */
		typedef std::unordered_map<std::string, options_set_method> mogv_opt_handler_map;
	
	    mogv_module_options  * options_list; /* Internal list of the options available. */
	    mogv_opt_handler_map * options_map;  /* Internal map of name->method */
	
	    /* Called at construction time to register options
	     * Parameters are the name, long description, type and method to process
	     * If this is overriden in child classes, it will be nessacery to override
	     * OptionsHandler::setOption() and OptionsHandler::SetOptionStack() as well. 
	     * @param name shortname of the parameter, should be lower case, and not have spaces. Examples; bitrate, hz, device
	     * @param description Long plain english description of the option. Example; "Set the encoded bitrate of the output mp3."
	     * @param type The type of input to expect. Use the MOGV_OPT_TYPE_ definations
	     * @param method method to process the options with.
	     */
	    virtual void registerOption(const char * name, const char * description, mogv_opt_type type, options_set_method method);
	public:
	    /* Process an single option setting
	     * @param opt Pointer to the mogv_option struct to process
	     */
	    virtual void setOption(mogv_option * opt); // exceptions???	
	    /* Process a mogv_option_stack stack (vector of mogv_option structs)
	     * @param opts Pointer to vector of mogv_option structs
	     */ 
	    virtual void setOptionStack(mogv_option_stack * opts);
	    virtual mogv_module_options * getOptions();
    };
}

#endif /* _MOGDECODEOBJECTS_MOGVOPTIONS_H_ */
