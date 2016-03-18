/* 
 * The size of the image header.
 */
#define IMAGE_HEADER_SIZE 8

typedef struct Image Image;

/* 
 * The image type definition, including the head, data, buffer pointers, 
 * with, height properties and reference as the memory reference count.
 * Meanwhile, it also has retain and release function pointers to implement
 * the memory allocation and release operation.
 */
typedef struct Image
{
    u8 *head;

    u8 *data;

    u8 *buffer;

    u16 width;
	
	u16 height;

	u32 reference;

	void (*retain)(Image *image);

	void (*release)(Image *image);

} Image;

/* 
 * Load the imgae data at the specified sector position and mainly from the harddisk.
 *
 * Parameters:
 * 		sector: the starting sector position of the image data in the harddisk.
 * Return:
 *		image data structure in the object form.
 */
Image* loadImageFromStorage(u32 sector);
