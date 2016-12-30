#ifndef __SNAKEMANAGE_H__
#define __SNAKEMANAGE_H__

#include "Snake.h"
#include "Singleton.h"	
class CSnakeManage : public CSingleton<CSnakeManage>
{
	friend class CSingleton<CSnakeManage>;
public:
	CSnakeManage();
	~CSnakeManage();
public:
	std::vector<CSnake*> m_ListSnake;
	void Update(float deltaTime);
	void CreateSnake(Vector2 pos, Direction m_Dir);

	void DrawSnake(CSnake* obj);
	void Draw();
	CTexture* Texture = new CTexture();
	CSprite* m_draw; //quan ly viec ve
};
#endif // !__SNAKEMANAGE_H__

