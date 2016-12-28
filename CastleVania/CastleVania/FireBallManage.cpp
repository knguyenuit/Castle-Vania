#include "FireBallManage.h"



CFireBallManage::CFireBallManage()
{
	//CreateFireBall(Vector2(800, 250), RIGHT);
}


CFireBallManage::~CFireBallManage()
{
}

void CFireBallManage::Update(float deltaTime)
{
	if (!this->m_ListFireBall.empty())
	{
		for (std::vector<CFireBall*>::iterator em = m_ListFireBall.begin(); em != m_ListFireBall.end(); ++em)
		{
			CFireBall* ball = *em;
			ball->Update(deltaTime);
			if (ball->m_isRemove)
			{
				m_ListFireBall.erase(em);
				break;
			}
		}
	}
}

void CFireBallManage::CreateFireBall(Vector2 pos, Direction m_Dir)
{
	CFireBall* ball;
	ball = new CFireBall(pos, m_Dir);
	this->m_ListFireBall.push_back(ball);
	
}

void CFireBallManage::Draw()
{

	if (!this->m_ListFireBall.empty())
	{
		for (std::vector<CFireBall*>::iterator em = m_ListFireBall.begin(); em != m_ListFireBall.end(); ++em)
		{
			CFireBall* fireball = *em;
			
			this->DrawFireBall(fireball);
		}
	}
}

void CFireBallManage::DrawFireBall(CFireBall* obj)
{
	int id = obj->GetID();
	CTexture* Texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(obj->GetPos().x, obj->GetPos().y);
	Texture->LoadImageFromFile(ENEMY_FIREBALL, D3DCOLOR_XRGB(255, 0, 255));
	if (obj->m_Dir == LEFT)
	{
		this->m_draw->Draw(Texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		this->m_draw->DrawFlipX(Texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}
