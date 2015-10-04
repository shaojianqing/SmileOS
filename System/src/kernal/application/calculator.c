#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/coorPanel.h"
#include "../system/descriptor.h"
#include "../execute/execute.h"
#include "../process/process.h"
#include "calculator.h"

extern Process *calculatorProcess;

Factory calculatorFactory;

Button *num1Btn;

Button *num2Btn;

Button *num3Btn;

Button *num4Btn;

Button *num5Btn;

Button *num6Btn;

Button *num7Btn;

Button *num8Btn;

Button *num9Btn;

Button *num0Btn;

Button *num00Btn;

Button *clearBtn;

Button *backBtn;

Button *allClearBtn;

Button *plusBtn;

Button *minusBtn;

Button *multiplyBtn;

Button *divisionBtn;

Button *equalityBtn;

int sign = 0;

void numBtnClick(Button *this, MouseEvent *event);

void operBtnClick(Button *button, MouseEvent *event);

void prepareProcessLdt(Process *process);

void calculatorApplicationMain();

void prepareWindowSheetCal(Sheet *sheet);

void calculatorOnTimer()
{
	calculatorFactory.changeButtonStatus(&calculatorFactory);
}

void startCalculatorApplication()
{
	if (calculatorProcess==null) {
		calculatorProcess = requestProcess();
		prepareProcessLdt(calculatorProcess);
		(*calculatorProcess).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
		(*calculatorProcess).tss.eip = (int) &calculatorApplicationMain;		
		(*calculatorProcess).tss.cs = 0 * 8 + 4;		
		(*calculatorProcess).tss.ds = 1 * 8 + 4;
		(*calculatorProcess).tss.es = 1 * 8 + 4;
		(*calculatorProcess).tss.fs = 1 * 8 + 4;
		(*calculatorProcess).tss.gs = 1 * 8 + 4;
		(*calculatorProcess).tss.ss = 2 * 8 + 4;
		(*calculatorProcess).tss.cr3 = 0x60000;
				
		startRunProcess(calculatorProcess, 4);
	}
}

void prepareProcessLdt(Process *process)
{
	if (process != null) {
		setLocalDescriptor((int)&(*process).ldt, 0, 0xFFFFF, 0x00000000, DA_C|DA_32_4K);
		setLocalDescriptor((int)&(*process).ldt, 1, 0xFFFFF, 0x00000000, DA_DRW|DA_32_4K);
		setLocalDescriptor((int)&(*process).ldt, 2, 0xFFFFF, 0x00000000, DA_DRWA|DA_32_4K);
	}
}

void calculatorApplicationMain()
{
	initFactory(&calculatorFactory, calculatorOnTimer);
	
	Sheet *winCalculator = prepareSheet();
    prepareWindowSheetCal(winCalculator);
    loadWindowSheet(winCalculator);
	(*calculatorProcess).mainWindow = winCalculator;

	while (TRUE) {
		calculatorFactory.deselectButton(&calculatorFactory);
		calculatorFactory.doProcessEvent(&calculatorFactory);
	}
}

void prepareWindowSheetCal(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 560;
        (*sheet).y = 80;
        (*sheet).width = 400;
        (*sheet).height = 500;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0,400, 500);

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

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
        mainColor.red = 210;
        mainColor.green = 210;
        mainColor.blue = 210;

		Color textColor;
        textColor.red = 0x55;
        textColor.green = 0x55;
        textColor.blue = 0x55;

        drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 0, 21, (*mainView).width, 480, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 478, mainColor);

		Corner inputBgCorner;
        inputBgCorner.leftTop=2;
        inputBgCorner.rightTop=2;
        inputBgCorner.leftBtm=3;
        inputBgCorner.rightBtm=3;

		Color inputBgColor;
        inputBgColor.red = 0x55;
        inputBgColor.green = 0x88;
        inputBgColor.blue = 0xaa;

		Corner inputCorner;
        inputCorner.leftTop=2;
        inputCorner.rightTop=2;
        inputCorner.leftBtm=3;
        inputCorner.rightBtm=3;

		Color inputColor;
        inputColor.red = 0xee;
        inputColor.green = 0xee;
        inputColor.blue = 0xee;

		drawCornerRect(mainView, 10, 30, (*mainView).width-20, 80, inputBgColor, inputBgCorner);
		drawCornerRect(mainView, 12, 32, (*mainView).width-24, 76, inputColor, inputCorner);

		printString(mainView, "Calculator-LDT", 14, 160, 4, textColor);

		clearBtn = createButton(10, 150, 80, 60, &calculatorFactory);
		(*clearBtn).initButton(clearBtn, "C", 1, ButtonStyleDarkOrange);
		(*clearBtn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)clearBtn);

		allClearBtn = createButton(110, 150, 80, 60, &calculatorFactory);
		(*allClearBtn).initButton(allClearBtn, "AC", 2, ButtonStyleDarkOrange);
		(*allClearBtn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)allClearBtn);

		backBtn = createButton(210, 150, 80, 60, &calculatorFactory);
		(*backBtn).initButton(backBtn, "<", 1, ButtonStyleDarkOrange);
		(*backBtn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)backBtn);

		num1Btn = createButton(10, 220, 80, 60, &calculatorFactory);
		(*num1Btn).initButton(num1Btn, "1", 1, ButtonStyleLightGray);
		(*num1Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num1Btn);

		num2Btn = createButton(110, 220, 80, 60, &calculatorFactory);
		(*num2Btn).initButton(num2Btn, "2", 1, ButtonStyleLightGray);
		(*num2Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num2Btn);

		num3Btn = createButton(210, 220, 80, 60, &calculatorFactory);
		(*num3Btn).initButton(num3Btn, "3", 1, ButtonStyleLightGray);
		(*num3Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num3Btn);

		num4Btn = createButton(10, 290, 80, 60, &calculatorFactory);
		(*num4Btn).initButton(num4Btn, "4", 1, ButtonStyleLightGray);
		(*num4Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num4Btn);

		num5Btn = createButton(110, 290, 80, 60, &calculatorFactory);
		(*num5Btn).initButton(num5Btn, "5", 1, ButtonStyleLightGray);
		(*num5Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num5Btn);

		num6Btn = createButton(210, 290, 80, 60, &calculatorFactory);
		(*num6Btn).initButton(num6Btn, "6", 1, ButtonStyleLightGray);
		(*num6Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num6Btn);

		num7Btn = createButton(10, 360, 80, 60, &calculatorFactory);
		(*num7Btn).initButton(num7Btn, "7", 1, ButtonStyleLightGray);
		(*num7Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num7Btn);

		num8Btn = createButton(110, 360, 80, 60, &calculatorFactory);
		(*num8Btn).initButton(num8Btn, "8", 1, ButtonStyleLightGray);
		(*num8Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num8Btn);

		num9Btn = createButton(210, 360, 80, 60, &calculatorFactory);
		(*num9Btn).initButton(num9Btn, "9", 1, ButtonStyleLightGray);
		(*num9Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num9Btn);

		num0Btn = createButton(10, 430, 80, 60, &calculatorFactory);
		(*num0Btn).initButton(num0Btn, "0", 1, ButtonStyleLightGray);
		(*num0Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num0Btn);

		num00Btn = createButton(110, 430, 180, 60, &calculatorFactory);
		(*num00Btn).initButton(num00Btn, "00", 2, ButtonStyleLightGray);
		(*num00Btn).onMouseClick = numBtnClick;
		(*mainView).addSubView(mainView, (View *)num00Btn);

		plusBtn = createButton(310, 150, 80, 60, &calculatorFactory);
		(*plusBtn).initButton(plusBtn, "+", 1, ButtonStyleDarkBlue);
		(*plusBtn).onMouseClick = operBtnClick;
		(*mainView).addSubView(mainView, (View *)plusBtn);

		minusBtn = createButton(310, 220, 80, 60, &calculatorFactory);
		(*minusBtn).initButton(minusBtn, "-", 1, ButtonStyleDarkBlue);
		(*minusBtn).onMouseClick = operBtnClick;
		(*mainView).addSubView(mainView, (View *)minusBtn);

		multiplyBtn = createButton(310, 290, 80, 60, &calculatorFactory);
		(*multiplyBtn).initButton(multiplyBtn, "*", 1, ButtonStyleDarkBlue);
		(*multiplyBtn).onMouseClick = operBtnClick;
		(*mainView).addSubView(mainView, (View *)multiplyBtn);

		divisionBtn = createButton(310, 360, 80, 60, &calculatorFactory);
		(*divisionBtn).initButton(divisionBtn, "/", 1, ButtonStyleDarkBlue);
		(*divisionBtn).onMouseClick = operBtnClick;
		(*mainView).addSubView(mainView, (View *)divisionBtn);

		equalityBtn = createButton(310, 430, 80, 60, &calculatorFactory);
		(*equalityBtn).initButton(equalityBtn, "=", 1, ButtonStyleDarkRed);
		(*equalityBtn).onMouseClick = operBtnClick;
		(*mainView).addSubView(mainView, (View *)equalityBtn);
		
		loadContentView(sheet, mainView);	
    }
}

void numBtnClick(Button *button, MouseEvent *event)
{
	if (button==num1Btn) {
		int a=-100;
		int b=a+133;

		showIntegerValue(b, 100, 50);
	} else if (button==num2Btn) {
		showIntegerValue(2, 100, 50);
	} else if (button==num3Btn) {
		showIntegerValue(3, 100, 50);
	}
}

void operBtnClick(Button *button, MouseEvent *event)
{
	if (button==equalityBtn) {
		showIntegerValue(sign, 100, 50);
		sign++;
	}	
}



