#ifndef __BLACK_KNIGHT_H__
#define __BLACK_KNIGHT_H__
#include "Enemy.h"

class CBlackKnight : public CEnemy
{
public:
	CBlackKnight();
	CBlackKnight(Vector2 pos);
	~CBlackKnight();
public:
	void Init();
	RECT* GetRectRS();

};

#endif // !__BLACK_KNIGHT_H__