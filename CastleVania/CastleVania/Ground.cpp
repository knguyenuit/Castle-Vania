#include "Ground.h"
#include "ManageAudio.h"



CGround::CGround()
{
	Init();
	
}

CGround::CGround(Vector2 pos)
{
	Init();
	InitAnimation();
	this->m_Pos = pos;
	m_isRemove = false;
}


CGround::~CGround()
{
}

Box CGround::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height, 0, 0);
}

RECT * CGround::GetBound()
{
	return nullptr;
}

RECT * CGround::GetRectRS()
{
	//return nullptr;
	return this->UpdateRectResource(m_Height, m_Width);
	//RECT* rectRS = new RECT();


	////cập nhật lại vị trí của Rect Resource
	//rectRS->left = 0;
	//rectRS->right = this->m_Width;
	//rectRS->top = 0;
	//rectRS->bottom = this->m_Height;
	//return rectRS;
}

void CGround::Init()
{
	this->m_Id = 601;
	this->m_Width = 32;
	this->m_Height = 64;
}

void CGround::InitAnimation()
{
	this->m_startFrame = 0;
	this->m_endFrame = 1;
	this->m_currentTime = 0;
	this->m_currentFrame = 1;
	this->m_elapseTimeChangeFrame = 0.2f;
	this->m_increase = 1;
	this->m_totalFrame = 2;
	this->m_column = 2;
}

void CGround::Update(float deltaTime)
{
	ChangeFrame(deltaTime);
	OnCaneCollision(deltaTime);
}

void CGround::OnCaneCollision(float deltaTime)
{
	if (this->simon->cane->m_currentFrame == 2 || this->simon->cane->m_currentFrame == 6 || this->simon->cane->m_currentFrame == 10)
	{
		if (CCollision::GetInstance()->AABBCheck(this->GetBox(), this->simon->cane->GetBox()))
		{
			this->m_isRemove = true;
			ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
			CItemManage::GetInstance()->CreateRandomItem(this->GetPos());

		}
	}
}
