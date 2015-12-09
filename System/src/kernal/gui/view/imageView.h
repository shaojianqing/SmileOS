
typedef struct ImageView ImageView;

typedef struct ImageView
{
    View view;

	Image *image;

	void (*initWithImage)(ImageView *this, Image *image, Color borderColor);

} ImageView;

ImageView *createImageView(int x, int y, int w, int h);
