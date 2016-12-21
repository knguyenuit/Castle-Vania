#include "DrawFont.h"



CDrawFont::CDrawFont()
{
	_font = NULL;
	D3DXCreateFont(
		CDevice::s_d3ddv,
		25,
		0,
		FW_BOLD,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		"Lucida Console",
		&_font);
}


CDrawFont::~CDrawFont()
{
}

void CDrawFont::DrawString(std::string str, RECT* rec)
{
	_font->DrawTextA(CDevice::s_spriteHandle, str.c_str(), -1, rec, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

void CDrawFont::DrawNumber(int num, RECT* rec)
{
	std::string temp;
	temp = std::to_string(num);
	_font->DrawTextA(CDevice::s_spriteHandle, temp.c_str(), -1, rec, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}
