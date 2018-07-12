#pragma once
#include "NxBase.h"
#include"SDL\SDL.h"
#include"SDL\SDL_ttf.h"

class CNxLiveWindow :
	public CNxBase
{
public:
	CNxLiveWindow();
	~CNxLiveWindow();

	void SDLCreateWindow(HWND hwnd,RECT re);
	void SetQueue(CNxBase *pBase);
private:
	void InitLiveWindow();
public:
	CNxBase			*m_pBase;
	SDL_Texture		*m_pTexture;
	SDL_Window		*m_pWindow;
	SDL_Renderer	*m_pRender;
	TTF_Font		*m_pFont;
	SDL_Color		 m_color;
};

