#include "include/timer.h"
#include "include/playSong.h"
#include "../arch/include/ports.h"
#include "../arch/include/playNote.h"

/*
tiempo - nota
*/

void playSong(){
	//TO DO	
}

void playNoteXSeconds(int freq, int seconds){
	playNote(freq);
	wait(seconds);
	noSound();
}

void noSound(){
	//TODO -- Dont know how!!
	//osdev dice:
 	uint8_t tmp = _inport(0x61) & 0xFC;
 	_outport(0x61, tmp);
}