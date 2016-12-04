#include "EnemyManage.h"
#include "Zombie.h"
#include "Resources.h"

CEnemyManage::CEnemyManage()
{
	this->currentEnemy = new CZombie(Vector2(400,400));
}


CEnemyManage::~CEnemyManage()
{
}

void CEnemyManage::CreateEnemy(ENEMY_type enemyType, Vector2 pos)
{
	switch (enemyType)
	{
	case ENEMY_type::Zombie:
		this->currentEnemy = new CZombie();
		break;
	default:
		break;
	}
}
void CEnemyManage::DrawEnemy(CEnemy* enemyObj)
{
	CTexture* Texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(enemyObj->GetPos().x, enemyObj->GetPos().y);
	switch (enemyObj->enemyType)
	{
	case Zombie:
		Texture->LoadImageFromFile(ENEMY_ZOMBIE, D3DCOLOR_XRGB(255, 0, 255));
		if (enemyObj->m_Dir == LEFT)
		{
			this->m_draw->Draw(Texture, enemyObj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		}
		else
		{
			this->m_draw->DrawFlipX(Texture, enemyObj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		}
		break;
	case BlackLeopard:
		break;
	case VampireBat:
		break;
	case Medusa:
		break;
	case FishMan:
		break;
	case AxeMan:
		break;
	case DragonSkullCanon:
		break;
	case BlackKnight:
		break;
	case WhiteSkeleton:
		break;
	case Ghost:
		break;
	case FireBall:
		break;
	case Bullet:
		break;
	case BossLevel1:
		break;
	case BossLevel2:
		break;
	default:
		break;
	}
}

void CEnemyManage::Draw()
{
	DrawEnemy(this->currentEnemy);
}

void CEnemyManage::Update(float deltaTime)
{
	this->currentEnemy->Update(deltaTime);
	if (this->currentEnemy->GetPos().x<=100)
	{
		this->currentEnemy->m_Dir = RIGHT;
	} 
	if(this->currentEnemy->m_Pos.x>=400)
	{
		this->currentEnemy->m_Dir = LEFT;
	}
	if (this->currentEnemy->m_Dir==LEFT)
	{
		this->currentEnemy->SetPos(Vector2(this->currentEnemy->GetPos().x - this->currentEnemy->m_vx*deltaTime, this->currentEnemy->GetPos().y));
	} 
	else 
	{
		this->currentEnemy->SetPos(Vector2(this->currentEnemy->GetPos().x + this->currentEnemy->m_vx*deltaTime, this->currentEnemy->GetPos().y));
	}
	
	/*this->currentEnemy->m_Pos.x -= this->currentEnemy->m_vx * deltaTime;
	if (this->currentEnemy->m_Pos.x <= 50)
	{
		this->currentEnemy->m_Pos.x += this->currentEnemy->m_vx * deltaTime;
	}*/
}
