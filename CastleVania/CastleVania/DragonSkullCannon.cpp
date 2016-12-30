#include "DragonSkullCannon.h"



CDragonSkullCannon::CDragonSkullCannon()
{
}

CDragonSkullCannon::CDragonSkullCannon(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
}


CDragonSkullCannon::~CDragonSkullCannon()
{
}

void CDragonSkullCannon::Init()
{
	this->enemyType = ENEMY_type::DragonSkullCanon;
	this->m_Id = this->enemyType;
	this->m_State = ENEMY_state::IDLE;
	this->m_Dir = LEFT;
	this->m_Width = 32;
	this->m_Height = 64;
	this->m_vx = 0;
	this->m_vy = 0;
	posIntanceFireBall1 = Vector2(this->m_Pos.x, this->m_Pos.y);
	posIntanceFireBall2 = Vector2(this->m_Pos.x, this->m_Pos.y + 20);
}

void CDragonSkullCannon::Update(float deltaTime)
{
	timeCountIntanceFireBall += deltaTime;
	if (timeCountIntanceFireBall >= 1)
	{
		posIntanceFireBall1 = Vector2(this->m_Pos.x, this->m_Pos.y);
		posIntanceFireBall2 = Vector2(this->m_Pos.x, this->m_Pos.y - 50);
		CFireBallManage::GetInstance()->CreateFireBall(posIntanceFireBall1, RIGHT);
		CFireBallManage::GetInstance()->CreateFireBall(posIntanceFireBall2, LEFT);
		timeCountIntanceFireBall = 0;
	}
	CFireBallManage::GetInstance()->Update(deltaTime);
	if (CSimon::GetInstance()->cane->m_checkActive)
	{
		OnCaneCollision();
	}
	CFireBallManage::GetInstance()->Draw();
	OnWeaponCollision(deltaTime, CWeaponManage::GetInstance()->m_weaponList);
}

void CDragonSkullCannon::OnCaneCollision()
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
				CFireBallManage::GetInstance()->m_ListFireBall.clear();
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