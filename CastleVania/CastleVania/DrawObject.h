#ifndef __CDRAW_OBJECT_H__
#define __CDRAW_OBJECT_H__

#include "Singleton.h"
#include "Sprite.h"
#include "BaseGameObject.h"
//#include "CResourece.h"
#include "Camera.h"

class CDrawObject : public CSingleton<CDrawObject>
{
	friend class CSingleton<CDrawObject>;
public:
	//Cac phuong thuc
	CDrawObject();
	~CDrawObject();
	void Draw(CBaseGameObject*);
	void Draw(CBaseGameObject*, D3DCOLOR);
private:
	//Khoi tao bien thanh vien
	CSprite* m_draw; //quan ly viec ve

};

#endif // !__CDRAW_OBJECT_H__
