#include "StateGameManager.h"






CStateGameManager::~CStateGameManager()
{
}

void CStateGameManager::LoadScene()
{
	this->gamePlayScene = new CStateGamePlay();
	this->gameStartScene = new CStateGameStart();
	this->gameIntroScene = new CStateGameIntro();
	gamePlayScene->Init();
	m_pCurrent = gamePlayScene;
	isStart = false;
	timeDelay = 0;
}

void CStateGameManager::Update(bool isUpdate, float deltaTime)
{
	if (this->m_pCurrent != this->m_pNext)
	{
		if (this->m_pCurrent)
		{
			this->m_pCurrent->Destroy();
			delete this->m_pCurrent;
		}
		if (this->m_pNext)
		{
			this->m_pNext->Init();
		}
		this->m_pCurrent = this->m_pNext;
	}
	if (m_pCurrent)
	{
		if (!isUpdate)
		{
			this->m_pCurrent->Update(deltaTime);
		}
		CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		if (CDevice::s_d3ddv->BeginScene())
		{
			CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
			this->m_pCurrent->Render();
			CDevice::s_spriteHandle->End();
			CDevice::s_d3ddv->EndScene();
		}
		CDevice::s_d3ddv->Present(NULL, NULL, NULL, NULL);
	}


	if (CInput::GetInstance()->IsKeyDown(DIK_RETURN))
	{
		
		isStart = true;
		ManageAudio::GetInstance()->playSound(TypeAudio::Select);
		ChangeState(this->gameIntroScene);

	}

	if (this->m_pCurrent == this->gameIntroScene)
	{
		if (gameIntroScene->simon_Intro->isChangeGamePlayState)
		{
			/*timeDelay += deltaTime;
			if (timeDelay > 1.0f)
			{
				if (this->m_pCurrent != this->gamePlayScene)
				{


				}


				timeDelay = 0;
				isStart = false;
			}*/
			ChangeState(this->gamePlayScene);
		}
	}


	/*if (this->m_pCurrent == this->worldMapScene)
	{
		gamePlayScene->m_mapId = this->worldMapScene->worldMap->mario->note.MapID;

		if (CInput::GetInstance()->IsKeyDown(DIK_RETURN) && gamePlayScene->m_mapId != -1)
		{
			ChangeState(gamePlayScene);
			ManageAudio::GetInstance()->stopSound(TypeAudio::AUDIO_WORLD_MAP);
		}
	}*/
}

void CStateGameManager::ChangeState(CState *state)
{
	this->m_pNext = state;
}

void CStateGameManager::Clear()
{
	if (this->m_pNext)
	{
		delete this->m_pNext;
	}
	if (this->m_pCurrent)
	{
		delete this->m_pCurrent;
	}

}
