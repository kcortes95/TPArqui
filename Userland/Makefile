include Makefile.inc

SAMPLE_DATA=01-sampleDataModule.bin

all:	clean libc shell sampleDataModule

libc:
	@cd libc; make
	@echo "LibC built"

shell:	libc
	@cd shell; make
	@echo "Shell built"

sampleDataModule:
	cat songs >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)
clean:
	@cd shell; make clean
	@cd libc; make clean
	- rm -rf *.bin


.PHONY: clean all libc shell sampleDataModule
