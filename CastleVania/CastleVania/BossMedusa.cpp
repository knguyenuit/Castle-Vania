#include "BossMedusa.h"



CBossMedusa::CBossMedusa()
{
	this->Init();
}

CBossMedusa::CBossMedusa(Vector2 pos)
{
	this->m_PosDefault = this->m_Pos = pos;
	this->Init();

}

CBossMedusa::~CBossMedusa()
{
}

void CBossMedusa::Init()
{
	this->enemyType = ENEMY_type::BossMedusa;
	this->m_State = ENEMY_state::IDLE;
	this->m_Id = this->enemyType;
	this->m_Width = 65;
	this->m_Height = 64;

	this->m_vx = 200;
	this->m_vy = 100;
	//Init Life
	this->m_enemyHP = 16;
	this->m_Dir = Direction::RIGHT;
	this->enemyItem = ITEM_name::MagicalCrystal;
	//init animation
	this->m_startFrame = 4;
	this->m_endFrame = 4;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.3f;
	this->m_increase = 1;
	this->m_totalFrame = 5;
	this->m_column = 5;
	//init Direction
	this->current_step_pos = this->m_PosDefault;
	this->check_arrive_x = this->check_arrive_y = false;
	this->isLeft = this->isRight = this->isUp = this->isDown = false;

}

RECT * CBossMedusa::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}

void CBossMedusa::MoveUpdate(float deltaTime)
{
	float simonPosX = this->simon->m_Pos.x, simonPosY = this->simon->m_Pos.y;
	float cameraPosX = camera->m_pos.x, cameraPosY = camera->m_pos.y;
	if (this->time_delay_step == 0.3f)
	{
		if (this->m_Pos.x > this->simon->m_Pos.x)
		{
			this->m_Dir = LEFT;
			if (this->m_Step % 2 == 0)
			{
				this->next_step_pos = this->current_step_pos + Vector2(-64, 16);
			}
			else
			{
				this->next_step_pos = this->current_step_pos + Vector2(-64, -16);
			}

		}
		else
		{
			this->m_Dir = RIGHT;
			if (this->m_Step % 2 == 0)
			{
				this->next_step_pos = this->current_step_pos + Vector2(64, 16);
			}
			else
			{
				this->next_step_pos = this->current_step_pos + Vector2(64, -16);
			}
		}
	}

	if (this->MoveTo(this->next_step_pos, deltaTime) == true)
	{
		if (this->m_Pos.x > this->simon->m_Pos.x)
		{
			this->m_Dir = LEFT;
		}
		else
		{
			this->m_Dir = RIGHT;
		}
		this->time_delay_step -= deltaTime;
		if (this->time_delay_step <= 0)
		{
			if (this->m_Step % 3 == 0)
			{
				if (this->m_Step % 2 == 0)
				{
					CSnakeManage::GetInstance()->CreateSnake(this->m_Pos + Vector2(0,-32), this->m_Dir);
				}
				else
				{
					CSnakeManage::GetInstance()->CreateSnake(this->m_Pos + Vector2(0, -16), this->m_Dir);
				}
				
			}

			this->m_Step += 1;
			this->current_step_pos = this->m_Pos;
			this->time_delay_step = 0.3f;
		}
	}
	CSnakeManage::GetInstance()->Update(deltaTime);

}

void CBossMedusa::Update(float deltaTime)
{
	if (this->simon->isKey_L == true)
	{
		this->simon->isKey_L = false;
		this->m_enemyHP -= 1;
	}
	this->simon->m_BossVampireBatHP = this->m_enemyHP;
	if (this->m_enemyHP <= 0)
	{
		this->m_isRemove = true;
		CItemManage::GetInstance()->CreateItem(this->enemyItem, this->m_PosDefault + Vector2(0, -200));
	}

	if (this->m_Pos.x <= CSimon::GetInstance()->m_Pos.x&&this->m_State == ENEMY_state::IDLE)
	{
		this->m_State = ENEMY_state::MOVE;
	}
	if (this->m_State == ENEMY_state::MOVE)
	{
		//animate
		this->m_startFrame = 0;
		this->m_endFrame = 3;
		ChangeFrame(deltaTime);
		this->MoveUpdate(deltaTime);
	}
	if (this->m_State != ENEMY_state::IDLE)
	{
		if (this->simon->isUnAvailable == false)
		{
			this->OnSimonCollision(deltaTime);
		}

		this->OnWeaponCollision(deltaTime, CWeaponManage::GetInstance()->m_weaponList);
		if (this->simon->cane->m_checkActive == true)
		{
			this->OnCaneCollision(deltaTime);
		}
		else
		{
			this->simon->cane->m_timeCollisionEnemy = 0;
		}
	}
	
}

void CBossMedusa::OnSimonCollision(float deltaTime)
{
	if (CCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
	{
		if (this->simon->timeCollisionEnemy == 0)
		{
			this->simon->simon_Status = SIMON_status::IDLE;
			this->simon->UpdateStatus(deltaTime);
			this->simon->timeCollisionEnemy += deltaTime;
			this->simon->m_hpSimon -= 1;
			this->simon->isArrowKeyLeft = this->simon->isArrowKeyRight = false;
			this->simon->simon_Status = COLLISION_ENEMY;
			this->simon->UpdateStatus(deltaTime);
			this->simon->isCollisionEnemy = true;
			if (this->simon->m_hpSimon <= 1)
			{
				this->changeState(ENEMY_state::DIE);
			}
		}
	}
}

void CBossMedusa::OnCaneCollision(float deltaTime)
{
	if (this->simon->cane->getCurrentFrame() == 2 ||
		this->simon->cane->getCurrentFrame() == 6 ||
		this->simon->cane->getCurrentFrame() == 10)
	{
		if (CCollision::GetInstance()->AABBCheck(this->simon->cane->GetBox(), this->GetBox()))
		{
			if (this->simon->cane->m_timeCollisionEnemy == 0)
			{
				this->m_enemyHP -= 2;
				this->simon->cane->m_timeCollisionEnemy += deltaTime;
			}
			this->simon->isAttackEnemy = true;
			if (this->simon->isAttackEnemy == true)
			{
				ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
				CSimon::GetInstance()->isAttackEnemy = false;
			}
		}
	}
}

void CBossMedusa::OnWeaponCollision(float deltaTime, std::vector<CWeapon*> listWeapon)
{
	/*CDirection normalX;
	CDirection normalY;
	float timeCollision;*/
	for (std::vector<CWeapon*>::iterator it = listWeapon.begin(); it != listWeapon.end(); it++)
	{
		CWeapon* weapon = *it;
		//timeCollision = COnCollision::GetInstance()->SweepAABB(weapon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (CCollision::GetInstance()->AABBCheck(weapon->GetBox(), this->GetBox()))
		{
			this->m_enemyHP -= 2;
			weapon->m_isRemove = true;
			ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
		}
	}
}

