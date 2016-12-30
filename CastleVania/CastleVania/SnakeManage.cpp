#include "SnakeManage.h"



CSnakeManage::CSnakeManage()
{
}


CSnakeManage::~CSnakeManage()
{
}

void CSnakeManage::Update(float deltaTime)
{
	if (!this->m_ListSnake.empty())
	{
		for (std::vector<CSnake*>::iterator em = m_ListSnake.begin(); em != m_ListSnake.end(); ++em)
		{
			CSnake* snake = *em;
			snake->Update(deltaTime);
			if (snake->m_isRemove)
			{
				m_ListSnake.erase(em);
				break;
			}
		}
	}
}

void CSnakeManage::CreateSnake(Vector2 pos, Direction m_Dir)
{
	CSnake* snake;
	snake = new CSnake(pos, m_Dir);
	this->m_ListSnake.push_back(snake);
}

void CSnakeManage::DrawSnake(CSnake * obj)
{
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(obj->GetPos().x, obj->GetPos().y);
	this->Texture->LoadImageFromFile(BOSS_SNAKE, D3DCOLOR_XRGB(255, 0, 255));
	if (obj->m_Dir == LEFT)
	{
		this->m_draw->Draw(this->Texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		this->m_draw->DrawFlipX(this->Texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}

void CSnakeManage::Draw()
{
	if (!this->m_ListSnake.empty())
	{
		for (std::vector<CSnake*>::iterator em = m_ListSnake.begin(); em != m_ListSnake.end(); ++em)
		{
			CSnake* snake = *em;

			this->DrawSnake(snake);
		}
	}
}
