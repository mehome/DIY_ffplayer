#pragma once
#include "NxBase.h"
#include "CNxLogINI.h"
extern "C"
{
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"
}


class CNxStream :
	public CNxBase
{
public:
	CNxStream();
	~CNxStream();
public:
	bool SetOpenPath(char *ch_path);
	bool ReadFrame();
private:
	bool regist();
public:
	AVFormatContext *m_pFormatContext;
	AVCodecContext	*m_pCodecContext;
	AVCodec			*m_pCodec;
	CNxLogINI		*m_pLogInstance;
	int				m_iIndex;
};

