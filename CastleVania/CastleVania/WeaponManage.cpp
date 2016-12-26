#include "WeaponManage.h"



CWeaponManage::CWeaponManage()
{
}


CWeaponManage::~CWeaponManage()
{
}

void CWeaponManage::CreateWeapon(WEAPON_name weaponName)
{
	CWeapon* weapon = new CWeapon(weaponName, CSimon::GetInstance()->m_Pos + Vector2(5, 12));
	this->m_weaponList.push_back(weapon);
}

void CWeaponManage::Update(float deltaTime)
{
	if (this->simon->timeDelayWeaponAttacking < 0.3f)
	{
		this->simon->timeDelayWeaponAttacking -= deltaTime;
		if (this->simon->timeDelayWeaponAttacking <= 0)
		{
			this->simon->timeDelayWeaponAttacking = 0.3f;
			if (this->simon->isSit == true)
			{
				this->simon->simon_Status = SIMON_status::SIT;
			}
			else
			{
				this->simon->simon_Status = SIMON_status::IDLE;
			}
			
			this->simon->UpdateStatus(deltaTime);
		}
	}
	if (this->simon->isWeaponAttacking == true)
	{
		if (this->simon->timeDelayWeaponAttacking == 0.3f)
		{
			this->CreateWeapon(simon->m_currentWeapon);
			ManageAudio::GetInstance()->playSound(TypeAudio::Using_Whip);
		}
		this->simon->timeDelayWeaponAttacking -= deltaTime;
		this->simon->isWeaponAttacking = false;
		if (this->simon->isMoveJump == false)
		{
			this->simon->simon_Status = SIMON_status::WEAPON_ATTACK;
			this->simon->UpdateStatus(deltaTime);
		}
	}
	if (!this->m_weaponList.empty())
	{
		for (std::vector<CWeapon*>::iterator it = this->m_weaponList.begin(); it != this->m_weaponList.end(); ++it)
		{
			CWeapon * weapon = *it;
			weapon->Update(deltaTime);
			if (weapon->m_isRemove)
			{
				this->m_weaponList.erase(it);
				break;
			}
		}
	}


}

void CWeaponManage::DrawWeapon(CWeapon * weapon)
{
	WEAPON_name weaponName = weapon->m_WeaponName;
     CTexture* texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(weapon->GetPos().x, weapon->GetPos().y);
	switch (weaponName)
	{
	case WEAPON_name::Axe:
		texture->LoadImageFromFile(WEAPON_AXE, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case WEAPON_name::Boomerang:
		texture->LoadImageFromFile(WEAPON_BOOMERANG, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case WEAPON_name::Dagger:
		texture->LoadImageFromFile(WEAPON_DAGGER, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case WEAPON_name::FireBomb:
		texture->LoadImageFromFile(WEAPON_FIREBOMB, D3DCOLOR_XRGB(255, 0, 255));
		break;
		
	default:
		break;
	}
	if (CSimon::GetInstance()->m_Dir == RIGHT)
	{
		CDrawObject::GetInstance()->m_draw->Draw(texture, weapon->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		CDrawObject::GetInstance()->m_draw->DrawFlipX(texture, weapon->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}

void CWeaponManage::Draw()
{
	if (!this->m_weaponList.empty())
	{
		for (std::vector<CWeapon*>::iterator it = this->m_weaponList.begin(); it != this->m_weaponList.end(); ++it)
		{
			CWeapon * weapon = *it;
			this->DrawWeapon(weapon);
		}
	}
}

