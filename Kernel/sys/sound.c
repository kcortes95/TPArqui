#include "include/sound.h"
#include "include/timer.h"
#include "include/video.h"

#define SOUND_DEBUG 1

//! output sound to speaker
void play(uint32_t frequency) {

	if ((frequency<19) || (frequency>22000)) return;

	// 
	_outport(0x43, 0xB6);
	_outport(0x42, frequency & 0xFF);
	_outport(0x42, ((frequency & 0xFF) >> 8) & 0x0F );
	_outport(0x61, _inport(0x61) | 3);
}

void pause() {

	_outport(0x61, _inport(0x61) & 0xFC);
}

void beep(void) {
	beeplf(100, 200);
}

void beeplf(unsigned int length, unsigned int freq) {
	
	if (SOUND_DEBUG) {
		println("beep registered:");
		prints("freq: ");
		puti(freq);
		prints(" duration: ");
		puti(length);
		println("ms");

		prints("playing...");
	}
	if (freq != 0)
		play(freq);
	wait(length);
	pause();
	if (SOUND_DEBUG )
		println("stopping");

}
