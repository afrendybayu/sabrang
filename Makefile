
NAMA_FILE=hasil

LDSCRIPT=lpc2368.ld
PAT =TOOLCHAIN/bin/
CC=$(PAT)arm-elf-gcc
OBJCOPY=$(PAT)arm-elf-objcopy
DISAMB=$(PAT)arm-elf-objdump
UKURAN=$(PAT)arm-elf-size
PENULIS=Penulis/lpc_dbe



#LINKER_FLAGS=-mthumb -nostartfiles -Xlinker -o$(NAMA_FILE).elf -Xlinker -M -Xlinker -Map=rtosdemo.map 
LINKER_FLAGS=-mthumb -nostartfiles -Xlinker -o$(NAMA_FILE).elf -Xlinker -M -Xlinker -Map=$(NAMA_FILE).map 

OPTIM=-O1


CFLAGS= $(DEBUG) \
		$(OPTIM) \
		-ITOOLCHAIN/arm-elf/include/ \
		-T$(LDSCRIPT) \
		-I . \
		-D ROWLEY_LPC23xx \
		-D THUMB_INTERWORK \
		-mcpu=arm7tdmi \
		-D PACK_STRUCT_END=__attribute\(\(packed\)\) \
		-D ALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) \
		-fomit-frame-pointer \
		-mthumb-interwork \

								
THUMB_SOURCE= \
		main.c 		\
		init.c		\
#		system/setup_cpu.c \


#ARM_SOURCE= \
#		serial/serialISR.c \
		


THUMB_OBJS = $(THUMB_SOURCE:.c=.o)
ARM_OBJS = $(ARM_SOURCE:.c=.o)

LIBS = -lc -lgcc -lm



all: RTOSDemo.bin sizebefore 

RTOSDemo.bin : RTOSDemo.hex 
	$(OBJCOPY) $(NAMA_FILE).elf -O binary $(NAMA_FILE).bin
	 
RTOSDemo.hex : RTOSDemo.elf
	$(OBJCOPY) $(NAMA_FILE).elf -O ihex $(NAMA_FILE).hex
	$(DISAMB) $(NAMA_FILE).elf -d > $(NAMA_FILE).S

RTOSDemo.elf : $(THUMB_OBJS) $(ARM_OBJS) system/boot.s Makefile 
	$(CC) $(CFLAGS) $(ARM_OBJS) $(THUMB_OBJS) $(LIBS) system/boot.s $(LINKER_FLAGS) 

$(THUMB_OBJS) : %.o : %.c Makefile
	$(CC) -c $(CFLAGS) -mthumb $< -o $@
	
$(ARM_OBJS) : %.o : %.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm $(THUMB_OBJS)
	rm $(NAMA_FILE).elf
	rm $(NAMA_FILE).hex
	rm $(NAMA_FILE).bin
	rm $(NAMA_FILE).S
	rm $(NAMA_FILE).map
#	rm $(ARM_OBJS)
#	touch Makefile
	
tulis :
	$(PENULIS) -hex $(NAMA_FILE).hex /dev/ttyUSB0 115200 14748

tulis1 :
	$(PENULIS) -hex $(NAMA_FILE).hex /dev/ttyUSB1 115200 14748
		
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after:

# Display size of file.
HEXSIZE = $(UKURAN) --target=$(FORMAT) $(NAMA_FILE).hex
ELFSIZE = $(UKURAN) -A $(NAMA_FILE).elf
sizebefore:
	@if [ -f $(NAMA_FILE).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(NAMA_FILE).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi




