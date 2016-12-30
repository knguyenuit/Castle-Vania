#ifndef __SIMON_H__
#define __SIMON_H__

#include "BaseGameObject.h"
#include "Animation.h"
#include "Singleton.h"
#include "Move.h"
#include "Input.h"
#include "Collision.h"
#include "Cane.h"
#include "Global.h"
#include "OnCollision.h"
#include "HinhChuNhat.h"
#include "Camera.h"
#include "ManageAudio.h"
#include "Sprite.h"
#include "Resources.h"
#include "DrawObject.h"
enum SIMON_status
{
	NONE = 0,
	IDLE = 1,
	MOVE = 2,
	JUMP = 3,
	SIT = 5,
	FALL = 6,
	ACTACK = 7,
	COLLISION_ENEMY = 8,
	ONSTAIR = 9,
	MOVE_JUMP = 10,
	MOVE_JUMP_ATTACK = 11,
	SIT_ATTACK = 12,
	WEAPON_ATTACK = 13
};

class CSimon : public CBaseGameObject, public CAnimation, public CMove, public CSingleton<CSimon>
{
	friend class CSingleton<CSimon>;

public:
	CSimon();
	~CSimon();
public:
	CCane *cane;
	CHinhChuNhat *hv;
	SIMON_status simon_Status;
	//cac ham ke thua tu BaseGameObject
public:
	void Update(float deltaTime);//ham Update chinh cua game
	Vector2 GetPos();
	void OnCollision(float deltaTime, std::hash_map<int, Box> listBox);
	void UpdateGround(float deltaTime, std::vector<CBaseGameObject*> listObject);
	void OnCollision(float deltaTime, CBaseGameObject* hv);
	void OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject);
	Box GetBox();
	RECT* GetBound();
	RECT* GetRectRS();
	CSprite * m_draw;
	//cac ham ke thua tu Animation
public:
	void SetFrame();		// ham chuyen frame.
public://Collect item
	bool isPickUpMorningStar = false;
	float timePickUpMorningStar = 0.0f;
public:
	//xu ly Input
	void OnKeyDown(float deltaTime);
	void OnKeyUp(float deltaTime);
	void ProcessInput(float deltaTime);
#pragma region Input Flag
	bool isArrowKeyDown = false;
	bool isArrowKeyUp = false;
	bool isArrowKeyLeft = false;
	bool isArrowKeyRight = false;
	bool isKey_Z = false;
	bool isKey_X = false;
	bool isKey_L = false;
#pragma endregion

	//cac thong so ve Simon
public: //xu li cau thang
	bool isUpStair = false, isDownStair = false;
	bool isOnStair = false;
	bool prepareOnStair = false, prepareOutStair = false;
	bool canUpStairLeft, canUpStairRight, canDownStairLeft, canDownStairRight;
	int currStairStep = 0;
	Vector2 currStairPos = Vector2(0, 0);
	Vector2 currSimonStairPos = Vector2(0, 0);
	bool isMoveToStair = false;
	bool isCancelStairMove = true;
	bool isFirstStairStep = false;
	//Xu ly di chuyen MoveTo
	bool isMoveToLeft, isMoveToRight, isMoveToUp, isMoveToDown; // direction, default left // direction, default left
	bool check_arrive_x = false, check_arrive_y = false;
public:
	int m_keyDown;
	int m_keyUp;
	float m_timeCountFrame;
	bool isInput;
	bool canJump = false;
	bool isJump = false;

	bool isFall = false;
	bool canFall = false;

	bool isSit = false;
	bool canSit = false;

	bool isMove = false;
	bool canMove = false;
	bool isMoveJump = false;

	bool isAttack = false; //tan cong bang cane
	bool canAttack = false;

	bool isWeaponAttacking = false; //tan cong bang weapon
	float timeDelayWeaponAttacking = 0.3f;
	bool canWeaponAttacking = false;

	bool isChangeStatus = false;
	bool canChangeStatus = false;

	bool isCheckChangeState = false;
	bool isCollisionEnemy = false;
	bool isUnAvailable = false;
	bool isUnAvailableDraw = false;
	float timeUnAvailable = 0.0f;
	float timeCollisionEnemy = 0.0f;
	bool isMoveLeft;
	//set co danh trung enemy ko
	bool isAttackEnemy = false;
	
public:
	//khoi luong cua simon
	int m_weight;
	//mau simon
	int m_hpSimon;
	//level hien tai
	int m_currentLevel;
	//so trai tim
	int m_countHeart = 0;
	//so mang
	int m_countLife = 2;
	//diem
	int m_Score = 0;
	// mau  boss enemy (choi lay)
	int m_BossVampireBatHP = 16;
	WEAPON_name m_currentWeapon;
public: // change screeen down
	bool canChangeDown = false;
	bool isChangeDown = false;

private:
	void InitAnimation();//khoi tao cac thong so cua Simon
	void InitMove();//khoi tao cac thong so chuyen dong cua Simon
	void Gravity(float deltaTime);

public:
	//ve draw
	Vector3 posDraw = Vector3();
	CTexture* texture = new CTexture();
	CDrawObject *drawManager;
	void Draw();
	//Xy ly hanh dong
	void UpdateStatus(float deltaTime);
	void ActionUpdate(float deltaTime);
	void MoveUpdate(float deltaTime);
	void JumpUpdate(float deltaTime);
	void SitUpdate(float deltaTime);
	void AttackUpdate(float deltaTime);
	void EnemyCollisionUpdate(float deltaTime);
	void FallUpdate(float deltaTime);
	void Jump(float deltaTime);
	//leo cau thang
	bool MoveTo(Vector2 point, float deltaTime);
	//reset gia tri cua simon khi chet
	void ResetSimon();
};


#endif // !__SIMON_H__

