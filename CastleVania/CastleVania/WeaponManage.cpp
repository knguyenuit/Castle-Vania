#include "WeaponManage.h"



CWeaponManage::CWeaponManage()
{
}


CWeaponManage::~CWeaponManage()
{
}

void CWeaponManage::CreateWeapon(WEAPON_name weaponName)
{
	CWeapon* weapon = new CWeapon(weaponName,CSimon::GetInstance()->m_Pos);
	this->m_weaponList.push_back(weapon);
}

void CWeaponManage::Update(float deltaTime)
{
	CSimon* simon = CSimon::GetInstance();
	if (simon->isWeaponAttacking)
	{
		this->CreateWeapon(simon->m_currentWeapon);
		simon->isWeaponAttacking = false;
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
		texture->LoadImageFromFile(WEAPON_AXE,D3DCOLOR_XRGB(255,255,255));
		break;
	case WEAPON_name::Boomerang:
		texture->LoadImageFromFile(WEAPON_BOOMERANG, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case WEAPON_name::Dagger:
		texture->LoadImageFromFile(WEAPON_DAGGER, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case WEAPON_name::FireBomb2:
		texture->LoadImageFromFile(WEAPON_FIREBOMB2, D3DCOLOR_XRGB(255, 255, 255));
		break;
	default:
		break;
	}
	CDrawObject::GetInstance()->m_draw->Draw(texture, weapon->GetRectRS(),pos, D3DCOLOR_XRGB(255, 255, 255), true);
}

void CWeaponManage::Draw()
{
	if (!this->m_weaponList.empty())
	{
		for(std::vector<CWeapon*>::iterator it = this->m_weaponList.begin(); it!=this->m_weaponList.end(); ++it)
		{
			CWeapon * weapon = *it;
			this->DrawWeapon(weapon);
		}
	}
}
