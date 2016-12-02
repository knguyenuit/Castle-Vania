#ifndef __TYPE__ITEM__ENUM__
#define __TYPE__ITEM__ENUM__

enum TypeItem
{
	SmallHeart = 301,
	LargeHeart = 302,
	MagicalCrystal = 303,
	MoneyBag = 304,
	TripleShot = 305,
	DoubleShot = 307,
	PorkChop = 309,
	MorningStar = 310,
	Watch = 311,
	Dagger = 312,
	FireBomb = 313,
	Boomerang = 314,
	Axe = 315,
	Cross = 316,
	MoneyBag1 = 3040,
	MoneyBag2 = 3041,
	MoneyBag3 = 3042
};

#endif // !__TYPE__ITEM__ENUM__

#ifndef __CITEM_H__
#define __CITEM_H__

#include "BaseGameObject.h"
#include "Animation.h"
#include "Move.h"

#define DisBound 16
//Va cham voi ground(nen) va va cham voi simon - anh huong toi simon.
class CItem : public CBaseGameObject, public CAnimation, public CMove
{
public:
	CItem();
	CItem(std::vector<std::string> arr);
	
	
	
	Box getBox();

	//di chuyen theo hinh zich zac
	void move(float delta_Time);

	//xuet hien item khi danh quai hoac den
	void appear(D3DXVECTOR2 posAppear);

	//tac dung vao simon khi va cham voi no
	//moi item se khac nhau o diem nay
	void effectSimon();
	bool canCollionSimon;
protected:
	float timeColSimon;//sau khoang thoi gian nay thi simon co the va cham item
					   //item se roi va dy chuyen theo hinh zich zac quanh vi tri
	float maxX;
	float minX;
	float disBound;//do lon cua vung di chuyen
	bool _idle;//khong di chuyen nua
	float timeLife;//thoi gian ton tai
	TypeItem _typeItem;
private:
};

#endif // !__ITEM_H__