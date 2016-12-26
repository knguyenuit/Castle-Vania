
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"
#include "Animation.h"
#include "Device.h"


class CSprite {
protected:
	
public:
	CSprite();
	
	//ve texture tai vi tri mac dinh la chinh giua
	void Draw(CTexture* image, RECT* RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);
	void drawGameObject(CTexture* image, RECT* RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);

	//ve texture tai vi tri mac dinh la chinh giua voi scale
	void Draw(CTexture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DXVECTOR2 scale, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);

	//va lap theo chieu ngang
	void DrawFlipX(CTexture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);
	//va lat theo chieu doc
	void DrawFlipY(CTexture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);
	void DrawFlipXY(CTexture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);
	~CSprite();
};

#endif