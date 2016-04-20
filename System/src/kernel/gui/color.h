/* 
 * The transparent value in the color set,that means if
 * three vectors of one color variable are all 0x00,than
 * it is just transparent, and we will see the color behind
 * it.
 */
#define 		TRANSPARENT				0x00

/* 
 * The Color data structure represents one color value in the OS 
 * and it contains red, green and blue vectors.
 */
typedef struct Color
{
    u8 red;

    u8 green;

    u8 blue;

} Color;
