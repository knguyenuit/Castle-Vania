#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "Enemy.h"
class CSnake :
	public CEnemy
{
public:
	CSnake();
	CSnake(Vector2 pos, Direction dir);
	CSnake(Vector2 pos, Direction dir, float v_x, float v_y);
	void Init();
	~CSnake();
public:
	void Draw();
	void Update(float deltaTime);
	void MoveUpdate(float deltaTime);
	float m_currentTimeLife = 0;
	RECT * GetRectRS();
	CSprite * m_draw;
	CTexture* Texture = new CTexture();
};
#endif //!__SNAKE_H__