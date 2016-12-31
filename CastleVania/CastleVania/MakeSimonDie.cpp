#include "MakeSimonDie.h"



CMakeSimonDie::CMakeSimonDie()
{
	this->Init();
}

CMakeSimonDie::CMakeSimonDie(Vector2 pos)
{
	this->Init();
	this->m_Pos = this->m_PosDefault = this->currentStepPos = pos;
}

void CMakeSimonDie::Init()
{
	this->enemyType = ENEMY_type::MakeSimonDie;
	this->m_Width = 64;
	this->m_Height = 16;
	this->m_vx = this->m_vxDefault = 0;
	this->m_vy = this->m_vyDefault = 150;
	this->MSDState = MSDState::Down;
}


CMakeSimonDie::~CMakeSimonDie()
{
}

void CMakeSimonDie::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	this->OnSimonCollision();
}

void CMakeSimonDie::Draw()
{
	CTexture* texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(this->GetPos().x, this->GetPos().y);
	texture->LoadImageFromFile(ENEMY_MAKE_SIMON_DIE, D3DCOLOR_XRGB(255, 0, 255));
	this->m_draw->Draw(texture, this->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	CTexture* texture2 = new CTexture();
	Vector3 pos2 = Vector3();
	pos2 = CCamera::GetInstance()->GetPointTransform(this->m_PosDefault.x - 7, this->m_PosDefault.y + 5);
	texture->LoadImageFromFile(ENEMY_MAKE_SIMON_DIE_2, D3DCOLOR_XRGB(255, 0, 255));
	this->m_draw->Draw(texture, this->GetRectRS2(), pos2, D3DCOLOR_XRGB(255, 255, 255), false);
}

void CMakeSimonDie::MSDStateUpdate()
{
	switch (this->MSDState)
	{
	case MSDState::Up:
		this->m_vy = 50;
	case MSDState::Down:
		this->m_vy = 150;
	default:
		break;
	}
}

void CMakeSimonDie::MoveUpdate(float deltaTime)
{
	if (this->MSDState == MSDState::Up)
	{
		if (this->MoveTo(this->currentStepPos + Vector2(0, 16), deltaTime))
		{
			this->currentStepPos = this->m_Pos;
			if (this->m_Pos.y >= this->m_PosDefault.y)
			{
				this->MSDState = MSDState::Down;
				this->MSDStateUpdate();
			}
		}
	}
	else
	{
		if (this->MSDState == MSDState::Down)
		{
			if (this->MoveTo(this->currentStepPos + Vector2(0, -16), deltaTime))
			{
				this->currentStepPos = this->m_Pos;
				if (this->m_Pos.y <= this->m_PosDefault.y - 100)
				{
					this->MSDState = MSDState::Up;
					this->MSDStateUpdate();
				}
			}
		}
	}
	
}

void CMakeSimonDie::OnSimonCollision()
{
	if (CCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
	{

			if (this->simon->timeCollisionEnemy == 0)
			{
				this->simon->m_hpSimon = 0;
			}
	}
}

RECT * CMakeSimonDie::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}

RECT * CMakeSimonDie::GetRectRS2()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + 14;
	rec->top = 0;
	rec->bottom = rec->top + this->m_PosDefault.y - this->m_Pos.y;
	return rec;
}
