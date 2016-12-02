#include "GameManager.h"
#include "LoadObject.h"
#include "Resources.h"



CGameManager::CGameManager()
{
	Init();
	CLoadObject::GetInstance()->readFile(FILE_LIST_OBJECT);
	
}


CGameManager::~CGameManager()
{
}

void CGameManager::Init()
{
	CPoolObject::GetInstance()->Init();
	CLoadBackground::GetInstance()->LoadBackgroundFromFile();
}

void CGameManager::Update(float deltaTime)
{
	CPoolObject::GetInstance()->Update(deltaTime);
	this->Draw();
}

void CGameManager::Draw()
{
	CDevice::s_d3ddv->ColorFill(CDevice::s_backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	if (CDevice::s_d3ddv->BeginScene())
	{
		CDevice::s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
		CLoadBackground::GetInstance()->Draw();
		CPoolObject::GetInstance()->Draw();
		CLoadObject::GetInstance()->Draw();
		CDevice::s_spriteHandle->End();
		CDevice::s_d3ddv->EndScene();
	}
	CDevice::s_d3ddv->Present(NULL, NULL, NULL, NULL);
}
