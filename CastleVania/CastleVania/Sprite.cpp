#include "Sprite.h"



CSprite::CSprite()
{
}

void CSprite::Draw(CTexture* image, RECT* RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor, bool isCenter)
{

	//isCenter = true;
	//transcolor = 0xFFFFFFFF;
	////D3DXVECTOR3 position((float)X, (float)Y, 0);
	//if (isCenter)
	//{
	//	D3DXVECTOR3* center = NULL;
	//	if (RectRS == NULL)
	//	{
	//		center = NULL;
	//	}
	//	else
	//	{
	//		center = new D3DXVECTOR3(
	//			(RectRS->right - RectRS->left) / 2.0f,
	//			(RectRS->bottom - RectRS->top) / 2.0f,
	//			0);
	//	}
	//	CDevice::GetInstance()->s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);

	//	CDevice::GetInstance()->s_spriteHandle->Draw(
	//		image->GetTexture(),
	//		RectRS,//&srect,
	//		center,
	//		&pos,
	//		transcolor
	//	);
	//	delete center;
	//	CDevice::GetInstance()->s_spriteHandle->End();
	//}
	//else
	//{
	//	CDevice::GetInstance()->s_spriteHandle->Draw(
	//		image->GetTexture(),
	//		RectRS,//&srect,
	//		NULL,
	//		&pos,
	//		transcolor
	//	);
	//}
	if (isCenter)
	{
		D3DXVECTOR3* center = NULL;
		if (RectRS == NULL)
		{
			center = NULL;
		}
		else
		{
			center = new D3DXVECTOR3((RectRS->right - RectRS->left) / 2.0f,(RectRS->bottom - RectRS->top) / 2.0f,0);
			//center = new D3DXVECTOR3(RectRS->left, RectRS->top, 0);
		}
		CDevice::s_spriteHandle->Draw(image->GetTexture(), RectRS, center, &pos, transcolor);
		delete center;
	}
	else {

		CDevice::s_spriteHandle->Draw(image->GetTexture(), RectRS, NULL, &pos, transcolor);
	}


}

void CSprite::drawGameObject(CTexture * image, RECT * RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor, bool isCenter)
{
	//isCenter = true;
	//transcolor = 0xFFFFFFFF;
	////D3DXVECTOR3 position((float)X, (float)Y, 0);
	//if (isCenter)
	//{
	//	D3DXVECTOR3* center = NULL;
	//	if (RectRS == NULL)
	//	{
	//		center = NULL;
	//	}
	//	else
	//	{
	//		center = new D3DXVECTOR3(
	//			(RectRS->right - RectRS->left) / 2.0f,
	//			(RectRS->bottom - RectRS->top) / 2.0f,
	//			0);
	//	}
	//	CDevice::GetInstance()->s_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);

	//	CDevice::GetInstance()->s_spriteHandle->Draw(
	//		image->GetTexture(),
	//		RectRS,//&srect,
	//		center,
	//		&pos,
	//		transcolor
	//	);
	//	delete center;
	//	CDevice::GetInstance()->s_spriteHandle->End();
	//}
	//else
	//{
	//	CDevice::GetInstance()->s_spriteHandle->Draw(
	//		image->GetTexture(),
	//		RectRS,//&srect,
	//		NULL,
	//		&pos,
	//		transcolor
	//	);
	//}
	if (isCenter)
	{
		D3DXVECTOR3* center = NULL;
		if (RectRS == NULL)
		{
			center = NULL;
		}
		else
		{
			//center = new D3DXVECTOR3((RectRS->right - RectRS->left) / 2.0f, (RectRS->bottom - RectRS->top) / 2.0f, 0);
			center = new D3DXVECTOR3(RectRS->left, RectRS->top, 0);
		}
		CDevice::s_spriteHandle->Draw(image->GetTexture(), RectRS, center, &pos, transcolor);
		delete center;
	}
	else {

		CDevice::s_spriteHandle->Draw(image->GetTexture(), RectRS, NULL, &pos, transcolor);
	}


}

void CSprite::Draw(CTexture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DXVECTOR2 scale, D3DCOLOR transcolor /* = 0xFFFFFFFF */, bool isCenter /* = true */)
{
	HRESULT result;

	//Lay ma tran transform hien tai
	D3DXMATRIX currMatrix;

	//tim ra vi tri moi trong he toa do sau khi scale
	D3DXVECTOR3 newPos = D3DXVECTOR3(pos.x / scale.x, pos.y / scale.y, pos.z);

	result = CDevice::s_spriteHandle->GetTransform(&currMatrix);
	if (result != D3D_OK)
	{
		return;
	}

	// Tạo ma trận transform mới
	D3DXMATRIX newMatrix;

	D3DXMatrixIdentity(&newMatrix);
	newMatrix._11 = scale.x;
	newMatrix._22 = scale.y;

	//ap dung ma tran transform moi de ve
	result = CDevice::s_spriteHandle->SetTransform(&newMatrix);
	if (result != D3D_OK)
	{
		return;
	}

	//doi nguoc truc z lai
	//newPos.z = -newPos.z;

	this->Draw(image, RectRS, newPos, transcolor, isCenter);

	result = CDevice::s_spriteHandle->SetTransform(&currMatrix);
	if (result != D3D_OK)
	{
		return;
	}
}

//ve texture theo lat ngang
void CSprite::DrawFlipX(CTexture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor, bool isCenter)
{
	D3DXVECTOR2 scaling = D3DXVECTOR2(-1, 1);
	this->Draw(image, RectRS, pos, scaling, transcolor, isCenter);
}
CSprite::~CSprite()
{
}
