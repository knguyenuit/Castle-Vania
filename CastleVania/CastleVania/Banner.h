#ifndef __CBANNER_H__
#define __CBANNER_H__
#include "BaseGameObject.h"
#include "Sprite.h"
#include "Singleton.h"
#include "Simon.h"


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
	CSprite* m_Draw;
	CTexture* m_TextureBanner;
	CTexture* m_textureHpPlayer;

public:
	D3DXVECTOR3 posHpSimon;
	int m_hpSimon;
};

#endif // !__CBANNER_H__