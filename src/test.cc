#include "mogconvert.h"
#include "decoder_objects.h"
#include "encoder_objects.h"
#include "init.h"
#include "filehandler.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>

#include <assert.h>

int main(int argc,  char* argv[])
{
//int get_code(const char *string);
const char *wav = "WAV";
int foo = get_code(wav);
printf("Testing 'WAV'. retval: %d\n",foo);

return 0;
}