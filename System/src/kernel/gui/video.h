/* 
 * The base address constant of the VideoModeInfo data in the memory.
 */
#define			VIDEO_INFO_BASE			0x21800

/* 
 * According to the VESA_VBE standard, here is the data structure of the Video mode infomation.
 * The detailed meaning is listed below, please refer to the name of the data field.
 */
typedef struct VideoModeInfo
{
	u16 modeAttribute;

	u8 winAttributeA;

	u8 winAttributeB;

	u16 winGranularity;

	u16 winSize;

	u16 winStartSegA;

	u16 winStartSegB;

	u32 winPosFunPointer;

	u16 scanLineByte;

	u16 widthPixel;

	u16 heightPixel;
	
	u8 widthCellPixel;

	u8 heightCellPixel;

	u8 memPlaneNumber;

	u8 bitPixelNumber;

	u8 blankNumber;

	u8 memModeType;

	u8 blankSize;

	u8 imagePageNumber;

	u8 reservedByte;

	u8 redMaskSize;

	u8 redFieldPosition;

	u8 greenMaskSize;

	u8 greenFieldPosition;

	u8 blueMaskSize;

	u8 blueFieldSize;

	u8 reservedMaskSize;

	u8 reservedMaskPosition;

	u8 colorModeInfo;

	u32 bufferAddress;

	u32 startPointer;

	u16 offScreenMem;

	u8 reservedData[206];

} VideoModeInfo;

/* 
 * Set the videoModeInfo point to the specified address, so that the OS can 
 * get the video infomation and settings by accessing the videoModeInfo data
 * structure.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initVideoModeInfo();

