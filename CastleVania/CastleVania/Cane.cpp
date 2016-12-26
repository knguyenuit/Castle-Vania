#include "Cane.h"
#include "Simon.h"
#include "ItemManage.h"
CCane::CCane()
{
	Init();
}

CCane::CCane(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
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
	this->m_elapseTimeChangeFrame = 0.1f;
	this->m_increase = 1;
	this->m_totalFrame = 12;
	this->m_column = 4;
	this->m_Dir = Direction::RIGHT;
	this->m_State = caneState::default;

}

void CCane::Update(Vector2 simonPos, Direction simonDir, float deltaTime)
{
	if (this->m_checkActive == true)
	{
		this->m_Dir = simonDir;
		this->m_Pos = simonPos;
		int dir = (this->m_Dir == Direction::LEFT) ? 1 : -1;
		this->m_Pos.x -= 28 * dir;
		this->ChangeFrame(deltaTime);
		if (this->m_currentFrame == this->m_endFrame)
		{
			this->m_checkActive = false;
			this->m_checkDone = true;
			switch (this->m_State)
			{
			case caneState::default:
				this->m_currentFrame = 0;
				break;
			case caneState::state2:
				this->m_currentFrame = 4;
				break;
			case caneState::state3:
				this->m_currentFrame = 8;
				break;
			default:
				break;
			}
		}

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
			//CDirection normalX;
			//CDirection normalY;
			//float timeCollision;
			if (m_currentFrame == 2 || m_currentFrame == 6 || m_currentFrame == 10)
			{

				/*timeCollision = COnCollision::GetInstance()->SweepAABB(this->GetBox(), obj->GetBox(), normalX, normalY, deltaTime);


				if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
				{
				MessageBox(NULL, "Danh trung Ground", "BG", MB_OK);
				}*/
				if (CCollision::GetInstance()->AABBCheck(this->GetBox(), obj->GetBox()))
				{
					obj->m_isRemove = true;
					CItemManage::GetInstance()->CreateRandomItem(obj->GetPos());

				}

			}
		}

	}

}


Box CCane::GetBox()
{
	int width = 0;
	float posx = 0;
	posx = (this->m_Dir == LEFT) ? this->m_Pos.x - 17 : this->m_Pos.x + 17; //tranh va cham khi dung ngay canh object
	switch (this->m_State)
	{
	case caneState::default:
		width = this->m_Width - 107;
		break;
	case caneState::state2:
		width = this->m_Width - 117;
		break;
	case caneState::state3:
		width = this->m_Width - 67;
		break;
	default:
		break;
	}
	return Box(posx, this->m_Pos.y, width, this->m_Height - 50);
}


RECT * CCane::GetBound()
{
	return nullptr;
}

RECT * CCane::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}

bool CCane::Use()
{
	this->m_checkActive = true;
	if (this->m_checkDone == true)
	{
		ManageAudio::GetInstance()->playSound(TypeAudio::Using_Whip);
		this->m_checkActive = false;
		this->m_checkDone = false;
		return true;
	}
	else
	{
		return false;
	}
}

void CCane::SetFrame()
{
	this->m_currentFrame = 0;
}

void CCane::updateState(caneState state)
{
	this->m_State = state;
	switch (state)
	{
	case caneState::default:
		this->m_currentFrame = 0;
		this->m_startFrame = 0;
		this->m_endFrame = 3;
		break;
	case caneState::state2:
		this->m_currentFrame = 4;
		this->m_startFrame = 4;
		this->m_endFrame = 7;
		break;
	case caneState::state3:
		this->m_currentFrame = 8;
		this->m_startFrame = 8;
		this->m_endFrame = 11;
		break;
	default:
		break;
	}
}