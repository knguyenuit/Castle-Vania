#include "BaseGameObject.h"
using namespace std;


CBaseGameObject::CBaseGameObject()
{
	
	this->m_Dir = Direction::NONE_DIR;
	this->m_Pos = Vector2(0, 0);
	m_isLive = true;
	this->m_Width = 0;
	this->m_Height = 0;
	this->m_RectRS = NULL;
	m_isRemove = false;

}


CBaseGameObject::~CBaseGameObject()
{
	if (this->m_RectRS)
	{
		delete m_RectRS;
	}
}


void CBaseGameObject::Update(float deltaTime)
{

}

void CBaseGameObject::SetPos(Vector2 pos)
{
	this->m_Pos = pos;
}


Vector2 CBaseGameObject::GetPos()
{
	return this->m_Pos;
}




Box CBaseGameObject::GetBox()
{
	return Box(this->m_Pos, this->m_Width, this->m_Height, 0, 0);
}

RECT* CBaseGameObject::GetBound()
{
	RECT* rect = new RECT();
	rect->top = this->m_Pos.y;
	rect->left = this->m_Pos.x;
	rect->bottom = rect->top + this->m_Height;
	rect->right = rect->left + this->m_Width;
	return rect;
}

RECT* CBaseGameObject::GetRectRS()
{
	return NULL;
}