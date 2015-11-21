#include "../arch/include/arch.h"
#include "include/syscalls.h"
#include "include/mouse.h"

#include "include/video.h"

uint8_t sensitivty = 8;

bool is_visible = yes;

listener_pool_t event_listeners;

void mouse_write(uint8_t a_write);
uint8_t mouse_read();
void mouse_install();
void mouse_wait(uint8_t a_type);
void on_mouse_event(ddword id, ddword rdi, ddword rsi, ddword rdx);

void init_mouse() {

	listener_t mouse_listener;

	mouse_install();

	mouse_listener.call = &on_mouse_event;

  event_listeners.size = 0;

	add_listener(MOUSE, mouse_listener);
}

error_t add_mouse_listener(listener_t listener) {

  if ( event_listeners.size >= MAX_LISTENERS_ALLOWED ) {
    return 1;
  }

  event_listeners.listeners[event_listeners.size++] = listener;

  return 0;

}

//http://forum.osdev.org/viewtopic.php?t=10247
//Mouse.inc by SANiK
//License: Use as you wish, except to cause damage
uint8_t mouse_cycle = 0;     //unsigned char
int8_t mouse_byte[3];    //signed char
int8_t mouse_x=0;         //signed char
int8_t mouse_y=0;         //signed char

int16_t x = 0, y = 0;


void on_mouse_event(ddword id, ddword rdi, ddword rsi, ddword rdx) {

  int i = 0;
  uint8_t buttons_flag = 0;

  if (is_visible)
    unset_cursor(x/sensitivty, y/sensitivty);

  if (mouse_cycle == 0) {

    mouse_byte[0] = _inport(0x60);
    mouse_cycle++;

  } else if (mouse_cycle == 1) {

    mouse_byte[1] = _inport(0x60);
    mouse_cycle++;

  } else {

    mouse_byte[2] = _inport(0x60);
    mouse_x = mouse_byte[1];
    mouse_y = mouse_byte[2];
    if (mouse_byte[0] & 0x1) {
      buttons_flag |= 1 << 0;
    }
    if (mouse_byte[0] & 0x2) {
      buttons_flag |= 1 << 1;
    }
    if (mouse_byte[0] & 0x4) {
      buttons_flag |= 1 << 2;
    }

    mouse_cycle = 0;

    x += mouse_x;
    y += mouse_y;
  }

  if (mouse_cycle == 0) {

    if (is_visible)
      set_cursor(x/sensitivty, y/sensitivty);

    for (; i < event_listeners.size; i++) {
      event_listeners.listeners[i].call(MOUSE, x, y, buttons_flag);
    }
  }

  

  // prints("x: ");
  // puti(x);
  // prints(" y: ");
  // puti(y);
  // putc('\n');
  
}

void mouse_set_visible(bool b) {
  if (is_visible && !b) {
    is_visible = b;
    unset_cursor(x/sensitivty, y/sensitivty);
  } else if (!is_visible && b) {
    is_visible = b;
    set_cursor(x/sensitivty, y/sensitivty);
  }
}

void mouse_set_sensitivity(uint8_t s) {
  unset_cursor(x/sensitivty, y/sensitivty);
  sensitivty = s;
  set_cursor(x/sensitivty, y/sensitivty);
}

void mouse_wait(uint8_t a_type) {
	println("waiting");

  dword _time_out = 100000; //unsigned int
  if ( a_type == 0) {
    while(_time_out--) {
      if((_inport(0x64) & 1)==1) {
        return;
      }
    }
    return;
  }
  else {
    while(_time_out--) {
      if((_inport(0x64) & 2) == 0) {
        return;
      }
    }
    return;
  }
}

void mouse_write(uint8_t a_write) {
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  _outport(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  _outport(0x60, a_write);
}

uint8_t mouse_read() {
  //Get's response from mouse
  mouse_wait(0); 
  return _inport(0x60);
}

void mouse_install() {
  byte _status;  //unsigned char

  putc('1');
  //Enable the auxiliary mouse device
  mouse_wait(1);
  _outport(0x64, 0xA8);
  
  //Enable the interrupts
  putc('2');
  mouse_wait(1);
  _outport(0x64, 0x20);
  putc('3');
  mouse_wait(0);
  _status=(_inport(0x60) | 2);
  puti(_status);
  putc('\n');
  putc('4');
  mouse_wait(1);
  _outport(0x64, 0x60);
  putc('5');
  mouse_wait(1);
  _outport(0x60, _status);
  
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
  
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge

}
