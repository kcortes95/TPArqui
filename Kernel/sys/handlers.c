#include "interruptsHandler.h"

int character = 0x0;

void on_ack_keyboard() {

}

void on_ack_timer_tick() {

}

void on_ack_syscall(ddword id, ddword arg1, ddword arg2, ddword arg3) {


}

void register_handlers() {

	listener_t keyboard_listener, tt_listener, syscall_listener;

	keyboard_listener.call = &on_ack_keyboard;
	tt_listener.call = &on_ack_timer_tick;
	syscall_listener = &on_ack_syscall;

}

void keyboardHandler(void) {

	unsigned char status = kin(KEYBOARD_STATUS_PORT);
	unsigned char keycode = kin(KEYBOARD_DATA_PORT);

	if(isScreenSaverShowing()){
		stopScreenSaver();
		return;
	}
	
	if (status &  0x01) {
		kKBKeyReceived(keycode);
	}

	resetTime();
}

void syscallHandler(ddword a, ddword b, ddword c, ddword d){

	DATE date;

	switch (a) {
		case WRITE:
		kWrite((char*)c, (int) d);
		ksetBackspaceLimit();
		break;
		case READ:
		kRead((char*)c, (char) d);
		break;
		case CLEAR_SCREEN:
		kclearScreen();
		break;
		case GET_TIME:
		getCurrentDate((DATE*) c);
		break;
		case SET_TIME:
		setCurrentDate((DATE*) c);
		break;
		case SET_SCREENSAVER_TIME:
		setScreenSaverTime((int)d);
		default:
		break;
	}
}

void TTHandler(){
	screenSaverTick();
}
