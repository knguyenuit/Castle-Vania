#ifndef __CBANNER_H__
#define __CBANNER_H__
#include "BaseGameObject.h"
#include "Sprite.h"
#include "Singleton.h"
#include "Simon.h"
#include "DrawFont.h"
#include "BossVampireBat.h"


class CBanner : public CBaseGameObject
{
	
public:
	void Init();
	void Update(float deltaTime);
	void DrawBannerBG();
	void DrawBannerProperty(); //ve cac thanh phan trong banner
	RECT* GetRectRS();
	CBanner();
	~CBanner();
public:
	CDrawFont* m_font;
	CSprite* m_Draw;
	CTexture* m_TextureBanner;
	CTexture* m_textureHpPlayer;
	CTexture* m_textureHpEnemy;
	CTexture* m_textureWeapon;
	int m_Point;
	int m_countTime = 0;
	float m_deepTime = 0;

public:
	D3DXVECTOR3 posHpSimon;
	D3DXVECTOR3 posHpEnemy;
	D3DXVECTOR3 posWeapon;
	D3DXVECTOR3 posPoint;


	//rect
	RECT* m_rectPoint;
	RECT* m_rectEnemyHP;
	RECT* m_rectTime;
	RECT* m_rectState;
	RECT* m_rectCountHeart;
	RECT* m_rectCountLife;
	
	//property
	int m_hpSimon;
	int m_enemyHP;
	int m_countHeart;
	int m_curState;
	int m_countLife;
	int m_Score;
	WEAPON_name m_typeWeapon;
};

#endif // !__CBANNER_H__