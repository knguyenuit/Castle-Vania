#include "Weapon.h"



CWeapon::CWeapon()
{
	this->m_WeaponName = WEAPON_name::None;
	this->Init();
}
CWeapon::CWeapon(WEAPON_name weaponName, Vector2 pos)
{
	this->m_WeaponName = weaponName;
	this->m_PosDefault = this->m_Pos = pos;
	this->Init();
}
void CWeapon::InitAnimate(int totalFrame, int column, int startFrame, int endFrame)
{
	this->m_totalFrame = totalFrame;
	this->m_column = column;
	this->m_startFrame = startFrame;
	this->m_endFrame = endFrame;
	this->m_increase = 1;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
}
void CWeapon::Init() {
	this->m_time_life = 0.0f;
	this->m_isRemove = false;
	this->m_Id = static_cast<int>(this->m_WeaponName);
	this->m_Dir = CSimon::GetInstance()->m_Dir;
	this->m_vxDefault = this->m_vx = 200;
	switch (this->m_WeaponName)
	{

	case WEAPON_name::Axe:
		this->m_Width = 30;
		this->m_Height = 28;
		//move
		this->m_vxDefault = this->m_vx = 250;
		this->m_vyDefault = this->m_vy = 400;
		this->m_a = 1000.0f;
		//animate
		this->InitAnimate(4, 4, 0, 3);
		break;
	case WEAPON_name::Boomerang:
		this->m_Width = 26;
		this->m_Height = 28;
		//move

		//Init Animation
		this->InitAnimate(3, 3, 0, 2);
		break;
	case WEAPON_name::Dagger:
		this->m_Width = 32;
		this->m_Height = 18;
		this->InitAnimate(1, 1, 0, 0);
		break;
	case WEAPON_name::FireBomb:
		this->m_Width = 32;
		this->m_Height = 26;
		//move
		this->m_vxDefault = this->m_vx = 250;
		this->m_vyDefault = this->m_vy = 400;
		this->m_a = 1000.0f;
		this->InitAnimate(1, 1, 0, 0);
		break;
	default:
		break;
	}


}
void CWeapon::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	this->ChangeFrame(deltaTime);
	this->m_time_life += deltaTime;
	if (this->m_time_life >= 10.0f)
	{
		this->m_isRemove = true;
	}

}
void CWeapon::MoveUpdate(float deltaTime)
{

	switch (this->m_WeaponName)
	{
	case WEAPON_name::Dagger:
		this->m_Pos.x =
			(this->m_Dir == Direction::LEFT) ?
			this->m_Pos.x - this->m_vx * deltaTime :
			this->m_Pos.x + this->m_vx * deltaTime;
		break;
	case WEAPON_name::FireBomb:
	case WEAPON_name::Axe:

		if (this->m_Dir == Direction::LEFT)
		{
			this->m_vx = -this->m_vxDefault;
		}
		else
		{
			this->m_vx = this->m_vxDefault;
		}
		this->m_Pos.x += this->m_vx * deltaTime;

		this->m_vy -= this->m_a * deltaTime;
		this->m_Pos.y += this->m_vy * deltaTime;
		break;
	case WEAPON_name::Boomerang:
		if (this->m_Dir == Direction::RIGHT) {
			if (this->m_Pos.x <= this->m_PosDefault.x + 300 && this->boomerang_turn_back == false)
			{
				this->m_Pos.x += this->m_vx * deltaTime;
			}
			else
			{
				this->boomerang_turn_back = true;
				this->m_Pos.x -= this->m_vx * deltaTime;
				this->m_isRemove =
					(
						CCollision::GetInstance()->AABBCheck(this->GetBox(), CSimon::GetInstance()->GetBox()) ||
						this->m_Pos.x <= CCamera::GetInstance()->m_pos.x
						) ? true : false;
				if (this->m_isRemove) break;
			}
		}
		else
		{
			//LEFT
			if (this->m_Pos.x >= this->m_PosDefault.x - 300 && this->boomerang_turn_back == false)
			{
				this->m_Pos.x -= this->m_vx * deltaTime;
			}
			else
			{
				this->boomerang_turn_back = true;
				this->m_Pos.x += this->m_vx * deltaTime;
				this->m_isRemove =
					(
						CCollision::GetInstance()->AABBCheck(this->GetBox(), CSimon::GetInstance()->GetBox()) ||
						this->m_Pos.x >= (CCamera::GetInstance()->m_pos.x + 600)
						) ? true : false;
				if (this->m_isRemove) break;
			}
		}

		break;
	default:
		this->m_vxDefault = this->m_vx = 200;
		this->m_Pos.x =
			(this->m_Dir == Direction::LEFT) ?
			this->m_Pos.x - this->m_vx * deltaTime :
			this->m_Pos.x + this->m_vx * deltaTime;
		break;
	}
}

Box CWeapon::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 2, this->m_Height - 2);
}

RECT * CWeapon::GetRectRS()
{
	/*RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;*/
	return this->UpdateRectResource(m_Height, m_Width);
}


CWeapon::~CWeapon()
{
}
