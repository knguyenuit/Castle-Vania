#ifndef __CITEMMANAGE_H__
#define __CITEMMANAGE_H__
#include "Item.h"
#include "Singleton.h"
#include "DrawObject.h"
#include "Simon.h"
#include "OnCollision.h"
class CItemManage : public CSingleton<CItemManage>
{
	friend class CSingleton<CItemManage>;
public:
	CItemManage();
	~CItemManage();
public:
	void Init();
	void Update(float deltaTime);
	void CreateItem(ITEM_name name, Vector2 pos);
	void CreateRandomItem(Vector2 pos);
	CItem* m_item;
	void Draw();
	void DrawItem(CItem* item);
	std::list<CItem*> m_ListItem;
	void OnSimonCollision(float deltaTime);
public:
	CSprite* m_draw; //quan ly viec ve
};

#endif

