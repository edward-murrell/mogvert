#ifndef _MOGDECODEOBJECTS_FLAC_H_
#define _MOGDECODEOBJECTS_FLAC_H_

#include "../mogconvert.h"
#include "../decoder_objects.h"
#include <FLAC++/decoder.h>
#include <stdio.h>


typedef struct flac_wave_buffer_node {
	unsigned char buffer[WAVE_BUFFER_SIZE];
	int buffer_used;
	struct flac_wave_buffer_node* next;
	bool finished;
}  flac_wave_buffer_node;


class Stream_Ext: public FLAC::Decoder::Stream {
	private:
FLAC__StreamDecoderReadStatus read_callback (FLAC__byte buffer[], unsigned *bytes);
FLAC__StreamDecoderWriteStatus write_callback (const::FLAC__Frame *frame, const FLAC__int32 *const buffer[]);
flac_wave_buffer_node *node_top;
flac_wave_buffer_node *node_tail;
FILE *inputfile;
	public:
Stream_Ext();
void set_file(FILE *setfile);
struct flac_wave_buffer_node* get_node();	// If null, nothing avaliable.
void metadata_callback (const::FLAC__StreamMetadata *metadata);
void error_callback (::FLAC__StreamDecoderErrorStatus status);
};


class flac_decoder: public decoder {
  private: Stream_Ext flacobject;
FILE *inputfile;
  public:
bool test(FILE *inputfile);
bool init(FILE *inputfile);
char* get_decoder_name();
void getgfi(struct generic_file_info &gfi);
int decode(unsigned char &wave_buffer);
int close(unsigned char &wave_buffer);
virtual ~flac_decoder();
};

#endif /* _MOGDECODEOBJECTS_FLAC_H_ */

