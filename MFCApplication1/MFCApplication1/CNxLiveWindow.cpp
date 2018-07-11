#include "stdafx.h"
#include "CNxLiveWindow.h"
#include<thread>

CNxLiveWindow::CNxLiveWindow()
{
	InitLiveWindow();
}


CNxLiveWindow::~CNxLiveWindow()
{
}
void thread_func_Live(CNxLiveWindow *p)
{
	CNxLiveWindow *pObj = p;
	
	while (true)
	{
		//pop queue

	}
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
	m_pFont = TTF_OpenFont("D:\\quanwei\\Project\\AJA_Driver\\xPlayer v1\\xPlayer_6_13\\xPlayer_6_13\\x64\\Debug64\\simkai.ttf", 20);

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
