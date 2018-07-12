#pragma once
extern "C"
{
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"
}
typedef struct CFrameInfo 
{
	AVFrame *pframe;
};