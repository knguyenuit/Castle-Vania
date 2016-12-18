#include "SimonIntro.h"
#include "Resources.h"
#include "Camera.h"



CSimonIntro::CSimonIntro()
{
	Init();
	InitAnimation();
	m_imageCurr = new CTexture();
	this->m_imageCurr->LoadImageFromFile(SIMON_RES, D3DCOLOR_XRGB(255, 0, 255));
	m_drawImg = new CSprite();
}


CSimonIntro::~CSimonIntro()
{
}

Box CSimonIntro::GetBox()
{
	return Box();
}

RECT * CSimonIntro::GetBound()
{
	return nullptr;
}

RECT * CSimonIntro::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}

void CSimonIntro::Init()
{

	this->m_vx = 50;
	this->m_vy = 380;
	this->m_vxDefault = 180;
	this->m_vyDefault = 380;

	this->m_a = -900;
	this->m_aDefault = this->m_a;
	this->m_ax = 0;
	this->m_Pos = Vector2(20, 110);
	this->m_Width = 60;
	this->m_Height = 68;
}

void CSimonIntro::InitAnimation()
{
	this->m_startFrame = 0;
	this->m_endFrame = 3;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.2f;
	this->m_increase = 1;
	this->m_totalFrame = 24;
	this->m_column = 8;
}

void CSimonIntro::Update(float deltaTime)
{
	ChangeFrame(deltaTime);
	MoveUpdate(deltaTime);
}
float time = 0;
void CSimonIntro::MoveUpdate(float deltaTime)
{
	this->m_Pos.x += this->m_vx * deltaTime;
	if (m_Pos.x >= 265)
	{
		this->m_vx = 0;
		this->m_startFrame = 9;
		this->m_endFrame = 9;
		time += deltaTime;
		if (time >= 0.5)
		{
			this->isChangeGamePlayState = true;
			time = 0;
		}
	}
}

void CSimonIntro::Draw()
{
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(m_Pos.x, m_Pos.y);
	this->m_drawImg->DrawFlipX(m_imageCurr, GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
}
