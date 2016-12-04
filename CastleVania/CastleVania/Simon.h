#ifndef __SIMON_H__
#define __SIMON_H__

#include "BaseGameObject.h"
#include "Animation.h"
#include "Singleton.h"
#include "Move.h"
#include "Input.h"
#include "Collision.h"
#include "Cane.h"
#include "Global.h"
#include "OnCollision.h"
#include "HinhChuNhat.h"
#include "ItemManage.h"
class CSimon : public CBaseGameObject, public CAnimation, public CMove, public CSingleton<CSimon>
{
	friend class CSingleton<CSimon>;

public:
	CSimon();
	~CSimon();
public:
	CCane *cane;
	CHinhChuNhat *hv;
	SIMON_status simon_Status;
	//cac ham ke thua tu BaseGameObject
public:
	void Update(float deltaTime);//ham Update chinh cua game
	Vector2 GetPos();
	void OnCollision(float deltaTime, std::hash_map<int, Box> listBox);
	void UpdateGround(float deltaTime, std::vector<CBaseGameObject*> listObject);
	void OnCollision(float deltaTime, CBaseGameObject* hv);
	void OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject);
	Box GetBox();
	RECT* GetBound();
	RECT* GetRectRS();
	//cac ham ke thua tu Animation
public:
	void SetFrame();		// ham chuyen frame.

public:
	//xu ly Input
	void OnKeyDown(float deltaTime);
	void OnKeyUp(float deltaTime);
	void ProcessInput(float deltaTime);
	void MoveUpdate(float deltaTime);
	//cac thong so ve Simon
public:
	int m_keyDown;
	int m_keyUp;
	float m_timeCountFrame;
	bool isInput;
	bool canJump = false;
	bool isFree = false;
	bool isSit = false;
	bool isMove = false;
	bool isAttacking= false;
	bool isChangeStatus = false;
	bool canChangeStatus = false;
	
private:
	void InitAnimation();//khoi tao cac thong so cua Simon
	void InitMove();//khoi tao cac thong so chuyen dong cua Simon
	void Gravity(float deltaTime);
	
public:
	void UpdateStatus(float deltaTime, SIMON_status simon_status);
	void Jump(float deltaTime);

};


#endif // !__SIMON_H__

