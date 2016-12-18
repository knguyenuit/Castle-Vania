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
	this->m_Width = this->m_Height = 32;
}

void CHideObject::Update(float deltaTime)
{
	this->OnSimonCollision();
}

void CHideObject::OnSimonCollision()
{

}

void CHideObject::OnKeyDown()
{
	this->m_keyDown = CInput::GetInstance()->GetKeyDown();
}


CHideObject::~CHideObject()
{
}
