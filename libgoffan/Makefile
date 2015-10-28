INC_PATH = include/
DIRECTIVES = -fno-builtin -nostartfiles -nostdlib -I $(INC_PATH)
FLAGS = -g -m32 -c

all:
	nasm -f elf -g loader.asm -o loader.o
	nasm -f elf -g libasm.asm -o libasm.o
	gcc $(FLAGS) kernel.c -o kernel.o $(DIRECTIVES) 
	gcc $(FLAGS) sys/video.c -o video.o $(DIRECTIVES) 
	gcc $(FLAGS) util/util.c -o util.o $(DIRECTIVES) 
	gcc $(FLAGS) sys/clock.c -o clock.o $(DIRECTIVES) 
	gcc $(FLAGS) sys/keyboard.c -o keyboard.o $(DIRECTIVES) 

	ld -m elf_i386 -T link.ld -o kernel.bin kernel.o libasm.o loader.o util.o video.o clock.o keyboard.o
	rm *.o
	mcopy kernel.bin z:/boot -o
clean:
	rm *.o
	rm kernel.bin
	
