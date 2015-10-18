################################
# Makefile for Shaojianqing OS #
################################

CP = cp
LD = ld
CC = gcc
ASM = nasm
ELFFLAGES = -f elf 
CCFLAGES = -c -m32
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

INTERFACE = tgt/interface.o

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

FACTORY = tgt/factory.o

VIEW = tgt/view.o

TEST = tgt/test.o

STARTBUTTON = tgt/startButton.o

COORPANEL = tgt/coorPanel.o

GRAPHPANEL = tgt/graphPanel.o

BUTTON = tgt/button.o

STYLE = tgt/style.o

#Background Resource#
BGS1 = tgt/bg1.image

BGS2 = tgt/bg2.image

BGS3 = tgt/bg3.image

BGS4 = tgt/bg4.image

#Image Resourcee#
APP1 = tgt/ico_app_sys.image

APP2 = tgt/ico_app_cmd.image

APP3 = tgt/ico_app_img.image

APP4 = tgt/ico_app_cal.image

APP5 = tgt/ico_app_grh.image

#Application Resourcee#
COMMAND = tgt/command.o

SYSINFO = tgt/sysInfo.o

CALCU = tgt/calculator.o

MATHE = tgt/mathematics.o

GRAPH = tgt/dataGraph.o

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

tgt/interface.o : src/kernal/interface/interface.c
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

#---------------------------------------------------------------#
tgt/view.o : src/kernal/gui/view/view.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/test.o : src/kernal/gui/test.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/startButton.o : src/kernal/gui/view/startButton.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/coorPanel.o : src/kernal/gui/view/coorPanel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/graphPanel.o : src/kernal/gui/view/graphPanel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/button.o : src/kernal/gui/view/button.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/style.o : src/kernal/gui/view/style.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/factory.o : src/kernal/gui/factory/factory.c
	$(CC) $(CCFLAGES) $< -o $@
#---------------------------------------------------------------#
tgt/ka.o : src/kernal/kernal.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernal/kernal.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernal.bin : $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) $(PERIPHERAL) $(ALGORITHM) $(CHARAPI) $(GRAPHICS) $(HARDDISK) $(DESCRIPTOR) $(INTERFACE) $(MEMORY) $(TIMING) $(PROCESS) $(KEYBOARD) $(MOUSE) $(VIDEO) $(SHEET) $(IMAGE) $(VIEW) $(DESKTOP) $(WINDOW) $(COMMAND) $(SYSINFO) $(MATHE) $(CALCU) $(GRAPH) $(STARTBUTTON) $(COORPANEL) $(GRAPHPANEL) $(STYLE) $(BUTTON)  $(TEST) $(FACTORY)
	$(LD) $(LDFLAGES) $(KERNALSTART) $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) $(PERIPHERAL) $(ALGORITHM) $(GRAPHICS) $(HARDDISK) $(CHARAPI) $(DESCRIPTOR) $(INTERFACE) $(MEMORY) $(TIMING) $(PROCESS) $(KEYBOARD) $(MOUSE) $(VIDEO) $(SHEET) $(IMAGE) $(VIEW) $(DESKTOP) $(WINDOW) $(COMMAND) $(SYSINFO) $(MATHE) $(CALCU) $(GRAPH) $(STARTBUTTON) $(COORPANEL) $(GRAPHPANEL) $(STYLE) $(BUTTON) $(TEST) $(FACTORY) -o $@

tgt/kernal.sys : $(KERNALBIN)
	$(TRIMELFHEADER) $< $@

#---------------------------------------------------------------#
tgt/charset.bin : res/charset/charset.csr
	$(IMAGETOOL) $(BUILDCHARSET) $< $@

#---------------------------------------------------------------#
tgt/mouse.sys : src/kernal/mouse/mouse.asm
	$(ASM) $< -o $@

#---------------------------------------------------------------#
tgt/command.o : src/kernal/application/command.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/sysInfo.o : src/kernal/application/systemInfo.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/mathematics.o : src/kernal/application/mathematics.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/calculator.o : src/kernal/application/calculator.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/dataGraph.o : src/kernal/application/dataGraph.c
	$(CC) $(CCFLAGES) $< -o $@
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
tgt/ico_app_sys.image : res/images/ico_app_sys.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/ico_app_cmd.image : res/images/ico_app_cmd.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/ico_app_img.image : res/images/ico_app_img.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/ico_app_cal.image : res/images/ico_app_cal.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

tgt/ico_app_grh.image : res/images/ico_app_grh.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

#---------------------------------------------------------------#
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernal.sys tgt/bg1.image tgt/bg2.image tgt/bg3.image tgt/bg4.image tgt/ico_app_sys.image tgt/ico_app_cmd.image tgt/ico_app_img.image tgt/ico_app_cal.image tgt/ico_app_grh.image tgt/charset.bin	
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
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP5) 17907712  #0x88a0
	$(RUN-SYSTEM)
	
