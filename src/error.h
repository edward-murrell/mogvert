#ifndef _ERROR_H_
#define _ERROR_H_

#include "mogconvert.h"
#include "filehandler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// for die_on_cmdline()
#define DIE_CMD_OPT 1
#define DIE_CMD_ARG 2

void die_on_file_openr(char *filename);
void die_on_file_openw(char *filename);
void die_on_cmdline(int cmd_error_code,int optind,const char *optarg, const char *prevarg = NULL);
void module_notfound(const char *module);
void type_mismatch(const char *module);
void invalid_encoder(const char *encoder);

#endif /* _ERROR_H_ */
