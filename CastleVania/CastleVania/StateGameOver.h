#pragma once
#include "State.h"
#include "Texture.h"
#include "Sprite.h"
#include "Resources.h"
#include "Input.h"
#include "DrawFont.h"

class CStateGameOver : public CState
{
public:
	CStateGameOver();
	~CStateGameOver();
public:
	CTexture* m_imageCurr;
	CSprite* m_drawImg;
	CDrawFont* _font;
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
public:
	float m_Width;//chieu rong cua hinh
	float m_Height;//chieu cao cua hinh
	Vector2 m_Pos;//vi tri

public:
	//ID3DXFont* _font;
	float timeDrawString = 0;
	bool canDrawString = false;
	float timeAnimation = 0;
};

