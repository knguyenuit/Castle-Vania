#ifndef __MAKESIMONDIEMANAGE_H__
#define __MAKESIMONDIEMANAGE_H__

#include "Singleton.h"
#include "MakeSimonDie.h"
class CMakeSimonDieManage :
	public CSingleton<CMakeSimonDieManage>
{
public:
	CMakeSimonDieManage();
	~CMakeSimonDieManage();
	void Update(float deltaTime);
	std::vector<CMakeSimonDie*> m_listMSD;
	void CreateMSD(Vector2 pos);
	void Draw();
};
#endif // !__MAKESIMONDIEMANAGE_H__

