#ifndef __CITEMMANAGE_H__
#define __CITEMMANAGE_H__
#include "Item.h"
#include "Singleton.h"
#include "DrawObject.h"
class CItemManage : public CSingleton<CItemManage>
{
	friend class CSingleton<CItemManage>;
public:
	CItemManage();
	~CItemManage();
public:
	void Init();
	void Update(float deltaTime);
	CItem* CreateItem(ITEM_name name, Vector2 pos);
	CItem* m_item;
	void DrawItem(CItem* item);
	std::vector<CItem*> m_ListItem;
public:
	CSprite* m_draw; //quan ly viec ve
};

#endif

