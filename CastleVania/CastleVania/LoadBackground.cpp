#include "LoadBackground.h"
#include "Camera.h"

#define BACK_GROUND_1 "..\\Resources\\Map\\lv1TS.PNG"//Map_1.png"
CLoadBackground::CLoadBackground()
{
	this->m_imageCurr = new CTexture();
	this->m_drawImg = new CSprite();
	this->m_cols = 0;
	this->m_rows = 0;





	this->m_drawImg = new CSprite();

	this->m_matrix = nullptr;
}


CLoadBackground::~CLoadBackground()
{
	this->DeleteMatrix();
}
void CLoadBackground::Draw()
{
#pragma region KHONG CO QUADTREE

	RECT *rectRS = new RECT();
	D3DXVECTOR3 pos;

	//for (int i = 0; i < this->m_rows; i++)
	//{
	//	for (int j = 0; j < this->m_cols; j++)
	//	{
	//		//Ve tung tile len man hinh
	//		rectRS->left = (this->m_matrix[i][j] % this->m_tileCols) * this->m_tileWidth;
	//		rectRS->right = rectRS->left + this->m_tileWidth;
	//		rectRS->top = (this->m_matrix[i][j] / this->m_tileCols) * this->m_tileHeight;
	//		rectRS->bottom = rectRS->top + this->m_tileHeight;
	//		pos.x = j * this->m_tileHeight;
	//		pos.y = (this->m_rows - i) * this->m_tileWidth - 16;
	//		pos.z = 0;
	//		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
	//		this->m_drawImg->Draw(this->m_imageCurr, rectRS, pos, D3DCOLOR_XRGB(255,255,255), false);
	//	}
	//}
	for (std::vector<BackGroundItem>::iterator it = this->listBackground.begin();
		it != this->listBackground.end();
		++it)
	{
		rectRS->left = it->_posTitleSet.x;
		rectRS->right = rectRS->left + it->_widthTitle;
		rectRS->top = it->_posTitleSet.y;
		rectRS->bottom = rectRS->top + it->_heighTitle;
		pos.x = it->_pos.x;
		pos.y = it->_pos.y;
		pos.z = 0;
		pos = CCamera::GetInstance()->GetPointTransform(pos.x, pos.y);
		this->m_drawImg->Draw(this->m_imageCurr, rectRS, pos, D3DCOLOR_XRGB(255, 255, 255), true);
	}

#pragma endregion


}
void CLoadBackground::LoadBackgroundFromFile(std::string filePath)
{
	//LoadMatrix(FILE_MAP);
	LoadMatrixFromFile(filePath);
	//this->m_tileCols = this->m_imageCurr->GetImageWidth() / this->m_tileWidth;
	//this->m_tileRows = this->m_imageCurr->GetImageHeight() / this->m_tileHeight;

}
void CLoadBackground::LoadImageFromFile(std::string filePath)
{
	this->m_imageCurr->LoadImageFromFile(filePath, D3DCOLOR_XRGB(255, 0, 255));
}
bool CLoadBackground::InitMatrix()
{
	if (this->m_cols != 0 && this->m_rows != 0)
	{
		this->m_matrix = new int*[this->m_rows];
		for (int i = 0; i < this->m_rows; i++)
		{
			this->m_matrix[i] = new int[this->m_cols];
		}
		return true;
	}
	return false;
}
void CLoadBackground::LoadMatrix(std::string filePath)
{
	std::vector<std::string> value = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> result; //Luu chuoi sau khi duoc cat
	for (int i = 0; i < value.size(); i++)
	{
		result = CFileUtil::GetInstance()->Split(value.at(i).c_str(), '\t');
		if (i == 0)
		{
			this->m_rows = std::atoi(result.at(0).c_str());
			this->m_cols = std::atoi(result.at(1).c_str());
			if (this->InitMatrix())
			{
			}
			else
			{
				MessageBox(NULL, "FAIL Load BG", "BG", MB_OK);
			}
		}
		else if (i == 1)
		{
			this->m_tileWidth = std::atoi(result.at(0).c_str());
			this->m_tileHeight = std::atoi(result.at(1).c_str());
		}
		else
		{
			for (int j = 0; j < result.size(); j++)
			{
				this->m_matrix[i - 2][j] = atoi(result.at(j).c_str());
			}
		}
	}
}

void CLoadBackground::DeleteMatrix()
{
	if (this->m_matrix != nullptr)
	{
		for (int i = 0; i < this->m_rows; i++)
		{
			delete this->m_matrix[i];
		}
		delete this->m_matrix;
		this->m_matrix = nullptr;
	}
}

void CLoadBackground::Clear()
{
	if (this->m_matrix)
		this->DeleteMatrix();

	if (this->m_imageCurr)
	{
		delete this->m_imageCurr;
		this->m_imageCurr = new CTexture();
	}
	if (listBackground.size() != 0)
	{
		for (std::vector<BackGroundItem>::iterator it = this->listBackground.begin();
			it != this->listBackground.end();
			++it)
		{

			it = this->listBackground.erase(it);
			if (listBackground.empty())
			{
				break;
			}
		}
	}
}

void CLoadBackground::LoadMatrixFromFile(std::string filePath)
{
	std::vector<std::string> value = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> result; //Luu chuoi sau khi duoc cat
	for (int i = 0; i < value.size(); i++)
	{
		result = CFileUtil::GetInstance()->Split(value.at(i).c_str(), '\t');
		BackGroundItem item;
		item._id = std::atoi(result.at(0).c_str());
		item._type = std::atoi(result.at(1).c_str());
		item._pos.x = std::atoi(result.at(2).c_str());
		item._pos.y = std::atoi(result.at(3).c_str());
		item._posTitleSet.x = std::atoi(result.at(4).c_str());
		item._posTitleSet.y = std::atoi(result.at(5).c_str());
		item._widthTitle = std::atoi(result.at(6).c_str());
		item._heighTitle = std::atoi(result.at(7).c_str());
		listBackground.push_back(item);
	}

}
