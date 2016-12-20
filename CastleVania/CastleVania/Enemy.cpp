#include "Enemy.h"
#include "Simon.h"
#include "ItemManage.h"
#include "ManageAudio.h"

CEnemy::CEnemy()
{
	CEnemy::Init();
}

void CEnemy::Init()
{
	this->m_State = ENEMY_state::IDLE;
	this->m_isRemove = false;
	this->m_vx = 100;
	this->m_vy = 200;
	this->m_Dir = Direction::LEFT;
	//init Direction (for MoveTo() )
	this->check_arrive_x = this->check_arrive_y = false;
	this->isLeft = this->isRight = this->isUp = this->isDown = false;
}

void CEnemy::InitAnimation()
{

}

void CEnemy::Update(float deltaTime)
{
	OnSimonCollision(deltaTime);
	if (CSimon::GetInstance()->cane->m_checkActive)
	{
		OnCaneCollision();
	}
	this->ChangeFrame(deltaTime);
	if (this->m_Pos.x < CCamera::GetInstance()->m_pos.x + 600)
	{
		if (this->m_State == ENEMY_state::IDLE)
		{
			switch (this->enemyType)
			{
			case BlackLeopard:
				this->m_State = ENEMY_state::JUMP;
				break;
			default:
				this->m_State = ENEMY_state::MOVE;
				break;
			}
		}
	}
	//Neu con enemy di qua phia ben trai man hinh thi remove ra khoi list
	if (CCamera::GetInstance()->m_pos.x>this->m_Pos.x)
	{
		this->m_isRemove = true;
	}
	if (this->m_State != ENEMY_state::IDLE)
	{
		this->MoveUpdate(deltaTime);
	}
	
}


bool CEnemy::MoveTo(Vector2 point, float deltaTime)
{
	if (!this->isLeft && !this->isRight)
	{

		if (this->m_Pos.x > point.x) //kiem tra xem co phai qua ben trai
		{
			this->isLeft = true;
		}
		else
		{
			this->isRight = true;
		}
	}

	if (this->isLeft) // neu isleft thi van toc x am
	{
		this->m_vx = (this->m_vx>0) ? -this->m_vx : this->m_vx;
		this->m_Dir = Direction::LEFT;
	}
	else
	{
		this->m_vx = (this->m_vx<0) ? -this->m_vx : this->m_vx;
		this->m_Dir = Direction::RIGHT;
	}

	//kiem tra xem co toi toa do X cua point chua
	if ((this->isLeft && this->m_Pos.x <= point.x) || (this->isRight && this->m_Pos.x >= point.x))
	{
		this->check_arrive_x = true;
		this->m_Pos.x = point.x;
	}
	if (!this->check_arrive_x)
	{
		this->m_Pos.x += this->m_vx * deltaTime; // thay doi pos.x cua Boss
	}



	if (!this->isDown && !this->isUp)
	{
		if (this->m_Pos.y > point.y) // kiem tra xem co phai di xuong duoi
		{
			this->isDown = true;
		}
		else
		{
			this->isUp = true;
		}
	}
	if (this->isDown) // neu isdown thi van toc y am
	{
		this->m_vy = (this->m_vy > 0) ? -this->m_vy : this->m_vy;
	}
	else // neu isUp thi van toc y duong
	{
		this->m_vy = (this->m_vy < 0) ? -this->m_vy : this->m_vy;
	}

	//neu da toi point.y
	if ((this->isDown && this->m_Pos.y <= point.y) || (this->isUp && this->m_Pos.y >= point.y))
	{
		this->check_arrive_y = true;
		this->m_Pos.y = point.y;
	}
	if (!this->check_arrive_y)
	{
		this->m_Pos.y += this->m_vy * deltaTime;// Neu chua toi thi Thay doi pos.y
	}
	//Neu da toi point thi tra ve true
	if (this->check_arrive_x && this->check_arrive_y)
	{
		this->check_arrive_x = this->check_arrive_y = false;
		this->isLeft = this->isRight = this->isUp = this->isDown = false;
		return true;
	}
	else
	{
		return false;
	}
}

void CEnemy::MoveUpdate(float deltaTime)
{
	//if (this->m_Pos.x <= CSimon::GetInstance()->GetPos().x)
	//{
	//	this->m_IsActive = false;
	//	MessageBox(NULL, "A", "b", true);
	//}

	switch (this->m_State)
	{
	case ENEMY_state::MOVE:
		if (this->m_Dir = LEFT)
		{
			this->m_Pos.x -= m_vx * deltaTime;
		}
		else
		{
			this->m_Pos.x += m_vx * deltaTime;
		}

		break;
	case ENEMY_state::FREE:
		this->m_Pos.y -= m_vy*deltaTime;
		break;
	default:
		break;
	}

}
void CEnemy::changeState(ENEMY_state state)
{
	this->m_State = state;
}
RECT * CEnemy::GetRectRS()
{
	return nullptr;
}


CEnemy::~CEnemy()
{
}

void CEnemy::OnSimonCollision(float deltaTime)
{
	CSimon* simon = CSimon::GetInstance();
	if (simon->isCollisionEnemy)
	{

		simon->simon_Status = COLLISION_ENEMY;
		if (simon->timeCollisionEnemy == 0)
		{
			simon->m_hpSimon -= 1;
		}
		simon->timeCollisionEnemy += deltaTime;
		if (simon->timeCollisionEnemy >= 1)
		{
			simon->m_Dir = simon->m_Dir == LEFT ? RIGHT : LEFT;
			simon->isCollisionEnemy = false;
			simon->timeCollisionEnemy = 0;
			simon->simon_Status = IDLE;

		}
	}
	else
	{
		
			if (CCollision::GetInstance()->AABBCheck(simon->GetBox(), this->GetBox()))
			{

				if (this->enemyType == Zombie)
				{

					//CItemManage::GetInstance()->CreateRandomItem(obj->GetPos());
					simon->cane->updateState(caneState::default);

				}
				if (this->enemyType == BlackLeopard)
				{
					simon->isCollisionEnemy = true;
					simon->m_Dir = this->m_Dir;

				}
			}

		}
	}


void CEnemy::OnCaneCollision()
{
	CCane* cane = CSimon::GetInstance()->cane;
	if (cane->getCurrentFrame() == 2 ||
		cane->getCurrentFrame() == 6 ||
		cane->getCurrentFrame() == 10)
	{
		if (CCollision::GetInstance()->AABBCheck(cane->GetBox(), this->GetBox()))
		{
			this->m_isRemove = true;
			ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
			if (this->enemyItem != ITEM_name::None)
			{
				CItemManage::GetInstance()->CreateItem(this->enemyItem, this->GetPos());
			}
			else
			{
				CItemManage::GetInstance()->CreateRandomItem(this->GetPos());
			}

			/*switch (this->enemyType)
			{
			case ENEMY_type::Zombie:

				break;
			case ENEMY_type::BlackLeopard:
				this->changeState(ENEMY_state::FREE);
				break;
			default:
				break;
			}*/
		}
	}
}
		
	

