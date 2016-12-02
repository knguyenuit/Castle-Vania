#include "Collision.h"
#include <algorithm>

CCollision::CCollision()
{

}

CCollision::~CCollision()
{

}

//Toa do truyen vao la toa do trung tam
//first.x, first.y là toa do tai diem trung tam cua box
float CCollision::SweptAABB(Box first, Box second, float& normalx, float& normaly, float deltaTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (first.vx > 0.0f)
	{
		xInvEntry = (second.x - second.w / 2) - (first.x + first.w / 2);
		xInvExit = (second.x + second.w / 2) - (first.x - first.w / 2);
	}
	else
	{
		xInvEntry = (second.x + second.w / 2) - (first.x - first.w / 2);
		xInvExit = (second.x - second.w / 2) - (first.x + first.w / 2);
	}

	if (first.vy > 0.0f)
	{
		yInvEntry = (first.y - first.h / 2) - (second.y + second.h / 2);
		yInvExit = (first.y + first.h / 2) - (second.y - second.h / 2);
	}
	else
	{
		yInvEntry = (second.y + second.h / 2) - (first.y - first.h / 2);
		yInvExit = (second.y - second.h / 2) - (first.y + first.h / 2);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (first.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / first.vx * deltaTime;
		xExit = xInvExit / first.vx * deltaTime;
	}

	if (first.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();

	}
	else
	{
		yEntry = yInvEntry / first.vy * deltaTime;
		yExit = yInvExit / first.vy * deltaTime;
	}

	// find the earliest/latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

Box CCollision::GetSweptBroadphaseBox(Box box, float deltaTime)
{
	/*Box broadphasebox;
	float posX;
	float posY;
	posX = b.vx > 0 ? (b.x - b.w / 2) : (b.x - b.w / 2) + b.vx * deltaTime;
	posY = b.vy > 0 ? (b.y + b.h / 2) + b.vy * deltaTime : (b.y + b.h / 2);
	broadphasebox.w = b.vx > 0 ? b.vx * deltaTime + b.w : b.w - b.vx * deltaTime;
	broadphasebox.h = b.vy > 0 ? b.vy * deltaTime + b.h : b.h - b.vy * deltaTime;
	broadphasebox.x = posX + broadphasebox.w / 2;
	broadphasebox.y = posY - broadphasebox.h / 2;
	return broadphasebox;*/
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = box.vx > 0 ? box.x : box.x + box.vx * deltaTime;
	broadphasebox.y = box.vy > 0 ? box.y : box.y + box.vy * deltaTime;
	broadphasebox.w = box.vx > 0 ? box.vx * deltaTime + box.w : box.w - box.vx * deltaTime;
	broadphasebox.h = box.vy > 0 ? box.vy * deltaTime + box.h : box.h - box.vy * deltaTime;

	return broadphasebox;
}

bool CCollision::AABBCheck(Box first, Box second, float& moveX, float& moveY, float& normalX, float& normalY)
{
	float l = (second.x - second.w / 2) - (first.x + first.w / 2);
	float r = (second.x + second.w / 2) - (first.x - first.w / 2);
	float t = (second.y + second.h / 2) - (first.y - first.h / 2);
	float b = (second.y - second.h / 2) - (first.y + first.h / 2);
	//Khong va cham
	if (l > 0 || r < 0 || t < 0 || b > 0)
	{
		moveX = 0;
		moveY = 0;
		normalX = 0;
		normalY = 0;
		return false;
	}
	//Xet truong hop ground
	moveX = (abs(l) < r) ? l : r;
	moveY = (abs(b) < t) ? b : t;
	//Loai tru truong hop hai doi tuong long nhau
	if (moveY >= second.h / 2)
	{
		moveX = 0;
		moveY = 0;
		normalX = 0;
		normalY = 0;
		return false;
	}
	if (abs(moveX) < abs(moveY))
	{
		moveY = 0.0f;
		normalX = (abs(l) > abs(r)) ? 1 : -1;
		normalY = 0;
	}
	else
	{
		moveX = 0.0f;
		normalY = (abs(t) < abs(b)) ? 1 : -1;
		normalX = 0;
	}
	return true;
}

bool CCollision::AABBCheck(Box b1, Box b2)
{
	/*return !((first.x + first.w / 2 < second.x - second.w / 2) ||
		(first.x - first.w / 2) > (second.x + second.w / 2) ||
		(first.y + first.h / 2) < (second.y - second.h / 2) ||
		(first.y - first.h / 2) > (second.y + second.h / 2));*/
	return !((b1.x + b1.w / 2) < (b2.x - b2.w / 2) || (b1.x - b1.w / 2) > (b2.x + b2.w / 2)
		|| (b1.y + b1.h / 2) < (b2.y - b2.h / 2) || (b1.y - b1.h / 2) > (b2.y + b2.h / 2));

}

bool CCollision::AABB(Box b1, Box b2, float & moveX, float & moveY)
{
	moveX = moveY = 0;

	// left - right
	float l = (b2.x - b2.w / 2) - (b1.x + b1.w / 2);// 

													//right - left
	float r = (b2.x + b2.w / 2) - (b1.x - b1.w / 2); //

													 // botton - top
	float t = (b2.y - b2.h / 2) - (b1.y + b1.h / 2);

	//top - botton
	float b = (b2.y + b2.h / 2) - (b1.y - b1.h / 2);

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return false;//neu khong co va cham

					 // find the offset of both sides
					 // tim khoang cach di chuyen de khong bi va cham
	moveX = abs(l) < abs(r) ? l : r;
	moveY = abs(t) < abs(b) ? t : b;

	// only use whichever offset is the smallest
	// chi su dung 1 phan dich chuyen nho hon
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

float CCollision::sweptAABB(Box b1, Box b2, float & normalx, float & normaly, float deltaTime)
{
	return 0.0f;
}

float CCollision::Collision(Box b1, Box b2, float & normalx, float & normaly, float deltaTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		// box 1 moving from left to right
		// left of box 2 - right of box 1
		xInvEntry = (b2.x - b2.w / 2) - (b1.x + b1.w / 2);

		// right of box 2 - left of box 1
		xInvExit = (b2.x + b2.w / 2) - (b1.x - b1.w / 2);
	}
	else
	{
		// box 1 moving from right to left
		// right of box 2 - left of box 1
		xInvEntry = (b2.x + b2.w / 2) - (b1.x - b1.w / 2);

		// left of box 2 - right of box 1
		xInvExit = (b2.x - b2.w / 2) - (b1.x + b1.w / 2);
	}

	if (b1.vy > 0.0f)
	{
		// box 1 moving from botton to top
		// botton of b2 - top of box 1
		yInvEntry = (b2.y - b2.h / 2) - (b1.y + b1.h / 2);

		// top of b2 - botton of b1
		yInvExit = (b2.y + b2.h / 2) - (b1.y - b1.h / 2);
	}
	else
	{
		// box 1 moving from top to botton
		// top of box 2 - botton of box 1
		yInvEntry = (b2.y + b2.h / 2) - (b1.y - b1.h / 2);

		// botton of box 2  - top of box 1
		yInvExit = (b2.y - b2.h / 2) - (b1.y + b1.h / 2);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	// tim thoi gian va cham va thoi gian het va cham
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (b1.vx * deltaTime);
		xExit = xInvExit / (b1.vx * deltaTime);
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (b1.vy * deltaTime);
		yExit = yInvExit / (b1.vy * deltaTime);
	}

	// find the earliest/latest times of collision
	// 
	//std::min
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			//va cham theo truc x
			if (xInvEntry < 0.0f)
			{
				//va cham ben trai
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				//va cham ben phai
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			//va cham theo truc y
			if (yInvEntry < 0.0f)
			{
				// va cham phia duoi
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				// va cham phia tren
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

float CCollision::Collision(CBaseGameObject * ObjectA, CBaseGameObject * ObjectB, float & normalx, float & normaly, float deltaTime)
{
	Box box = ObjectA->GetBox();
	Box staticBox = ObjectB->GetBox();

	Box broadphaseBox = GetSweptBroadphaseBox(box, deltaTime);

	float moveX = 0;
	float moveY = 0;

	//kiem tra 2 box hien tai da va cham chua
	if (AABBCheck(box, staticBox))
	{
		if (AABB(box, staticBox, moveX, moveY))
		{
			normalx = moveX;
			normaly = moveY;
			//this->_pos.x += moveX;
			//this->_pos.y += moveY;
			return 2.0f;
		}
		return 1.0f;
	}
	else
	{
		//kiem tra 2 object co the va cham ko?
		if (AABBCheck(broadphaseBox, staticBox))
		{
			float timeCol = sweptAABB(box, staticBox, normalx, normaly, deltaTime);
			return timeCol;
		}
		else
		{
			return 1.0;//khong co va cham
		}
	}

	return 0.0f;
}


float CCollision::Collision(CBaseGameObject* objectA, CBaseGameObject* objectB, float& normalx, float& normaly, float& moveX, float& moveY, float deltaTime)
{
	//Box first = objectA->GetBox();
	//Box second = objectB->GetBox();
	//Box broadphaseBox = this->GetSweptBroadphaseBox(first, deltaTime);

	//float collisiontime;
	//if (AABBCheck(first, second, moveX, moveY, normalx, normaly))
	//{
	//	return 2.0f;
	//}
	//else if (this->AABBCheck(broadphaseBox, second))
	//{
	//	//Lay thoi gian co the va cham
	//	collisiontime = SweptAABB(first, second, normalx, normaly, deltaTime);
	//	if (collisiontime < 1.0f && collisiontime > 0.0f)
	//	{
	//		//Xay ra va cham trong frame tiep theo
	//		return collisiontime;
	//	}
	//	else
	//	{
	//	}
	//}
	//Box first1 = objectB->GetBox();
	//Box second1 = objectA->GetBox();
	//Box broadphaseBox1 = this->GetSweptBroadphaseBox(first1, deltaTime);
	//float collisiontime2;

	//if (this->AABBCheck(broadphaseBox1, second1))
	//{
	//	//Lay thoi gian co the va cham
	//	collisiontime2 = SweptAABB(first1, second1, normalx, normaly, deltaTime);
	//	if (collisiontime2 < 1.0f && collisiontime2 > 0.0f)
	//	{
	//		normalx *= -1;
	//		return collisiontime2;
	//	}
	//	else
	//	{
	//	}
	//}


	//return -1.0f;
	Box first = objectA->GetBox();
	Box second = objectB->GetBox();
	Box broadphaseBox = this->GetSweptBroadphaseBox(first, deltaTime);
	float collisiontime;
	if (AABBCheck(first, second, moveX, moveY, normalx, normaly))
	{
		return 2.0f;
	}
	else if (this->AABBCheck(broadphaseBox, second))
	{
		//Lay thoi gian co the va cham
		collisiontime = SweptAABB(first, second, normalx, normaly, deltaTime);
		if (collisiontime < 1.0f && collisiontime > 0.0f)
		{
			//Xay ra va cham trong frame tiep theo
			return collisiontime;
		}
	}
	else
	{
		return 1.0f;
	}

}

float CCollision::Collision(Box first, Box second, float & normalx, float & normaly, float & moveX, float & moveY, float deltaTime)
{
	Box broadphaseBox = this->GetSweptBroadphaseBox(first, deltaTime);

	float collisiontime;
	if (AABBCheck(first, second, moveX, moveY, normalx, normaly))
	{
		return 2.0f;
	}
	else if (this->AABBCheck(broadphaseBox, second))
	{
		//Lay thoi gian co the va cham
		collisiontime = SweptAABB(first, second, normalx, normaly, deltaTime);
		if (collisiontime < 1.0f && collisiontime > 0.0f)
		{
			//Xay ra va cham trong frame tiep theo
			return collisiontime;
		}
		else
		{
		}
	}
	Box first1 = second;
	Box second1 = first;
	Box broadphaseBox1 = this->GetSweptBroadphaseBox(first1, deltaTime);
	float collisiontime2;

	if (this->AABBCheck(broadphaseBox1, second1))
	{
		//Lay thoi gian co the va cham
		collisiontime2 = SweptAABB(first1, second1, normalx, normaly, deltaTime);
		if (collisiontime2 < 1.0f && collisiontime2 > 0.0f)
		{
			normalx *= -1;
			return collisiontime2;
		}
		else
		{
		}
	}


	return -1.0f;

}



