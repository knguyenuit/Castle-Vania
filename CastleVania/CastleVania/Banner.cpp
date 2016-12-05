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

}

void CBanner::Update(float deltaTime)
{

}

void CBanner::Draw()
{
	m_TextureBanner->LoadImageFromFile(BANNER, D3DCOLOR_XRGB(255, 0, 255));
	Vector3 pos = Vector3();
	RECT* rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	pos = CCamera::GetInstance()->GetPointTransform(this->m_Pos.x, this->m_Pos.y);
	this->m_Draw->Draw(m_TextureBanner, GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
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
