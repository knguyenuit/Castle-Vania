#include "StateGameIntro.h"



CStateGameIntro::CStateGameIntro()
{
	simon_Intro = new CSimonIntro();
	m_imageCurr = new CTexture();
	this->m_imageCurr->LoadImageFromFile(INTRO_SCREEN, D3DCOLOR_XRGB(255, 255, 255));
	m_drawImg = new CSprite();
}


CStateGameIntro::~CStateGameIntro()
{
}

void CStateGameIntro::Init()
{
	this->m_Pos.x = 0;
	this->m_Pos.y = 0;
}

void CStateGameIntro::Update(float deltaTime)
{
	this->simon_Intro->Update(deltaTime);
}

void CStateGameIntro::Render()
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
	this->simon_Intro->Draw();
}

void CStateGameIntro::Destroy()
{
}
