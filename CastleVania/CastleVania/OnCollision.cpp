#include "OnCollision.h"



COnCollision::COnCollision()
{
}


COnCollision::~COnCollision()
{
}

bool COnCollision::AABBCheck(Box first, Box second)
{
	return !((first.x + first.w / 2 < second.x - second.w / 2) ||
		(first.x - first.w / 2) > (second.x + second.w / 2) ||
		(first.y + first.h / 2) < (second.y - second.h / 2) ||
		(first.y - first.h / 2) > (second.y + second.h / 2));
}



float COnCollision::SweepAABB(Box box1, Box box2, CDirection & normalX, CDirection & normalY, float frameTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Xác định các khoảng cách bắt đầu và kết thúc va chạm theo hai chiều x, y
	if (box1.vx > 0.0f)
	{
		xInvEntry = (box2.x - box2.w/2) - (box1.x + box1.w / 2);
		xInvExit = (box2.x + box2.w / 2) - (box1.x - box1.w / 2);
	}
	else
	{
		xInvEntry = (box2.x + box2.w / 2) - (box1.x - box1.w / 2);
		xInvExit = (box2.x - box2.w/2) - (box1.x + box1.w /2);
	}

	if (box1.vy > 0.0f)
	{
		yInvEntry = (box2.y- box2.h / 2) - (box1.y + box1.h / 2);
		yInvExit = (box2.y + box2.h)- (box1.y - box1.h / 2);
	}
	else
	{
		yInvEntry = (box2.y + box2.h/2) - (box1.y - box1.h / 2);
		yInvExit = (box2.y - box2.h / 2) - (box1.y + box1.h / 2);
	}

	// Tính thời gian bắt đầu và kết thúc va chạm theo hai chiều x, y
	float xEntry, xExit;
	float yEntry, yExit;

	if (box1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.vx;
		xExit = xInvExit / box1.vx;
	}

	if (box1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1.vy;
		yExit = yInvExit / box1.vy;
	}

	// Tìm ra khoảng thời gian bắt đầu và kết thúc va chạm tổng hợp
	float entryTime, exitTime;

	entryTime = __max(xEntry, yEntry);
	exitTime = __min(xExit, yExit);

#pragma region Xét va chạm với các trường hợp còn lại
	// Nếu không có va chạm trong frameTime này thì trả về false
	if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>frameTime || yEntry>frameTime)
	{
		// Mặc định không va chạm theo hai hướng
		normalX = CDirection::NONE_DIRECT;
		normalY = CDirection::NONE_DIRECT;

		if (box1.IntersecWith(box2,true))
		{
			// Nếu 2 box va chạm lẫn nhau thì có thể hai box này đã dính nhau
			if (fabsf(box1.y - box1.h / 2 - (box2.y + box2.h/2)) <= 2.0f
				&& !(box1.x + box1.w / 2 <= (box2.x - box2.w /2) || box1.x - box1.w / 2 >= box2.x + box2.w /2))
				normalY = CDirection::ON_DOWN;

			else if (fabsf(box1.y + box1.h / 2 - (box2.y- box2.h)) <= 2.0f
				&& !((box1.x + box1.w /2) <= (box2.x  - box2.w /2) || box1.x - box1.w / 2 >= box2.x + box2.w / 2))
				normalY = CDirection::ON_UP;

			else if (fabsf((box1.x + box1.w /2) - (box2.x - box2.w /2)) <= 2.0f
				&& !(box1.y- box1.h /2 >= (box2.y  +box2.h/2)|| (box1.y + box1.h / 2)<= box2.y- box2.h/2))
				normalX = CDirection::ON_RIGHT;

			else if (fabsf((box1.x - box1.w/2) - (box2.x + box2.w/2)) <= 2.0f
				&& !(box1.y- box1.h/2 >= box2.y + box2.h /2 || box1.y + box1.h /2 <= box2.y- box2.h/2))
				normalX = CDirection::ON_LEFT;

			else if (!(box1.y- box1.h / 2 >= box2.y + box2.h /2 
				|| box1.y - box1.h / 2 <= box2.y- box2.h/2
				|| box1.x + box1.w / 2 <= box2.x - box2.w /2 
				|| box1.x - box1.w / 2 >= box2.x + box2.w/2))
				normalX = normalY = CDirection::INSIDE;
		}
		return 0;
	}
#pragma  endregion
#pragma region Nếu có va chạm xảy ra
	else
	{
		if (xEntry > yEntry)
		{
			if (box1.vx > 0.0f) // Nếu va chạm từ trái sang phải
			{
				if (!(box1.y- box1.h /2 >= box2.y + box2.h / 2|| box1.y + box1.h / 2<= box2.y- box2.h))
				{
					normalX = CDirection::ON_RIGHT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.y- box1.h /2 - (box2.y+ box2.h / 2)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf((box1.y + box1.h / 2)- (box2.y- box2.h /2) <= 2.0f))
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ phải sang trái
			{
				if (!(box1.y- box1.h/2 >= (box2.y+box2.h /2)|| box1.y + box1.h /2<= box2.y- box2.h /2))
				{
					normalX = CDirection::ON_LEFT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.y- box1.h/2 -(box2.y+box2.h / 2)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.y + box1.h /2 - (box2.y- box2.h/2)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
		}
		else
		{
			if (box1.vy > 0.0f) // Nếu va chạm từ dưới lên
			{
				if (!(box1.x + box1.w/2 <= box2.x - box2.w/2 || box1.x - box1.w/2 >= box2.x + box2.w/2))
				{
					normalY = CDirection::ON_UP;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.x + box1.w/2 - (box2.x - box2.w/2)) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.x - box1.w/ 2 - (box2.x + box2.w/2))<2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ trên xuống
			{
				if (!(box1.x + box1.w/2 <= (box2.x- box2.w/2) || box1.x - box1.w/2 >= box2.x + box2.w/2))
				{
					normalY = CDirection::ON_DOWN;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.x + box1.w/2 - (box2.x- box2.w /2)) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf((box1.x - box1.w/2) - (box2.x + box2.w/2))<2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
		}
		return entryTime;
	}
#pragma endregion
}

float COnCollision::SweepAABB(CBaseGameObject * obj1, CBaseGameObject * obj2, CDirection & normalX, CDirection & normalY, float frameTime)
{
	Box box1 = obj1->GetBox();
	Box box2 = obj2->GetBox();
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Xác định các khoảng cách bắt đầu và kết thúc va chạm theo hai chiều x, y
	if (box1.vx > 0.0f)
	{
		xInvEntry = (box2.x - box2.w / 2) - (box1.x + box1.w / 2);
		xInvExit = (box2.x + box2.w / 2) - (box1.x - box1.w / 2);
	}
	else
	{
		xInvEntry = (box2.x + box2.w / 2) - (box1.x - box1.w / 2);
		xInvExit = (box2.x - box2.w / 2) - (box1.x + box1.w / 2);
	}

	if (box1.vy > 0.0f)
	{
		yInvEntry = (box2.y - box2.h / 2) - (box1.y + box1.h / 2);
		yInvExit = (box2.y + box2.h) - (box1.y - box1.h / 2);
	}
	else
	{
		yInvEntry = (box2.y + box2.h / 2) - (box1.y - box1.h / 2);
		yInvExit = (box2.y - box2.h / 2) - (box1.y + box1.h / 2);
	}

	// Tính thời gian bắt đầu và kết thúc va chạm theo hai chiều x, y
	float xEntry, xExit;
	float yEntry, yExit;

	if (box1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.vx;
		xExit = xInvExit / box1.vx;
	}

	if (box1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1.vy;
		yExit = yInvExit / box1.vy;
	}

	// Tìm ra khoảng thời gian bắt đầu và kết thúc va chạm tổng hợp
	float entryTime, exitTime;

	entryTime = __max(xEntry, yEntry);
	exitTime = __min(xExit, yExit);

#pragma region Xét va chạm với các trường hợp còn lại
	// Nếu không có va chạm trong frameTime này thì trả về false
	if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>frameTime || yEntry>frameTime)
	{
		// Mặc định không va chạm theo hai hướng
		normalX = CDirection::NONE_DIRECT;
		normalY = CDirection::NONE_DIRECT;

		if (box1.IntersecWith(box2, true))
		{
			// Nếu 2 box va chạm lẫn nhau thì có thể hai box này đã dính nhau
			if (fabsf(box1.y - box1.h / 2 - (box2.y + box2.h / 2)) <= 2.0f
				&& !(box1.x + box1.w / 2 <= (box2.x - box2.w / 2) || box1.x - box1.w / 2 >= box2.x + box2.w / 2))
				normalY = CDirection::ON_DOWN;

			else if (fabsf(box1.y + box1.h / 2 - (box2.y - box2.h)) <= 2.0f
				&& !((box1.x + box1.w / 2) <= (box2.x - box2.w / 2) || box1.x - box1.w / 2 >= box2.x + box2.w / 2))
				normalY = CDirection::ON_UP;

			else if (fabsf((box1.x + box1.w / 2) - (box2.x - box2.w / 2)) <= 2.0f
				&& !(box1.y - box1.h / 2 >= (box2.y + box2.h / 2) || (box1.y + box1.h / 2) <= box2.y - box2.h / 2))
				normalX = CDirection::ON_RIGHT;

			else if (fabsf((box1.x - box1.w / 2) - (box2.x + box2.w / 2)) <= 2.0f
				&& !(box1.y - box1.h / 2 >= box2.y + box2.h / 2 || box1.y + box1.h / 2 <= box2.y - box2.h / 2))
				normalX = CDirection::ON_LEFT;

			else if (!(box1.y - box1.h / 2 >= box2.y + box2.h / 2
				|| box1.y - box1.h / 2 <= box2.y - box2.h / 2
				|| box1.x + box1.w / 2 <= box2.x - box2.w / 2
				|| box1.x - box1.w / 2 >= box2.x + box2.w / 2))
				normalX = normalY = CDirection::INSIDE;
		}
		return 0;
	}
#pragma  endregion
#pragma region Nếu có va chạm xảy ra
	else
	{
		if (xEntry > yEntry)
		{
			if (box1.vx > 0.0f) // Nếu va chạm từ trái sang phải
			{
				if (!(box1.y - box1.h / 2 >= box2.y + box2.h / 2 || box1.y + box1.h / 2 <= box2.y - box2.h))
				{
					normalX = CDirection::ON_RIGHT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.y - box1.h / 2 - (box2.y + box2.h / 2)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf((box1.y + box1.h / 2) - (box2.y - box2.h / 2) <= 2.0f))
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ phải sang trái
			{
				if (!(box1.y - box1.h / 2 >= (box2.y + box2.h / 2) || box1.y + box1.h / 2 <= box2.y - box2.h / 2))
				{
					normalX = CDirection::ON_LEFT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.y - box1.h / 2 - (box2.y + box2.h / 2)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.y + box1.h / 2 - (box2.y - box2.h / 2)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
		}
		else
		{
			if (box1.vy > 0.0f) // Nếu va chạm từ dưới lên
			{
				if (!(box1.x + box1.w / 2 <= box2.x - box2.w / 2 || box1.x - box1.w / 2 >= box2.x + box2.w / 2))
				{
					normalY = CDirection::ON_UP;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.x + box1.w / 2 - (box2.x - box2.w / 2)) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf(box1.x - box1.w / 2 - (box2.x + box2.w / 2))<2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ trên xuống
			{
				if (!(box1.x + box1.w / 2 <= (box2.x - box2.w / 2) || box1.x - box1.w / 2 >= box2.x + box2.w / 2))
				{
					normalY = CDirection::ON_DOWN;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1.x + box1.w / 2 - (box2.x - box2.w / 2)) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf((box1.x - box1.w / 2) - (box2.x + box2.w / 2))<2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
		}
		return entryTime;
	}
#pragma endregion
}
