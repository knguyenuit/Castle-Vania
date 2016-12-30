#include "PoolObject.h"
#include <stdio.h>
#include "OnCollision.h"
#include "LoadObject.h"



CPoolObject::CPoolObject()
{
	Init();
}


CPoolObject::~CPoolObject()
{
}

void CPoolObject::Init()
{
	this->drawManager = new CDrawObject();
	this->itemManage = CItemManage::GetInstance();
	this->simon = CSimon::GetInstance();
	this->hcn = new CHinhChuNhat();
	this->hv = new CHinhVuong();
	this->banner = new CBanner();
	//this->ground = new CGround();
	//this->item = new CItem(ITEM_name::MorningStar, Vector2(300,300));
	
	
}

void CPoolObject::Update(float deltaTime)
{
	if (this->simon->isPickUpMorningStar == false)
	{
		CSimon::GetInstance()->Update(deltaTime);
		CLoadObject::GetInstance()->Update(deltaTime);
	}
	else
	{
		this->simon->timePickUpMorningStar += deltaTime;
		if (this->simon->timePickUpMorningStar >= 0.6f)
		{
			this->simon->isPickUpMorningStar = false;
			this->simon->timePickUpMorningStar = 0.0f;
		}
	}
	
	CItemManage::GetInstance()->Update(deltaTime);
	//CEnemyManage::GetInstance()->Update(deltaTime);
	CWeaponManage::GetInstance()->Update(deltaTime);
	CAnimationObjectManage::GetInstance()->Update(deltaTime);
	//CHideObjectManage::GetInstance()->Update(deltaTime);
	
	banner->Update(deltaTime);
	//this->ground->Update(deltaTime);
	//CLoadObject::GetInstance()->Collision(deltaTime, this->simon);
	//OnCollision(deltaTime);
	//this->hv->Update(deltaTime);
	//this->hcn->Update(deltaTime);
}

void CPoolObject::OnCollision(float deltaTime)
{
	
	float normal_x = 0;
	float normal_y = 0;
	
	float moveX = 0;
	float moveY = 0;
	/*float timeCollision = CCollision::GetInstance()->Collision(hcn, hv, normal_x, normal_y, deltaTime);
	if (timeCollision > 0.0f && timeCollision < 1.0f)
	{
		MessageBox(NULL, "VA CHAM BEN PHAI - XET HV THEO HCN", "BG", MB_OK);
	}*/
	CDirection x;
	CDirection y;
	float timeCollision = COnCollision::GetInstance()->SweepAABB(hv, hcn, x, y,deltaTime);
	if (x == CDirection::ON_LEFT || x == CDirection::ON_RIGHT)
	{
		MessageBox(NULL, "VA CHAM BEN PHAI - XET HV THEO HCN", "BG", MB_OK);
	}
	if (y != CDirection::NONE_DIRECT)
	{
		MessageBox(NULL, "VA CHAM BEN PHAI - XET HV THEO HCN", "BG", MB_OK);
	}
	/*float timeCollision = CCollision::GetInstance()->Collision(this->simon, hv, normal_x, normal_y,moveX, moveY, deltaTime);
	if (timeCollision > 0.0f && timeCollision < 1.0f )
	{
		if (normal_x == 1)
		{
			MessageBox(NULL, "VA CHAM BEN PHAI - XET HV THEO HCN", "BG", MB_OK);
		}
		if (normal_x == -1)
		{
			MessageBox(NULL, "Va cham ben trai - xet hinh vuong theo hcn", "BG", MB_OK);
		}
		if (normal_y == 1)
		{
			MessageBox(NULL, "Va cham phia duoi - xet hinh vuong theo hcn", "BG", MB_OK);
		}
		if (normal_y == -1)
		{
			MessageBox(NULL, "Va cham phia tren - xet hinh vuong theo hcn", "BG", MB_OK);
		}
	}*/
}

//ham` quan li ve, ve cai gi thi truyen truc tiep o day, nhieu doi tuong thi dung for
void CPoolObject::Draw()
{
	this->simon->Draw();
	CLoadObject::GetInstance()->Draw();
	CItemManage::GetInstance()->Draw();
	//CEnemyManage::GetInstance()->Draw();
	CAnimationObjectManage::GetInstance()->Draw();
	CWeaponManage::GetInstance()->Draw();
	CSnakeManage::GetInstance()->Draw();
	CFireBallManage::GetInstance()->Draw();
	//ve banner
	banner->DrawBannerBG();
	banner->DrawBannerProperty();

	/*this->drawManager->Draw(this->hcn);
	this->drawManager->Draw(this->hv);*/
}
