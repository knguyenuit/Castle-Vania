#include "Cane.h"
#include "Simon.h"
#include "ItemManage.h"



CCane::CCane()
{
	Init();
}


CCane::~CCane()
{
}

void CCane::Init()
{
	//this->m_Pos = Vector2(500, 500);
	this->m_Id = 12;
	this->m_Width = 160;
	this->m_Height = 68;

	this->m_realWidth = 60;
	this->m_realHeight = 17;

	//animatin
	this->m_startFrame = 0;
	this->m_endFrame = 3;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 12;
	this->m_column = 4;
	this->m_Dir = Direction::LEFT;

	
}

void CCane::Update(float deltaTime)
{
	
	OnCollision(deltaTime, CLoadObject::GetInstance()->m_listGameObject);
	
	if (this->m_checkActive)
	{
		ChangeFrame(deltaTime);

	}
	if (this->m_currentFrame == this->m_endFrame)
	{
		this->m_checkActive = false;
		this->isChangeSimonStatus = true;
		this->m_currentFrame = 0;
	}
}

Vector2 CCane::GetPos()
{
	return this->m_Pos;
}



void CCane::OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject)
{
	for (std::vector<CBaseGameObject*>::iterator it = listObject.begin();
		it != listObject.end();
		++it)
	{
		CBaseGameObject* obj = *it;
		if (obj->m_Id == 601)
		{
			CDirection normalX;
			CDirection normalY;
			float timeCollision;
			if (m_currentFrame == 2)
			{
				
				/*timeCollision = COnCollision::GetInstance()->SweepAABB(this->GetBox(), obj->GetBox(), normalX, normalY, deltaTime);


				if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
				{
					MessageBox(NULL, "Danh trung Ground", "BG", MB_OK);
				}*/
				if (CCollision::GetInstance()->AABBCheck(this->GetBox(), obj->GetBox()))
				{
					CItemManage::GetInstance()->CreateRandomItem(Vector2(300,60));
					obj->m_isRemove = true;
				}

			}
		}

	}
	
}

Box CCane::GetBox()
{
	/*if (this->isLeft)
	{
		return Box(this->m_Pos.x - this->m_realWidth / 2, this->m_Pos.y + this->m_realHeight / 2,
			this->m_realWidth, this->m_realHeight);
	}
	else
	{
		return Box(this->m_Pos.x + this->m_realWidth / 2, this->m_Pos.y + this->m_realHeight / 2,
			this->m_realWidth, this->m_realHeight);
	}*/
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 80, this->m_Height);
}

RECT * CCane::GetBound()
{
	return nullptr;
}

RECT * CCane::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);	
}

void CCane::Use(D3DXVECTOR2 m_posSimon, bool isLeft)
{
	this->m_Pos = m_posSimon;

	int dir = isLeft ? 1 : -1;
	this->m_Pos.x -= 28 * dir;
}

void CCane::SetFrame()
{
	this->m_currentFrame = 0;
}


