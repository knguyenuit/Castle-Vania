#ifndef __HIDEOBJECT_H__
#define __HIDEOBJECT_H__
#include "BaseGameObject.h"
#include "Simon.h"
#include "OnCollision.h"
enum HideObject_TYPE
{
	GroundHorizontal = 702,// unlimit x 32 ( ngang )
	GroundVertical = 712,// unlimit x 32 ( dọc )
	StopScrollScene = 706, // 32 - max
	ChangeScene = 705, // 32 - 96
	Free = 701, // 32 - 32        
	DownStairLeft = 703, // 32 - 32
	UpStairLeft = 704,// 32 - 32        
	DownStairRight = 713, // 32 - 32
	UpStairRight = 714, // 32 - 32
	ChangeTop = 715, // 32 - 32
	ChangeDown = 716, // 32 - 32
	CheckSimonDie = 888
};

class CHideObject : public CBaseGameObject
{
public:
	CHideObject();
	CHideObject(HideObject_TYPE type, Vector2 pos);
	HideObject_TYPE m_typeHideObject;
	void Init();
	~CHideObject();
public:
	CSimon * simon = CSimon::GetInstance();
	bool isSimonCollision = false;
public:
	void Update(float deltaTime);
	void OnSimonCollision();
	void SimonMove(float deltaTime);
};

#endif // !__HIDEOBJECT_H__

