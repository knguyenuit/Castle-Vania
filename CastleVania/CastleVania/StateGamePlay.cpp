#include "StateGamePlay.h"



CStateGamePlay::CStateGamePlay()
{
}


CStateGamePlay::~CStateGamePlay()
{
}

void CStateGamePlay::Init()
{
	CPoolObject::GetInstance()->Init();
	CLevel::GetInstance()->readFileLevel(MANAGE_LEVEL);

	ChangeLevel(2);
}

void CStateGamePlay::Update(float deltaTime)
{
	if (CSimon::GetInstance()->isCheckChangeState)
	{
		isCheck = true;

		ChangeLevel(2);
		CSimon::GetInstance()->isCheckChangeState = false;
	}
	CPoolObject::GetInstance()->Update(deltaTime);
}

void CStateGamePlay::Render()
{
	CLoadBackground::GetInstance()->Draw();
	CPoolObject::GetInstance()->Draw();
	CLoadObject::GetInstance()->Draw();
}

void CStateGamePlay::Destroy()
{
}

void CStateGamePlay::ChangeLevel(int lv)
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
		CSimon::GetInstance()->m_Pos = CSimon::GetInstance()->m_PosDefault;
		CCamera::GetInstance()->m_pos.x = CSimon::GetInstance()->m_Pos.x - 100;
	}
}
