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

	return bre;
}
void thread_readframe(CNxStream *pParam)
{
	CNxStream *pObj = pParam;

	AVFrame *pFrame = nullptr;
	AVFrame *pFrame_YUV = nullptr;

	pFrame = av_frame_alloc();

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
				avcodec_decode_video2(pObj->m_pCodecContext,
					pFrame, &got_picture_ptr, &packet);
				if (got_picture_ptr != 0)
				{//push queue
					sws_scale(sc, 
						(const uint8_t* const*)pFrame->data,
						pFrame->linesize,
						0,
						pObj->m_pCodecContext->height,
						pFrame_YUV->data,
						pFrame_YUV->linesize);

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
		if (m_pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_iIndex = i;

			break;
		}
	}
	//
	m_pCodecContext = m_pFormatContext->streams[m_iIndex]->codec;

	//Find Decode
	m_pCodec = avcodec_find_decoder(m_pCodecContext->codec_id);

	//open
	if (avcodec_open2(m_pCodecContext, m_pCodec, nullptr) != 0)
	{
		m_pLogInstance->LogDebug("Error avcodec_open2", __func__);
		return false;
	}

	return bre;
}