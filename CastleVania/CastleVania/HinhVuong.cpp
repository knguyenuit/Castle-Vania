#include "HinhVuong.h"



void CHinhVuong::Init()
{
	this->m_Id = 2;
	this->m_Width = 88;
	this->m_Height = 64;
	this->m_Pos = Vector2(200, 200);
	this->m_vx = 0;
	this->m_vy =0;
	//animatin
	
}

void CHinhVuong::Update(float deltaTime)
{
	MoveUpdate(deltaTime);
}

CHinhVuong::CHinhVuong()
{
	Init();
}


CHinhVuong::~CHinhVuong()
{
}

void CHinhVuong::MoveUpdate(float deltaTime)
{
	this->m_Pos.x += this->m_vx * deltaTime;
	this->m_Pos.y += this->m_vy * deltaTime;
}

Box CHinhVuong::GetBox()
{
	return Box(this->m_Pos, this->m_Width, this->m_Height, this->m_vx, this->m_vy);
	/*Vector2 m_Pos1 = Vector2(m_Pos.x - m_Width / 2, m_Pos.y - m_Height / 2);
	return Box(m_Pos1, this->m_Width, this->m_Height, this->m_vx, this->m_vy);*/
}
