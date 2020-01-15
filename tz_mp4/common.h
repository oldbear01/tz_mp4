
#ifndef _COMMON_H_
#define _COMMON_H_

#define MAX_PLAY_CHN 9

#include "Classes/MutexInteger.h"
#include "Classes/TzThread.h"
#include "Inc/stdint.h"
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

extern "C"
{
#include "Inc/libavcodec/avcodec.h"
#include "Inc/libavdevice/avdevice.h"
#include "Inc/libavfilter/avfilter.h"
#include "Inc/libavfilter/buffersink.h"
#include "Inc/libavfilter/buffersrc.h"
#include "Inc/libavformat/avformat.h"
#include "Inc/libavutil/avutil.h"
#include "Inc/libpostproc/postprocess.h"
#include "Inc/libswresample/swresample.h"
#include "Inc/libswscale/swscale.h"
#include "Inc/libavutil/imgutils.h"
};

#pragma comment(lib,"lib/avcodec.lib")
#pragma comment(lib,"lib/avdevice.lib")
#pragma comment(lib,"lib/avfilter.lib")
#pragma comment(lib,"lib/avformat.lib")
#pragma comment(lib,"lib/avutil.lib")
#pragma comment(lib,"lib/postproc.lib")
#pragma comment(lib,"lib/swresample.lib")
#pragma comment(lib,"lib/swscale.lib")



#include <map>
using namespace std;
using namespace vfc;


#endif