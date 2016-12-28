#include "HideObject.h"



CHideObject::CHideObject()
{

}

CHideObject::CHideObject(HideObject_TYPE type, Vector2 pos)
{
	Init();
	m_typeHideObject = type;
	this->m_Pos = pos;
}

void CHideObject::Init()
{
	
}

void CHideObject::Update(float deltaTime)
{


}

void CHideObject::OnSimonCollision()
{
	if (abs(this->simon->m_Pos.x - this->m_Pos.x) < 30
		&& abs(this->simon->m_Pos.y - this->m_Pos.y) < 50)
	{
		this->isSimonCollision = true;
	}
	else
	{
		this->isSimonCollision = false;
	}
}
void CHideObject::SimonMove(float deltaTime)
{
}
CHideObject::~CHideObject()
{
}
