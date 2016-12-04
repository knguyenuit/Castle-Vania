#ifndef __CPOOLOBJECT_H__
#define __CPOOLOBJECT_H__

#include "Simon.h"
#include "Cane.h"
#include "HinhChuNhat.h"
#include "HinhVuong.h"
#include "Singleton.h"
#include "Collision.h"
#include "DrawObject.h"
#include "Ground.h"
#include "ItemManage.h"
#include "EnemyManage.h"
#include "Banner.h"
class CPoolObject : public CSingleton<CPoolObject>
{
	friend class CSingleton<CPoolObject>;
public:
	//ve bao nhieu doi tuong thi o day tao bay nhieu doi tuong
	CSimon *simon; 
	CItemManage *itemManage;
	CHinhChuNhat *hcn;
	CHinhVuong *hv;
	CGround *ground;
	CBanner *banner;
public:

	CPoolObject();
	~CPoolObject();
public:
	CDrawObject *drawManager;
	void Init();
	void Update(float deltaTime);
	void OnCollision(float deltaTime);
	void Draw();
};

#endif