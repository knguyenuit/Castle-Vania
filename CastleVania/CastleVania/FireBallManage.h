#ifndef __FIREBALLMANAGE_H__
#define __FIREBALLMANAGE_H__
#include "FireBall.h"
#include "Singleton.h"	
class CFireBallManage : public CSingleton<CFireBallManage>
{
	friend class CSingleton<CFireBallManage>;
public:
	CFireBallManage();
	~CFireBallManage();
public:
	std::vector<CFireBall*> m_ListFireBall;
	void Update(float deltaTime);
	void CreateFireBall(Vector2 pos, Direction m_Dir);
	
	void DrawFireBall(CFireBall* obj);
	void Draw();
	CTexture* Texture = new CTexture();
	CSprite* m_draw; //quan ly viec ve
};

#endif // !__FIREBALLMANAGE_H__