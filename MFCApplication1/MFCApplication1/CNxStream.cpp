#include "stdafx.h"
#include "CNxStream.h"
#include<thread>
CNxStream::CNxStream()
{
	m_pFormatContext = nullptr;
	m_pLogInstance = CNxLogINI::LogCreateInstance();

	regist();
}


CNxStream::~CNxStream()
{
}
bool CNxStream::regist()
{
	bool bre = true;
	
	av_register_all();

	m_pFormatContext = avformat_alloc_context();

	InitMap(0);

	return bre;
}
void thread_readframe(CNxStream *pParam)
{
	CNxStream *pObj = pParam;

	AVFrame *pFrame = nullptr;
	AVFrame *pFrame_YUV = nullptr;

	AVPacket packet;
	int got_picture_ptr = 0;

	SwsContext *sc = sws_getContext(
		pObj->m_pCodecContext->width,
		pObj->m_pCodecContext->height,
		pObj->m_pCodecContext->pix_fmt,
		pObj->m_pCodecContext->width,
		pObj->m_pCodecContext->height,
		AV_PIX_FMT_YUV420P,
		SWS_BICUBIC,
		nullptr,
		nullptr,
		nullptr
		);

	while (true)
	{
		if (av_read_frame(pObj->m_pFormatContext, &packet) == 0)
		{
			if (packet.stream_index == pObj->m_iIndex)
			{
				
				got_picture_ptr  = avcodec_send_packet(pObj->m_pCodecContext, &packet);
				if (got_picture_ptr != 0)
				{
					break;
				}
				
				pFrame = av_frame_alloc();

				while (avcodec_receive_frame(pObj->m_pCodecContext, pFrame) == 0)
				{
					CFrameInfo *p = new CFrameInfo;
					
					p->pframe = pFrame;

					pObj->Pushback(p);
				}

				av_frame_free(&pFrame);
			}
		}
	}
}
bool CNxStream::ReadFrame()
{
	std::thread th(thread_readframe,this);

	return true;
}
bool CNxStream::SetOpenPath(char *ch_path)
{
	bool bre = true;
	//
	int ie = avformat_open_input(&m_pFormatContext,
		ch_path, nullptr, nullptr);
	if (ie != 0)
	{
		m_pLogInstance->LogDebug("Error avformat_open_input", __func__);
		return false;
	}
	////Find Stream info
	ie = avformat_find_stream_info(m_pFormatContext, nullptr);
	if (ie < 0)
	{
		m_pLogInstance->LogDebug("Error avformat_find_stream_info", __func__);
		return false;
	}
	//Get Codec
	for (int i = 0; i < m_pFormatContext->nb_streams;i++)
	{
		if (m_pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_iIndex = i;

			break;
		}
	}
	//Find Decode
	m_pCodec = avcodec_find_decoder(m_pFormatContext->streams[m_iIndex]->codecpar->codec_id);

	//Get CodecContex
	m_pCodecContext = avcodec_alloc_context3(m_pCodec);

	//open
	if (avcodec_open2(m_pCodecContext, m_pCodec, nullptr) != 0)
	{
		m_pLogInstance->LogDebug("Error avcodec_open2", __func__);
		return false;
	}

	return bre;
}