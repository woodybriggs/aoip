#include <stdio.h>
#include <stdlib.h>
#include "aoip.h"
#include "portaudio.h"

struct sockaddr_in source_addr, destin_addr;
int sock_fd;

int pa_call(const void * in_buf,
            void * out_buf,
            unsigned long fpb,
            const PaStreamCallbackTimeInfo * timeinfo,
            PaStreamCallbackFlags flags,
            void * userdata)
{
  /* @NOTE Redundant  */
  /*float *buf = (float *) in_buf;*/

  /* Potentially a blocking function */
  sendto( sock_fd,                          // Socket to use
          in_buf,                           // Pointer to data to send
          (fpb * 2) * 4,                    // Total size of data
          0,                                // Flags
          (struct sockaddr *) &destin_addr, // Address to send to
          sizeof(destin_addr) );            // Size of address struct

  return paContinue;
}

int main(int argc, char *argv[])
{
  /* Setup source socket */
  init_addr(&source_addr, INADDR_ANY, DEFAULT_PORT);
  sock_fd = init_socket((struct sockaddr *) &source_addr, sizeof(source_addr));
  if (sock_fd < 0) { perror("FAILED TO CREATE SOCKET"); exit(1); }

  /* Setup destination addr */
  init_addr(&destin_addr, inet_addr("169.254.199.17"), DEFAULT_PORT);

 /* Start Portaudio */
  PaStream *stream;
  PaError err;

  /* Initialize library before making any other calls. */
  err = Pa_Initialize();
  if( err != paNoError ) goto error;

  /* Open an audio I/O stream. */
  err = Pa_OpenDefaultStream( &stream,
                              2,          /* No input channels */
                              0,          /* Stereo output */
                              paFloat32,  /* 32 bit floating point output */
                              48000,      /* Sample rate */
                              256,        /* Frames per buffer */
                              pa_call,    /* Callback function */
                              NULL );
  if( err != paNoError ) goto error;

  /* Initiate PortAudio stream */
  err = Pa_StartStream( stream );
  if( err != paNoError ) goto error;

  /* Sleep for ever */
  while (1) {
    Pa_Sleep(5000);
  }

  err = Pa_StopStream( stream );
  if( err != paNoError ) goto error;
  err = Pa_CloseStream( stream );
  if( err != paNoError ) goto error;
  Pa_Terminate();
  return err;
error:
  Pa_Terminate();
  fprintf( stderr, "An error occured while using the portaudio stream\n" );
  fprintf( stderr, "Error number: %d\n", err );
  fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
  return err;

  return 0;
}
