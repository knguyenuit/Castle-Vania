#pragma once
#include "Global.h"
#include "BaseGameObject.h"
#include "Ground.h"
#include "Singleton.h"
#include "Collision.h"
#include "Brick.h"
#include "QuadTree.h"
#include "Resources.h"
#include "EnemyManage.h"
#include "FileUtil.h"
#include "Camera.h"
#include "DrawObject.h"


class CLoadObject : public CSingleton<CLoadObject>
{
	friend class CSingleton<CLoadObject>;
public:
	CLoadObject();
	~CLoadObject();

public:
	void Update(float deltaTime);
	void Collision(float deltaTime, CBaseGameObject* gameObj);
	void Draw();
public:
	std::hash_map<int, Box> listBox;
	// D/s tat ca cac duong link chua file map.
	std::vector<CBaseGameObject*> m_listGameObject;
	std::vector<CBaseGameObject*> m_listEmemy;
	
	std::hash_map<int, CBaseGameObject*> LoadGameObjectInfo(const std::string&);

	CBaseGameObject* CreateObject(int id, Vector2 pos);
	

	// TT
	bool contains(std::vector<int> v, int x);

	void readFile(const std::string&); // read file object .

									   // list quadtree
	std::hash_map<int, std::string>* m_listQuadTree;
	// <stt map, quadtree cua map>

	// List id cua doi tuong tren viewPort.
	std::vector<int> m_listIdObject;

	//Luu quad tree hien tai
	CQuadTree* m_quadTree;

	// d/s cac doi tuong cua map hien tai.
	std::hash_map<int, CBaseGameObject*> m_listObjectCurr;

	void Clear(); //clear object khi chuyen background

	std::vector<CBaseGameObject*> GetListGameObjectOnScreen() { return this->m_listGameObject; };
	void CreateObjectOnScreen();
	void LoadReSourceFromFile(std::string fileOJ, std::string fileQTOJ);
};

