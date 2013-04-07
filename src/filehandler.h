#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

#include "mogconvert.h"
#include "error.h"
#include <strings.h>
#include <stdio.h>

const char * get_ext(const char *arg);
int check_decoder(const char *decoder);
int check_encoder(const char *encoder);
int get_code(const char *string);
char get_letter();

#endif /* _FILEHANDLER_H_ */
