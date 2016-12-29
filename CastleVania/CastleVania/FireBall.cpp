#include "FireBall.h"


CFireBall::CFireBall()
{
	//this->m_vxDefault = this->m_vx = 300;
	//this->m_vyDefault = this->m_vx = 300;
	this->Init();
	this->m_Pos = Vector2(300, 300);
	this->m_Dir = LEFT;
}

CFireBall::CFireBall(Vector2 pos, Direction dir)
{
	this->m_PosDefault = this->m_Pos = pos;
	this->m_Dir = dir;
	this->m_vxDefault = this->m_vx = 100;
	this->m_vyDefault = this->m_vx = 300;
	this->Init();
}

CFireBall::CFireBall(Vector2 pos, Direction dir, float v_x, float v_y)
{
	this->m_PosDefault = this->m_Pos = pos;
	this->m_Dir = dir;
	this->m_vxDefault = this->m_vx = v_x;
	this->m_vyDefault = this->m_vx = v_y;
	this->Init();
}

void CFireBall::Init()
{
	this->enemyType = ENEMY_type::FireBall;
	this->m_Width = 14;
	this->m_Height = 12;
}


CFireBall::~CFireBall()
{
}

void CFireBall::Draw()
{
	CTexture* Texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(this->m_Pos.x, this->m_Pos.y);
	Texture->LoadImageFromFile(ENEMY_FIREBALL, D3DCOLOR_XRGB(255, 0, 255));
	if (this->m_Dir == LEFT)
	{
		this->m_draw->Draw(Texture, this->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		this->m_draw->DrawFlipX(Texture, this->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}

}

void CFireBall::Update(float deltaTime)
{
	//this->Draw();
	MoveUpdate(deltaTime);
	m_currentTimeLife += deltaTime;
	if (m_currentTimeLife >= 3)
	{
		this->m_isRemove = true;
		m_currentTimeLife = 0;
	}
}

void CFireBall::MoveUpdate(float deltaTime)
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

RECT * CFireBall::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}

