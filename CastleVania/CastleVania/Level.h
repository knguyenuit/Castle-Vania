#pragma once
#include "BaseGameObject.h"
#include "Resources.h"
#include "FileUtil.h"

struct Level
{
	int level;
	std::string fileImageBackgroud;
	std::string fileBackground;
	std::string fileObject;
	std::string fileBackgroundQuadtree;
	std::string fileObjectQuadtree;

	Level(int _level, std::string _fileImageBackgroud, std::string _fileBackground, std::string _fileObject, std::string _fileBackgroundQuadtree, std::string _fileObjectQuadtree)
	{
		fileImageBackgroud = _fileImageBackgroud;
		level = _level;
		fileBackground = _fileBackground;
		fileObject = _fileObject;
		fileBackgroundQuadtree = _fileBackgroundQuadtree;
		fileObjectQuadtree = _fileObjectQuadtree;
	}
	Level()
	{
		level = 1;
		fileImageBackgroud = "";
		fileBackground = "";
		fileObject = "";
		fileBackgroundQuadtree = "";
		fileObjectQuadtree = "";
	}
};
class CLevel : public CSingleton<CLevel>
{
	friend class CSingleton<CLevel>;
public:
	std::hash_map<int, Level*> listLevel;
public:
	CLevel();
	~CLevel();
	void readFileLevel(const std::string& filePath);
};

