#ifndef AUDIOPCM_H_
#define AUDIOPCM_H_

#include <audio/audio_manager_routing.h>

#include <QDebug>
#include "DataSender.hpp"
#include "DataReceiver.hpp"
#include "CircularBuffer.h"

namespace ayvu {

// Constants for clearer init code
// Jitter buffer size.
static const int JITTER_BUFFER_NUMBER_FRAMES = 20;
// Standard VoIP
static const int PREFERRED_FRAME_SIZE = 640;
static const int VOIP_SAMPLE_RATE = 16000;
// ulaw silence is FF
static const char SILENCE = 0xFF;

class AudioPCM {

public:

	void startPcmAudio();
	void stopPcmAudio();
	int toggleSpeaker(bool);
	void capturesetup();
	void playsetup();

	static void setCaptureReady(bool);
	static bool writeDatagramToCircularBuffer(QByteArray*);
	/**
	 * Get bitrate in kbps
	 */
	static int getBitRate();

private:
	static void* playerThread(void*);
	static void* captureThread(void*);
	static int capture(circular_buffer_t*);
	static int play(circular_buffer_t*);
	static void resetPlay();

	pthread_t g_capturethread;
	pthread_t g_playerthread;
	pthread_attr_t attr_p;
	unsigned int g_audio_manager_handle_t;

	static snd_pcm_t *g_pcm_handle_c;
	static snd_pcm_t *g_pcm_handle_p;
	static unsigned int g_audio_manager_handle_c;
	static unsigned int g_audio_manager_handle_p;
	static int g_frame_size_c;
	static int g_frame_size_p;

	// Global used by both threads
	static circular_buffer_t* g_circular_buffer; //temporary capture buffer
	static circular_buffer_t* data_to_play; // voice data received

	// Flag to stop the record and capture threads
	static bool g_execute_audio;
	static bool capture_ready;
};
}


#endif /* AUDIOPCM_H_ */
