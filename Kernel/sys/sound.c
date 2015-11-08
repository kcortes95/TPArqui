#include "include/sound.h"
#include "include/timer.h"
#include "include/video.h"

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
	beeplf(500, 0x533);
}

void beeplf(unsigned int length, unsigned int freq) {
	
	println("\nbeep registered:");
	prints("freq: ");
	puti(freq);
	prints(" duration: ");
	puti(length);
	println("ms");

	prints("playing...");
	play(freq);
	wait(length);
	pause();
	println("stopping");

}
