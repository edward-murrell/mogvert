#include "error.h"

// exit with an error if the file can't be opened (ro)
void mog_die_fopenr(char *filename) 
{
	printf("Error! Could not open file '%s' for reading!\n",filename);
	exit(1);
}

// exit with an error if the file can't be opened (a)
void die_die_fopenw(char *filename)
{
	printf("Error! Could not open file '%s' for writing!\n",filename);
	exit(1);
}

/* exit if there was a problem parsing the command line arguments
	@param cmd_error_code	Type of error. Possible values are as follows.
		0	Error parsing option
		1	Unknown option
		All other values spit a default "unknown error" message.
	@param optind	Index of the argument on the command line.
	@param prevarg	Previous argument ("-l" in "-l 3").
	@param optarg	The arg that caused the problem ("3" in the previous example).

	// TODO, Wouldn't it be better to have prevarg and optarg the other way round in case we
	// ever have single-value args, then prevarg can be void (by default).
*/
void die_on_cmdline(int cmd_error_code, int optind, char *optarg, char *prevarg)
{
	printf("Error!\n");
	switch (cmd_error_code)
	{
	case DIE_CMD_OPT:
		printf("Error parsing option %d (%s)", optind-1, prevarg);
		printf(", unrecognised value \"%s\"\n", optarg);
		break;
	case DIE_CMD_ARG:
		printf("Unrecognised option \"%s\"\n", prevarg);
		break;
	default:
		printf("Unknown error parsing command line arguments.\n");
	}
	exit(EXIT_FAILURE);
}

// exit if the specified module doesn't exist
void module_notfound(const char *module)
{
	printf("Error!\nModule %s not found!",module);
	exit(1);
}

// exit if the actual filetype and the decoding module are a mismatch
void type_mismatch(char *module)
{
	char response = 0;
	printf("Error!\nType was not %s!\n",module);
	while(response == 0) {
		printf("Do you want to force mogconvert to decode the input");
		printf("file as an %s? (y/n) ",module);
		response = get_letter();
		if(response != 'y' && response != 'n') response = 0;
	}
	if(response == 'n') {
		printf("Cannot proceed, exiting!\n");
		exit(1);
	} else {
		printf("Warning! We are forcing mogconvert to decode the input file as %s! This may cause a segmentation fault!\n",module);
//		printf("Forcing mogconvert to decode input file as %s\n",module);
//		printf("Hold onto your hat we may seg fault here...\n");
	}
}

void unexplained_error()
{
	printf("Error! Something unexpected happened!\n");
	printf("Fix the source code!");
	exit(1);
}

void invalid_decoder(char *decoder)
{
	printf("Error!\nThere is no %s decoder! Exiting...\n",decoder);
	exit(1);
}


void invalid_encoder(char *encoder)
{
	printf("Error!\nThere is no %s encoder! Exiting...\n",encoder);
	exit(1);
}
