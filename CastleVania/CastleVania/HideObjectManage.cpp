#include "HideObjectManage.h"



CHideObjectManage::CHideObjectManage()
{
}


CHideObjectManage::~CHideObjectManage()
{
}

void CHideObjectManage::Update(float deltaTime)
{
	if (this->m_listHideObject.size() != 0)
	{
		for (std::vector<CHideObject*>::iterator it = this->m_listHideObject.begin();
			it != this->m_listHideObject.end(); ++it)
		{
			CHideObject* obj = *it;
			obj->Update(deltaTime);
		}
	}

}

CHideObject * CHideObjectManage::CreateHideObject(HideObject_TYPE type, Vector2 pos)
{
	CHideObject* obj = NULL;
	switch (type)
	{
	case GroundHorizontal:
		break;
	case GroundVertical:
		break;
	case StopScrollScene:
		break;
	case ChangeScene:
		break;
	case Free:
		break;
		//cau thang
	case DownStairLeft:
		obj = new CStair(HideObject_TYPE::DownStairLeft, pos);
		break;
	case UpStairLeft:
		obj = new CStair(HideObject_TYPE::UpStairLeft, pos);
		break;
	case DownStairRight:
		obj = new CStair(HideObject_TYPE::DownStairRight, pos);
		break;
	case UpStairRight:
		obj = new CStair(HideObject_TYPE::UpStairRight, pos);
		break;

	case ChangeTop:
		break;
	case ChangeDown:
		break;
	default:
		break;
	}
	this->m_listHideObject.push_back(obj);
	return obj;
}
