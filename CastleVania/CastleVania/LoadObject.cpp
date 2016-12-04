#include "LoadObject.h"
#include "FileUtil.h"
#include "Camera.h"
#include "DrawObject.h"



CLoadObject::CLoadObject()
{
	
	
}


CLoadObject::~CLoadObject()
{
}

void CLoadObject::Update(float deltaTime)
{

	for (std::vector<CBaseGameObject*>::iterator it = this->m_listGameObject.begin();
		it != this->m_listGameObject.end();
		)
	{
		CBaseGameObject* gameObj = *it;

		if (gameObj != NULL && gameObj->m_isRemove == false)
		{
			gameObj->Update(deltaTime);
		}

		if (gameObj->m_isRemove)
		{
			it = this->m_listGameObject.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CLoadObject::Collision(float deltaTime, CBaseGameObject *gameObj)
{
	
	

	
}

void CLoadObject::Draw()
{

	for (std::vector<CBaseGameObject*>::iterator it = this->m_listGameObject.begin();
		it != this->m_listGameObject.end();
		++it)
	{		
		CBaseGameObject* gameObj = *it;	
		CDrawObject::GetInstance()->Draw(gameObj);		
	}
}




bool CLoadObject::contains(std::vector<int> v, int x)
{
	if (std::find(v.begin(), v.end(), x) != v.end()) {
		/* v contains x */
		return true;
	}
	else {
		/* v does not contain x */
		return false;
	}
}

CBaseGameObject* CLoadObject::CreateObject(int id, Vector2 pos)
{

	switch (id)
	{
		
	case 601://Cuc gach an tien binh thuong
		return new CGround(pos);
		break;
	case 602://Cuc gach an tien binh thuong
		return new CGround(pos);
		break;
	case 603://Cuc gach an tien binh thuong
		return new CGround(pos);
		break;
	
	default:
		break;
	}

}


void CLoadObject::LoadGameObjectFromFile(const std::string& filePath)
{
	
}
std::hash_map<int, CBaseGameObject*> CLoadObject::LoadGameObjectInfo(const std::string& filePath)
{
	std::hash_map<int, CBaseGameObject*> listInfo;
	std::vector<std::string> data = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> item;
	typedef pair<int, CBaseGameObject*> Pair;
	if (!data.empty())
	{
		int size = data.size();
		int iDObjectInMap;
		for (int i = 0; i < size; i++)
		{
			CBaseGameObject* gameObj;
			std::vector<int> info;
			item = CFileUtil::GetInstance()->Split(data.at(i).c_str(), '\t');
			if (!item.empty())
			{
				iDObjectInMap = atoi(item.at(0).c_str());
				int idItem = atoi(item.at(1).c_str());
				float x = atoi(item.at(2).c_str());
				float y = atoi(item.at(3).c_str());
				Vector2 pos = Vector2(x, y);
				
				
					gameObj = this->CreateObject(idItem, pos);
					this->m_listGameObject.push_back(gameObj);
				
				listInfo.insert(Pair(iDObjectInMap, gameObj));
			}

		}
	}
	return listInfo;
}

void CLoadObject::readFile(const std::string &filePath)
{
	std::vector<std::string> data = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> item;
	
	typedef pair<int, Box> Pair;
	if (!data.empty())
	{
		int size = data.size();
		int iDObjectInMap;
		for (int i = 0; i < size; i++)
		{
			CBaseGameObject* gameObj;
			std::vector<int> info;
			item = CFileUtil::GetInstance()->Split(data.at(i).c_str(), '\t');
			if (!item.empty())
			{
				iDObjectInMap = atoi(item.at(0).c_str());
				int idItem = atoi(item.at(1).c_str());
				float PosX = atoi(item.at(2).c_str());
				float PosY = atoi(item.at(3).c_str());
				float Width = atoi(item.at(4).c_str());
				float Height = atoi(item.at(5).c_str());
				Box b = Box(PosX, PosY, Width, Height);
				this->listBox.insert(Pair(iDObjectInMap, b));
				if (idItem == 601 || idItem == 602 || idItem == 603)
				{
					Vector2 pos = Vector2(PosX, PosY);
					gameObj = this->CreateObject(idItem, pos);
					this->m_listGameObject.push_back(gameObj);
				}
				
			}
		}
	}
	else
	{
		MessageBox(NULL, "aaaaaaa", "aaaaaa", MB_OK);
	}
}