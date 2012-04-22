#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

#include "mogconvert.h"
#include "error.h"
#include <strings.h>
#include <stdio.h>

int check_decoder(char *decoder);
int check_encoder(char *encoder);
int get_code(char *string);
char get_letter();

#endif /* _FILEHANDLER_H_ */
