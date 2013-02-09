#define MOGV_OPT_TYPE_UINT 1
#define MOGV_OPT_TYPE_SINT 3
#define MOGV_OPT_TYPE_CHAR 4
#define MOGV_OPT_TYPE_UINT_ARRAY 129
#define MOGV_OPT_TYPE_SINT_ARRAY 131
#define MOGV_OPT_TYPE_CHAR_ARRAY 132
/* TODO: Add ranges, and arrays of ranges */

include <types.h>
include <list>

typedef struct {
	const char * name;
	mog_opt_type type;
    union {
       uint32_t		uint_value;	# MOGV_OPT_TYPE_UINT
        int32_t		sint_value;	# MOGV_OPT_TYPE_SINT
       const char	char_value;	# MOGV_OPT_TYPE_CHAR
       uint32_t   * []	a_uint_value;	# MOGV_OPT_TYPE_UINT_ARRAY
         int32_t  * []	a_sint_value;	# MOGV_OPT_TYPE_SINT_ARRAY
       const char *	a_char_value;	# MOGV_OPT_TYPE_CHAR_ARRAY
    } data;
} mog_option;

typedef mogv_object

namespace mogvert
{
  class mogvOptions
    {
	public:
	    virtual bool getOptions(mog_opt_type option_type)=0;
    };
}