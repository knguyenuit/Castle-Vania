#include "BossVampireBat.h"

void CBossVampireBat::Init()
{
	this->enemyType = ENEMY_type::BossVampireBat;
	this->m_Id = this->enemyType;
	this->m_Width = 96;
	this->m_Height = 46;

	this->m_vx = 200;
	this->m_vy = 100;

	this->m_Dir = Direction::RIGHT;
	//init animation
	this->m_startFrame = 0;
	this->m_endFrame = 2;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.3f;
	this->m_increase = 1;
	this->m_totalFrame = 3;
	this->m_column = 3;
	//init Direction
	this->check_arrive_x = this->check_arrive_y = false;
	this->isLeft = this->isRight = this->isUp = this->isDown = false;
}

CBossVampireBat::CBossVampireBat()
{
	this->Init();
}

CBossVampireBat::CBossVampireBat(Vector2 pos)
{
	this->Init();
	this->m_PosDefault = pos;
	this->SetPos(pos);
}


CBossVampireBat::~CBossVampireBat()
{
}

bool CBossVampireBat::MoveTo(Vector2 point, float deltaTime)
{
	if (!this->isLeft && !this->isRight)
	{

		if (this->m_Pos.x > point.x) //kiem tra xem co phai qua ben trai
		{
			this->isLeft = true;
		}
		else
		{
			this->isRight = true;
		}
	}

	if (this->isLeft) // neu isleft thi van toc x am
	{
		this->m_vx = (this->m_vx>0) ? -this->m_vx : this->m_vx;
	}
	else
	{
		this->m_vx = (this->m_vx<0) ? -this->m_vx : this->m_vx;
	}

	//kiem tra xem co toi toa do X cua point chua
	if ((this->isLeft && this->m_Pos.x <= point.x) || (this->isRight && this->m_Pos.x >= point.x))
	{
		this->check_arrive_x = true;
		this->m_Pos.x = point.x;
	}
	if (!this->check_arrive_x)
	{
		this->m_Pos.x += this->m_vx * deltaTime; // thay doi pos.x cua Boss
	}



	if (!this->isDown && !this->isUp)
	{
		if (this->m_Pos.y > point.y) // kiem tra xem co phai di xuong duoi
		{
			this->isDown = true;
		}
		else
		{
			this->isUp = true;
		}
	}
	if (this->isDown) // neu isdown thi van toc y am
	{
		this->m_vy = (this->m_vy > 0) ? -this->m_vy : this->m_vy;
	}
	else // neu isUp thi van toc y duong
	{
		this->m_vy = (this->m_vy < 0) ? -this->m_vy : this->m_vy;
	}

	//neu da toi point.y
	if ((this->isDown && this->m_Pos.y <= point.y) || (this->isUp && this->m_Pos.y >= point.y))
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
		this->isLeft = this->isRight = this->isUp = this->isDown = false;
		return true;
	}
	else
	{
		return false;
	}
}

RECT * CBossVampireBat::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}

void CBossVampireBat::Update(float deltaTime)
{
	if (this->m_Pos.x <= CSimon::GetInstance()->m_Pos.x&&this->m_State == ENEMY_state::IDLE)
	{
		this->m_State = ENEMY_state::MOVE;
	}
	if (this->m_State == ENEMY_state::MOVE)
	{
		//animate
		this->m_startFrame = 1;
		ChangeFrame(deltaTime);
		this->MoveUpdate(deltaTime);
	}

}

void CBossVampireBat::MoveUpdate(float deltaTime)
{

	CSimon *simon = CSimon::GetInstance();
	CCamera *camera = CCamera::GetInstance();
	float simonPosX = simon->m_Pos.x, simonPosY = simon->m_Pos.y;
	float cameraPosX = camera->m_pos.x, cameraPosY = camera->m_pos.y;
	if (this->m_State == ENEMY_state::MOVE)
	{
		switch (this->m_Step)
		{
		case 1:
			if (this->m_isAttacking == false)
			{
				this->m_isAttacking = true;
				int index = rand() % 5;
				this->m_StepPos[0] = Vector2(this->m_PosDefault.x + this->m_pos_x_prepare_attack[index], simon->m_Pos.y + this->m_pos_y_prepare_attack[index]);
				int index2 = rand() % 5;
				while (index == index2)
				{
					index2 = rand() % 5;
				}
				this->m_StepPos[2] = Vector2(this->m_PosDefault.x + this->m_pos_x_prepare_attack[index2], simon->m_Pos.y + this->m_pos_y_prepare_attack[index2]);
			}
			this->m_vy = 150;
			if (this->MoveTo(this->m_StepPos[0], deltaTime) == true)
			{
				this->time_delay_step -= deltaTime;
				if (this->time_delay_step <= 0)
				{
					this->m_StepPos[1] = Vector2(simon->m_Pos.x, simon->m_Pos.y);
					this->m_Step = 2;
					this->time_delay_step = 1.0f;
				}

			}
			break;
		case 2:
			this->m_vx = 300;
			this->m_vy = 200;
			if (this->MoveTo(this->m_StepPos[1], deltaTime) == true)
			{
				this->m_Step = 3;
			}
			break;
		case 3:
			this->m_vx = 250;
			this->m_vy = 150;
			if (this->MoveTo(this->m_StepPos[2], deltaTime) == true)
			{
				this->time_delay_step -= deltaTime;
				if (this->time_delay_step <= 0)
				{
					this->m_isAttacking = false;
					this->m_Step = 1;
					this->time_delay_step = 1.5f;
				}
			}
			break;
		default:
			break;
		}


	}

}
