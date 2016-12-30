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
	m_Level = 1;
	ChangeLevel(CSimon::GetInstance()->m_currentLevel);
}

void CStateGamePlay::Update(float deltaTime)
{
	if (CSimon::GetInstance()->isCheckChangeState)
	{
		CSimon::GetInstance()->m_currentLevel += 1;
		isCheck = true;
		ChangeLevel(CSimon::GetInstance()->m_currentLevel);
		CSimon::GetInstance()->isCheckChangeState = false;
	}
	if (CSimon::GetInstance()->isDie)
	{
		isCheck = true;
		ChangeLevel(CSimon::GetInstance()->m_currentLevel);
		CSimon::GetInstance()->isDie = false;
	}
	CPoolObject::GetInstance()->Update(deltaTime);
	if (CSimon::GetInstance()->m_countLife < 0)
	{
		isChangeState = true;
	}
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
			CAnimationObjectManage::GetInstance()->m_listAnimationObject.clear();
			isCheck = false;
		}
		CLoadBackground::GetInstance()->LoadImageFromFile(m_currentLevel->fileImageBackgroud);
		CLoadObject::GetInstance()->LoadReSourceFromFile(m_currentLevel->fileObject, m_currentLevel->fileObjectQuadtree);
		CLoadBackground::GetInstance()->LoadBackgroundFromFile(m_currentLevel->fileBackground, m_currentLevel->fileBackgroundQuadtree);
		CAnimationObjectManage::GetInstance()->CreateAnimationObject(lv);
		CSimon::GetInstance()->ResetSimon();

	}
}
