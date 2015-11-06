#include "include/timer.h"
#include "include/ports.h"
#include "include/playSong.h"
#include "include/playNote.h"

/*
tiempo - nota
*/

void playSong(){
	//TO DO	
}

private void playNoteXSeconds(int freq, int seconds){
	playNote(freq);
	wait(seconds);
	noSound();
}

private void noSound(){
	//TODO -- Dont know how!!
	//osdev dice:
 	uint8_t tmp = _inport(0x61) & 0xFC;
 	_outport(0x61, tmp);
}