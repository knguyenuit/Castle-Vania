#include "EnemyManage.h"

CEnemyManage::CEnemyManage()
{
	CreateEnemy(Zombie, Vector2(400, 60));
	CreateEnemy(BlackLeopard, Vector2(300, 48));
	CreateEnemy(VampireBat, Vector2(200, 48));
}


CEnemyManage::~CEnemyManage()
{
}

void CEnemyManage::CreateEnemy(ENEMY_type enemyType, Vector2 pos)
{
	CEnemy * enemy;
	switch (enemyType)
	{
	case ENEMY_type::Zombie:
		enemy = new CZombie(pos);
		break;
	case ENEMY_type::BlackLeopard:
		enemy = new CBlackLeopard(pos);
		break;
	case ENEMY_type::VampireBat:
		enemy = new CVampireBat(pos);
		break;
	default:
		break;
	}
	this->m_ListEnemy.push_back(enemy);
}
void CEnemyManage::DrawEnemy(CEnemy* enemyObj)
{
	CTexture* Texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(enemyObj->m_Pos.x, enemyObj->m_Pos.y);
	switch (enemyObj->enemyType)
	{
	case Zombie:
		Texture->LoadImageFromFile(ENEMY_ZOMBIE, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case BlackLeopard:
		Texture->LoadImageFromFile(ENEMY_BLACKLEOPARD, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case VampireBat:
		Texture->LoadImageFromFile(ENEMY_VAMPIREBAT, D3DCOLOR_XRGB(255, 255, 255));
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
	if (enemyObj->m_Dir == LEFT)
	{
		this->m_draw->Draw(Texture, enemyObj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		this->m_draw->DrawFlipX(Texture, enemyObj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}

void CEnemyManage::Draw()
{
	for (std::vector<CEnemy*>::iterator it = this->m_ListEnemy.begin(); it != this->m_ListEnemy.end(); ++it)
	{
		CEnemy* enemy = *it;
		DrawEnemy(enemy);
	}
	
}

void CEnemyManage::Update(float deltaTime)
{
	if (!this->m_ListEnemy.empty())
	{
		for (std::vector<CEnemy*>::iterator it = this->m_ListEnemy.begin(); it != this->m_ListEnemy.end(); ++it)
		{
			CEnemy* enemy = *it;
			if (enemy!=NULL && enemy->m_isRemove==false)
			{
				enemy->Update(deltaTime);
			}
			if (enemy->m_isRemove)
			{
				it = this->m_ListEnemy.erase(it);
			}
		}
	}
	/*this->currentEnemy->Update(deltaTime);
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
	}*/
	
	/*this->currentEnemy->m_Pos.x -= this->currentEnemy->m_vx * deltaTime;
	if (this->currentEnemy->m_Pos.x <= 50)
	{
		this->currentEnemy->m_Pos.x += this->currentEnemy->m_vx * deltaTime;
	}*/
}
