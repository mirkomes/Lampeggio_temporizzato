CFLAGS = -ffreestanding -Wall -mthumb -march=armv7-m -O2 -ggdb
ASFLAGS = -mthumb -march=armv7-m
LDFLAGS = -Bstatic -T

CROSS_COMPILE	?= /home/mirko/Universita/Sistemi_Linux_Real_Time/arm-2010q1/bin/arm-none-eabi-

AS              = $(CROSS_COMPILE)as
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
OBJCOPY         = $(CROSS_COMPILE)objcopy
OBJDUMP         = $(CROSS_COMPILE)objdump

all: led.bin checksum

led.bin: led checksum
	$(OBJCOPY) -O binary led $@
	./checksum/fix-checksum $@

checksum:
	$(MAKE) -C checksum

led: led.o boot.o vectors.o TBV.o
	$(LD) $(LDFLAGS) linker.lds $^ -o $@

.PHONY: all

led.bin: led checksum

clean:
	rm -f led *.o led.bin
	$(MAKE) -C checksum clean

.PHONY: checksum clean