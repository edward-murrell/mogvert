#include "init.h"

mog_info mog_initmog(int argc, char* argv[]) {
	// if no command-line options were given, print a usage message
	if (argc == 1) {
		mog_showhelp(argv[0]);
		exit(0);
	}

	char *prevarg; // this was moved in from file scope

	int			c; // getopt's return val
	int			show_stats;
	int			show_help;
	struct mog_info		info;	// infile outfile decmod encmod
	extern char 		*optarg;
	extern int 		optind;

	// set some default values which will hopefully be changed
	// by arguments on the command line
	//c 		    =	' ';
	// TODO: put these all in config.h
	info.enc_module		=	0; // TODO: this should be a malloc()'ed string, at least strlen("FLAC") in length
	show_stats	    =	0;
	show_help	    =	0;
    prevarg		    =	argv[1];
	info.input_file     = 	"/dev/stdin";
	info.output_file    = 	"/dev/stdout";
	info.copy_tags	    =   1;
	info.enc_module     = 	DEFAULT_ENCODER;
	info.bitrate	    = 	DEFAULT_ENCODER_BITRATE; 
	info.reencode_time  =  -1;
	info.check_validity =   1;

	fprintf(stderr,"\nMOG Converter Starting Up\n\n");
	fprintf(stderr,"Reading & interpreting command line arguments... ");

	while ((c = getopt(argc, (char* const*) argv, "i:o:b:d:e:l:shtq")) != -1) {
		switch (c) {
		case 'h': // output help
			mog_showhelp(argv[0]);
			exit(0);
		case 'i': // input file
			if(!strncmp(optarg,"-",1))
				die_on_cmdline(DIE_CMD_ARG, optind, optarg, (char *)prevarg);
			else
				info.input_file = optarg;
			break;
		case 'o': // output file
			  if(!strncmp(optarg,"-",1))
			    die_on_cmdline(DIE_CMD_ARG, optind, optarg, (char *)prevarg);
			  else
			    info.output_file = optarg;
			  break;
			case 'b': // encode bitrate
			  if(!strncmp(optarg,"-",1))
			    die_on_cmdline(DIE_CMD_ARG, optind, optarg, (char *)prevarg);
			  else
			    info.bitrate = atoi(optarg);
			  break;
			case 'l': // max reencode time
			  if(!strncmp(optarg,"-",1))
			    die_on_cmdline(DIE_CMD_ARG, optind, optarg, (char *)prevarg);
			  else
			   info.reencode_time = sqrt(atoi(optarg)*atoi(optarg));
			  break;
			case 't': // do we copy tags
			  info.copy_tags = 0;
			  break;
			case 'd': // decode module
			  if(!strncmp(optarg,"-",1))
			    die_on_cmdline(DIE_CMD_ARG, optind, optarg, (char *)prevarg);
			  else
			    info.dec_module = optarg;
			  break;
			case 'e': // encode module
			  if(!strncmp(optarg,"-",1))
			    die_on_cmdline(DIE_CMD_ARG, optind, optarg, (char *)prevarg);
			  else
			    info.enc_module = optarg;
			  break;
			case 's': // print summary of user input
			    show_stats = 1;
			  break;
			case 'q': // don't check input file validity
			    info.check_validity = 0;
			  break;
			default: // die if option is unknown
			    die_on_cmdline(DIE_CMD_OPT, optind, optarg);
			  break;
		}

		// set the previous argument so if we have an error we know
		// what option caused it
		prevarg = (char *)optarg;
	}
	fprintf(stderr,"Done!\n");
	if(show_stats == 1) mog_sumstats(info);
	return info;
}

void mog_sumstats(struct mog_info info) {
	fprintf(stderr,"Summary of user input:\n");
	fprintf(stderr,"Input File:      %s\n",info.input_file);
	fprintf(stderr,"Output File:     %s\n",info.output_file);
	fprintf(stderr,"Decoder Module:  %s\n",info.dec_module);
	fprintf(stderr,"Encoder Module:  %s\n",info.enc_module);
	fprintf(stderr,"Bitrate:         %d kpbs\n",info.bitrate);
	if(info.reencode_time == -1)
        	fprintf(stderr,"Reencode Time:   unlimited\n");
	else
		fprintf(stderr,"Reencode Time:   %d seconds\n",info.reencode_time);
	if(info.copy_tags) 
	     	fprintf(stderr,"Copy Tags:       yes\n\n");
	else fprintf(stderr,"Copy Tags:       no\n\n");
}

void mog_showhelp(char *app) {
	printf("Usage:\n");
	// IMO it'd be nice to have input and output files not specified as options but just as args, ie...
	// printf(\t%s [ -stq ] [ -b bitrate ] [ -e encoder_module ] [ -l length ] in-file [ out-file ]\n", app);
	// Batch processing would use in-file and out-file the same way the "cp" utility does.
	printf("\t%s [ -stq ] [ -i input_file ] [ -o output_file ] [ -b bitrate ] [ -e encoder_module ] [ -l length ]\n",app);
	printf("\t%s [ -h ]\n",app);
	printf("\t-s\t - Show summary statistics\n");
	printf("\t-t\t - Do not perform tag detection, and do not copy tags to output file\n");
	printf("\t-q\t - Do not check inputfile for validity, must be used when readin from pipes\n");
	printf("\t-i\t - Decode audio from this file\n");
	printf("\t-o\t - Encode audio to this file\n");
	printf("\t-b\t - Encode at this bitrate\n");
	printf("\t-d\t - DEcode input as this format\n");
	printf("\t-e\t - Encode output in this format\n");
	printf("\t-l\t - Reencode for at most this many seconds\n");
	printf("\t-h\t - Output this usage information\n");
}
