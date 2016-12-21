#pragma once

#include "Texture.h"
#include "Device.h"



class CDrawFont
{
public:
	ID3DXFont* _font;
	CDrawFont();
	~CDrawFont();
	void DrawString(std::string str, RECT* rec);
	void DrawNumber(int num, RECT* rec);
};

