

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

void initVideoModeInfo();

