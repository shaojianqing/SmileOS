#include "../../const/const.h"
#include "../../type/type.h"
#include "../sheet.h"
#include "../color.h"
#include "../corner.h"
#include "view.h"
#include "../image.h"
#include "../graphics.h"
#include "imageButton.h"

static void setSelect(ImageButton *this, bool isSelect);

static void onMouseDown(View *this, MouseEvent *event);

static void initWithImage(ImageButton *this, Image *image, Color normalColor, Color selectColor);

ImageButton *createImageButton(int x, int y, int w, int h)
{
	ImageButton *imageButton = (ImageButton *)alloc(sizeof(ImageButton));
	imageButton = (ImageButton *)initWithViewFunction((View*)imageButton, x, y, w, h);
	(*imageButton).initWithImage = initWithImage;
	(*imageButton).setSelect = setSelect;
	(*imageButton).view.onMouseDown = onMouseDown;
	
	return imageButton;
}

static void initWithImage(ImageButton *this, Image *image, Color normalColor, Color selectColor)
{
	if (this!=null && image!=null) {
		Image *originImage = (*this).image;
		if (originImage!=null) {
			(*originImage).release(originImage);
		}
		(*image).retain(image);	
		(*this).image = image;
		View *view = (View *)this;
		u32 width = (*view).width;
		u32 height = (*view).height;

		(*this).normalColor.red = normalColor.red;
		(*this).normalColor.green = normalColor.green;
		(*this).normalColor.blue = normalColor.blue;

		(*this).selectColor.red = selectColor.red;
		(*this).selectColor.green = selectColor.green;
		(*this).selectColor.blue = selectColor.blue;

		drawRect((View *)this, 0, 0, width, height, (*this).normalColor);
		drawImage((View *)this, 1, 1, (*this).image);
		refreshViewRect(view, 0, 0, width, height, (*view).z);	
	}
}

static void setSelect(ImageButton *this, bool isSelect)
{
	View *view = (View *)this;
	u32 width = (*view).width;
	u32 height = (*view).height;

	if (isSelect) {
		drawRect((View *)this, 0, 0, width, height, (*this).selectColor);
	} else {
		drawRect((View *)this, 0, 0, width, height, (*this).normalColor);
	}

	drawImage((View *)this, 1, 1, (*this).image);
	refreshViewRect(view, 0, 0, width, height, (*view).z);
}

static void onMouseDown(View *this, MouseEvent *event)
{
	ImageButton *imageButton = (ImageButton *)this;
	if ((*imageButton).onMouseClick!=null) {
		(*imageButton).onMouseClick(imageButton, event);
	}
}

