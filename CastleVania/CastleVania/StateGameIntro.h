#pragma once
#include "State.h"
#include "Texture.h"
#include "Sprite.h"
#include "Resources.h"
#include "Input.h"
#include "SimonIntro.h"

class CStateGameIntro : public CState
{
public:
	CStateGameIntro();
	~CStateGameIntro();
public:
	CTexture* m_imageCurr;
	CSprite* m_drawImg;
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
public:
	float m_Width;//chieu rong cua hinh
	float m_Height;//chieu cao cua hinh
	Vector2 m_Pos;//vi tri
public:
	CSimonIntro* simon_Intro;
	
public:
	ID3DXFont* _font;
	float timeDrawString = 0;
	bool canDrawString = false;
	float timeAnimation = 0;
};

