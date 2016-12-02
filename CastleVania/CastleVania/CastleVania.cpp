#include "CastleVania.h"
#include "Device.h"
#include "Input.h"



CCastleVania::CCastleVania()
{
}

void CCastleVania::Init()
{
	CViewWindows::GetInstance()->InitClienWindow();
	CDevice::GetInstance()->InitDirect3D();
	CInput::GetInstance()->InitInput(CViewWindows::m_hInstance);
	CInput::GetInstance()->InitKeyboard(CViewWindows::m_hwndWindow);

	
}

void CCastleVania::Destroy()
{

}

void CCastleVania::ProcessInput()
{
	CInput::GetInstance()->ProcessKeyboard();
	CInput::GetInstance()->Update();
}


