#ifndef __CSTATEMANAGEMENT_H__
#define __CSTATEMANAGEMENT_H__

#include "Singleton.h"
#include "State.h"
#include "Device.h"
#include "StateGamePlay.h"
#include "StateGameStart.h"
#include "StateGameIntro.h"
#include "Global.h"
#include "ManageAudio.h"
#include "StateGameOver.h"

enum StateScene
{

	STARTSCENE = 1,
	INTRO_SCENE = 2,
	
	GAME_PLAY_SCENE = 3,
	GAME_OVER_SCENE = 4
	
};

class CStateGameManager : public CSingleton<CStateGameManager>
{
	friend class CSingleton<CStateGameManager>;
private:
	float timeDelay;
public:
	StateScene currentScene;
	void LoadScene();
	void Update(bool isUpdate, float deltaTime);
	void ChangeState(CState*);

	void Clear();
public:
	CStateGamePlay *gamePlayScene;
	CStateGameStart *gameStartScene;
	CStateGameIntro *gameIntroScene;
	CStateGameOver *gameOverScene;
	bool isStart;
protected:
	CStateGameManager() : m_pNext(0), m_pCurrent(0) {}
	~CStateGameManager();
protected:
	CState* m_pNext;
	CState* m_pCurrent;
};
#endif // !__CSTATEMANAGEMENT_H__
