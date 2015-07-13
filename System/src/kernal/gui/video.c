#include "../type/type.h"
#include "video.h"

VideoModeInfo *videoModeInfo;

void initVideoModeInfo()
{
	videoModeInfo = (VideoModeInfo *)0x21800;
}
