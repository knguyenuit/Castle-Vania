#include "GameManager.h"
#include "LoadObject.h"
#include "Resources.h"




CGameManager::CGameManager()
{
	Init();
	CLevel::GetInstance()->readFileLevel(MANAGE_LEVEL);

	ChangeLevel(2);


}


CGameManager::~CGameManager()
{
}



void CGameManager::Init()
{
	CPoolObject::GetInstance()->Init();
	m_Level = 1;

}


void CGameManager::Update(float deltaTime)
{


	if (CSimon::GetInstance()->isCheckChangeState)
	{
		isCheck = true;

		ChangeLevel(2);
		CSimon::GetInstance()->isCheckChangeState = false;
	}
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

		CDevice::s_spriteHandle->End();
		CDevice::s_d3ddv->EndScene();
	}
	CDevice::s_d3ddv->Present(NULL, NULL, NULL, NULL);
}

void CGameManager::ChangeLevel(int lv)
{
	m_currentLevel = CLevel::GetInstance()->listLevel[lv];
	if (m_currentLevel != NULL)
	{
		if (isCheck)
		{
			CLoadBackground::GetInstance()->Clear();
			CLoadObject::GetInstance()->Clear();
		}
		CLoadBackground::GetInstance()->LoadImageFromFile(m_currentLevel->fileImageBackgroud);
		CLoadObject::GetInstance()->LoadReSourceFromFile(m_currentLevel->fileObject, m_currentLevel->fileObjectQuadtree);
		CLoadBackground::GetInstance()->LoadBackgroundFromFile(m_currentLevel->fileBackground, m_currentLevel->fileBackgroundQuadtree);
	}
}
