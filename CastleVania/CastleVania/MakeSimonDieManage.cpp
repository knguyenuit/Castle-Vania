#include "MakeSimonDieManage.h"



CMakeSimonDieManage::CMakeSimonDieManage()
{
	this->CreateMSD(Vector2(300, 200));
}


CMakeSimonDieManage::~CMakeSimonDieManage()
{
}

void CMakeSimonDieManage::Update(float deltaTime)
{
	if (!this->m_listMSD.empty())
	{
		for (std::vector<CMakeSimonDie*>::iterator em = this->m_listMSD.begin(); em != this->m_listMSD.end(); ++em)
		{
			CMakeSimonDie* obj = *em;
			obj->Update(deltaTime);
		}
	}
}

void CMakeSimonDieManage::CreateMSD(Vector2 pos)
{
	CMakeSimonDie * msd = new CMakeSimonDie(pos);
	this->m_listMSD.push_back(msd);
}

void CMakeSimonDieManage::Draw()
{
	if (!this->m_listMSD.empty())
	{
		for (std::vector<CMakeSimonDie*>::iterator em = this->m_listMSD.begin(); em != this->m_listMSD.end(); ++em)
		{
			CMakeSimonDie* obj = *em;
			obj->Draw();
		}
	}
}
