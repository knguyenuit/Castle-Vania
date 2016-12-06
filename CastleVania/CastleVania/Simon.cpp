#include "Simon.h"
#include "Camera.h"
#include "LoadObject.h"
#include "ItemManage.h"
#define MAX_HIGH 400

CSimon::CSimon()
{
	this->m_Id = 1;
	m_hpSimon = 16;
	this->isInput = false;
	this->m_Dir = Direction::LEFT;
	this->simon_Status = IDLE;
	this->InitMove();
	this->InitAnimation();
	this->cane = new CCane();
	this->cane->m_Pos = this->m_Pos;
	this->hv = new CHinhChuNhat();
}
#pragma region Init

void CSimon::InitAnimation()
{
	this->m_startFrame = 0;
	this->m_endFrame = 0;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 24;
	this->m_column = 8;
}
void CSimon::InitMove()
{
	
	this->m_vx = 10;
	this->m_vy = 380;
	this->m_vxDefault = this->m_vx;
	this->m_vyDefault = 380;

	this->m_a = -900;
	this->m_aDefault = this->m_a;
	this->m_ax = 0;
	this->m_Pos = Vector2(200, 60);
	this->m_Width = 60;
	this->m_Height = 68;
	this->m_isJumping = false;
}

#pragma endregion

CSimon::~CSimon()
{
	delete this;
}

void CSimon::Update(float deltaTime)
{
	//SetFrame();
	
	ChangeFrame(deltaTime);
	//this->m_Pos.x += m_vx * deltaTime;
	MoveUpdate(deltaTime);
	OnCollision(deltaTime, CLoadObject::GetInstance()->listBox);
	UpdateGround(deltaTime, CLoadObject::GetInstance()->m_listGameObject);
	OnCollision(deltaTime, CLoadObject::GetInstance()->m_listGameObject);
	OnCollision(deltaTime, hv);
	this->cane->Update(deltaTime);
}


void CSimon::Gravity(float deltaTime)
{
	
}


void CSimon::Jump(float deltaTime)
{
	this->m_currentFrame = 0;
	isAttacking = false;
	this->m_Height = 68;
	this->m_Pos.y = 60;
	m_startFrame = 0;
	m_endFrame = 0;
	
}

void CSimon::UpdateStatus(float deltaTime,SIMON_status simon_status)
{
	if (this->cane->isChangeSimonStatus == true)
	{
		if (!isSit)
		{
			this->m_currentFrame = 0;
			isAttacking = false;
			this->m_Height = 68;
			this->m_Pos.y = 60;
			m_startFrame = 0;
			m_endFrame = 0;
		}
		else
		{
			this->m_currentFrame = 4;
			m_startFrame = 4;
			m_endFrame = 4;
			this->m_Height = 50;
			this->m_Pos.y = 51;
			isAttacking = false;
		}
		this->cane->isChangeSimonStatus = false;
	}
	switch (simon_status)
	{
	case NONE:
		break;
	case IDLE:
		isAttacking = false;
		this->m_Height = 68;
		this->m_Pos.y = 60;
		m_startFrame = 0;
		m_endFrame = 0;
		
		isMove = true;
		canJump = true;
		break;
	case MOVE:
		
			if (isMove)
			{
				if (this->m_Dir == Direction::LEFT)
				{
					this->m_startFrame = 0;
					this->m_endFrame = 3;
					this->m_ax = 30;
					this->m_ax += this->m_ax * deltaTime;
					m_Pos.x -= this->m_ax * this->m_vx * deltaTime;
				}
				if (this->m_Dir == Direction::RIGHT)
				{
					this->m_startFrame = 0;
					this->m_endFrame = 3;
					this->m_ax = 30;
					this->m_ax += this->m_ax * deltaTime;
					m_Pos.x += this->m_ax * this->m_vx * deltaTime;
				}
			}
		
		break;
	case JUMP:

		canJump = false;
			this->m_vy += this->m_a * deltaTime;
			this->m_Pos.y += this->m_vy * deltaTime;
			

			if (this->m_vy <= 0)
			{
				isFree = true;
				simon_Status = SIMON_status::FALL;
				this->canJump = false;
				
			}
			this->m_startFrame = 4;
			this->m_endFrame = 4;
			/*if (m_Pos.y >= 150)
			{
				simon_Status = SIMON_status::FALL;
				canJump = false;
			}*/
		
		
		break;
	case SIT:
		isMove = false;
		if (!isAttacking)
		{
			this->m_startFrame = 4;
			this->m_endFrame = 4;
			this->m_Height = 50;
			this->m_Pos.y = 51;
		}
		isSit = true;
		
		
		break;
	case FALL:
		if (isFree)
		{
			this->m_vy += this->m_a * deltaTime * 2;
			this->m_Pos.y += this->m_vy * deltaTime;
		}
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		break;
	case ACTACK:
		if (isAttacking)
		{	
			
			if (isSit)
			{
				this->m_startFrame = 15;
				this->m_endFrame = 17;
				this->cane->m_Pos.y = 51;
				this->m_Height = 66;
				this->m_Pos.y = 42;
				this->cane->m_checkActive = true;
			}
			else
			{				
				this->m_startFrame = 5;
				this->m_endFrame = 7;
				this->cane->m_checkActive = true;
			}
			
			this->cane->Use(this->m_Pos, isLeft);
		}
		break;
	case COLLISION_ENEMY:
		this->m_startFrame = 8;
		this->m_endFrame = 8;
		if (this->timeCollisionEnemy<0.6)
		{
			this->m_Pos.x -= deltaTime * 100;
			this->m_Pos.y += deltaTime * 100;
		}
		else 
		{
			this->m_Pos.y -= deltaTime * 100;
		}
		
		break;

	default:
		break;
	}
	/*if (isChangeStatus)
	{
		

	}*/
}

void CSimon::MoveUpdate(float deltaTime)
{
	Gravity(deltaTime);
	OnKeyDown(deltaTime);
	OnKeyUp(deltaTime);
	UpdateStatus(deltaTime, simon_Status);
	
	//lay vi tri cua cay roi theo vi tri cua simon
	
	
	//update camera
	CCamera::GetInstance()->Update(this->m_Pos.x, this->m_Pos.y);
}

//thay doi Frame
void CSimon::SetFrame()
{
	this->m_startFrame = 0;
	this->m_endFrame = 0;
}


#pragma region GetBox

Vector2 CSimon::GetPos()
{
	return this->m_Pos;
}

void CSimon::OnCollision(float deltaTime, std::hash_map<int, Box> listBox)
{
	CDirection normalX;
	CDirection normalY;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;
	std::hash_map<int, Box>::iterator it;
	for (it = listBox.begin(); it != listBox.end(); it++)
	{
		
		timeCollision = COnCollision::GetInstance()->SweepAABB(this->GetBox(), it->second, normalX, normalY, deltaTime);
		if (normalY == CDirection::ON_DOWN)
		{
			
			isFree = false;
			canJump = true;
		}
	}
}

void CSimon::UpdateGround(float deltaTime, std::vector<CBaseGameObject*> listObject)
{
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;

	for (std::vector<CBaseGameObject*>::iterator it = listObject.begin();
		it != listObject.end();
		++it)
	{
		CBaseGameObject* obj = *it;
		obj->Update(deltaTime);
		/*timeCollision = CCollision::GetInstance()->Collision(this, *it , normalX, normalY, deltaTime);

		if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2)
		{

			if (normalX = 1)
			{

				this->m_vy = 0;
				this->m_vx = 0;
			}
		}*/
	}

}

void CSimon::OnCollision(float deltaTime, CBaseGameObject * hv)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this, hv, normalX, normalX, deltaTime);
	if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
	{
		this->m_vx = 0;
	}
}

void CSimon::OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject)
{
	for (std::vector<CBaseGameObject*>::iterator it = listObject.begin();
		it != listObject.end();
		++it)
	{
		CBaseGameObject* obj = *it;
		if (obj->m_Id == 601)
		{
			CDirection normalX;
			CDirection normalY;
			float timeCollision;
			timeCollision = COnCollision::GetInstance()->SweepAABB(this, obj, normalX, normalX, deltaTime);
			if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
			{
				//MessageBox(NULL, "dung ground", "BG", MB_OK);
			}
		}
	}
}


Box CSimon::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 10, this->m_Height - 8, this->m_vx, this->m_vy);
}
RECT* CSimon::GetBound()
{
	return nullptr;
}
RECT* CSimon::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}
#pragma endregion

#pragma region Input

void CSimon::OnKeyDown(float deltaTime)
{
	this->m_keyDown = CInput::GetInstance()->GetKeyDown();
	switch (this->m_keyDown)
	{
	case DIK_SPACE:
		if (canJump)
		{
			this->simon_Status = SIMON_status::JUMP;
			this->m_vy = m_vyDefault;
		}
			// start jump if is not "on-air"
		break;
	case DIK_LEFT:
		isLeft = true;
		this->cane->isLeft = true;
		this->m_Dir = Direction::LEFT;
		this->cane->m_Dir = Direction::LEFT;
		this->simon_Status = SIMON_status::MOVE;
		break;
	case DIK_RIGHT:
		isLeft = false;
		this->cane->isLeft = false;
		this->m_Dir = Direction::RIGHT;
		this->cane->m_Dir = Direction::RIGHT;
		this->simon_Status = SIMON_status::MOVE;
		break;
	case DIK_UP:
		break;
	case DIK_DOWN:
		this->simon_Status = SIMON_status::SIT;
		break;
	case DIK_Z:
		/*if (isSit)
		{
			this->m_startFrame = 14;
			this->m_endFrame = 16;
			this->m_Height = 50;
			this->m_Pos.y = 51;
			this->cane->m_Pos.y = 40;
		}
		else*/
		
		isAttacking = true;
		this->simon_Status = SIMON_status::ACTACK;
		
		
		break;
	case DIK_Q:
		this->cane->updateState(state2);
		break;
	case DIK_C: //test change status
		isCheckChangeState = true;
		break;
	default:
		break;
	}
}
void CSimon::OnKeyUp(float deltaTime)
{
	this->m_keyUp = CInput::GetInstance()->GetKeyUp();
	switch (this->m_keyUp)
	{
	case DIK_SPACE:
		
		
		break;

	case DIK_LEFT:
		simon_Status = SIMON_status::IDLE;
		
		this->m_ax = 0;
		break;
	case DIK_RIGHT:
		simon_Status = SIMON_status::IDLE;
		
		this->m_ax = 0;
		break;
	case DIK_UP:
		
		break;
	case DIK_DOWN:
		simon_Status = SIMON_status::IDLE;
		
		
		isSit = false;
		break;
	case DIK_Z:
		
		
		
		
		break;
	default:
		break;
	}
}
void CSimon::ProcessInput(float deltaTime)
{
	int key = CInput::GetInstance()->GetKeyDown();
	int key_up = CInput::GetInstance()->GetKeyUp();
	//de phim
	if (CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (this->simon_Status == SIMON_status::MOVE || this->simon_Status == SIMON_status::IDLE)
		{
			this->simon_Status = SIMON_status::MOVE;
		}
	}
	if (CInput::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		if (this->simon_Status == SIMON_status::MOVE || this->simon_Status == SIMON_status::IDLE)
		{
			this->simon_Status = SIMON_status::MOVE;
		}
	}
	if (key == DIK_SPACE)
	{
		if (this->canJump)
		{
			if (CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
			{
				this->m_vx = this->m_vxDefault;
			}

			if (CInput::GetInstance()->IsKeyDown(DIK_LEFT))
			{
				this->m_vx = -this->m_vxDefault;
			}

			this->simon_Status = SIMON_status::JUMP;
			this->m_vy = this->m_vyDefault;
		}
	}
}
#pragma endregion



