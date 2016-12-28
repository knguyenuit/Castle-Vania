#include "Enemy.h"

CEnemy::CEnemy()
{
	CEnemy::Init();
}

void CEnemy::Init()
{
	this->m_State = ENEMY_state::IDLE;
	this->m_isRemove = false;
	//init Direction (for MoveTo() )
	this->check_arrive_x = this->check_arrive_y = false;
	this->isLeft = this->isRight = this->isUp = this->isDown = false;
	this->InitAnimation();
}

void CEnemy::InitAnimation()
{
	this->m_vx = 100;
	this->m_vy = 200;
	
}

void CEnemy::Update(float deltaTime)
{
	if (this->simon->isUnAvailable == false)
	{
		OnSimonCollision(deltaTime);
	}
	
	if (CSimon::GetInstance()->cane->m_checkActive)
	{
		OnCaneCollision();
	}
	OnWeaponCollision(deltaTime, CWeaponManage::GetInstance()->m_weaponList);
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
		if (isChangeDir)
		{
			if (m_Dir == Direction::LEFT)
			{
				m_Dir = Direction::RIGHT;
				isChangeDir = false;
			}
			else
			{
				m_Dir = Direction::LEFT;
				isChangeDir = false;
			}
		}
		if (this->m_Dir == LEFT)
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
	case ENEMY_state::DIE:
		this->m_isRemove = true;
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
	if (CCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
	{
		if (this->enemyType == ENEMY_type::SmallLight)
		{
			return;
		}
		else
		{
			if (this->simon->timeCollisionEnemy == 0)
			{
				this->simon->simon_Status = SIMON_status::IDLE;
				this->simon->UpdateStatus(deltaTime);
				this->simon->timeCollisionEnemy += deltaTime;
				this->simon->m_hpSimon -= 1;
				this->simon->isArrowKeyLeft = this->simon->isArrowKeyRight = false;
				this->simon->simon_Status = COLLISION_ENEMY;
				this->isSimonCollision = true;
				this->simon->UpdateStatus(deltaTime);
				if (this->simon->m_hpSimon <= 1)
				{
					this->changeState(ENEMY_state::DIE);
				}
				
			}
			

		}
	}
}


void CEnemy::OnCaneCollision()
{
	if (this->simon->cane->getCurrentFrame() == 2 ||
		this->simon->cane->getCurrentFrame() == 6 ||
		this->simon->cane->getCurrentFrame() == 10)
	{
		if (CCollision::GetInstance()->AABBCheck(this->simon->cane->GetBox(), this->GetBox()))
		{
			CAnimationObjectManage::GetInstance()->CreateAnimation(Animation_object::FireOn, this->m_Pos);
			this->simon->m_Score += 10;
			this->m_isRemove = true;
			CSimon::GetInstance()->isAttackEnemy = true;
			if (CSimon::GetInstance()->isAttackEnemy)
			{
				ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
				CSimon::GetInstance()->isAttackEnemy = false;
			}
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

void CEnemy::OnWeaponCollision(float deltaTime, std::vector<CWeapon*> listWeapon)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	for (std::vector<CWeapon*>::iterator it = listWeapon.begin(); it != listWeapon.end(); it++)
	{
		CWeapon* weapon = *it;
		timeCollision = COnCollision::GetInstance()->SweepAABB(weapon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalX == ON_LEFT || normalX == ON_RIGHT || normalY == ON_UP || normalY == ON_DOWN)
		{

			m_isRemove = true;
			this->simon->m_Score += 10;
			weapon->m_isRemove = true;
			CItemManage::GetInstance()->CreateRandomItem(this->GetPos());
			ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
		}
	}
}



