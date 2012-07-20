#define MOG_OPT_TYPE_UINT 1
#define MOG_OPT_TYPE_SINT 3
#define MOG_OPT_TYPE_CHAR 4
#define MOG_OPT_TYPE_UINT_ARRAY 129
#define MOG_OPT_TYPE_SINT_ARRAY 131
#define MOG_OPT_TYPE_CHAR_ARRAY 132

#define mog_opt_type int

set_options(struct mogopt)

typedef struct {
	mog_opt_type type;
    union {
       int value; // VERY TEMPORARY
    } data;
} mog_option_stack;


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

cli {
    override constructor()
    provide help
    detect based on file magic for badly named file
}
