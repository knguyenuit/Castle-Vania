#include "FishMan.h"

CFishMan::CFishMan()
{
	Init();
}

CFishMan::CFishMan(Vector2 pos, std::vector<CEnemy*> &ListEnemy)
{
	Init();
	this->m_PosDefault = this->m_Pos = pos;
	this->m_FireBall = new CFireBall(this->m_Pos, LEFT);
	ListEnemy.push_back(this->m_FireBall);
}


CFishMan::~CFishMan()
{
}

void CFishMan::Init()
{
	this->enemyType = ENEMY_type::FishMan;
	this->m_Id = this->enemyType;
	this->m_State = ENEMY_state::IDLE;
	this->m_Width = 32;
	this->m_Height = 64;
	this->m_vx = 100;
	this->m_vy = 200;
	//Init Animation
	this->m_startFrame = 0;
	this->m_endFrame = 2;
	this->m_currentTime = 0;
	this->m_column = 3;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_currentFrame = 2;
	this->m_increase = 1;
	this->m_totalFrame = 3;
}

void CFishMan::Update(float deltaTime)
{
	//this->m_FireBall->Update(deltaTime);

	if ((this->m_Pos.x<CSimon::GetInstance()->m_Pos.x - 100 || this->m_Pos.x>CSimon::GetInstance()->m_Pos.x + 100)
		&& this->m_State == ENEMY_state::IDLE)
	{
		this->m_State = ENEMY_state::JUMP;

	}
	if (this->m_State != ENEMY_state::IDLE)
	{
		this->MoveUpdate(deltaTime);

	}
}


void CFishMan::MoveUpdate(float deltaTime)
{

	switch (this->m_State)
	{
	case ENEMY_state::JUMP:
		this->m_Pos.y = this->m_FireBall->m_Pos.y += this->m_vy * deltaTime;
		if (this->m_Pos.y >= 150)
		{
			this->m_State = ENEMY_state::MOVE;
			this->m_startFrame = 1;
			this->m_endFrame = 2;
		}
		break;

	case ENEMY_state::MOVE:
		if (this->MoveTo(Vector2(CSimon::GetInstance()->m_Pos.x + ((this->m_Dir == LEFT) ? 100 : -100), CSimon::GetInstance()->m_Pos.y), deltaTime) == true)
		{
			this->m_State = ENEMY_state::ATTACK;
		}
		this->m_FireBall->m_Pos = Vector2(this->m_Pos.x, this->m_Pos.y + 20);
		this->ChangeFrame(deltaTime);

		break;
	case ENEMY_state::ATTACK:
		/*	if (this->m_FireBall==NULL)
		{

		}*/
		if (this->time_delay_attack <= 0)
		{
			this->m_State = ENEMY_state::MOVE;
			this->time_delay_attack = 3.0f;
		}
		else
		{
			this->time_delay_attack -= deltaTime;
		}
		if (this->m_FireBall->MoveTo(Vector2(this->m_Pos.x + ((this->m_Dir == LEFT) ? -600 : 600), this->m_Pos.y + 20), deltaTime))
		{

		}
		break;
	default:
		break;
	}

}

RECT * CFishMan::GetRectRS()
{
	return this->UpdateRectResource(this->m_Height, this->m_Width);
}
