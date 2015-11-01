#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include "arch/include/arch.h"

#include "sys/include/video.h"

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

int main() {

	init_idt();
	init_interrupts();



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

	wait(500);

	clc();	


	return 0;
}
