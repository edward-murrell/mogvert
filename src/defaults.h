#ifndef DEFAULTS_H
#define DEFAULTS_H

/*********************************************
These defaults are used if they aren't overridden at compile-time with -D
*********************************************/

#define _DEFAULT_DECODER "wav"
#define _DEFAULT_ENCODER "mp3"
#define _DEFAULT_ENCODER_BITRATE 128


/**********************************************
  Set defaults in case the command-line didn't
***********************************************/
#ifndef DEFAULT_ENCODER
#define DEFAULT_ENCODER _DEFAULT_ENCODER
#endif

#ifndef DEFAULT_DECODER
#define DEFAULT_DECODER _DEFAULT_DECODER
#endif

#ifndef DEFAULT_ENCODER_BITRATE
#define DEFAULT_ENCODER_BITRATE _DEFAULT_ENCODER_BITRATE
#endif

#endif /* ifndef DEFAULTS_H */
