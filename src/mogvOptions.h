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

namespace mogvert
{
  class mogvOptions
    {
	public:
	    virtual mogv_iteration * getIteration()=0;
    };
}
