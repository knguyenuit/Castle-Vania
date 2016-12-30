#include "StateGameOver.h"



CStateGameOver::CStateGameOver()
{
	this->m_imageCurr = new CTexture();
	this->m_drawImg = new CSprite();
	this->m_imageCurr->LoadImageFromFile(END_SCREEN, D3DCOLOR_XRGB(255, 255, 255));
	_font = new CDrawFont();
}


CStateGameOver::~CStateGameOver()
{
}

void CStateGameOver::Init()
{
	this->m_Pos.x = 0;
	this->m_Pos.y = 0;
}

void CStateGameOver::Update(float deltaTime)
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

void CStateGameOver::Render()
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
		rectRS_font->top = 200;
		rectRS_font->right = 500;
		rectRS_font->bottom = 300;

		_font->DrawString("GAME OVER", rectRS_font);

		/*RECT *rectRS1_font = new RECT();
		rectRS1_font->left = 0;
		rectRS1_font->top = 100;
		rectRS1_font->right = 100;
		rectRS1_font->bottom = 200;
		int c = 42;
		std::string info_core;
		info_core = std::to_string(c);
		_font->DrawNumber(10, rectRS1_font);*/
	}
}

void CStateGameOver::Destroy()
{
}
