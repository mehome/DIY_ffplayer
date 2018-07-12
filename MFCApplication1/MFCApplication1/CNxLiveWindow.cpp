#include "stdafx.h"
#include "CNxLiveWindow.h"
#include<thread>

CNxLiveWindow::CNxLiveWindow()
{
	m_pBase = nullptr;

	InitLiveWindow();
}


CNxLiveWindow::~CNxLiveWindow()
{
}
void thread_func_Live(CNxLiveWindow *p)
{
	CNxLiveWindow *pObj = p;
	SDL_Rect re;
	re.x = 0;
	re.y = 0;
	re.h = 540;
	re.w = 960;
	while (true)
	{
		//pop queue
		CFrameInfo *p = pObj->m_pBase->m_mapBase[0]->pop_front();

		SDL_UpdateTexture(pObj->m_pTexture, &re, p->pframe->data[0], p->pframe->linesize[0]);

		SDL_RenderClear(pObj->m_pRender);
		SDL_RenderCopy(pObj->m_pRender, pObj->m_pTexture, &re, &re);
		SDL_RenderPresent(pObj->m_pRender);

	}
}
void CNxLiveWindow::SetQueue(CNxBase *pBase)
{
	m_pBase = pBase;
}
void CNxLiveWindow::SDLCreateWindow(HWND hwnd, RECT re)
{
	m_pWindow = SDL_CreateWindowFrom(hwnd);

	m_pRender = SDL_CreateRenderer(m_pWindow, 0, SDL_RENDERER_ACCELERATED);
	
	SDL_Rect sdl_re = {0,0,re.right,re.bottom};

	SDL_RenderSetViewport(m_pRender, &sdl_re);

	m_pTexture = SDL_CreateTexture(m_pRender,
		SDL_PIXELFORMAT_YUY2,
		SDL_TEXTUREACCESS_STREAMING,
		960, 540);

	//TTF
	m_pFont = TTF_OpenFont("C:\\Windows\\Fonts\\simkai.ttf", 20);

	TTF_SetFontStyle(m_pFont, TTF_STYLE_NORMAL);

	m_color.a = m_color.b = m_color.g = m_color.r = 255;

	std::thread thread_func(thread_func_Live,this);
}
void CNxLiveWindow::InitLiveWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{

	}
	if (TTF_Init() != 0)
	{

	}
}
