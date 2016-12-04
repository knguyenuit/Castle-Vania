#ifndef __CBANNER_H__
#define __CBANNER_H__
#include "BaseGameObject.h"
#include "Sprite.h"


class CBanner : public CBaseGameObject
{
public:
	void Init();
	void Update(float deltaTime);
	void Draw();
	RECT* GetRectRS();
	CBanner();
	~CBanner();
public:
	CSprite* m_Draw;
	CTexture* m_TextureBanner;
};

#endif // !__CBANNER_H__