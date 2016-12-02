#ifndef __CCANE_H__
#define __CCANE_H__

#include "Animation.h"
#include "BaseGameObject.h"
#include "LoadObject.h"


class CCane : public CBaseGameObject, public CAnimation
{
public:
	CCane();

	~CCane();
public:
	void Init();
	void Update(float deltaTime);//ham Update chinh cua game
	Vector2 GetPos();
	void OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject);
	
	Box GetBox();
	RECT* GetBound();
	RECT* GetRectRS();
	void Use(D3DXVECTOR2 m_posSimon, bool isLeft);
	//cac ham ke thua tu Animation
public:
	void SetFrame();		// ham chuyen frame.
	int getCurrentFrame() { return m_currentFrame; }
public:
	bool m_checkActive = false; //xet xem co' danh' roi hay ko
	bool isChangeSimonStatus = false;;
};

#endif // !__CCANE_H__