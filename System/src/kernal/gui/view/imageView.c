#include "../../const/const.h"
#include "../../type/type.h"
#include "../sheet.h"
#include "../color.h"
#include "../corner.h"
#include "view.h"
#include "../image.h"
#include "../graphics.h"
#include "imageView.h"

static void initWithImage(ImageView *this, Image *image, Color borderColor);

ImageView *createImageView(int x, int y, int w, int h)
{
	ImageView *imageView = (ImageView *)alloc(sizeof(ImageView));
	imageView = (ImageView *)initWithViewFunction((View *)imageView, x, y, w, h);
	(*imageView).initWithImage = initWithImage;
	
	return imageView;
}

static void initWithImage(ImageView *this, Image *image, Color borderColor)
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
		
		drawRect(view, 0, 0, width, height, borderColor);
		drawImage(view, 1, 1, (*this).image);
		refreshViewRect(view, 0, 0, width, height, (*view).z);	
	}
}
