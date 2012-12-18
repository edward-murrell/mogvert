#define MOG_OPT_TYPE_UINT 1
#define MOG_OPT_TYPE_SINT 3
#define MOG_OPT_TYPE_CHAR 4
#define MOG_OPT_TYPE_UINT_ARRAY 129
#define MOG_OPT_TYPE_SINT_ARRAY 131
#define MOG_OPT_TYPE_CHAR_ARRAY 132

#define mog_opt_type int

include <types.h>
include <list>

set_options(struct mogopt)

typedef struct {
	const char * name;
	mog_opt_type type;
    union {
       u_int32_t	uint_value;
       int32_t		sint_value;
       const char	char_value;	
       const char *	a_char_value;
    } data;
} mog_option;


// rough plan
    cli args implements mogopts, then; main() {
    mog_options opt = new mog_opts_CLI(argv,argc);
    encoder enc = new opt.get_encoder();
    enc->init(opt.get_input_stream());
    enc->set_opts(opt.get_decoder_opts());
   }

base {
    set_decoder
    set_encoder
    get_decoder_opts();
    get_encoder_opts();
    get_tagger_opts();

}


template <class T >
class myList : public std::list<T>
class mogvert::options: STL vector {???
protected:
	list<mog_option> 
public:
	
}

class mogvert::options::cli: mogvert::options {
private:
	void print_help();
	void detect_file_type();
protected:
	mogvert::options decoder_opts;
	mogvert::options encoder_opts;
	mogvert::options metacode_opts;
public:
	cli(int argc,  char* argv[]); // If you think this looks like CLI input commands, you'd be right
}

