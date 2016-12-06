#include "EnemyManage.h"
#include "ItemManage.h"
CEnemyManage::CEnemyManage()
{
	CreateEnemy(Zombie, Vector2(800, 60));
	CreateEnemy(BlackLeopard, Vector2(1000, 200));
	CreateEnemy(Zombie, Vector2(1100, 60));
	CreateEnemy(VampireBat, Vector2(1200, 80));
}
CEnemyManage::~CEnemyManage()
{
}

void CEnemyManage::Update(float deltaTime)
{
	if (CSimon::GetInstance()->cane->m_checkActive)
	{
		CEnemyManage::OnCaneCollision();
	}
	CEnemyManage::OnSimonCollision(deltaTime);
	if (!this->m_ListEnemy.empty())
	{
		for (std::vector<CEnemy*>::iterator it = this->m_ListEnemy.begin();
			it != this->m_ListEnemy.end(); ++it)
		{
			CEnemy* enemy = *it;
			if (enemy != NULL && enemy->m_isRemove == false)
			{
				enemy->Update(deltaTime);
			}
			if (enemy->m_isRemove)
			{
				it = this->m_ListEnemy.erase(it);
					break;

			}
		}
	}
}
void CEnemyManage::OnCaneCollision()
{
	CCane* cane = CSimon::GetInstance()->cane;
	if (!this->m_ListEnemy.empty())
	{
		for (std::vector<CEnemy*>::iterator it = this->m_ListEnemy.begin();
			it != this->m_ListEnemy.end();
			++it)
		{
			CEnemy* enemy = *it;
				if (cane->getCurrentFrame() == 2 ||
					cane->getCurrentFrame() == 6 ||
					cane->getCurrentFrame() == 10)
				{
					if (CCollision::GetInstance()->AABBCheck(cane->GetBox(), enemy->GetBox()))
					{
						enemy->m_isRemove = true;
						CItemManage::GetInstance()->CreateRandomItem(enemy->GetPos());
						switch (enemy->enemyType)
						{
						case ENEMY_type::Zombie:

							break;
						case ENEMY_type::BlackLeopard:
							enemy->changeState(ENEMY_state::FREE);
							break;
						default:
							break;
						}
					}
				}
		}
	}
		
}
void CEnemyManage::OnSimonCollision(float deltaTime)
{
	CSimon* simon = CSimon::GetInstance();
	for (std::vector<CEnemy*>::iterator it = this->m_ListEnemy.begin();
		it != this->m_ListEnemy.end();
		++it)
	{
		CEnemy* obj = *it;
		if (CCollision::GetInstance()->AABBCheck(simon->GetBox(), obj->GetBox()))
		{
			if (obj->enemyType == Zombie)
			{
				
						//CItemManage::GetInstance()->CreateRandomItem(obj->GetPos());
						simon->cane->updateState(caneState::default);
				
			}
			if (obj->enemyType == BlackLeopard)
			{
				simon->UpdateStatus(deltaTime, COLLISION_ENEMY);
			}
		}

	}
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


