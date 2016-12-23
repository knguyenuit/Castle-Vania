#include "BossVampireBat.h"

void CBossVampireBat::Init()
{
	this->enemyType = ENEMY_type::BossVampireBat;
	this->m_Id = this->enemyType;
	this->m_Width = 96;
	this->m_Height = 46;

	this->m_vx = 200;
	this->m_vy = 100;
	//Init Life
	this->m_enemyHP = 16;
	this->m_Dir = Direction::RIGHT;
	this->enemyItem = ITEM_name::MagicalCrystal;
	//init animation
	this->m_startFrame = 0;
	this->m_endFrame = 2;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.3f;
	this->m_increase = 1;
	this->m_totalFrame = 3;
	this->m_column = 3;
	//init Direction
	this->check_arrive_x = this->check_arrive_y = false;
	this->isLeft = this->isRight = this->isUp = this->isDown = false;
}

CBossVampireBat::CBossVampireBat()
{
	this->Init();
}

CBossVampireBat::CBossVampireBat(Vector2 pos)
{
	this->Init();
	this->m_PosDefault = pos;
	this->SetPos(pos);
}


CBossVampireBat::~CBossVampireBat()
{
}

RECT * CBossVampireBat::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}

void CBossVampireBat::Update(float deltaTime)
{
	this->simon->m_BossVampireBatHP = this->m_enemyHP;
	if (this->m_Pos.x <= CSimon::GetInstance()->m_Pos.x&&this->m_State == ENEMY_state::IDLE)
	{
		this->m_State = ENEMY_state::MOVE;
	}
	if (this->m_State == ENEMY_state::MOVE)
	{
		//animate
		this->m_startFrame = 1;
		ChangeFrame(deltaTime);
		this->MoveUpdate(deltaTime);
	}
	this->OnSimonCollision(deltaTime);
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

void CBossVampireBat::MoveUpdate(float deltaTime)
{

	CCamera *camera = CCamera::GetInstance();
	float simonPosX = this->simon->m_Pos.x, simonPosY = this->simon->m_Pos.y;
	float cameraPosX = camera->m_pos.x, cameraPosY = camera->m_pos.y;
	if (this->m_State == ENEMY_state::MOVE)
	{
		switch (this->m_Step)
		{
		case 1:
			if (this->m_isAttacking == false)
			{
				this->m_isAttacking = true;
				int index = rand() % 5;
				this->m_StepPos[0] = Vector2(this->m_PosDefault.x + this->m_pos_x_prepare_attack[index], simon->m_Pos.y + this->m_pos_y_prepare_attack[index]);
				int index2 = rand() % 5;
				while (index == index2)
				{
					index2 = rand() % 5;
				}
				this->m_StepPos[2] = Vector2(this->m_PosDefault.x + this->m_pos_x_prepare_attack[index2], simon->m_Pos.y + this->m_pos_y_prepare_attack[index2]);
			}
			this->m_vy = 150;
			if (this->MoveTo(this->m_StepPos[0], deltaTime) == true)
			{
				this->time_delay_step -= deltaTime;
				if (this->time_delay_step <= 0)
				{
					this->m_StepPos[1] = Vector2(simon->m_Pos.x, simon->m_Pos.y);
					this->m_Step = 2;
					this->time_delay_step = 1.0f;
				}

			}
			break;
		case 2:
			this->m_vx = 300;
			this->m_vy = 200;
			if (this->MoveTo(this->m_StepPos[1], deltaTime) == true)
			{
				this->m_Step = 3;
			}
			break;
		case 3:
			this->m_vx = 250;
			this->m_vy = 150;
			if (this->MoveTo(this->m_StepPos[2], deltaTime) == true)
			{
				this->time_delay_step -= deltaTime;
				if (this->time_delay_step <= 0)
				{
					this->m_isAttacking = false;
					this->m_Step = 1;
					this->time_delay_step = 1.5f;
				}
			}
			break;
		default:
			break;
		}


	}

}

void CBossVampireBat::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	if (normalY == CDirection::ON_DOWN || normalY == CDirection::ON_UP || normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
	{
		if (this->simon->timeCollisionEnemy == 0)
		{
			this->simon->m_hpSimon -= 1;
			this->simon->isArrowKeyLeft = this->simon->isArrowKeyRight = false;
			this->simon->simon_Status = COLLISION_ENEMY;
			this->simon->isCollisionEnemy = true;
		}
	}
}

void CBossVampireBat::OnCaneCollision(float deltaTime)
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
			if (this->m_enemyHP < 0)
			{
				this->m_isRemove = true;
				CItemManage::GetInstance()->CreateItem(this->enemyItem, this->m_PosDefault + Vector2(0, -200));
			}
			else
			{
				return;
			}
		}
	}
}

void CBossVampireBat::OnWeaponCollision(float deltaTime, std::vector<CWeapon*> listWeapon)
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
			this->m_enemyHP -= 2;
			weapon->m_isRemove = true;
			ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
			if (this->m_enemyHP < 0)
			{
				this->m_isRemove = true;
				CItemManage::GetInstance()->CreateItem(this->enemyItem, this->m_PosDefault + Vector2(0, -200));
			}
			else
			{
				return;
			}
		}
	}
}

