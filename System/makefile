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
APPLICATIONSTART = 0x0000
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

APPLICATION = tgt/application.o

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

EXECUTE = tgt/execute.o

FACTORY = tgt/factory.o

VIEW = tgt/view.o

TEST = tgt/test.o

IMAGEVIEW = tgt/imageView.o

STARTBUTTON = tgt/startButton.o

IMAGEBUTTON = tgt/imageButton.o

COORPANEL = tgt/coorPanel.o

GRIDPANEL = tgt/gridPanel.o

GRAPHPANEL = tgt/graphPanel.o

GRIDDATAITEM = tgt/gridDataItem.o

BUTTON = tgt/button.o

STYLE = tgt/style.o

#Background Resource#
BGS1 = tgt/bg1.image

BGS2 = tgt/bg2.image

BGS3 = tgt/bg3.image

BGS4 = tgt/bg4.image

BGS5 = tgt/bg5.image

#Background Resource#
BGSMALL1 = tgt/bg_small_1.image

BGSMALL2 = tgt/bg_small_2.image

BGSMALL3 = tgt/bg_small_3.image

BGSMALL4 = tgt/bg_small_4.image

BGSMALL5 = tgt/bg_small_5.image

BGMIDDLE1 = tgt/bg_middle_1.image

BGMIDDLE2 = tgt/bg_middle_2.image

BGMIDDLE3 = tgt/bg_middle_3.image

BGMIDDLE4 = tgt/bg_middle_4.image

BGMIDDLE5 = tgt/bg_middle_5.image

#Image Resource#
APP1 = tgt/ico_app_sys.image

APP2 = tgt/ico_app_cmd.image

APP3 = tgt/ico_app_img.image

APP4 = tgt/ico_app_cal.image

APP5 = tgt/ico_app_grh.image

APP6 = tgt/ico_app_mat.image

#Icon Resource#
ICO_BTN_BAR_GRAPH = tgt/ico_btn_bar_graph.image

ICO_BTN_LINE_GRAPH = tgt/ico_btn_line_graph.image

ICO_BTN_HYBD_GRAPH = tgt/ico_btn_hybd_graph.image

ICO_BTN_FIN_GRAPH = tgt/ico_btn_fin_graph.image

ICO_BTN_LINE_MATH = tgt/ico_btn_line_math.image

ICO_BTN_QUAD_MATH = tgt/ico_btn_quadratic_math.image

ICO_BTN_CIRC_MATH = tgt/ico_btn_circle_math.image

ICO_BTN_ELLI_MATH = tgt/ico_btn_ellipse_math.image

ICO_BTN_PRO_SYS = tgt/ico_btn_sys_process.image

ICO_BTN_MEM_SYS = tgt/ico_btn_sys_memory.image

ICO_BTN_BGD = tgt/ico_btn_background.image

ICO_SYS_NETWORK = tgt/ico_sys_network.image

ICO_SYS_POWER = tgt/ico_sys_power.image

ICO_SYS_LOGO = tgt/ico_sys_logo.image

ICO_BTN_CLS = tgt/ico_btn_close.image

ICO_BTN_MIN = tgt/ico_btn_miniz.image

#Application Resource#
COMMAND = tgt/command.o

SYSINFO = tgt/sysInfo.o

CALCU = tgt/calculator.o

MATHE = tgt/mathematics.o

GRAPH = tgt/dataGraph.o

IMAGEVIEWER = tgt/imageViewer.o

DATA_SETTING = tgt/dataSetting.o

#ElfApp Resource#
RUNNABLE = tgt/runnable.o

SYSTEMAPI = tgt/systemApi.o

BROWSEROBJ = tgt/browser.o

BROWSER = tgt/browser.elf

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

tgt/application.o : src/kernal/execute/application.c
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

tgt/imageView.o : src/kernal/gui/view/imageView.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/startButton.o : src/kernal/gui/view/startButton.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/imageButton.o : src/kernal/gui/view/imageButton.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/coorPanel.o : src/kernal/gui/view/coorPanel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/gridPanel.o : src/kernal/gui/view/gridPanel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/graphPanel.o : src/kernal/gui/view/graphPanel.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/button.o : src/kernal/gui/view/button.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/gridDataItem.o : src/kernal/gui/view/item/gridDataItem.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/style.o : src/kernal/gui/view/style.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/factory.o : src/kernal/gui/factory/factory.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/execute.o : src/kernal/execute/execute.c
	$(CC) $(CCFLAGES) $< -o $@
#---------------------------------------------------------------#
tgt/ka.o : src/kernal/kernal.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/kc.o : src/kernal/kernal.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/kernal.bin : $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) $(PERIPHERAL) $(ALGORITHM) $(CHARAPI) $(GRAPHICS) $(HARDDISK) $(DESCRIPTOR) $(INTERFACE) $(MEMORY) $(TIMING) $(PROCESS) $(KEYBOARD) $(MOUSE) $(VIDEO) $(SHEET) $(IMAGE) $(VIEW) $(DESKTOP) $(WINDOW) $(COMMAND) $(SYSINFO) $(MATHE) $(CALCU) $(GRAPH)  $(DATA_SETTING) $(IMAGEVIEWER) $(STARTBUTTON) $(IMAGEBUTTON) $(IMAGEVIEW) $(COORPANEL) $(GRIDPANEL) $(GRAPHPANEL) $(STYLE) $(BUTTON) $(GRIDDATAITEM) $(TEST) $(FACTORY) $(EXECUTE) $(APPLICATION)
	$(LD) $(LDFLAGES) $(KERNALSTART) $(KERNALOBJS) $(PUBLICOBJS) $(INTERRUPTOBJS) $(PERIPHERAL) $(ALGORITHM) $(GRAPHICS) $(HARDDISK) $(CHARAPI) $(DESCRIPTOR) $(INTERFACE) $(MEMORY) $(TIMING) $(PROCESS) $(KEYBOARD) $(MOUSE) $(VIDEO) $(SHEET) $(IMAGE) $(VIEW) $(DESKTOP) $(WINDOW) $(COMMAND) $(SYSINFO) $(MATHE) $(CALCU) $(GRAPH) $(DATA_SETTING) $(IMAGEVIEWER) $(STARTBUTTON) $(IMAGEBUTTON) $(IMAGEVIEW) $(COORPANEL) $(GRIDPANEL) $(GRAPHPANEL) $(STYLE) $(BUTTON) $(GRIDDATAITEM) $(TEST) $(FACTORY) $(EXECUTE) $(APPLICATION) -o $@

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

tgt/dataSetting.o : src/kernal/application/dataSetting.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/imageViewer.o : src/kernal/application/imageViewer.c
	$(CC) $(CCFLAGES) $< -o $@
#---------------------------------------------------------------#
tgt/systemApi.o :src/kernal/execute/systemApi.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/runnable.o :src/kernal/execute/runnable.asm
	$(ASM) $(ELFFLAGES) $< -o $@

tgt/browser.o : src/kernal/application/browser.c
	$(CC) $(CCFLAGES) $< -o $@

tgt/browser.elf : tgt/runnable.o tgt/browser.o tgt/systemApi.o
	$(LD) $(LDFLAGES) $(APPLICATIONSTART) $(RUNNABLE) $(SYSTEMAPI) $(BROWSEROBJ) -o $@
#---------------------------------------------------------------#
tgt/bg1.image : res/background/bg1.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg2.image : res/background/bg2.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg3.image : res/background/bg3.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg4.image : res/background/bg4.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg5.image : res/background/bg5.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 1024 768 true

tgt/bg_small_1.image : res/background/bg_small_1.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 120 90 true

tgt/bg_small_2.image : res/background/bg_small_2.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 120 90 true

tgt/bg_small_3.image : res/background/bg_small_3.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 120 90 true

tgt/bg_small_4.image : res/background/bg_small_4.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 120 90 true

tgt/bg_small_5.image : res/background/bg_small_5.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 120 90 true

tgt/bg_middle_1.image : res/background/bg_middle_1.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 600 450 true

tgt/bg_middle_2.image : res/background/bg_middle_2.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 600 450 true

tgt/bg_middle_3.image : res/background/bg_middle_3.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 600 450 true

tgt/bg_middle_4.image : res/background/bg_middle_4.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 600 450 true

tgt/bg_middle_5.image : res/background/bg_middle_5.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 600 450 true

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

tgt/ico_app_mat.image : res/images/ico_app_mat.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 80 80 false

#---------------------------------------------------------------#
tgt/ico_btn_bar_graph.image : res/images/ico_btn_bar_graph.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_line_graph.image : res/images/ico_btn_line_graph.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_hybd_graph.image : res/images/ico_btn_hybd_graph.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_fin_graph.image : res/images/ico_btn_fin_graph.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_line_math.image : res/images/ico_btn_line_math.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_quadratic_math.image : res/images/ico_btn_quadratic_math.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_circle_math.image : res/images/ico_btn_circle_math.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_ellipse_math.image : res/images/ico_btn_ellipse_math.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_sys_process.image : res/images/ico_btn_sys_process.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_sys_memory.image : res/images/ico_btn_sys_memory.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_btn_background.image : res/images/ico_btn_background.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 24 24 false

tgt/ico_sys_network.image : res/images/ico_sys_network.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 32 24 false

tgt/ico_sys_power.image : res/images/ico_sys_power.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 60 24 false

tgt/ico_sys_logo.image : res/images/ico_sys_logo.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 100 24 false

tgt/ico_btn_close.image : res/images/ico_btn_close.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 20 20 false

tgt/ico_btn_miniz.image : res/images/ico_btn_miniz.bmp
	$(IMAGETOOL) $(CONVERTIMAGE) $< $@ 20 20 false

#---------------------------------------------------------------#
System.vhd : tgt/boot.bin tgt/loader.bin tgt/kernal.sys tgt/browser.elf tgt/bg1.image tgt/bg2.image tgt/bg3.image tgt/bg4.image tgt/bg5.image tgt/bg_small_1.image tgt/bg_small_2.image tgt/bg_small_3.image tgt/bg_small_4.image tgt/bg_small_5.image tgt/bg_middle_1.image tgt/bg_middle_2.image tgt/bg_middle_3.image tgt/bg_middle_4.image tgt/bg_middle_5.image tgt/ico_app_sys.image tgt/ico_app_cmd.image tgt/ico_app_img.image tgt/ico_app_cal.image tgt/ico_app_grh.image tgt/ico_app_mat.image tgt/ico_btn_bar_graph.image tgt/ico_btn_line_graph.image tgt/ico_btn_hybd_graph.image tgt/ico_btn_fin_graph.image tgt/ico_btn_line_math.image tgt/ico_btn_quadratic_math.image tgt/ico_btn_circle_math.image tgt/ico_btn_ellipse_math.image tgt/ico_btn_sys_process.image tgt/ico_btn_sys_memory.image tgt/ico_btn_background.image tgt/ico_sys_logo.image tgt/ico_sys_power.image tgt/ico_sys_network.image tgt/ico_btn_close.image tgt/ico_btn_miniz.image tgt/charset.bin  
	$(CP) $(EMPTY) $@
	$(IMAGETOOL) $(COPYBINARY) $@ $(BOOT) 0
	$(IMAGETOOL) $(COPYBINARY) $@ $(LOADER) 512
	$(IMAGETOOL) $(COPYBINARY) $@ $(CHARSET) 4096
	$(IMAGETOOL) $(COPYBINARY) $@ $(KERNAL) 36864
	$(IMAGETOOL) $(COPYBINARY) $@ $(BROWSER) 2097152   #0x1000
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_BAR_GRAPH) 4194304  #0x2000
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_PRO_SYS) 4196352  #0x2004
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_BGD) 4198400  #0x2008
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_CLS) 4201472  #0x200e
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_MIN) 4204544  #0x2014
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_LINE_GRAPH) 4207616  #0x201a
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_HYBD_GRAPH) 4210688 #0x2020
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_FIN_GRAPH) 4213760  #0x2026
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_FIN_GRAPH) 4213760  #0x2026
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_LINE_MATH) 4216832  #0x202c
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_QUAD_MATH) 4219904  #0x2032
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_CIRC_MATH) 4222976  #0x2038
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_ELLI_MATH) 4226048  #0x203E
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_BTN_MEM_SYS) 4229120  	#0x2044
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_SYS_LOGO) 4232192  	#0x204a
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_SYS_POWER) 4240384  #0x205a
	$(IMAGETOOL) $(COPYBINARY) $@ $(ICO_SYS_NETWORK) 4245504  #0x2064
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS1) 8388608   #0x4000
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS2) 10748928  #0x5202	
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS3) 13109248  #0x6404	
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS4) 15469568  #0x7606
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGS5) 17829888  #0x8808
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP1) 20190208  #0x9a0a
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP2) 20209664  #0x9a30
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP3) 20229120  #0x9a56
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP4) 20248576  #0x9a7c
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP5) 20268032  #0x9aa2
	$(IMAGETOOL) $(COPYBINARY) $@ $(APP6) 20287488  #0x9ac8
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGSMALL1) 20971520  #0xa000
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGSMALL2) 21135360  #0xa140
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGSMALL3) 21299200  #0xa280
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGSMALL4) 21463040  #0xa3c0
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGSMALL5) 21626880  #0xa500
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGMIDDLE1) 23068672  #0xb000
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGMIDDLE2) 23879680  #0xb630
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGMIDDLE3) 24690688  #0xbc60
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGMIDDLE4) 25501696  #0xc290
	$(IMAGETOOL) $(COPYBINARY) $@ $(BGMIDDLE5) 26312704  #0xc8c0

	$(RUN-SYSTEM)
	
