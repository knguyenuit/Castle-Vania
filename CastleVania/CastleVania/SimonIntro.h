#pragma once
#include "BaseGameObject.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Move.h"
class CSimonIntro : public CBaseGameObject, public CAnimation, public CMove
{
public:
	CSimonIntro();
	~CSimonIntro();
public:
	CTexture* m_imageCurr;
	CSprite* m_drawImg;
public:
	Box GetBox();
	RECT* GetBound();
	RECT* GetRectRS();
public:
	void Init();
	void InitAnimation();
	void Update(float deltaTime);
	void MoveUpdate(float deltaTime);
	void Draw();
	bool isChangeGamePlayState = false;
};

