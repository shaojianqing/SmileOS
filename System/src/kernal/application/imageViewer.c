#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/resource.h"
#include "../gui/sheet.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/image.h"
#include "../gui/view/imageView.h"
#include "../gui/view/imageButton.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "imageViewer.h"

extern Process *imageViewerProcess;

static Sheet *sheet;

static View *mainView;

static ImageView *imageView;

static Factory imageViewerFactory;

static Button *setBackgroundBtn;

static ImageButton *bgSmall1Btn;

static ImageButton *bgSmall2Btn;

static ImageButton *bgSmall3Btn;

static ImageButton *bgSmall4Btn;

static ImageButton *bgSmall5Btn;

static ImageButton *currentImgBtn;

static void initMainView();

static void renderImageView();

static void renderImageListView();

static void imageViewerApplicationMain();

static void prepareWindowSheetImage(Sheet *sheet);

static void onBackgroundBtnClick(Button *this, MouseEvent *event);

static void onImageButtonClick(ImageButton *this, MouseEvent *event);

void startImageViewerApplication()
{
	if (imageViewerProcess==null) {
		imageViewerProcess = requestProcess();
		(*imageViewerProcess).tss.esp = allocPage(64 * 1024) + 64 * 1024;
		(*imageViewerProcess).tss.eip = (int) &imageViewerApplicationMain;
		(*imageViewerProcess).tss.es = 2 * 8;
		(*imageViewerProcess).tss.cs = 1 * 8;
		(*imageViewerProcess).tss.ss = 2 * 8;
		(*imageViewerProcess).tss.ds = 2 * 8;
		(*imageViewerProcess).tss.fs = 2 * 8;
		(*imageViewerProcess).tss.gs = 2 * 8;
		(*imageViewerProcess).tss.cr3 = 0x60000;

		startRunProcess(imageViewerProcess, 4);
	}
}

static void imageViewerOnTimer()
{
	imageViewerFactory.changeButtonStatus(&imageViewerFactory);
}

static void imageViewerApplicationMain()
{
	initFactory(&imageViewerFactory, imageViewerOnTimer);
	
	Sheet *winImageViewer = prepareSheet();
    prepareWindowSheetImage(winImageViewer);
    loadWindowSheet(winImageViewer);
	(*imageViewerProcess).mainWindow = winImageViewer;

	while(TRUE) {
		imageViewerFactory.deselectButton(&imageViewerFactory);
		imageViewerFactory.doProcessEvent(&imageViewerFactory);
	}
}

static void prepareWindowSheetImage(Sheet *sheetPara)
{
    if (sheetPara != null) {
		sheet = sheetPara;

		initMainView();
		renderImageListView();
		renderImageView();
    }
}

static void initMainView()
{
	(*sheet).x = 80;
    (*sheet).y = 70;
    (*sheet).width = 800;
    (*sheet).height = 560;
    (*sheet).buffer = (u8 *)allocPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
	mainView = createView(0, 0, 800, 560);

    Color startColor;
    startColor.red = 20;
    startColor.green = 36;
    startColor.blue = 54;

    Color endColor;
    endColor.red = 32;
    endColor.green = 42;
    endColor.blue = 60;

    Corner corner;
    corner.leftTop=2;
    corner.rightTop=2;
    corner.leftBtm=0;
    corner.rightBtm=0;

    Color mainBgColor;
    mainBgColor.red = 120;
    mainBgColor.green = 120;
    mainBgColor.blue = 120;

	Color mainColor;
    mainColor.red = 20;
    mainColor.green = 36;
    mainColor.blue = 54;

	Color textColor;
    textColor.red = 0xaa;
    textColor.green = 0xbb;
    textColor.blue = 0x66;

	Color shadowColor;
    shadowColor.red = 0xaa;
    shadowColor.green = 0xbb;
    shadowColor.blue = 0x66;

	Color separateColor;
    separateColor.red = 50;
    separateColor.green = 60;
    separateColor.blue = 70;

    drawCornerRect(mainView, 0, 0, (*mainView).width, 40, mainBgColor, corner);
    drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 40, startColor, endColor, corner, DIRECTION_UP);
	drawRect(mainView, 0, 40, (*mainView).width, 530, mainBgColor);
	drawRect(mainView, 1, 40, (*mainView).width-2, 41, separateColor);
    drawRect(mainView, 1, 41, (*mainView).width-2, 518, mainColor);

	printString(mainView, "ImageViewer", 12, 350, 12, textColor, shadowColor);

	Image *backgroundIco = (Image *)loadImageFromStorage(ico_btn_background);
	setBackgroundBtn = createButton(500, 514, 270, 36, &imageViewerFactory, backgroundIco);
	(*setBackgroundBtn).initButton(setBackgroundBtn, "Set As Desktop Background", 26, ButtonStyleBlackBlue);
	(*setBackgroundBtn).onMouseClick = onBackgroundBtnClick;
	(*mainView).addSubView(mainView, (View *)setBackgroundBtn);

	loadContentView(sheet, mainView);
}

static void renderImageListView()
{
	Color borderColor;
    borderColor.red = 80;
    borderColor.green = 100;
    borderColor.blue = 120;

	Image *image = loadImageFromStorage(bg_small_1);
	bgSmall1Btn = createImageButton(18, 58, 122, 92);
	(*bgSmall1Btn).initWithImage(bgSmall1Btn, image, borderColor);
	(*bgSmall1Btn).onMouseClick = onImageButtonClick;
	(*mainView).addSubView(mainView, (View *)bgSmall1Btn);

	image = loadImageFromStorage(bg_small_2);
	bgSmall2Btn = createImageButton(18, 158, 122, 92);
	(*bgSmall2Btn).initWithImage(bgSmall2Btn, image, borderColor);
	(*bgSmall2Btn).onMouseClick = onImageButtonClick;
	(*mainView).addSubView(mainView, (View *)bgSmall2Btn);

	image = loadImageFromStorage(bg_small_3);
	bgSmall3Btn = createImageButton(18, 258, 122, 92);
	(*bgSmall3Btn).initWithImage(bgSmall3Btn, image, borderColor);
	(*bgSmall3Btn).onMouseClick = onImageButtonClick;
	(*mainView).addSubView(mainView, (View *)bgSmall3Btn);

	image = loadImageFromStorage(bg_small_4);
	bgSmall4Btn = createImageButton(18, 358, 122, 92);
	(*bgSmall4Btn).initWithImage(bgSmall4Btn, image, borderColor);
	(*bgSmall4Btn).onMouseClick = onImageButtonClick;
	(*mainView).addSubView(mainView, (View *)bgSmall4Btn);

	image = loadImageFromStorage(bg_small_5);
	bgSmall5Btn = createImageButton(18, 458, 122, 92);
	(*bgSmall5Btn).initWithImage(bgSmall5Btn, image, borderColor);
	(*bgSmall5Btn).onMouseClick = onImageButtonClick;
	(*mainView).addSubView(mainView, (View *)bgSmall5Btn);

	currentImgBtn = bgSmall1Btn;
	(*currentImgBtn).setSelect(currentImgBtn, TRUE);
}

static void renderImageView()
{
	Color borderColor;
    borderColor.red = 80;
    borderColor.green = 100;
    borderColor.blue = 120;	
	
	Image *image = loadImageFromStorage(bg_middle_1);
	imageView = createImageView(168, 58, 602, 452);
	(*imageView).initWithImage(imageView, image, borderColor);
	(*mainView).addSubView(mainView, (View *)imageView);
}

static void onImageButtonClick(ImageButton *this, MouseEvent *event)
{
	if (currentImgBtn!=null) {
		(*currentImgBtn).setSelect(currentImgBtn, FALSE);
	}
	currentImgBtn = this;
	(*currentImgBtn).setSelect(currentImgBtn, TRUE);

	Color borderColor;
	borderColor.red = 80;
	borderColor.green = 100;
	borderColor.blue = 120;

	if (this==bgSmall1Btn) {
		Image *image = loadImageFromStorage(bg_middle_1);
		(*imageView).initWithImage(imageView, image, borderColor);
	} else if (this==bgSmall2Btn) {
		Image *image = loadImageFromStorage(bg_middle_2);
		(*imageView).initWithImage(imageView, image, borderColor);
	} else if (this==bgSmall3Btn) {
		Image *image = loadImageFromStorage(bg_middle_3);
		(*imageView).initWithImage(imageView, image, borderColor);
	} else if (this==bgSmall4Btn) {
		Image *image = loadImageFromStorage(bg_middle_4);
		(*imageView).initWithImage(imageView, image, borderColor);
	} else if (this==bgSmall5Btn) {
		Image *image = loadImageFromStorage(bg_middle_5);
		(*imageView).initWithImage(imageView, image, borderColor);
	}
}

static void onBackgroundBtnClick(Button *this, MouseEvent *event)
{
	u32 bgImageCode = 0;
	if (currentImgBtn==bgSmall1Btn) {
		bgImageCode = bg_1;
	} else if (currentImgBtn==bgSmall2Btn) {
		bgImageCode = bg_2;
	} else if (currentImgBtn==bgSmall3Btn) {
		bgImageCode = bg_3;
	} else if (currentImgBtn==bgSmall4Btn) {
		bgImageCode = bg_4;
	} else if (currentImgBtn==bgSmall5Btn) {
		bgImageCode = bg_5;
	} 

	setBackground(bgImageCode);
}

