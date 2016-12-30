#include "LoadObject.h"





CLoadObject::CLoadObject()
{
	this->m_listGameObject = std::vector<CBaseGameObject*>();
	
	
	this->m_quadTree = new CQuadTree();

}


CLoadObject::~CLoadObject()
{
}

void CLoadObject::Update(float deltaTime)
{
	this->CreateObjectOnScreen();

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


CBaseGameObject* CLoadObject::CreateObject(int id, Vector2 pos, int width, int height)
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
	case 702:
		return new CBrick(pos, width, height);
		break;
	case 705:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::ChangeScene, pos);
		
		break;
	case 201:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::Zombie, pos);
		break;
	case 202:
	case 203:
		return CEnemyManage::GetInstance()->CreateEnemy(static_cast<ENEMY_type>(id), pos);
		break;
	case 205:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::FishMan, pos);
		break;
	case 208:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::BlackKnight, pos);
		break;
	case 207:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::DragonSkullCanon, pos);
		break;
	case 401:
		return CEnemyManage::GetInstance()->CreateEnemy(BossVampireBat, pos);
		break;
	case 612:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::SmallLight, pos, ITEM_name::Boomerang);
		break;
	case 613:
	case 611:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::SmallLight, pos, ITEM_name::Axe);
		break;
	case 615:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::SmallLight, pos, ITEM_name::FireBomb);
		break;
	case 616:
	case 614:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::SmallLight, pos, ITEM_name::SmallHeart);
		break;
	case 617:
		return CEnemyManage::GetInstance()->CreateEnemy(ENEMY_type::SmallLight, pos, ITEM_name::SmallHeart);
		break;
	case 703:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::DownStairLeft, pos);
		break;
	case 704:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::UpStairLeft, pos);
		break;
	case 706:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::StopScrollScene, pos);
		break;
	case 716:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::ChangeDown, pos);
		break;
	case 712:
		return new CBrickVertical(pos, width, height);
		break;
	case 713:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::DownStairRight, pos);
		break;
	
	case 714:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::UpStairRight, pos);
		break;
	case 888:
		return CHideObjectManage::GetInstance()->CreateHideObject(HideObject_TYPE::CheckSimonDie, pos);
		break;
	case 653:
		return CGroundMovingManage::GetInstance()->CreateGroundMovingPlatform(pos);
		break;
	default:
		break;
	}

}

std::hash_map<int, CBaseGameObject*> CLoadObject::LoadGameObjectInfo(const std::string &filePath)
{
	std::hash_map<int, CBaseGameObject*> listInfo;
	std::vector<std::string> data = CFileUtil::GetInstance()->LoadFromFile(filePath);
	std::vector<std::string> item;
	typedef pair<int, CBaseGameObject*> Pair;
	typedef pair<int, Box> Pair1;
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
				Vector2 pos = Vector2(PosX, PosY);
				float Width = atoi(item.at(4).c_str());
				float Height = atoi(item.at(5).c_str());
				Box b = Box(PosX, PosY, Width, Height);
				gameObj = this->CreateObject(idItem, pos, Width, Height);
				listInfo.insert(Pair(iDObjectInMap, gameObj));
			}
		}

		return listInfo;
	}
}


void CLoadObject::Clear()
{
	if (this->m_quadTree)
	{
		this->m_quadTree->Clear();
		this->m_quadTree = nullptr;
		this->m_quadTree = new CQuadTree();
	}
	m_listGameObject.clear();
	m_listObjectCurr.clear();
	m_listIdObject.clear();
	listBox.clear();

}
//Xen trong quadtree va khoi tao doi tuong
void CLoadObject::CreateObjectOnScreen()
{
	
	std::vector<int> m_oldListIdObject;
	m_oldListIdObject.swap(this->m_listIdObject);
	this->m_listIdObject.clear();

	if (this->m_quadTree)
	{
		// Lay ra danh sach id cua doi tuong dinh voi viewPort.
		this->m_quadTree->GetListObjectOnScreen(CCamera::GetInstance()->GetBound(),
			this->m_quadTree->GetRoot(),
			m_listIdObject);

		if (m_listIdObject.size() != 0)
		{
			// Duyet qua tung phan tu cua d/s cac doi tuong tren man hinh..
			// Neu doi tuong trong ds moi nay
			// - Co trong moi + co trong cu => thuc hien update
			// - Moi co + cu k co => thuc hien ve doi tuong do ra
			// - Moi k co + cu co => xoa doi tuong ra khoi d/s can ve

			// xoa dt khoi d/s
			vector<CBaseGameObject*>::iterator it;

			// Duyet moi trong cu
			for (int j = 0; j < m_oldListIdObject.size(); j++)
			{
				// List moi co, ma cu k co
				// Thuc hien xoa doi tuong khoi node.
				if (!contains(m_listIdObject, m_oldListIdObject.at(j)))
				{
					for (it = m_listGameObject.begin(); it != m_listGameObject.end();)
					{
						if (*it == this->m_listObjectCurr.find(m_oldListIdObject.at(j))->second)
						{
							//Xoa doi tuong cu ra khoi danh sach.
							it = this->m_listGameObject.erase(it);
						}
						else
							++it;
					}
				}
			}

			// Duyet cu trong moi
			for (int i = 0; i < m_listIdObject.size(); i++)
			{
				// m_listIdObject la ds moi
				// m_oldListIdObject la ds cu.

				// Co trong moi nhung k ton tai trong cu
				if (!contains(m_oldListIdObject, m_listIdObject.at(i)))
				{
					//NO bo cho nay sau khi goi change map no trung doi tuong
					// Them doi tuong vao d/s

					if (this->m_listObjectCurr.find(m_listIdObject.at(i)) != this->m_listObjectCurr.end())
					{
						
						this->m_listGameObject.push_back(this->m_listObjectCurr.find(m_listIdObject.at(i))->second);
					}
					else
					{
						int count = 0;
					}


				}

			}
		}
	}

}

void CLoadObject::LoadReSourceFromFile(std::string fileOJ, std::string fileQTOJ)
{
	this->m_listObjectCurr = this->LoadGameObjectInfo(fileOJ);
	//readFile(fileOJ);
	this->m_quadTree->ReBuildQuadTree(fileQTOJ);
	
}
