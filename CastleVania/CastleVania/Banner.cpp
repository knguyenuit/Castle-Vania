#include "Banner.h"
#include "Resources.h"
#include "Camera.h"


void CBanner::Init()
{
	this->m_Width = 510;
	this->m_Height = 79;
	this->m_Id = 100;
	this->m_Pos = Vector2(255, 400);
	m_TextureBanner = new CTexture();
	m_TextureBanner->LoadImageFromFile(BANNER, D3DCOLOR_XRGB(255, 0, 255));
	m_textureHpPlayer = new CTexture();
	m_textureHpPlayer->LoadImageFromFile(SIMON_HP, D3DCOLOR_XRGB(255, 0, 255));
	this->posHpSimon = D3DXVECTOR3(176, 73, 0);
	this->m_hpSimon = CSimon::GetInstance()->m_hpSimon;
}

void CBanner::Update(float deltaTime)
{
	//ve banner theo camera
		this->m_Pos.x = CCamera::GetInstance()->m_pos.x + 320;
		//cap nhat mau cua simon
		this->m_hpSimon = CSimon::GetInstance()->m_hpSimon;
	
}

void CBanner::DrawBannerBG()
{
	
	Vector3 pos = Vector3();
	RECT* rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	pos = CCamera::GetInstance()->GetPointTransform(this->m_Pos.x, this->m_Pos.y);
	this->m_Draw->Draw(m_TextureBanner, GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
}

void CBanner::DrawBannerProperty()
{
	D3DXVECTOR3 positionHpSimon = this->posHpSimon;
	for (int i = 0; i < this->m_hpSimon; i++)
	{
		this->m_Draw->Draw(this->m_textureHpPlayer, NULL, positionHpSimon);
		positionHpSimon.x += 8;
	}
}

RECT * CBanner::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}

CBanner::CBanner()
{
	Init();
}


CBanner::~CBanner()
{
}
