#include "HinhChuNhat.h"



CHinhChuNhat::CHinhChuNhat()
{
	Init();
}


CHinhChuNhat::~CHinhChuNhat()
{
}

void CHinhChuNhat::Init()
{
	this->m_Id = 3;
	this->m_Width = 100;
	this->m_Height = 100;
	this->m_Pos = Vector2(0, 0);
	this->m_vx = 0;
	this->m_vy = 0;
}

void CHinhChuNhat::Update(float deltaTime)
{
	this->m_Pos.x += this->m_vx * deltaTime;
	this->m_Pos.y += this->m_vy * deltaTime;
}

RECT * CHinhChuNhat::GetRectRS()
{
	RECT* rectRS = new RECT();
	
	
	//cập nhật lại vị trí của Rect Resource
	rectRS->left =this->m_Pos.x;
	rectRS->right = rectRS->left + this->m_Width;
	rectRS->top = this->m_Pos.y;
	rectRS->bottom = rectRS->top + this->m_Height;
	return rectRS;
}

Box CHinhChuNhat::GetBox()
{
	return Box(this->m_Pos, this->m_Width, this->m_Height, this->m_vx, this->m_vy);
	/*Vector2 m_Pos1 = Vector2(m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2);
	return Box(m_Pos1, this->m_Width, this->m_Height, this->m_vx, this->m_vy);*/
}
