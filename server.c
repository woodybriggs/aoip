#include <stdio.h>
#include <stdlib.h>
#include "aoip.h"
#include "portaudio.h"

struct sockaddr_in coms_addr;
int coms_sock_fd;

int pa_call(const void * in_buf,
            void * out_buf,
            unsigned long fpb,
            const PaStreamCallbackTimeInfo * timeinfo,
            PaStreamCallbackFlags flags,
            void * userdata)
{
  /* Fill Buffers */
  return paContinue;
}

int main(int argc, char *argv[])
{
  /* Setup default coms on TCP */
  coms_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (coms_sock_fd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

bind_socket:
  int port = DEFAULT_PORT;
  init_addr(&coms_addr, INADDR_ANY, port);
  if (bind(coms_sock_fd, (struct sockaddr *)&coms_addr, sizeof(coms_addr)) < 0) {
    /* if bind returns not bound then try new port */
    port++;
    goto bind_socket;
  }



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
