#pragma once
#include "PoolObject.h"
#include "DrawObject.h"
#include "LoadBackground.h"
#include "Singleton.h"
#include "Level.h"
#include "State.h"
#include "LoadObject.h"
#include "AnimationObjectManage.h"

class CStateGamePlay : public CState
{
public:
	CStateGamePlay();
	~CStateGamePlay();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
public:
	bool isCheck = false;

public:
	Level* m_currentLevel;
	int m_Level;
	void ChangeLevel(int lv);
};

