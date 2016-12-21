#ifndef __WEAPONMANAGE_H__
#define __WEAPONMANAGE_H__
#include "Singleton.h"
#include "Weapon.h"
#include "Simon.h"
#include "DrawObject.h"

class CWeaponManage:
	public CSingleton<CWeaponManage>
{
	friend class CSingleton<CWeaponManage>;
public:
	CWeaponManage();
	~CWeaponManage();
public:
	std::vector<CWeapon*> m_weaponList; //danh sach weapon da duoc danh ra
public: //cac phuong thuc tao weapon
	void CreateWeapon(WEAPON_name weaponName);
public: //cac phuong thuc update weapon
	void Update(float deltaTime);
	void DrawWeapon(CWeapon * weapon); //ve ra 1 weapon
	void Draw(); //ve ra m_weaponList
	
};

#endif // !__WEAPONMANAGE_H__
