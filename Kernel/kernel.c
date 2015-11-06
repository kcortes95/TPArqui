#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include "arch/include/arch.h"
#include "sys/include/video.h"
#include "sys/include/timer.h"
#include "sys/include/keyboard.h"
#include "sys/include/syscalls.h"
#include "sys/include/sound.h"
#include "sys/include/playNote.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
		);
}

void * initializeKernelBinary()
{
	char buffer[10];

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

void play_intro() {

	uint8_t i = 0;

	clc();

	println("El TP de arqui esta booteando...");

	wait(1200);

	println("Hacete un cafecito. Ya arrancamos");

	wait(1500);

	println("Vamos??");

	wait(1700);

	clc();

	println("	            ____________________________________________________");
	println("            /                                                    \\");
	println("           |    _____________________________________________     |");
	println("           |   |                                             |    |");
	println("           |   |  OS$> make me a sandwich                    |    |");
	println("           |   |  make it yourself                           |    |");
	println("           |   |  OS$> sudo make me a sandwich               |    |");
	println("           |   |  alright...                                 |    |");
	println("           |   |  OS$> _                                     |    |");
	println("           |   |                                             |    |");
	println("           |   |                                             |    |");
	println("           |   |                                             |    |");
	println("           |   |                                             |    |");
	println("           |   |                                             |    |");
	println("           |   |                                             |    |");
	println("           |   |                                             |    |");
	println("           |   |_____________________________________________|    |");
	println("           |                                                      |");
	println("            \\_____________________________________________________/");
	println("                   \\_______________________________________/");
	println("                _______________________________________________");
	println("             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_");
	println("          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_");
	println("       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_");
	println("    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_");

	wait(2000);

	move_up();

	for (; i < 80; i++) {
		putc('*');
		wait(80);
	}

	clc();



}

int main() {

	init_idt();
	init_interrupts();
	init_timer();
	init_syscalls();
	init_keyboard();
	beeplf(2,9121); //de lo de goffan
	
	clc();

	// Con esto ejecutamos Userland
	((EntryPoint)sampleCodeModuleAddress)();

	return 0;
}
