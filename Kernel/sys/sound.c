#include "include/sound.h";

static unsigned int timeout = 0;

//! output sound to speaker
void sound(uint32_t frequency) {

	if ((frequency<19) || (frequency>22000)) return;

	_outport(0x61, _inport(0x61) | 3);
	_outport(0x43, 0xB6);
	_outport(0x42, (1193182L / frequency) & 0xFF);
	_outport(0x42, (1193182L / frequency) >> 8);
}

void nosound(void) {

	_outport(0x61, _inport(0x61) & 0xFC);
}

void beep(void) {
	beepl(1);
}

void beepl(unsigned int length) {
	beeplf(length, 0x533);
}

void beeplf(unsigned int length, unsigned int freq) {
	timeout = timeout > length ? timeout : length;
	sound(freq);
}


void tick_sound(void) {
	if (timeout > 0) {
		timeout--;
	} else {
		nosound();
	}
}