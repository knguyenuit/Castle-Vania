#include "Simon.h"
#define MAX_HIGH 400

CSimon::CSimon()
{
	this->m_Id = 1;
	m_hpSimon = 16;
	this->isInput = false;
	this->m_Dir = Direction::RIGHT;
	this->simon_Status = IDLE;
	this->InitMove();
	this->InitAnimation();
	this->cane = new CCane();
	this->m_currentLevel = 3;
	this->hv = new CHinhChuNhat();
	this->m_currentWeapon = WEAPON_name::Dagger;
	//init stair status
	this->canUpStairLeft = this->canUpStairRight = this->canDownStairLeft = this->canDownStairRight = false;
	this->isArrowKeyDown = this->isArrowKeyUp = false;
	this->isCancelStairMove = true;
	this->isMoveLeft = false;
}
#pragma region Init
void CSimon::InitAnimation()
{
	this->m_startFrame = 0;
	this->m_endFrame = 0;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.1f;
	this->m_increase = 1;
	this->m_totalFrame = 24;
	this->m_column = 8;
}
void CSimon::InitMove()
{

	this->m_vx = 10;
	this->m_vy = 450;
	this->m_vxDefault = 180;
	this->m_vyDefault = 450;
	this->m_weight = 35;
	this->m_a = -1300;
	this->m_aDefault = this->m_a;
	this->m_ax = 0;
	this->m_Pos = this->m_PosDefault = Vector2(100, 90);
	this->m_Width = 60;
	this->m_Height = 68;
	this->m_isJumping = false;
	this->isMoveToLeft = this->isMoveToRight = this->isMoveToUp = this->isMoveToDown = false;
}

#pragma endregion

CSimon::~CSimon()
{
	delete this;
}
float countTime = 0;
void CSimon::Update(float deltaTime)
{
	if (this->m_hpSimon <= 0)
	{
		this->m_isLive = false;
		ManageAudio::GetInstance()->stopSound(TypeAudio::Stage_01_Vampire_Killer);
		ManageAudio::GetInstance()->playSound(TypeAudio::Life_Lost);
		countTime += deltaTime;
		if (countTime >= 1)
		{
			m_countLife -= 1;
			isDie = true;
			isSimonDie = true;
		}
		
	}
	ActionUpdate(deltaTime);
	if (this->cane->m_checkActive == true)
	{
		this->cane->Update(this->m_Pos, this->m_Dir, deltaTime);
	}
	this->Gravity(deltaTime);
}


void CSimon::Gravity(float deltaTime)
{
	if (this->isOnStair == false && this->isMoveToStair == false && isWeaponAttacking == false)
	{
		this->m_Pos.y -= this->m_weight * 10 * deltaTime;
	}
}

bool CSimon::MoveTo(Vector2 point, float deltaTime)
{
	if (!this->isMoveToLeft && !this->isMoveToRight)
	{
		if (this->m_Pos.x > point.x) //kiem tra xem co phai qua ben trai
		{
			this->isMoveToLeft = true;
		}
		else
		{
			if (this->m_Pos.x < point.x)
			{
				this->isMoveToRight = true;
			}
			else
			{
				this->isMoveToLeft = (this->m_Dir == LEFT) ? true : false;
				this->isMoveToRight = (this->m_Dir == RIGHT) ? true : false;
			}

		}
		this->isLeft = this->isMoveToLeft;
	}

	if (this->isMoveToLeft) // neu isleft thi van toc x am
	{
		this->m_vx = (this->m_vx>0) ? -this->m_vx : this->m_vx;
		this->m_Dir = Direction::LEFT;
	}
	else
	{
		this->m_vx = (this->m_vx<0) ? -this->m_vx : this->m_vx;
		this->m_Dir = Direction::RIGHT;
	}

	//kiem tra xem co toi toa do X cua point chua
	if ((this->isMoveToLeft && this->m_Pos.x <= point.x) || (this->isMoveToRight && this->m_Pos.x >= point.x))
	{
		this->check_arrive_x = true;
		this->m_Pos.x = point.x;
	}
	if (!this->check_arrive_x)
	{
		this->m_Pos.x += this->m_vx * deltaTime; // thay doi pos.x cua Boss
	}



	if (!this->isMoveToDown && !this->isMoveToUp)
	{
		if (this->m_Pos.y > point.y) // kiem tra xem co phai di xuong duoi
		{
			this->isMoveToDown = true;
		}
		else
		{
			this->isMoveToUp = true;
		}
	}
	if (this->isMoveToDown) // neu isdown thi van toc y am
	{
		this->m_vy = (this->m_vy > 0) ? -this->m_vy : this->m_vy;
	}
	else // neu isUp thi van toc y duong
	{
		this->m_vy = (this->m_vy < 0) ? -this->m_vy : this->m_vy;
	}

	//neu da toi point.y
	if ((this->isMoveToDown && this->m_Pos.y <= point.y) || (this->isMoveToUp && this->m_Pos.y >= point.y))
	{
		this->check_arrive_y = true;
		this->m_Pos.y = point.y;
	}
	if (!this->check_arrive_y)
	{
		this->m_Pos.y += this->m_vy * deltaTime;// Neu chua toi thi Thay doi pos.y
	}
	//Neu da toi point thi tra ve true
	if (this->check_arrive_x && this->check_arrive_y)
	{
		this->check_arrive_x = this->check_arrive_y = false;
		this->isMoveToLeft = this->isMoveToRight = this->isMoveToUp = this->isMoveToDown = false;
		return true;
	}
	else
	{
		return false;
	}
}

void CSimon::ResetSimon()
{
	//if (m_currentLevel == 3)
	//{
	//	//m_Pos = Vector2(100, 40);
	//	m_Pos = Vector2(129,300);
	//	//simon_Status = SIMON_status::ONSTAIR;
	//	//this->isOnStair = true;
	//}
	//else
	//{
	//	if (m_currentLevel == 4)
	//	{
	//		m_Pos = Vector2(200, 90);
	//		simon_Status = SIMON_status::IDLE;
	//		this->isOnStair = false;
	//		this->isCancelStairMove = true;
	//	}
	//	else
	//	{
	//		if (m_currentLevel == 5)
	//		{
	//			m_Pos = Vector2(100, 40);
	//			simon_Status = SIMON_status::IDLE;
	//		}
	//		else
	//		{
	//			m_Pos = CSimon::GetInstance()->m_PosDefault;
	//			simon_Status = SIMON_status::IDLE;
	//		}
	//	}
	//	
	//}
	switch (m_currentLevel)
	{
	case 1:
		m_Pos = CSimon::GetInstance()->m_PosDefault;
		simon_Status = SIMON_status::IDLE;
		isSimonDie = false;
		break;
	case 2:
		m_Pos = CSimon::GetInstance()->m_PosDefault;
		simon_Status = SIMON_status::IDLE;
		isSimonDie = false;
		break;
	case 3:
		this->m_Pos = Vector2(129, 300);
		isSimonDie = false;
		break;
	case 4:
		m_Pos = Vector2(200, 90);
		simon_Status = SIMON_status::IDLE;
		this->isOnStair = false;
		this->isCancelStairMove = true;
		isSimonDie = false;
		break;
	case 5:
		m_Pos = Vector2(100, 40);
		simon_Status = SIMON_status::IDLE;
		isSimonDie = false;
		break;
	case 6:
		if (isSimonDie == true)
		{
			m_Pos = Vector2(2353, 300);
		}
		else
		{
			m_Pos = Vector2(2353, 63);
		}
		isSimonDie = false;
		simon_Status = SIMON_status::IDLE;
		break;
	case 7: 
		if (isSimonDie == true)
		{
			m_Pos = Vector2(1740, 200);
		}
		else
		{
			m_Pos = Vector2(1680, 30);
		}
		isSimonDie = false;
		simon_Status = SIMON_status::IDLE;
		break;
	case 8:
		if (isSimonDie == true)
		{
			m_Pos = Vector2(1320, 200);
		}
		else
		{
			m_Pos = Vector2(1360, 200);
		}
		isSimonDie = false;
		simon_Status = SIMON_status::IDLE;
		break;
	case 9:
		break;
	default:
		break;
	}
	m_hpSimon = 16;
	m_isLive = true;
	canChangeDown = false;
	isChangeDown = false;
	CCamera::GetInstance()->m_pos.x = m_Pos.x - 100;
	CCamera::GetInstance()->isStopScrollCamera = false;
	ManageAudio::GetInstance()->stopSound(TypeAudio::Life_Lost);
	ManageAudio::GetInstance()->playSound(TypeAudio::Stage_01_Vampire_Killer);
}

void CSimon::Jump(float deltaTime)
{
	/*this->m_currentFrame = 0;
	isAttacking = false;
	this->m_Height = 68;
	this->m_Pos.y = 60;
	m_startFrame = 0;
	m_endFrame = 0;*/

}

void CSimon::Draw()
{
	//draw cane
	this->posDraw = CCamera::GetInstance()->GetPointTransform(this->cane->GetPos().x, this->cane->GetPos().y);
	if (this->cane->m_checkActive == true)
	{
		this->texture->LoadImageFromFile(CANE_RES, D3DCOLOR_XRGB(255, 0, 255));
		if (this->GetDirection() == Direction::LEFT)
		{
			this->m_draw->Draw(texture, this->cane->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		}
		else
		{
			this->m_draw->DrawFlipX(texture, this->cane->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		}
	}
	//draw simon
	this->posDraw = CCamera::GetInstance()->GetPointTransform(this->GetPos().x, this->GetPos().y);
	if (this->m_isLive == true)
	{
		if (this->isUnAvailable == true) //Neu vua bi enemy tan cong
		{
			this->isUnAvailableDraw = !this->isUnAvailableDraw;
			if (this->isUnAvailableDraw == true) //ve tranparency
			{
				texture->LoadImageFromFile(SIMON_UNAVAILABLE, D3DCOLOR_XRGB(255, 0, 255));
			}
			else
			{
				texture->LoadImageFromFile(SIMON_RES, D3DCOLOR_XRGB(255, 0, 255));
			}
		}
		else
		{
			if (this->isPickUpMorningStar == true)
			{
				int r = rand() % 100 + 100;
				int g = rand() % 50 + 50;
				int b = rand() % 50;
				D3DCOLOR transcolor = D3DCOLOR_XRGB(r, g, b);
				texture->LoadImageFromFile(SIMON_RES, D3DCOLOR_XRGB(255, 0, 255));
				if (this->GetDirection() == Direction::LEFT)
				{
					this->m_draw->Draw(this->texture, this->GetRectRS(), this->posDraw, transcolor, true);
				}
				else
				{
					this->m_draw->DrawFlipX(this->texture, this->GetRectRS(), this->posDraw, transcolor, true);
				}
				return;
			}
			else // Ve binh thuong
			{
				texture->LoadImageFromFile(SIMON_RES, D3DCOLOR_XRGB(255, 0, 255));
			}
			
		}
	}
	else //Neu con si mon chet
	{
		texture->LoadImageFromFile(SIMON_DIE, D3DCOLOR_XRGB(255, 0, 255));
	}
	if (this->GetDirection() == Direction::LEFT)
	{
		this->m_draw->Draw(this->texture, this->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
	}
	else
	{
		this->m_draw->DrawFlipX(this->texture, this->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
	}
}

void CSimon::UpdateStatus(float deltaTime)
{
	ChangeFrame(deltaTime);
	//Vx direction
	this->isLeft = (this->m_Dir == Direction::LEFT) ? true : false;
	if (this->isLeft)
	{
		this->m_vx = (this->m_vx > 0) ? -this->m_vx : this->m_vx;
	}
	else
	{
		this->m_vx = (this->m_vx < 0) ? -this->m_vx : this->m_vx;
	}
	switch (this->simon_Status)
	{
	case NONE:
		break;
	case IDLE:

		//Init Animation
		m_startFrame = 0;
		m_endFrame = 0;
		this->m_Height = 68;
		this->m_vx = this->m_vxDefault;
		this->m_vy = this->m_vyDefault;
		//Init Can
		canAttack = true;
		canMove = true;
		canJump = true;
		canSit = true;
		//Init Is
		this->isMoveJump = this->isMove = this->isJump = this->isAttack = this->isSit = this->isOnStair = this->isFall = false;
		break;
	case MOVE:
		this->m_elapseTimeChangeFrame = 0.1f;
		this->isMove = true;
		//Init Animation
		this->m_startFrame = 0;
		this->m_endFrame = 3;
		//Init Can Action
		canJump = true;
		canAttack = true;
		canMove = true;
		canSit = false;
		if (this->isKey_X == true)
		{
			this->simon_Status = SIMON_status::MOVE_JUMP;
			this->UpdateStatus(deltaTime);
		}
		if (this->isKey_Z == true)
		{
			this->simon_Status = SIMON_status::ACTACK;
			this->UpdateStatus(deltaTime);
		}
		break;
	case MOVE_JUMP:
		this->isKey_X = false;
		if (this->isMoveJump == false)
		{
			this->m_vy *= 2;
		}
		//Init is Can
		this->isMove = false;
		this->isMoveJump = true;
		this->canMove = false;
		this->canJump = false;
		//Init Animation
		if (this->isLeft == true)
		{
			if (this->m_vx != 0)
			{
				this->m_vx = -180;
			}
		}
		else
		{
			if (this->m_vx != 0)
			{
				this->m_vx = 180;
			}
		}
		if (this->isKey_Z == true)
		{
			this->isAttack = true;
		}
		if (this->isAttack == true)
		{
			this->m_startFrame = 5;
			this->m_endFrame = 7;
			this->m_Height = 64;
			if (this->cane->Use())
			{
				this->isAttack = false;
			}
		}
		else
		{
			if (this->m_vy>this->m_weight * 10)
			{
				this->m_startFrame = 4;
				this->m_endFrame = 4;
				this->m_Height = 50;
			}
			else
			{
				if (this->m_vy < -300)
				{
					this->simon_Status = IDLE;
					this->UpdateStatus(deltaTime);
					break;
				}
				if (this->m_vy < 0)
				{
					this->m_startFrame = 0;
					this->m_endFrame = 0;
					this->m_Height = 68;
					break;
				}
				
			}
		}

		break;
	case MOVE_JUMP_ATTACK:
		//Init is Can
		this->isMove = false;
		this->isMoveJump = false;
		this->canMove = false;
		this->canJump = false;
		break;
	case ONSTAIR:
		this->canSit = false;
		this->canJump = false;
		this->canMove = false;
		this->canAttack = false;
		this->m_vx = this->m_vy = 80;
		this->m_elapseTimeChangeFrame = 0.1f;
		//Dung cane
		if (this->isKey_Z == true)
		{
			this->isAttack = true;
		}
		if (this->isAttack == true)
		{
			if (this->isDownStair == true)
			{
				this->m_startFrame = 18;
				this->m_endFrame = 20;
			}
			else
			{
				this->m_startFrame = 21;
				this->m_endFrame = 23;
			}
			this->m_Height = 66;
			if (this->cane->Use())
			{
				this->isAttack = false;
				this->isKey_Z = false;
			}
			break;
		}
		//Xet Frame 
		if (this->isCancelStairMove == false)
		{
			if (this->isDownStair == true)
			{
				this->m_startFrame = 10;
				this->m_endFrame = 11;
				break;
			}
			if (this->isUpStair == true)
			{
				this->m_startFrame = 12;
				this->m_endFrame = 13;
				break;
			}
		}
		else
		{
			if (this->isDownStair == true)
			{
				this->m_startFrame = 10;
				this->m_endFrame = 10;
				break;
			}
			if (this->isUpStair == true)
			{
				this->m_startFrame = 12;
				this->m_endFrame = 12;
				break;
			}
		}


		break;
	case JUMP:
		this->isKey_X = false;
		if (this->isJump == false)
		{
			this->m_vy = this->m_vyDefault + this->m_weight * 10;
		}
		//Init Is Can
		this->isJump = true;
		this->canJump = false;
		this->canMove = false;
		this->canSit = false;
		this->canAttack = true;
		//Init Animation
		if (this->isKey_Z == true)
		{
			this->isAttack = true;
		}
		if (this->isAttack == true)
		{
			this->m_startFrame = 5;
			this->m_endFrame = 7;
			this->m_Height = 64;
			if (this->cane->Use())
			{
				this->isAttack = false;
			}
		}
		else
		{
			this->m_startFrame = 4;
			this->m_endFrame = 4;
			this->m_Height = 50;
		}

		break;

	case SIT:
		this->isSit = true;
		this->canJump = false;
		this->canAttack = true;
		this->canMove = false;
		this->canSit = false;
		if (this->isKey_Z == true)
		{
			this->isAttack = true;
		}
		if (this->isAttack == false)
		{
			this->m_startFrame = 4;
			this->m_endFrame = 4;
			this->m_Height = 66;
			//this->m_Pos.y = 85;
		}
		else
		{
			/*this->m_Pos.y += 9;*/
			this->m_startFrame = 15;
			this->m_endFrame = 17;
			this->m_Height = 66;
		}
		break;
	case FALL:
		canMove = canAttack = canJump = canSit = false;
		/*this->m_vy += this->m_a * deltaTime * 1.2;
		this->m_Pos.y += this->m_vy * deltaTime;
		this->m_startFrame = 0;
		this->m_endFrame = 0;*/
		break;
	case ACTACK:
		this->isAttack = true;
		this->canMove = this->canJump = this->canSit = this->canAttack = false;
		this->isMove = this->isJump = false;
		//ManageAudio::GetInstance()->playSound(TypeAudio::Using_Whip);
		this->m_startFrame = 5;
		this->m_endFrame = 7;
		break;
	case WEAPON_ATTACK:
		this->canMove = this->canJump = this->canSit = this->canAttack = false;
		this->isMove = this->isJump = false;
		//ManageAudio::GetInstance()->playSound(TypeAudio::Using_Whip);
		if (this->isSit == false)
		{
			this->m_startFrame = 5;
			this->m_endFrame = 7;
		}
		else
		{
			this->m_startFrame = 15;
			this->m_endFrame = 17;
		}
		
		break;
	case COLLISION_ENEMY:
		this->isUnAvailable = true;
		this->isCollisionEnemy = true;
		this->canAttack = this->canMove = this->canSit = false;
		this->canFall = false;
		this->canJump = false;
		this->m_startFrame = 8;
		this->m_endFrame = 8;
		this->m_Height = 68;
		break;

	default:
		break;
	}
	/*if (isChangeStatus)
	{


	}*/
}

void CSimon::ActionUpdate(float deltaTime)
{
	this->OnKeyDown(deltaTime);
	this->OnKeyUp(deltaTime);
	this->UpdateStatus(deltaTime);
	//update camera
	CCamera::GetInstance()->Update(this->m_Pos.x, this->m_Pos.y);
#pragma region On UnAvailable
	if (this->isUnAvailable == true)
	{
		this->timeUnAvailable += deltaTime;
		if (this->timeUnAvailable >= 2.0f)
		{
			this->isUnAvailable = false;
			this->isUnAvailableDraw = false;
			this->timeUnAvailable = 0.0f;
		}
	}
#pragma endregion
#pragma region On Event Weapon Attack
	if (this->isWeaponAttacking == true || (this->timeDelayWeaponAttacking<0.3f && this->timeDelayWeaponAttacking >=0))
	{
		if (this->isSit == true)
		{
			this->m_startFrame = 15;
			this->m_endFrame = 17;
		}
		else
		{
			this->m_startFrame = 5;
			this->m_endFrame = 7;
		}
	}
#pragma endregion
#pragma region On Event Key_X (JUMP)
	if (this->canJump == true)
	{
		if (this->isKey_X == true)
		{
			this->simon_Status = SIMON_status::JUMP;
			this->UpdateStatus(deltaTime);
		}
	}
	if (this->isJump == true)
	{
		if (this->isAttack == true)
		{
			if (this->cane->Use())
			{

				this->isAttack = false;
				this->isKey_Z = false;
				this->m_startFrame = 0;
				this->m_endFrame = 0;
				this->m_Height = 68;
			}
		}
		this->JumpUpdate(deltaTime);
		return;
	}

#pragma endregion
#pragma region On Event Move
	if (this->canMove == true)
	{
		if (this->isArrowKeyLeft == true || this->isArrowKeyRight == true)
		{
			this->m_Dir = (this->isArrowKeyLeft) ? Direction::LEFT:Direction::RIGHT;
			this->simon_Status = SIMON_status::MOVE;
		}
		else
		{
			this->simon_Status = SIMON_status::IDLE;
		}
	}
	if (this->isMove == true)
	{
		if ((this->isArrowKeyLeft == false && this->m_Dir == LEFT) || (this->isArrowKeyRight == false && this->m_Dir == RIGHT))
		{
			this->isMove = false;
			this->simon_Status = SIMON_status::IDLE;
		}
		else
		{
			this->MoveUpdate(deltaTime);
		}
		
		return;
	}
#pragma endregion
#pragma region On Event Move Jump
	if (this->isMoveJump == true)
	{
		this->m_Pos.y += this->m_vy * deltaTime;
		this->m_vy += (this->m_a - 700) * deltaTime;
		this->m_Pos.x += this->m_vx * deltaTime;
		if (!(this->m_vy <= this->m_weight * 10))
		{
			if (this->m_vx != 0)
			{
				this->m_vx = 50;
			}
			
		}
		return;
	}
#pragma endregion
#pragma region On Event Attack
	if (this->canAttack = true)
	{
		if (this->isKey_Z == true && this->isSit == false && this->isMove == false && this->isOnStair == false && this->isCollisionEnemy == false)
		{
			this->simon_Status = SIMON_status::ACTACK;
		}
	}
	if (this->isAttack == true && this->isSit == false && this->isMoveJump == false && this->isOnStair == false && this->isCollisionEnemy == false)
	{
		this->AttackUpdate(deltaTime);
		return;
	}
#pragma endregion
#pragma region On Event Sit
	if (this->canSit == true)
	{
		if (this->isArrowKeyDown == true)
		{
			this->simon_Status = SIMON_status::SIT;
			return;
		}
	}
	if (this->isSit == true)
	{
		if (this->isAttack == true)
		{
			if (this->cane->Use())
			{
				this->isAttack = false;
				this->isKey_Z = false; // tranh viec giu~ phim Z thi danh lien tuc
			}
		}
	}
#pragma endregion
#pragma region On Event Enemy Collision
	if (this->simon_Status == SIMON_status::COLLISION_ENEMY)
	{
		this->EnemyCollisionUpdate(deltaTime);
		return;
	}
#pragma endregion
}

void CSimon::MoveUpdate(float deltaTime)
{
	this->m_Pos.x += this->m_vx * deltaTime;
	if (this->isJump == true)
	{
		this->m_Pos.y += this->m_vy * deltaTime;
		this->m_vy += this->m_a * deltaTime;
	}

}

void CSimon::JumpUpdate(float deltaTime)
{
	this->m_vy += this->m_a * deltaTime;
	this->m_Pos.y += this->m_vy * deltaTime;
	if (this->m_vy <= this->m_weight * 10)
	{
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		this->m_Height = 68;
	}
	if (this->m_vy <= 0)
	{
		this->simon_Status = SIMON_status::IDLE;
		this->UpdateStatus(deltaTime);
	}
}

void CSimon::SitUpdate(float deltaTime)
{
}

void CSimon::AttackUpdate(float deltaTime)
{
	if (this->cane->Use())
	{
		this->simon_Status = SIMON_status::IDLE;
		this->isKey_Z = false; // tranh viec giu~ phim Z
	}
}

void CSimon::EnemyCollisionUpdate(float deltaTime)
{
	this->timeCollisionEnemy += deltaTime;
	if (this->timeCollisionEnemy >= 0.5)
	{
		this->isCollisionEnemy = false;
		this->timeCollisionEnemy = 0;
		this->simon_Status = SIMON_status::IDLE;
		this->UpdateStatus(deltaTime);
		return;
	}
	if (this->timeCollisionEnemy<0.5)
	{
		this->m_Pos.x -= deltaTime * 100;
		this->m_Pos.y += deltaTime * (100 + this->m_weight * 10);
	}
}

void CSimon::FallUpdate(float deltaTime)
{
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
	case DIK_L:
		this->isKey_L = true;
		break;
	case DIK_SPACE:
		/*if (canJump)
		{
		this->isJump = true;
		this->simon_Status = SIMON_status::JUMP;
		this->m_vy = m_vyDefault;
		}*/
		break;
	case DIK_LEFT:
		if (this->isCancelStairMove == true)
		{
			this->isArrowKeyLeft = true;
		}

		/*if (this->canMove)
		{
		isMoveLeft = true;
		isLeft = true;
		this->cane->isLeft = true;
		this->m_Dir = Direction::LEFT;
		this->cane->m_Dir = Direction::LEFT;
		this->simon_Status = SIMON_status::MOVE;
		}*/
		break;
	case DIK_RIGHT:
		if (this->isCancelStairMove == true)
		{
			this->isArrowKeyRight = true;
		}

		/*isMoveLeft = false;
		isLeft = false;
		this->cane->isLeft = false;
		this->m_Dir = Direction::RIGHT;
		this->cane->m_Dir = Direction::RIGHT;
		this->simon_Status = SIMON_status::MOVE;*/
		break;
	case DIK_UP:
		if (this->isCancelStairMove == true)
		{
			this->isArrowKeyUp = true;
		}

		break;
	case DIK_DOWN:
		if (this->isCancelStairMove == true)
		{
			this->isArrowKeyDown = true;
		}
		if (this->canChangeDown)
		{
			isChangeDown = true;
			isCheckChangeState = true;
		}
		//if (this->canSit == true)
		//{
		//	this->isSit = true;
		//	this->simon_Status = SIMON_status::SIT;
		//	this->canMove = false;
		//	this->canJump = false;
		//}
		break;

	case DIK_X:
		if (this->canJump == true)
		{
			this->isKey_X = true;
		}
		break;

	case DIK_Z:
		this->isKey_Z = true;
		break;

	case DIK_Q:
		this->cane->updateState(state2);
		break;
	case DIK_C: //test change status
		this->m_hpSimon -= 1;
		break;
	case DIK_V: //test change status
		this->isCheckChangeState = true;
		break;
	case DIK_E:
		this->isWeaponAttacking = true;
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
		this->isArrowKeyLeft = false;
		break;
	case DIK_RIGHT:
		this->isArrowKeyRight = false;
		break;
	case DIK_UP:
		this->isArrowKeyUp = false;
		break;
	case DIK_DOWN:
		this->isArrowKeyDown = false;
		if (this->isSit == true)
		{
			simon_Status = SIMON_status::IDLE;
		}
		break;
	case DIK_X:
		this->isKey_X = false;
		break;
	case DIK_Z:
		this->isKey_Z = false;
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



