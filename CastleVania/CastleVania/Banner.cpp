#include "Banner.h"
#include "Resources.h"
#include "Camera.h"


void CBanner::Init()
{
	this->m_Width = 510;
	this->m_Height = 79;
	this->m_Id = 100;
	this->m_Pos = Vector2(200, 425);

	m_font = new CDrawFont();
	m_TextureBanner = new CTexture();
	m_TextureBanner->LoadImageFromFile(BANNER, D3DCOLOR_XRGB(255, 0, 255));
	m_textureHpPlayer = new CTexture();
	m_textureWeapon = new CTexture();
	m_textureHpPlayer->LoadImageFromFile(SIMON_HP, D3DCOLOR_XRGB(255, 0, 255));
	m_textureHpEnemy = new CTexture();
	m_textureHpEnemy->LoadImageFromFile(ENEMY_HP, D3DCOLOR_XRGB(255, 0, 255));
	this->posHpSimon = D3DXVECTOR3(122, 48, 0);
	this->posHpEnemy = D3DXVECTOR3(122, 70, 0);
	this->posWeapon = D3DXVECTOR3(308, 50, 0);
	this->posPoint = D3DXVECTOR3(122, 30, 0);

	this->m_hpSimon = CSimon::GetInstance()->m_hpSimon;

	//rect
	//rect point
	m_rectPoint = new RECT();
	m_rectPoint->left = 122;
	m_rectPoint->right = 192;
	m_rectPoint->top = 14;
	m_rectPoint->bottom = 60;

	//rect enemy hp
	m_rectEnemyHP = new RECT();
	m_rectEnemyHP->left = 122;
	m_rectEnemyHP->right = 192;
	m_rectEnemyHP->top = 70;
	m_rectEnemyHP->bottom = 100;

	//rect time
	m_rectTime = new RECT();
	m_rectTime->left = 300;
	m_rectTime->right = 340;
	m_rectTime->top = 14;
	m_rectTime->bottom = 60;
	
	//rect state
	m_rectState = new RECT();
	m_rectState->left = 470;
	m_rectState->right = 500;
	m_rectState->top = 14;
	m_rectState->bottom = 35;

	//rect count heart
	m_rectCountHeart = new RECT();
	m_rectCountHeart->left = 480;
	m_rectCountHeart->right = 510;
	m_rectCountHeart->top = 40;
	m_rectCountHeart->bottom = 60;

	//rect count life
	m_rectCountLife = new RECT();
	m_rectCountLife->left = 480;
	m_rectCountLife->right = 510;
	m_rectCountLife->top = 70;
	m_rectCountLife->bottom = 90;

	//m_enemyHP = 16;
}

void CBanner::Update(float deltaTime)
{
	//ve banner theo camera
	this->m_deepTime += deltaTime;
	this->m_countTime = (int)m_deepTime;
		this->m_Pos.x = CCamera::GetInstance()->m_pos.x + 265;
		//cap nhat mau cua simon
		this->m_hpSimon = CSimon::GetInstance()->m_hpSimon;
		this->m_enemyHP = CSimon::GetInstance()->m_BossVampireBatHP;
		this->m_countHeart = CSimon::GetInstance()->m_countHeart;
		this->m_curState = CSimon::GetInstance()->m_currentLevel;
		this->m_countLife = CSimon::GetInstance()->m_countLife;
		this->m_Score = CSimon::GetInstance()->m_Score;
		this->m_typeWeapon = CSimon::GetInstance()->m_currentWeapon;

		switch (this->m_typeWeapon)
		{
		case WEAPON_name::Axe:
			this->m_textureWeapon->LoadImageFromFile(AXE_BANNER, D3DCOLOR_XRGB(255, 0, 255));
			break;
		case WEAPON_name::Boomerang:
			this->m_textureWeapon->LoadImageFromFile(BOOMERANG_BANNER, D3DCOLOR_XRGB(255, 0, 255));
			break;
		case WEAPON_name::Dagger:
			this->m_textureWeapon->LoadImageFromFile(WEAPON_DAGGER, D3DCOLOR_XRGB(255, 0, 255));
			break;
		case WEAPON_name::FireBomb:
			this->m_textureWeapon->LoadImageFromFile(FIRE_BOMB_BANNER, D3DCOLOR_XRGB(255, 0, 255));
			break;
		case WEAPON_name::Watch:
			this->m_textureWeapon->LoadImageFromFile(WEAPON_WATCH, D3DCOLOR_XRGB(255, 0, 255));
			break;
		case WEAPON_name::None:
			this->m_textureWeapon->LoadImageFromFile(NONE_WEAPON_BANNER, D3DCOLOR_XRGB(255, 0, 255));
			break;
		}
}

void CBanner::DrawBannerBG()
{
	
	Vector3 pos = Vector3();
	RECT* rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	pos = CCamera::GetInstance()->GetPointTransform(this->m_Pos.x, this->m_Pos.y);
	this->m_Draw->Draw(m_TextureBanner, GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
}

void CBanner::DrawBannerProperty()
{
	D3DXVECTOR3 positionHpSimon = this->posHpSimon;
	D3DXVECTOR3 positionHpEnemy = this->posHpEnemy;
	for (int i = 0; i < this->m_hpSimon; i++)
	{
		this->m_Draw->Draw(this->m_textureHpPlayer, NULL, positionHpSimon);
		positionHpSimon.x += 8;
	}
	for (int i = 0; i < this->m_enemyHP; i++)
	{
		this->m_Draw->Draw(this->m_textureHpEnemy, NULL, positionHpEnemy);
		positionHpEnemy.x += 8;
	}
	this->m_Draw->Draw(this->m_textureWeapon, NULL, posWeapon);
	//score
	m_font->DrawNumber(m_Score, m_rectPoint);
	//time
	m_font->DrawNumber(m_countTime, m_rectTime);
	//state
	m_font->DrawNumber(m_curState, m_rectState);
	//count heart
	m_font->DrawNumber(m_countHeart, m_rectCountHeart);
	//count life
	m_font->DrawNumber(m_countLife, m_rectCountLife);
}

RECT * CBanner::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}

CBanner::CBanner()
{
	Init();
}


CBanner::~CBanner()
{
}
