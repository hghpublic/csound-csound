/*
    cs_jack.h:

    Copyright (C) 2008 by  Cesare Marilungo

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
    02110-1301 USA
*/

#pragma once

#define MAX_NAME_LEN    32      /* for client and port name */

typedef struct RtJackBuffer_ {
#ifdef LINUX
    pthread_mutex_t csndLock;               /* signaled by process callback */
    pthread_mutex_t jackLock;               /* signaled by audio thread     */
#else
    void    *csndLock;                      /* signaled by process callback */
    void    *jackLock;                      /* signaled by audio thread     */
#endif
    jack_default_audio_sample_t **inBufs;   /* 'nChannels' capture buffers  */
    jack_default_audio_sample_t **outBufs;  /* 'nChannels' playback buffers */
} RtJackBuffer;

typedef struct RtJackGlobals_ {
    CSOUND  *csound;                    /* Csound instance pointer          */
    int32_t     jackState;                  /* 0: OK, 1: sr changed, 2: quit    */
    char    clientName[MAX_NAME_LEN + 1];       /* client name              */
    char    inputPortName[MAX_NAME_LEN + 1];    /* input port name prefix   */
    char    outputPortName[MAX_NAME_LEN + 1];   /* output port name prefix  */
    int32_t     sleepTime;                  /* sleep time in us (deprecated)    */
    char    *inDevName;                 /* device name for -i adc           */
    char    *outDevName;                /* device name for -o dac           */
    int32_t     sampleRate;                 /* sample rate in Hz                */
    int32_t     nChannels;                  /* number of channels               */
    int32_t     nChannels_i;                /* number of in channels            */
    int32_t     bufSize;                    /* buffer size in sample frames     */
    int32_t     nBuffers;                   /* number of buffers (>= 2)         */
    int32_t     inputEnabled;               /* non-zero if capture (adc) is on  */
    int32_t     outputEnabled;              /* non-zero if playback (dac) is on */
    int32_t     csndBufCnt;                 /* current buffer in Csound thread  */
    int32_t     csndBufPos;                 /* buffer position in Csound thread */
    int32_t     jackBufCnt;                 /* current buffer in JACK callback  */
    int32_t     jackBufPos;                 /* buffer position in JACK callback */
    jack_client_t   *client;            /* JACK client pointer              */
    jack_port_t     **inPorts;          /* 'nChannels' ports for capture    */
    jack_default_audio_sample_t **inPortBufs;
    jack_port_t     **outPorts;         /* 'nChannels' ports for playback   */
    jack_default_audio_sample_t **outPortBufs;
    RtJackBuffer    **bufs;             /* 'nBuffers' I/O buffers           */
    int32_t     xrunFlag;                   /* non-zero if an xrun has occured  */
    jack_client_t   *listclient;
    int32_t outDevNum, inDevNum;            /* select devs by number */
    MYFLT sr;
} RtJackGlobals;
