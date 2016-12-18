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
			//set currsiomstairPos = this->pos
			if (this->simon->currSimonStairPos.y < this->m_Pos.y)
			{
				this->simon->currSimonStairPos = this->m_Pos;
			}
			//Neu an nut len va simon khong o trong trang thai tren cau thang thi` chuyen trang thai con simon thanh onstair
			if (this->simon->isArrowKeyUp == true && this->simon->isOnStair == false)
			{

				this->simon->isOnStair = true;
			}

			//Neu simon dung cuc upstairRight ma khi dang tren cau thang thi prepareDownStair = true
			if (this->simon->isOnStair == true)
			{
				if (this->simon->isArrowKeyDown == true)
				{
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
			if (this->simon->currSimonStairPos.y >= this->m_Pos.y)
			{
				this->simon->currSimonStairPos = this->m_Pos + Vector2(0, 12);
			}
			//Neu simon dung cuc downstairleft khi dang o tren cau thang thi prepareUp = true
			if (this->simon->isOnStair == true)
			{
				if (this->simon->m_Pos.x > this->simon->currStairPos.x)
				{
					this->simon->prepareUpStair = true;
				}
				else
				{
					this->simon->prepareUpStair = false;
				}
			}
			else
			{
				if (this->simon->isArrowKeyDown == true)
				{
					this->simon->isOnStair = true;
				}
			}

			break;
		case HideObject_TYPE::UpStairLeft:

			break;
		case HideObject_TYPE::DownStairRight:

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

		Vector2 next;
		next.x = this->simon->currSimonStairPos.x + 16;
		next.y = this->simon->currSimonStairPos.y + 16;
		if (this->simon->MoveTo(next, deltaTime))
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
			if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, 16), deltaTime))
			{
				this->simon->currSimonStairPos = this->simon->m_Pos;
				if (this->simon->isArrowKeyUp == false)
				{
					this->simon->isCancelStairMove = true;
				}
				this->simon->currStairStep += 1;
				//Neu con simon dang chuan bi di len het cau thang
				if (this->simon->prepareUpStair == true)
				{
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareUpStair = false;
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
			this->simon->currStairStep += 1;
		}
	}
	else
	{
		if (this->simon->canUpStairRight)
		{

			Vector2 next;
			next = this->simon->currSimonStairPos - Vector2(16, 16);
			if (this->simon->MoveTo(next, deltaTime))
			{
				this->simon->currSimonStairPos = this->simon->m_Pos;
				if (this->simon->isArrowKeyDown == false)
				{
					this->simon->isCancelStairMove = true;
				}
				this->simon->currStairStep -= 1;
				//Neu con si mon chuan bi di xuong het cau thang
				if (this->simon->prepareDownStair == true)
				{
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareDownStair = false;
				}
			}
		}
	}
}

void CStair::MoveDownStairRight(float deltaTime)
{
	if (this->simon->canDownStairLeft)
	{
		Vector2 next;
		next.x = this->m_Pos.x - this->simon->currStairStep * 16 - 12;
		next.y = this->m_Pos.y - this->simon->currStairStep * 16 + 14;
		if (this->simon->MoveTo(next, deltaTime))
		{
			if (this->simon->isArrowKeyDown == false)
			{
				this->simon->isCancelStairMove = true;
			}
			this->simon->currStairStep += 1;
		}

	}
	else
	{
		if (this->simon->canUpStairRight)
		{

			Vector2 next;
			next = this->simon->currSimonStairPos - Vector2(16, 16);
			if (this->simon->MoveTo(next, deltaTime))
			{
				this->simon->currSimonStairPos = this->simon->m_Pos;
				if (this->simon->isArrowKeyDown == false)
				{
					this->simon->isCancelStairMove = true;
				}
				this->simon->currStairStep -= 1;
				//Neu con si mon chuan bi di xuong het cau thang
				if (this->simon->prepareDownStair == true)
				{
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareDownStair = false;
				}
			}
		}
	}
}

void CStair::MoveUpStairLeft(float deltaTime)
{
	if (this->simon->canUpStairRight)
	{

		Vector2 next;
		next.x = this->simon->currSimonStairPos.x + 16;
		next.y = this->simon->currSimonStairPos.y + 16;
		if (this->simon->MoveTo(next, deltaTime))
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
			if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, 16), deltaTime))
			{
				this->simon->currSimonStairPos = this->simon->m_Pos;
				if (this->simon->isArrowKeyUp == false)
				{
					this->simon->isCancelStairMove = true;
				}
				this->simon->currStairStep += 1;
				//Neu con simon dang chuan bi di len het cau thang
				if (this->simon->prepareUpStair == true)
				{
					this->simon->isOnStair = false;
					this->simon->simon_Status = SIMON_status::IDLE;
					this->simon->prepareUpStair = false;
				}
			}
		}
	}
}

void CStair::resetCanStair()
{
	this->simon->canDownStairLeft = this->simon->canDownStairRight = this->simon->canUpStairLeft = this->simon->canUpStairRight = false;
}

