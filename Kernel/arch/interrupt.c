#include "include/interrupts_handler.h"
#include "include/idt.h"

#include "include/arch.h"
#include "../sys/include/video.h"

#include "../sys/include/timer.h"

extern void _load_handler(byte entry, ddword handler, ddword idt_start);

// Handlers
extern void _keyboard_interrupt_handler();
extern void _mouse_interrupt_handler();
extern void _syscall_interrupt_handler();
extern void _tt_interrupt_handler();

extern void _force_int33(ddword);
extern void _mouse_init();

void mouse_write(uint8_t a_write);
uint8_t mouse_read();
void mouse_install();
void mouse_wait(uint8_t a_type);
void mouse_handler(ddword id, ddword rdi, ddword rsi, ddword rdx);

static listener_pool_t listeners_map[MOUSE - KEYBOARD];

void init_interrupts(void) {

	uint8_t i = 0;

	/**
	 *
	 *	Cargo las rutinas de atencion de interrupcion
	 * 
	 */

	idt_set_handler(0x20, (ddword)&_tt_interrupt_handler);
	idt_set_handler(0x21, (ddword)&_keyboard_interrupt_handler);
	// idt_set_handler(0x33, (ddword)&_mouse_interrupt_handler);
	idt_set_handler(0x80, (ddword)&_syscall_interrupt_handler);

  idt_set_handler(12,   (ddword)&_mouse_interrupt_handler);
  idt_set_handler(0x12, (ddword)&_mouse_interrupt_handler);
  idt_set_handler(0x24, (ddword)&_mouse_interrupt_handler);
  idt_set_handler(0x33, (ddword)&_mouse_interrupt_handler);
  idt_set_handler(0x2d, (ddword)&_mouse_interrupt_handler);
  idt_set_handler(0x2c, (ddword)&_mouse_interrupt_handler);
  idt_set_handler(0x74, (ddword)&_mouse_interrupt_handler);

	for (; i < MOUSE - KEYBOARD; i++) {
		listeners_map[i].size = 0;
	}

	mouse_install();

	return;
}

error_t add_listener(interrupt_id id, listener_t listener) {

	if ( listeners_map[id].size >= MAX_LISTENERS_ALLOWED ) {
		return 1;
	}

	listeners_map[id].listeners[listeners_map[id].size++] = listener;

	return 0;
}

void on_interrupt(interrupt_id id, ddword sid, ddword arg1, ddword arg2, ddword arg3) {

	uint8_t i = 0;

	for (; i < listeners_map[id].size; i++) {
		listeners_map[id].listeners[i].call((syscall_id)sid, arg1, arg2, arg3);
	}

}

void on_timer_tick(ddword id, ddword arg1, ddword arg2, ddword arg3) {
	on_interrupt(TIMER_TICK, id, arg1, arg2, arg3);
}

void on_keyboard(ddword id, ddword arg1, ddword arg2, ddword arg3) {

	// _force_int33(3);

	on_interrupt(KEYBOARD, id, arg1, arg2, arg3);
}

void on_syscall(ddword id, ddword rdi, ddword rsi, ddword rdx, ddword r10) {

	on_interrupt(SYSCALL, id, rdi, rsi, rdx);
}

void on_mouse(ddword id, ddword arg1, ddword arg2, ddword arg3) {
	// puti(id); putc(' ');
	// puti(arg1); putc(' ');
	// puti(arg2); putc(' ');
	// puti(arg3); putc(' ');
	// on_interrupt(MOUSE, id, arg1, arg2, arg3);
}




//Mouse.inc by SANiK
//License: Use as you wish, except to cause damage
uint8_t mouse_cycle = 0;     //unsigned char
int8_t mouse_byte[3];    //signed char
int8_t mouse_x=0;         //signed char
int8_t mouse_y=0;         //signed char

//Mouse functions
// void mouse_handler()
// {
//   switch(mouse_cycle)
//   {
//     case 0:
//       mouse_byte[0]=_inport(0x60);
//       mouse_cycle++;
//       break;
//     case 1:
//       mouse_byte[1]=_inport(0x60);
//       mouse_cycle++;
//       break;
//     case 2:
//       mouse_byte[2]=_inport(0x60);
//       mouse_x=mouse_byte[1];
//       mouse_y=mouse_byte[2];
//       mouse_cycle=0;
//       break;
//   }
//   prints("x: ");
//   puti(mouse_x);
//   prints(" y: ");
//   puti(mouse_y);
//   putc('\n');
// }
// 
// 
uint8_t x = 0, y = 0;


void mouse_handler(ddword id, ddword rdi, ddword rsi, ddword rdx)
{
  static signed char delta_x, delta_y, flags;
  int x_final,y_final;
  // static unsigned char cycle = 0;
  // static char mouse_bytes[3];
  mouse_byte[mouse_cycle++] = _inport(0x60);
  

  // if (mouse_cycle == 3) { // if we have all the 3 bytes...
    // mouse_cycle = 0; // reset the counter
    // do what you wish with the bytes, this is just a sample
    // if ((mouse_byte[0] & 0x80) || (mouse_byte[0] & 0x40))
      // return; // the mouse only sends information about overflowing, do not care about it and return
    // if (!(mouse_byte[0] & 0x20))
      // y |= 0xFFFFFF00; //delta-y is a negative value
    // if (!(mouse_byte[0] & 0x10))
      // x |= 0xFFFFFF00; //delta-x is a negative value
    // if (mouse_byte[0] & 0x4)
    //   prints("Middle button is pressed!n");
    // if (mouse_byte[0] & 0x2)
    //   prints("Right button is pressed!n");
    // if (mouse_byte[0] & 0x1)
    //   prints("Left button is pressed!n");
    // do what you want here, just replace the puts's to execute an action for each button
    // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
  // }

  switch(mouse_cycle){
    case 0:{
      flags = _inport(0x60) & 0x0FF;
      if ((flags & 8) == 0){
        mouse_cycle=0;
        return;
      }
      mouse_cycle++;  
      break;
    }
    case 1:{
      delta_x = _inport(0x60) & 0x0FF;
      mouse_cycle++;
      break;
    }
    case 2:{
      delta_y = _inport(0x60) & 0x0FF;
      mouse_cycle = 0;
      if((flags & 1) != 0){
        println("left button pressed");
        // mouse.l_button_pressed=1;
      }
      if((flags & 2)!=0){
        println("right button pressed");
        // mouse.r_button_pressed=1;
      }
      if((flags & 4)!=0){
        println("middle button pressed");
        // mouse.m_button_pressed=1;
      }
      int p = x;
      int u = y;
      x_final=(delta_x%5)+p;
      x_final=x_final>79?79:x_final;
      x_final=x_final<0?0:x_final;
      y_final=(delta_y%5)*(-1)+u;
      y_final=y_final>24?24:y_final;
      y_final=y_final<0?0:y_final;
      // mouse_cursor(mouse.x,mouse.y,x_final,y_final);
      // mouse.x=x_final;
      // mouse.y=y_final;
      break;
    }
    default:{
      break;
    } 
  }

  prints("x: ");
  puti(x_final);
  prints(" y: ");
  puti(y_final);
  putc('\n');
  
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
  uint8_t f = mouse_read();  //Acknowledge

  puti(f); putc('\n');

  //Setup the mouse handler
  

  //wait(500);

  // _mouse_init();

  // mouse_handler();

}
