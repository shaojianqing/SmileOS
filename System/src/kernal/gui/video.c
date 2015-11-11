#include "../type/type.h"
#include "video.h"

VideoModeInfo *videoModeInfo;

void initVideoModeInfo()
{
	videoModeInfo = (VideoModeInfo *)VIDEO_INFO_BASE;
}
