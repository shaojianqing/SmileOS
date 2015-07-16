################################
# Makefile for Shaojianqing OS #
################################

CC = gcc
CP = cp
ASM = nasm
ELFFLAGES = -f elf 
CCFLAGES = -c -m32
LD = ld
LDFLAGES = -m elf_i386 -s -Ttext
KERNALSTART = 0x80000
IMAGETOOL = java -jar ImageTool.jar
CREATEIMAGE = createImage
COPYBINARY = copyBinary
CONVERTIMAGE = convertImage
BUILDCHARSET = buildCharSet
TRIMELFHEADER = objcopy -O binary
FILLBYTECONTENT = fillByteContent
CONVERT-VHD-FMT = VBoxManage clonehd
VDI-FORMAT = --format vdi
RUN-SYSTEM = VBoxManage startvm System

TGT = tgt/*

EMPTY = Empty.vhd

TARGET = System.vhd

VHARDDISK = System.vdi

#Booter Target#
BOOT = tgt/boot.bin

#Loader Target#
LOADER = tgt/loader.bin

#Public Object#
PUBLICOBJS = tgt/public.o

#Interrupt Object#
INTERRUPTOBJS = tgt/interrupta.o tgt/interruptc.o 

#Kernal Target#
KERNAL = tgt/kernal.sys

KERNALBIN = tgt/kernal.bin

KERNALOBJS = tgt/ka.o tgt/kc.o

#Module Target#
PERIPHERAL = tgt/peripheral.o

ALGORITHM = tgt/algorithm.o

CHARAPI = tgt/charset.o

DESCRIPTOR = tgt/descriptor.o

KEYBOARD = tgt/keyboard.o

MEMORY = tgt/memory.o

GRAPHICS = tgt/graphics.o

HARDDISK = tgt/harddisk.o

PROCESS = tgt/process.o

TIMING = tgt/timing.o

DESKTOP = tgt/desktop.o

WINDOW = tgt/window.o

SHEET = tgt/sheet.o

IMAGE = tgt/image.o

VIDEO = tgt/video.o

MOUSE = tgt/mouse.o

BACK = tgt/back.o

#Background Resource#
BGS1 = tgt/bg1.image

BGS2 = tgt/bg2.image

BGS3 = tgt/bg3.image

BGS4 = tgt/bg4.image

#Image Resourcee#
APP1 = tgt/app1.image

APP2 = tgt/app2.image

APP3 = tgt/app3.image

APP4 = tgt/app4.image

#Charset Resource#
CHARSET = tgt/charset.bin

.PHONY : build clean

build : clean $(TARGET)

clean :
	 rm -f $(TARGET) $(TGT)

rmfiles :
	 rm -f $(TGT)

#---------------------------------------------------------------#
tgt/boot.bin : src/boot/boot.asm
	$(ASM) $< -o $@

#---------------------------------------------------------------#
tgt/loader.bin : src/boot/loader.asm src/boot/structure.inc
	$(ASM) $< -o $@

tgt/public.o : src/kernal/public/public.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/interrupta.o : src/kernal/system/interrupt.asm
	$(ASM) $(ELFFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/peripheral.o : src/kernal/include/peripheral.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/algorithm.o : src/kernal/algorithm/algorithm.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/charset.o : src/kernal/gui/charset.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/descriptor.o : src/kernal/system/descriptor.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/interruptc.o : src/kernal/system/interrupt.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/process.o : src/kernal/process/process.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/desktop.o : src/kernal/gui/desktop.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/memory.o : src/kernal/memory/memory.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/graphics.o : src/kernal/gui/graphics.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/harddisk.o : src/kernal/include/harddisk.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/timing.o : src/kernal/include/timing.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/sheet.o : src/kernal/gui/sheet.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/window.o : src/kernal/gui/window.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/image.o : src/kernal/gui/image.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/video.o : src/kernal/gui/video.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/keyboard.o : src/kernal/include/keyboard.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/mouse.o : src/kernal/include/mouse.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/back.o : src/kernal/gui/back.c
	$(CC) $(CCFLAGES) $< -o $@
#---------------------------------------------------------------#
tgt/ka.o : src/kernal/kernal.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernal/kernal.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernal.bin : $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) $(PERIPHERAL) $(ALGORITHM) $(CHARAPI) $(GRAPHICS) $(HARDDISK) $(DESCRIPTOR) $(MEMORY) $(TIMING) $(PROCESS) $(KEYBOARD) $(MOUSE) $(VIDEO) $(SHEET) $(IMAGE) $(BACK) $(DESKTOP) $(WINDOW)
	$(LD) $(LDFLAGES) $(KERNALSTART) $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) $(PERIPHERAL) $(ALGORITHM) $(GRAPHICS) $(HARDDISK) $(CHARAPI) $(DESCRIPTOR) $(MEMORY) $(TIMING) $(PROCESS) $(KEYBOARD) $(MOUSE) $(VIDEO) $(SHEET) $(IMAGE) $(BACK) $(DESKTOP) $(WINDOW) -o $@

tgt/kernal.sys : $(KERNALBIN)
	$(TRIMELFHEADER) $< $@

#---------------------------------------------------------------#
tgt/charset.bin : res/charset/charset.csr
	$(IMAGETOOL) $(BUILDCHARSET) $< $@

#---------------------------------------------------------------#
tgt/mouse.sys : src/kernal/mouse/mouse.asm
	$(ASM) $< -o $@

#---------------------------------------------------------------#
tgt/bg1.image : res/background/bg1.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg2.image : res/background/bg2.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg3.image : res/background/bg3.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg4.image : res/background/bg4.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

#---------------------------------------------------------------#
tgt/app1.image : res/images/app1.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/app2.image : res/images/app2.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/app3.image : res/images/app3.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/app4.image : res/images/app4.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

#---------------------------------------------------------------#
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernal.sys tgt/bg1.image tgt/bg2.image tgt/bg3.image tgt/bg4.image tgt/app1.image tgt/app2.image tgt/app3.image tgt/app4.image tgt/charset.bin	
	$(CP) $(EMPTY) $@
	$(IMAGETOOL) $(COPYBINARY) $@ $(BOOT) 0
	$(IMAGETOOL) $(COPYBINARY) $@ $(LOADER) 512
	$(IMAGETOOL) $(COPYBINARY) $@ $(CHARSET) 4096
	$(IMAGETOOL) $(COPYBINARY) $@ $(KERNAL) 32768
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS1) 8388608   #0x4000
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS2) 10748928  #0x5202	
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS3) 13109248  #0x6404	
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS4) 15469568  #0x7606
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP1) 17829888  #0x8808
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP2) 17849344  #0x882e
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP3) 17868800  #0x8854
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP4) 17888256  #0x887a
	$(RUN-SYSTEM)
	
