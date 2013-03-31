#include "flac.h"

flac_decoder::flac_decoder() {
}

coder_info * flac_decoder::get_coder_info() {
	coder_info * info = new coder_info;
	info->type      = MOGV_OBJECT_DECODER;
	info->shortname = "FLAC";
    info->longname  = "FLAC decoder";
	info->suffix    = "flac";
	info->magic		= "fLaC";
	return info;
}


bool flac_decoder::test(FILE *inputfile)
{
	return true;
}
bool flac_decoder::init(FILE *inputfile)
{
	flacobject.set_file(inputfile);
    flacobject.set_metadata_respond_all();
	flacobject.init();
	flacobject.process_until_end_of_metadata(); // TODO Check these returns;
	return true;
}
void flac_decoder::getgfi(struct generic_file_info &gfi)
{
	return flacobject.getgfi(gfi);
}

int flac_decoder::decode(unsigned char &wave_buffer)
{
	flacobject.process_single();	// TODO - Return some crap if this dies.
//	flacobject.process_until_end_of_stream();	// Useful if/when doing threading
	flac_wave_buffer_node *node_read = flacobject.get_node();
	if (node_read == NULL && flacobject.get_state() == FLAC__STREAM_DECODER_READ_FRAME  )
	{		return 0;
	}
	else if (node_read == NULL)
		return -1;	// This should happen at the end of the stream, and all the blocks read

	unsigned char *in_buf = (unsigned char *) &wave_buffer;
	int size = node_read->buffer_used;

	for (int i=0; i<size;i++)
	{	
		in_buf[i] = node_read->buffer[i];
	//	printf("DECODE(a) %i nd_buf cont: %u\n",i,node_read->buffer[i]);
//		printf("DECODE(b) %i in_buf cont: %u\n",i,in_buf[i]);

	}
	delete node_read;
	return size;
}


int flac_decoder::close(unsigned char &wave_buffer)
{
	// TODO - Unh, shouldn't there by something actually here?
	// Check for unencoded wave blocks left behind maybe
	return 0; // is 0 even the right return value for success?
}

flac_decoder::~flac_decoder()
{
	// yay.
}

// ====== Implementations of protected virtual functions here =====
FLAC__StreamDecoderReadStatus Stream_Ext::read_callback (FLAC__byte buffer[], size_t *bytes)
{	// Important, bytes contains the maximum number of bytes allowed to be read.
	int buffer_size = INPUT_BUFFER_SIZE;
	if (*bytes < INPUT_BUFFER_SIZE)
		buffer_size = *bytes;
//	printf("READ_CALLBACK() start\n");
//	printf("READ_CALLBACK() bytes: %u\n",*bytes);
	//get bytes from file, stick in buffer, return size or address
	unsigned char file_buffer[buffer_size];
	unsigned int size = fread(&file_buffer,1,buffer_size,inputfile);

	for (unsigned int i=0; i<size;i++)
	{
		buffer[i] = file_buffer[i];
	}
	*bytes = size;

	if (size > 0)
		return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
	else if (size == 0)
		return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
	else
	{
		return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
	}
}


FLAC__StreamDecoderWriteStatus Stream_Ext::write_callback (const::FLAC__Frame *frame, const FLAC__int32 *const buffer[])
{
	// printf("WRITE_CALLBACK() start\n");
	unsigned int bytes_per_chan = get_blocksize()*2;	// 16 bits per byte
	//unsigned int channels = get_channels();	// Not caring atm really.
	//unsigned int channels = 2; // not even used at the moment

	// Need to kill these eventually.
	// printf("bytes per chan %u\n",bytes_per_chan);
	// printf("samples %u\n",get_blocksize());
	// printf("bits per sample %u\n",get_bits_per_sample());

	// TODO - Need to check for funky header values here, no errors in test filess
	// TODO - This will ignore anything other than two channels, unless I can find a better way to handle it in the encoders
	// I will probably have to rewrite the buffer interface. Oh Joy.

	flac_wave_buffer_node *node_created = new flac_wave_buffer_node;
	node_created->next = NULL;

	// printf("node_created ptr: %p\n",node_created);
	// printf("buffer ptr: %p\n",buffer);

	unsigned char* l_buffer = (unsigned char*)buffer[0];
	unsigned char* r_buffer = (unsigned char*)buffer[1];

	for (unsigned int i = 0; i < bytes_per_chan; ++i)
	{	// valgrind throws a shit about this, but it does work. Doesn't handle anything except 16 bit though
		node_created->buffer[4*i] =   l_buffer[(4*i)+0];
		node_created->buffer[4*i+1] = l_buffer[(4*i)+1];
		node_created->buffer[4*i+2] = r_buffer[(4*i)+0];
		node_created->buffer[4*i+3] = r_buffer[(4*i)+1];
	}
	node_created->buffer_used = bytes_per_chan*2;

	if (node_top != NULL)
	{
		if (node_created != NULL)
			node_top->next = node_created;
		else node_top->next = NULL;
	}
	else
	{
		node_top = node_created;
		node_tail = node_created;
	}

	node_created->finished = true; // This is set when the node is allowed to be used.
	// printf("WRITE_CALLBACK() finished\n");
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void Stream_Ext::set_file(FILE *setfile)
{
	inputfile = setfile;
}

struct flac_wave_buffer_node* Stream_Ext::get_node()
{
	struct flac_wave_buffer_node *node_return = NULL;

	if (node_tail != NULL)
	{	
		if (node_tail->finished == false)	// This is in case we have threaded decoders.
			return NULL;
		else
		{
			node_return = node_tail;
			if (node_tail->next != NULL)
				node_tail = node_tail->next;
			else 
			{
				node_tail = NULL;
				node_top = NULL;
			}
			return node_return;
		}
	}
	else return NULL;
}

void Stream_Ext::metadata_callback (const::FLAC__StreamMetadata *metadata)
{
        switch (metadata->type) {
            case FLAC__METADATA_TYPE_STREAMINFO: {
                const FLAC__StreamMetadata_StreamInfo * stream_info = &metadata->data.stream_info;
                fprintf(stderr,"Decoder: FLAC: Samplerate/bits/channels: %i/%i/%i\n",stream_info->sample_rate,stream_info->bits_per_sample,stream_info->channels);
                //TODO, turn this into useful information
            } break;
            case FLAC__METADATA_TYPE_VORBIS_COMMENT: {
                this->metadata = new FLAC::Metadata::VorbisComment(metadata);
                fprintf(stderr,"Decoder: FLAC: Found Ogg Vorbis type comment.\n");
            } break;
            default: {
                fprintf(stderr,"Decoder: FLAC: Unhandled metadata found.\n");
            }
        }
}

void Stream_Ext::error_callback (::FLAC__StreamDecoderErrorStatus status)
{
	if (status == FLAC__STREAM_DECODER_ERROR_STATUS_LOST_SYNC)
	{
		printf("Decoder: FLAC: An error in the stream caused the decoder to lose synchronization.\n");
		reset();
	}
	else if (status == FLAC__STREAM_DECODER_ERROR_STATUS_BAD_HEADER)
		printf("Decoder: FLAC: The decoder encountered a corrupted frame header.\n");
	else if (status == FLAC__STREAM_DECODER_ERROR_STATUS_FRAME_CRC_MISMATCH)
		printf("Decoder: FLAC: The frame's data did not match the CRC in the footer.\n");
}

Stream_Ext::Stream_Ext()
{
	node_top = NULL;
	node_tail = NULL;
    this->metadata = NULL;
}

void Stream_Ext::getgfi(struct generic_file_info &gfi) {
    if (metadata == NULL)
        return;

	for(uint i=0;i<metadata->get_num_comments();i++)
	{   
        FLAC::Metadata::VorbisComment::Entry comment = metadata->get_comment(i);
        const char * tag_key =   comment.get_field_name();
        const char * tag_value = comment.get_field_value();
        
		       if (strcasecmp(tag_key,"title") == 0) {
            strcpy(gfi.title,tag_value);
        } else if (strcasecmp(tag_key,"artist") == 0) {
            strcpy(gfi.artist,tag_value);
        } else if (strcasecmp(tag_key,"album") == 0) {
            strcpy(gfi.album,tag_value);
        } else if (strcasecmp(tag_key,"comment") == 0) {
            strcpy(gfi.comment,tag_value);
        } else if (strcasecmp(tag_key,"genre") == 0) {
            strcpy(gfi.genre,tag_value);
        } else if (strcasecmp(tag_key,"date") == 0) {
            strcpy(gfi.year,tag_value);
        } else if (strcasecmp(tag_key,"year") == 0) {
            strcpy(gfi.year,tag_value);
        } else if (strcasecmp(tag_key,"tracknumber") == 0) {
            strcpy(gfi.track,tag_value);
        } else {
            fprintf(stderr,"Decoder: FLAC: Unknown metadata comment '%s'=>'%.*s'\n",tag_key,80,tag_value);
        }
	}
}
