#include "Snake.h"



CSnake::CSnake()
{
	this->Init();
	this->m_Pos = Vector2(300, 300);
	this->m_Dir = LEFT;
}

CSnake::CSnake(Vector2 pos, Direction dir)
{
	this->m_PosDefault = this->m_Pos = pos;
	this->m_Dir = dir;
	this->m_vxDefault = this->m_vx = 100;
	this->m_vyDefault = this->m_vx = 300;
	this->Init();
}

CSnake::CSnake(Vector2 pos, Direction dir, float v_x, float v_y)
{
	this->m_PosDefault = this->m_Pos = pos;
	this->m_Dir = dir;
	this->m_vxDefault = this->m_vx = v_x;
	this->m_vyDefault = this->m_vx = v_y;
	this->Init();
}

void CSnake::Init()
{
	this->enemyType = ENEMY_type::Snake;
	this->m_Width = 64;
	this->m_Height = 20;
}


CSnake::~CSnake()
{
}

void CSnake::Draw()
{
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(this->m_Pos.x, this->m_Pos.y);
	Texture->LoadImageFromFile(BOSS_SNAKE, D3DCOLOR_XRGB(255, 0, 255));
	if (this->m_Dir == LEFT)
	{
		this->m_draw->Draw(this->Texture, this->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		this->m_draw->DrawFlipX(this->Texture, this->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}

void CSnake::Update(float deltaTime)
{
	this->OnSimonCollision(deltaTime);
	if (this->simon->cane->m_checkActive == true)
	{
		this->OnCaneCollision();
	}
	MoveUpdate(deltaTime);
	m_currentTimeLife += deltaTime;
	if (m_currentTimeLife >= 3)
	{
		this->m_isRemove = true;
		m_currentTimeLife = 0;
	}
}

void CSnake::MoveUpdate(float deltaTime)
{
	if (this->m_Dir == LEFT)
	{
		this->m_Pos.x -= this->m_vx * deltaTime;
	}
	else
	{
		this->m_Pos.x += this->m_vx * deltaTime;
	}
}

RECT * CSnake::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}
