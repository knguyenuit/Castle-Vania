#include "UpStairRight.h"



CUpStairRight::CUpStairRight()
{
	this->Init();
}

CUpStairRight::CUpStairRight(Vector2 pos)
{
	this->Init();
	this->m_Pos = pos;
	this->m_typeHideObject = HideObject_TYPE::UpStairRight;
}


CUpStairRight::~CUpStairRight()
{
}

void CUpStairRight::Update(float deltaTime)
{
	this->OnSimonCollision(deltaTime);
	if (this->simon->currStairPos == this->m_Pos) // chi chay khi con khi con simon da dung trung no
	{
		// neu cuc nay dang va cham voi con simon
		if (this->isSimonCollision == true)
		{
			if (this->simon->isArrowKeyUp == true) // va nhan nut Up
			{
				if (this->simon->isOnStair == false) //va con simon dang khong o tren cau thang
				{
					if (this->simon->prepareOnStair == false) //Va con simon khong o trang thai chuan bi len cau thang
					{
						this->simon->isMoveToStair = true; //thi gan co` la dang di toi cho cau thang
						this->simon->isCancelStairMove = false;
					}
					else //Neu o trang thai chuan bi len cau thang
					{
						this->simon->isUpStair = true;
						this->simon->isDownStair = false;
						this->simon->isOnStair = true;//Dat trang thai con simon la dang o tren cau thang
						this->simon->simon_Status = SIMON_status::ONSTAIR;
						this->simon->isFirstStairStep = true;
						this->simon->isMoveToStair = false;
						this->simon->isCancelStairMove = false;
					}
				}
				else //Neu dang o trang thai isOnStair
				{
					this->simon->isCancelStairMove = false;
					this->simon->isUpStair = true;
					this->simon->isDownStair = false;
				}
			} // End press Up
			else // Nguoc lai neu dang khong nhan phim Up
			{
				if (this->simon->isArrowKeyDown == true) // Va nhan nut Down
				{
					if (this->simon->isOnStair == true) // Va con simon dang o tren cau thang 
					{
						this->simon->isUpStair = false;
						this->simon->isDownStair = true;
						this->simon->isCancelStairMove = false;
						if (this->simon->m_Pos.y - this->simon->currStairPos.y <= 34) //Fix bug: dang o buoc thu 2 da xuong cau thang
						{
							this->simon->prepareOutStair = true; //Thi gan trang thai con simon la chuan bi ra khoi cau thang
						}

					}
					else //Nguoc lai : Neu nhan phim Down khi dang va cham voi voi cuc UpstairRight nhung khong o trang thai tren cau thang
					{
						return; //Thoat
					}
				} //End press Down
			}
			if (this->simon->m_Pos != this->simon->currStairPos + Vector2(0, 16) && this->simon->isFirstStairStep == false) // Neu simon khong dung dung cho len cau thang
			{
				this->simon->prepareOnStair = false;
			}

		}// End Dang va cham voi cuc stair nay
		else // Neu cuc nay dang khong va cham voi simon - Nhung ma no da va cham truoc do (Tuc la dang dung tren cau thang)
		{
			if (this->simon->isOnStair == true)//va con simon phai dang o trang thai onStair
			{
				if (this->simon->isArrowKeyUp == true)
				{
					this->simon->isCancelStairMove = false;
					this->simon->isUpStair = true;
					this->simon->isDownStair = false;
				}
				else
				{
					if (this->simon->isArrowKeyDown == true)
					{
						this->simon->isCancelStairMove = false;
						this->simon->isDownStair = true;
						this->simon->isUpStair = false;
					}
				}
			}

		}
		//thuc hien di chuyen
		//di chuyen den cho cau thang
		if (this->simon->isMoveToStair == true && this->simon->isCancelStairMove == false)
		{
			this->SimonMoveToStair(deltaTime);
			return;
		}
		//Di chuyen len tren cau thang buoc 1
		if (this->simon->prepareOnStair == true)
		{
			if (this->simon->isCancelStairMove == false)
			{
				if (this->SimonMoveOnStair(deltaTime) == true) //Neu da di xong buoc 1
				{
					this->simon->prepareOnStair = false; //Tat chuan bi len cau thang
					this->simon->isFirstStairStep = false; //Tat buoc dau tien len cau thang
					if (this->simon->isArrowKeyUp == false)
					{
						this->simon->isCancelStairMove = true;
					}
				}
			}

			return;
		}
		//Di chuyen tren cau thang cac buoc khac
		if (this->simon->isOnStair == true && this->simon->isCancelStairMove == false)
		{
			this->SimonMoveOnStair(deltaTime);
			return;
		}
		//Di chuyen ra khoi cau thang khi dung cuc nay
		if (this->simon->prepareOutStair == true)
		{
			this->SimonMoveOutStair(deltaTime);
			return;
		}
	}
}

bool CUpStairRight::SimonMoveOnStair(float deltaTime)
{
	if (this->simon->isUpStair == true)
	{
		if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(16, 16), deltaTime)) // Neu da di toi cho chuan bi len cau thang
		{
			this->simon->currSimonStairPos = this->simon->m_Pos;
			if (this->simon->isArrowKeyUp == false)
			{
				this->simon->isCancelStairMove = true;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (this->simon->isDownStair == true)
		{
			if (this->simon->m_Pos.y <= this->simon->currStairPos.y + 16) //Fix Bug nhan giu~ phim down thi con simon di xuong luon
			{
				this->ResetSimonStair();
				return true;
			}
			if (this->simon->MoveTo(this->simon->currSimonStairPos + Vector2(-16, -16), deltaTime)) // Neu da di toi cho chuan bi len cau thang
			{
				this->simon->currSimonStairPos = this->simon->m_Pos;
				if (this->simon->isArrowKeyDown == false)
				{
					this->simon->isCancelStairMove = true;
				}
				return true;
			}
			else
			{
				return false;
			}
		}
	}


}

bool CUpStairRight::SimonMoveToStair(float deltaTime)
{
	//Init Animation
	this->simon->m_vx = this->simon->m_vy = 40;
	this->simon->m_startFrame = 0;
	this->simon->m_endFrame = 3;
	if (this->simon->MoveTo(this->simon->currStairPos + Vector2(0, 16), deltaTime))
	{
		this->simon->m_Dir = Direction::RIGHT;
		this->simon->isMoveToStair = false; //Tat trang thai dang di toi cau thang
		this->simon->prepareOnStair = true; //Bat trang thai chuan bi vao cau thang
		this->simon->currSimonStairPos = this->simon->currStairPos + Vector2(0, 16);//Gan pos buoc dau tien tren cau thang
		if (this->simon->isArrowKeyUp == false)
		{
			this->simon->isCancelStairMove = true;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool CUpStairRight::SimonMoveOutStair(float deltaTime)
{
	if (this->simon->MoveTo(this->simon->currStairPos + Vector2(-16, 16), deltaTime))
	{
		this->ResetSimonStair();
		return true;
	}
	else
	{
		return false;
	}
}
