#pragma once
#include "Global.h"
#include "BaseGameObject.h"
#include "Ground.h"
#include "Singleton.h"
#include "Collision.h"
#include "Brick.h"






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

	std::vector<int> m_listIdObject;
	void LoadGameObjectFromFile(const std::string&);

	CBaseGameObject* CreateObject(int id, Vector2 pos);
	std::hash_map<int, CBaseGameObject*> LoadGameObjectInfo(const std::string&);

	// TT
	bool contains(std::vector<int> v, int x);

	void readFile(const std::string&);

	void Clear(); //clear object khi chuyen background

};

