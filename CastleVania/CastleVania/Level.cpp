#include "Level.h"



CLevel::CLevel()
{
}


CLevel::~CLevel()
{
}

void CLevel::readFileLevel(const std::string & filePath)
{
	std::vector<std::string> data = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> item;
	typedef pair<int, Level*> Pair;
	if (!data.empty())
	{
		int size = data.size();
		int idLevel;
		for (int i = 0; i < size; i++)
		{
			CBaseGameObject* gameObj;
			std::vector<int> info;
			item = CFileUtil::GetInstance()->Split(data.at(i).c_str(), '\t');
			if (!item.empty())
			{
				idLevel = atoi(item.at(0).c_str());
				std::string fileImageBackgroud = item.at(1).c_str();
				std::string fileBackground = item.at(2).c_str();
				std::string fileObject = item.at(3).c_str();

				Level* lv = new Level(idLevel, fileImageBackgroud, fileBackground, fileObject);
				this->listLevel.insert(Pair(idLevel, lv));

			}
		}
	}
	else
	{
		MessageBox(NULL, "aaaaaaa", "aaaaaa", MB_OK);
	}
}
