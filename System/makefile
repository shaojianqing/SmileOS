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
KERNALSTART = 0x30400
IMAGETOOL = java -jar ImageTool.jar
CREATEIMAGE = createImage
COPYBINARY = copyBinary
CONVERTIMAGE = convertImage
BUILDCHARSET = buildCharSet
TRIMELFHEADER = trimElfHeader
RUN-SYSTEM = VBoxManage startvm System

TGT = tgt/*

EMPTY = Empty.vhd

TARGET = System.vhd

#Booter Target#
BOOT = tgt/boot.bin

#Loader Target#
LOADER = tgt/loader.bin

#Public Object#
PUBLICOBJS = tgt/public.o

#Interrupt Object#
INTERRUPTOBJS = tgt/interrupt.o

#Kernal Target#
KERNAL = tgt/kernal.sys

KERNALBIN = tgt/kernal.bin

KERNALOBJS = tgt/ka.o tgt/kc.o

#Keyboard Target#
KEYBOARD = tgt/keyboard.sys

#Mouse Target#
MOUSE = tgt/mouse.sys

#Gate Test Target#
GATE_TEST = tgt/gate.bin

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
	 rm -f $(BOOT) $(TGT)

#---------------------------------------------------------------#
tgt/boot.bin : src/boot/boot.asm
	$(ASM) $< -o $@

#---------------------------------------------------------------#
tgt/loader.bin : src/boot/loader.asm src/boot/structure.inc
	$(ASM) $< -o $@

tgt/public.o : src/kernal/public/public.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/interrupt.o : src/kernal/include/interrupt.asm
	$(ASM) $(ELFFLAGES) $< -o $@

#---------------------------------------------------------------#
tgt/ka.o : src/kernal/kernal.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernal/kernal.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernal.bin : $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS)
	$(LD) $(LDFLAGES) $(KERNALSTART) $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) -o $@

tgt/kernal.sys : $(KERNALBIN)
	$(IMAGETOOL) $(TRIMELFHEADER) $< $@

#---------------------------------------------------------------#
tgt/charset.bin : res/charset/charset.csr
	$(IMAGETOOL) $(BUILDCHARSET) $< $@

tgt/gate.bin : src/kernal/gate/gate.asm
	$(ASM) $< -o $@

#---------------------------------------------------------------#
tgt/keyboard.sys : src/kernal/keyboard/keyboard.asm
	$(ASM) $< -o $@

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
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernal.sys tgt/keyboard.sys tgt/mouse.sys tgt/bg1.image tgt/bg2.image tgt/bg3.image tgt/bg4.image tgt/app1.image tgt/app2.image tgt/app3.image tgt/app4.image tgt/charset.bin tgt/gate.bin
	$(CP) $(EMPTY) $@
	$(IMAGETOOL) $(COPYBINARY) $@ $(BOOT) 0
	$(IMAGETOOL) $(COPYBINARY) $@ $(LOADER) 512
	$(IMAGETOOL) $(COPYBINARY) $@ $(CHARSET) 4096
	$(IMAGETOOL) $(COPYBINARY) $@ $(KEYBOARD) 8192
	$(IMAGETOOL) $(COPYBINARY) $@ $(MOUSE) 9216
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
	
