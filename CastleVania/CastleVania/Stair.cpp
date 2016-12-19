#include "Stair.h"



CStair::CStair()
{
	this->Init();
}

CStair::CStair(HideObject_TYPE type, Vector2 pos)
{
	this->Init();
	this->m_typeHideObject = type;
	this->m_Pos = pos;
}



CStair::~CStair()
{
}

void CStair::OnSimonCollision(float deltaTime)
{
	if (abs(this->simon->m_Pos.x - this->m_Pos.x) < 30
		&& abs(this->simon->m_Pos.y - this->m_Pos.y) < 50)
	{
		this->resetCanStair(); //khi va cham thi chuyen het canstair ve false
		this->simon->currStairPos = this->m_Pos; // khi va cham voi cuc cau thang nao thi stairpos cua con simon = voi pos cua cuc do

		switch (this->m_typeHideObject)
		{
		case HideObject_TYPE::UpStairRight:
			this->simon->canUpStairRight = true;
			if (this->simon->isOnStair == false) //Neu dang ko o tren cau thang
			{
				this->simon->currSimonStairPos = this->m_Pos + Vector2(0, 16); //set currsiomstairPos = this->pos
																			   //Neu an nut Up va con simon da~ toi" dung cho len cau thang
				if (this->simon->isArrowKeyUp == true && this->simon->m_Pos == this->simon->currSimonStairPos)
				{
					this->simon->isOnStair = true;
				}
				else // Neu chua toi dung cho
				{
					if (this->simon->isArrowKeyUp == true)
					{
						this->simon->isCancelStairMove = false;
					}
					//Truoc khi len cau thang thi di chuyen con simon toi dung vi tri cua cau thang
					if (this->simon->isCancelStairMove == false)
					{
						//Init Move Simon
						this->simon->m_startFrame = 0;
						this->simon->m_endFrame = 3;
						this->simon->m_vx = this->simon->m_vy = 150;
						if (this->simon->MoveTo(this->simon->currSimonStairPos, deltaTime))
						{

							if (this->simon->isArrowKeyUp == false)
							{
								this->simon->isCancelStairMove = true;
								this->simon->simon_Status = SIMON_status::IDLE;
							}
							else
							{
								this->simon->isOnStair = true;
							}
						}
					}
				}
			}
			else //Neu dang o tren cau thang
			{
				if (this->simon->currSimonStairPos.y - this->m_Pos.y < 48 && this->simon->isDownStair && this->simon->m_Dir == LEFT)
				{
					this->simon->currSimonStairPos = this->m_Pos + Vector2(0, 16);
					this->simon->prepareDownStair = true;
				}
				else
				{
					this->simon->prepareDownStair = false;
				}
			}



			break;
		case HideObject_TYPE::DownStairLeft:
			this->simon->canDownStairLeft = true;
			this->simon->canSit = false;
			//Neu simon dung cuc downstairleft khi dang o tren cau thang thi prepareUp = true
			if (this->simon->isOnStair == true)
			{
				if (abs(this->simon->currSimonStairPos.y - this->m_Pos.y) < 16 && this->simon->isUpStair && this->simon->m_Dir == RIGHT)
				{
					this->simon->prepareUpStair = true;
				}
				else
				{
					this->simon->prepareUpStair = false;
				}
			}
			else // Neu dung khi khong o tren cau thang
			{
				this->simon->prepareUpStair = false;
				this->simon->currSimonStairPos = this->m_Pos + Vector2(5, 14); //set currsiomstairPos = this->pos
				if (this->simon->isArrowKeyDown == true && this->simon->m_Pos == this->simon->currSimonStairPos)
				{
					this->simon->isOnStair = true;
				}
				else
				{
					if (this->simon->isArrowKeyDown == true)
					{
						this->simon->isCancelStairMove = false;
					}
					if (this->simon->isCancelStairMove == false)
					{
						//Init Move Simon
						this->simon->m_startFrame = 0;
						this->simon->m_endFrame = 3;
						this->simon->m_vx = this->simon->m_vy = 150;
						if (this->simon->MoveTo(this->simon->currSimonStairPos, deltaTime))
						{
							if (this->simon->isArrowKeyDown == false)
							{
								this->simon->isCancelStairMove = true;
								this->simon->simon_Status = SIMON_status::IDLE;
							}
							else
							{
								this->simon->isOnStair = true;
							}
						}
					}

				}
			}

			break;
		case HideObject_TYPE::UpStairLeft:
			this->simon->canUpStairLeft = true;
			if (this->simon->isOnStair == false) //Neu dang ko o tren cau thang
			{
				this->simon->currSimonStairPos = this->m_Pos + Vector2(0, 16); //set currsiomstairPos = this->pos
																			   //Neu an nut Up va con simon da~ toi" dung cho len cau thang
				if (this->simon->isArrowKeyUp == true && this->simon->m_Pos == this->simon->currSimonStairPos)
				{
					this->simon->isOnStair = true;
				}
				else // Neu chua toi dung cho
				{
					if (this->simon->isArrowKeyUp == true)
					{
						this->simon->isCancelStairMove = false;
					}
					//Truoc khi len cau thang thi di chuyen con simon toi dung vi tri cua cau thang
					if (this->simon->isCancelStairMove == false)
					{
						//Init Move Simon
						this->simon->m_startFrame = 0;
						this->simon->m_endFrame = 3;
						this->simon->m_vx = this->simon->m_vy = 150;
						if (this->simon->MoveTo(this->simon->currSimonStairPos, deltaTime))
						{

							if (this->simon->isArrowKeyUp == false)
							{
								this->simon->isCancelStairMove = true;
								this->simon->simon_Status = SIMON_status::IDLE;
							}
							else
							{
								this->simon->isOnStair = true;
							}
						}
					}
				}
			}
			else //Neu dang o tren cau thang
			{
				if (this->simon->currSimonStairPos.y - this->m_Pos.y < 36 && this->simon->isDownStair && this->simon->m_Dir == RIGHT)
				{
					if (this->simon->isArrowKeyDown)
					{
						this->simon->currSimonStairPos = this->m_Pos + Vector2(0, 16);
						this->simon->prepareDownStair = true;
					}

				}
				else
				{
					this->simon->prepareDownStair = false;
				}
			}
			break;
		case HideObject_TYPE::DownStairRight:
			this->simon->canDownStairRight = true;
			this->simon->canSit = false;
			//Neu simon dung cuc downstairleft khi dang o tren cau thang thi prepareUp = true
			if (this->simon->isOnStair == true)
			{
				if (abs(this->simon->currSimonStairPos.y - this->m_Pos.y) < 16 && this->simon->isUpStair && this->simon->m_Dir == LEFT)
				{
					this->simon->currSimonStairPos = this->m_Pos + Vector2(0, 12);
					this->simon->prepareUpStair = true;
				}
				else
				{
					this->simon->prepareUpStair = false;
				}
			}
			else // Neu va cham khi khong o tren cau thang
			{
				this->simon->prepareUpStair = false;
				this->simon->currSimonStairPos = this->m_Pos + Vector2(12, 14); //set currsiomstairPos = this->pos
				if (this->simon->isArrowKeyDown == true && this->simon->m_Pos == this->simon->currSimonStairPos)
				{
					this->simon->isOnStair = true;
				}
				else
				{
					if (this->simon->isArrowKeyDown == true)
					{
						this->simon->isCancelStairMove = false;
					}
					if (this->simon->isCancelStairMove == false)
					{
						//Init Move Simon
						this->simon->m_startFrame = 0;
						this->simon->m_endFrame = 3;
						this->simon->m_vx = this->simon->m_vy = 150;
						if (this->simon->MoveTo(this->simon->currSimonStairPos, deltaTime))
						{
							if (this->simon->isArrowKeyDown == false)
							{
								this->simon->isCancelStairMove = true;
								this->simon->simon_Status = SIMON_status::IDLE;
							}
							else
							{
								this->simon->isOnStair = true;
							}
						}
					}

				}
			}
			break;
		default:
			break;
		}
	}
}

void CStair::Update(float deltaTime)
{
	this->OnSimonCollision(deltaTime);

	if (this->simon->isOnStair)
	{
		if (this->simon->isArrowKeyUp == true)
		{
			if (this->simon->canUpStairRight || this->simon->canDownStairLeft)
			{
				this->simon->m_Dir = RIGHT;
			}
			else
			{
				if (this->simon->canUpStairLeft || this->simon->canDownStairRight)
				{
					this->simon->m_Dir = LEFT;
				}
			}
			this->simon->isUpStair = true;
			this->simon->isDownStair = false;
		}
		else
		{
			if (this->simon->isArrowKeyDown == true)
			{
				if (this->simon->canUpStairRight || this->simon->canDownStairLeft)
				{
					this->simon->m_Dir = LEFT;
				}
				else
				{
					if (this->simon->canUpStairLeft || this->simon->canDownStairRight)
					{
						this->simon->m_Dir = RIGHT;
					}
				}
				this->simon->isDownStair = true;
				this->simon->isUpStair = false;
			}
		}

		this->simon->simon_Status = SIMON_status::ONSTAIR;
		this->SimonMove(deltaTime);
	}
}

void CStair::SimonMove(float deltaTime)
{
	if (this->simon->isArrowKeyUp == true || this->simon->isArrowKeyDown == true)
	{
		this->simon->isCancelStairMove = false;
	}
	if (this->simon->isCancelStairMove == false)
	{
		if (this->simon->isUpStair && this->simon->m_Dir == RIGHT)
		{
			this->MoveUpStairRight(deltaTime);
		}
		if (this->simon->isUpStair && this->simon->m_Dir == LEFT)
		{
			this->MoveUpStairLeft(deltaTime);
		}
		if (this->simon->isDownStair && this->simon->m_Dir == LEFT)
		{
			this->MoveDownStairLeft(deltaTime);
		}
		if (this->simon->isDownStair && this->simon->m_Dir == RIGHT)
		{
			this->MoveDownStairRight(deltaTime);
		}
	}

}

void CStair::MoveUpStairRight(float deltaTime)
{
	if (this->simon->canUpStairRight)
	{
		if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, 16), deltaTime))
		{
			this->simon->currSimonStairPos = this->simon->m_Pos;
			if (this->simon->isArrowKeyUp == false)
			{
				this->simon->isCancelStairMove = true;
			}
			this->simon->currStairStep += 1;
		}

	}
	else
	{
		if (this->simon->canDownStairLeft)
		{
			//Neu con simon dang chuan bi di len het cau thang
			if (this->simon->prepareUpStair == true)
			{

				if (this->simon->MoveTo(this->simon->currStairPos + Vector2(16, 14), deltaTime))
				{
					this->simon->currSimonStairPos = this->simon->m_Pos;
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareUpStair = false;
					this->simon->isCancelStairMove = true;
				}
			}
			else
			{
				if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, 16), deltaTime))
				{
					this->simon->currSimonStairPos = this->simon->m_Pos;
					if (this->simon->isArrowKeyUp == false)
					{
						this->simon->isCancelStairMove = true;
					}
				}
			}

		}
	}
}

void CStair::MoveDownStairLeft(float deltaTime)
{
	
	if (this->simon->canDownStairLeft)
	{
		if (this->simon->MoveTo(this->simon->currSimonStairPos - Vector2(16, 16), deltaTime))
		{
			this->simon->currSimonStairPos = this->simon->m_Pos;
			if (this->simon->isArrowKeyDown == false)
			{
				this->simon->isCancelStairMove = true;
			}
		}
	}
	else
	{
		if (this->simon->canUpStairRight)
		{
			//Neu con si mon chuan bi di xuong het cau thang
			if (this->simon->prepareDownStair == true)
			{
				if (this->simon->MoveTo(this->simon->currSimonStairPos, deltaTime))
				{
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareDownStair = false;
				};

			}
			else
			{
				if (this->simon->MoveTo(this->simon->currSimonStairPos - Vector2(16, 16), deltaTime))
				{
					this->simon->currSimonStairPos = this->simon->m_Pos;
					if (this->simon->isArrowKeyDown == false)
					{
						this->simon->isCancelStairMove = true;
					}
				}
			}

		}
	}
}

void CStair::MoveUpStairLeft(float deltaTime)
{
	if (this->simon->canUpStairLeft)
	{
		if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(-16, 16), deltaTime))
		{
			this->simon->currSimonStairPos = this->simon->m_Pos;
			if (this->simon->isArrowKeyUp == false)
			{
				this->simon->isCancelStairMove = true;
			}
		}

	}
	else
	{
		if (this->simon->canDownStairRight)
		{
			//Neu con simon dang chuan bi di len het cau thang
			if (this->simon->prepareUpStair == true)
			{

				if (this->simon->MoveTo(this->simon->currStairPos + Vector2(0, 14), deltaTime))
				{
					this->simon->currSimonStairPos = this->simon->m_Pos;
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareUpStair = false;
					this->simon->isCancelStairMove = true;
				}
			}
			else
			{
				if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(-16, 16), deltaTime))
				{

					this->simon->currSimonStairPos = this->simon->m_Pos;
					if (this->simon->isArrowKeyUp == false)
					{
						this->simon->isCancelStairMove = true;
					}
				}
			}

		}
	}
}

void CStair::MoveDownStairRight(float deltaTime)
{
	if (this->simon->canDownStairRight)
	{
		if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, -16), deltaTime))
		{

			this->simon->currSimonStairPos = this->simon->m_Pos;
			if (this->simon->isArrowKeyDown == false)
			{
				this->simon->isCancelStairMove = true;
			}
		}
	}
	else
	{
		if (this->simon->canUpStairLeft)
		{

			//Neu con si mon chuan bi di xuong het cau thang
			if (this->simon->prepareDownStair == true)
			{
				if (this->simon->MoveTo(this->simon->currSimonStairPos, deltaTime))
				{
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareDownStair = false;
				};

			}
			else
			{
				if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, -16), deltaTime))
				{
					this->simon->currSimonStairPos = this->simon->m_Pos;
					if (this->simon->isArrowKeyDown == false)
					{
						this->simon->isCancelStairMove = true;
					}
				}
			}

		}
	}
}

void CStair::resetCanStair()
{
	this->simon->canDownStairLeft = this->simon->canDownStairRight = this->simon->canUpStairLeft = this->simon->canUpStairRight = false;
}

