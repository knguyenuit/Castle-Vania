#include "StateGameStart.h"
#include "Device.h"



CStateGameStart::CStateGameStart()
{
	this->m_imageCurr = new CTexture();
	this->m_drawImg = new CSprite();
	this->m_imageCurr->LoadImageFromFile(START_SCREEN, D3DCOLOR_XRGB(255, 255, 255));
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


CStateGameStart::~CStateGameStart()
{
}

void CStateGameStart::Init()
{
	this->m_Pos.x = 0;
	this->m_Pos.y = 0;
	
}

void CStateGameStart::Update(float deltaTime)
{
	this->timeDrawString += deltaTime;
	if (this->timeDrawString >= 1.0f)
	{
		this->canDrawString = true;
		timeAnimation += deltaTime;
		if (timeAnimation >= 0.5f)
		{
			timeDrawString = 0;
			timeAnimation = 0;
			this->canDrawString = false;
		}
	}
}

void CStateGameStart::Render()
{
	RECT *rectRS = new RECT();

	D3DXVECTOR3 pos;
	pos.x = this->m_Pos.x;
	pos.y = this->m_Pos.y;
	pos.z = 0;
	rectRS->left = 0;
	rectRS->top = 0;
	rectRS->right = m_imageCurr->GetImageWidth();
	rectRS->bottom = m_imageCurr->GetImageHeight();
	this->m_drawImg->Draw(this->m_imageCurr, rectRS, pos, D3DCOLOR_XRGB(255, 255, 225), false);
	if (canDrawString)
	{
		RECT *rectRS_font = new RECT();
		rectRS_font->left = 100;
		rectRS_font->top = 300;
		rectRS_font->right = 500;
		rectRS_font->bottom = 400;
		_font->DrawTextA(CDevice::s_spriteHandle, "PUSH ENTER TO START", -1, rectRS_font, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		
		
	}
}

void CStateGameStart::Destroy()
{
}


