#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "portaudio.h"
#include "rtp.h"

// Definitions
#ifndef RTP_PORT
#define RTP_PORT 8600
#endif

// Globals
int rtp_sock_fd;
struct sockaddr_in rtp_server_addr;


int  audio_callback(const void                      *input,
                    void                            *output,
                    unsigned long                   frameCount,
                    const  PaStreamCallbackTimeInfo *timeInfo,
                           PaStreamCallbackFlags    statusFlags,
                    void                            *userData);


int main(int argc, char *argv[]) {
  // Socket Setup
  init_addr(&rtp_server_addr, inet_addr("192.168.0.7") , RTP_PORT);

  rtp_sock_fd  = init_socket((struct sockaddr *) &rtp_server_addr, sizeof(rtp_server_addr));
  if (rtp_sock_fd < 0) {
    perror("FAILED TO CREATE SOCKET");
    exit(1);
  }

  /*// PortAudio Setup
  PaStream   *stream;
  PaError    err;
  int audio_data;

  err = Pa_Initialize();
  if (err != paNoError) printf("PortAudio Error: %s\n", Pa_GetErrorText(err));

  err = Pa_OpenDefaultStream( &stream,
                              2,
                              2,
                              paFloat32,
                              48000,
                              64,
                              audio_callback,
                              &audio_data );
  if (err != paNoError) printf("PortAudio Error: %s\n", Pa_GetErrorText(err));

  err = Pa_StartStream(stream);
  if (err != paNoError) printf("PortAudio Error: %s\n", Pa_GetErrorText(err));

  Pa_Sleep(10000);

  err = Pa_StopStream(stream);
  if (err != paNoError) printf("PortAudio Error: %s\n", Pa_GetErrorText(err));

  err = Pa_CloseStream(stream);
  if (err != paNoError) printf("PortAudio Error: %s\n", Pa_GetErrorText(err));

  Pa_Terminate();*/

  return 0;
}


int audio_callback(const void                      *input,
                   void                            *output,
                   unsigned long                   frameCount,
                   const  PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags    statusFlags,
                   void                            *userData) {
  const float *in  = (const float *) input;

  return paContinue;
}
