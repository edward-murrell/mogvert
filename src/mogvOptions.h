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
#include <vector>

#include "mogconvert.h"
#include "decoder_objects.h" // TODO, Not happy with having these here
#include "encoder_objects.h" 
#include "mogvModuleProxy.h"

typedef struct {
	const char * name;
	const char * description;
	mogv_opt_type type;
} mogv_option_listing;

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

typedef std::vector<mogv_option> mogv_options;

// TODO, move this somewhere better
typedef struct {
	FILE * inputfile;
	FILE * outputfile;
	decoder * decoder_obj;
	encoder * encoder_obj;
} mogv_iteration;


typedef struct {
	FILE * inputfile;
	FILE * outputfile;
	mogvModuleProxy * decoder_proxy;
	mogvModuleProxy * encoder_proxy;
	mogv_options * decoder_options;
	mogv_options * encoder_options;
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
	    /* Called at construction time to register options
	     * Parameters are the name, long description, type and method to process
	     * If this is overriden in child classes, it will be nessacery to override
	     * OptionsHandler::setOption() and OptionsHandler::SetOptionStack() as well. 
	     * @param name shortname of the parameter, should be lower case, and not have spaces. Examples; bitrate, hz, device
	     * @param description Long plain english description of the option. Example; "Set the encoded bitrate of the output mp3."
	     * @param type The type of input to expect. Use the MOGV_OPT_TYPE_ definations
	     * @param method method to process the options with.
	     */ 
	    virtual void registerOption(const char * name, const char * description, mogv_opt_type type, void (OptionsHandler::*method)(mogv_option * opt)); 
	protected:
	    // TODO, add hashmap(s) to hold data from registerOption() here
	public:
	    /* Process an single option setting
	     * @param opt Pointer to the mogv_option struct to process
	     */
	    virtual void setOption(mogv_option * opt); // exceptions???	
	    /* Process a mogv_options stack (vector of mogv_option structs)
	     * @param opts Pointer to vector of mogv_option structs
	     */ 
	    virtual void setOptionStack(mogv_options * opts); // exceptions???
    };

}

#endif /* _MOGDECODEOBJECTS_MOGVOPTIONS_H_ */

