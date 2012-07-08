#include "filehandler.h"
#include <assert.h>

int test_getcode(const char * test){
	int code = get_code(test);
	printf("Testing '%s'.  \tretval: %d\n",test,code);
	return code;
}

int main(int argc,  char* argv[]){

	/* Testing getcode:  int get_code(const char *string);  */
	if(argc > 1){ 
		for (int i = 1; i < argc; i++){
			test_getcode(argv[i]); }
		}
	else{
		if(test_getcode("wav") != 1) assert(0);
		if(test_getcode(".wav") != 1) assert(0);
		if(test_getcode("WAV") != 1) assert(0);
		if(test_getcode(".WAV") != 1) assert(0);
		if(test_getcode("blarwav") != 65536) assert(0);
		if(test_getcode("ALWOER.WAv") != 1) assert(0);
		if(test_getcode("foo.mp3") != 2) assert(0);
		if(test_getcode("foo.MP3") != 2) assert(0);
		if(test_getcode("FMP3") != 65536) assert(0);
		printf("Passed function tests:\tint get_code(const char *string);\n");
	}
	return 0;

}

