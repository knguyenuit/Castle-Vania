#ifndef __CLOAD_BACK_GROUND_H__
#define __CLOAD_BACK_GROUND_H__

#pragma once
#include "Singleton.h"
#include "Texture.h"
#include "Sprite.h"

#include "Global.h"
#include "FileUtil.h"


#define FILE_MAP "..\\Resources\\Map\\lv1BG.txt"

struct BackGroundItem
{
	int _id;
	int _type;
	Vector2 _pos;
	Vector2 _posTitleSet;
	int _widthTitle;
	int _heighTitle;
};

class CLoadBackground :public CSingleton<CLoadBackground>
{
	friend class CSingleton<CLoadBackground>;
public:
	CLoadBackground();
	~CLoadBackground();
public:
	int** m_matrix; //Dung de luu lai ma tran
	int m_cols; //So cot ma tran
	int m_rows; //So dong ma tran
	int m_tileHeight; // Chieu rong cua tile
	int m_tileWidth; // Chieu dai cua tile
	int m_tileCols; //So luong tile tren chieu dai cua Image
	int m_tileRows; //So luong tile tren chieu rong cua Image

	CTexture* m_imageCurr; //Lay texture trong bo dem, can dung lop managertexture
	CSprite* m_drawImg; //Dung de ve anh len man hinh, can dung lop managerSprite

	void LoadImageFromFile(std::string filePath);
	bool InitMatrix();
	void LoadMatrix(std::string filePath);
	void DeleteMatrix();
	void Clear(); //Xoa noi dug hien tai
	void LoadMatrixFromFile(std::string filePath);
	std::vector<BackGroundItem> listBackground;

public:
	void LoadBackgroundFromFile(std::string filePath);
	void Draw();
};
#endif

