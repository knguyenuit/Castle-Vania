#include "CastleVania.h"
#include "Device.h"
#include "Input.h"
#include "StateGameManager.h"
#include "ManageAudio.h"



CCastleVania::CCastleVania()
{
}

void CCastleVania::Init()
{
	CViewWindows::GetInstance()->InitClienWindow();
	CDevice::GetInstance()->InitDirect3D();

	CInput::GetInstance()->InitInput(CViewWindows::m_hInstance);
	CInput::GetInstance()->InitKeyboard(CViewWindows::m_hwndWindow);

	CStateGameManager::GetInstance()->LoadScene();
	CStateGameManager::GetInstance()->ChangeState(new CStateGamePlay());

	////Audio
	ManageAudio::GetInstance()->init_DirectSound(CViewWindows::m_hwndWindow);
	ManageAudio::GetInstance()->readFileAudio();
}

void CCastleVania::Destroy()
{

}

void CCastleVania::ProcessInput()
{
	CInput::GetInstance()->ProcessKeyboard();
	CInput::GetInstance()->Update();
}


