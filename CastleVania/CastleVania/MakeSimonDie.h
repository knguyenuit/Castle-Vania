#pragma once
#include "Enemy.h"
enum class MSDState {
	None = 0,
	Up = 1,
	Down = 2
};
class CMakeSimonDie :
	public CEnemy
{
public:
	CMakeSimonDie();
	CMakeSimonDie(Vector2 pos);
	void Init();
	~CMakeSimonDie();
public:
	void Update(float deltaTime);
	void Draw();
	void MSDStateUpdate();
	void MoveUpdate(float deltaTime);
	void OnSimonCollision();
	Vector2 currentStepPos;
	float timeDelay = 0.3f;
	MSDState MSDState = MSDState::None;
	RECT * GetRectRS();
	RECT * GetRectRS2();
	CSprite * m_draw;
};

