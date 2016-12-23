#ifndef __HIDEOBJECTMANAGE_H__
#define __HIDEOBJECTMANAGE_H__
#include "Singleton.h"
#include "DownStairLeft.h"
#include "DownStairRight.h"
#include "UpStairLeft.h"
#include "UpStairRight.h"
#include "ChangeScreen.h"
class CHideObjectManage :
	public CSingleton<CHideObjectManage>
{
	friend class CSingleton<CHideObjectManage>;
public:
	CHideObjectManage();
	~CHideObjectManage();
public:
	void Update(float deltaTime);
	CHideObject * CreateHideObject(HideObject_TYPE type, Vector2 pos);
	std::vector<CHideObject*> m_listHideObject;
};
#endif // !__HIDEOBJECTMANAGE_H__

