#ifndef __CMANAGE__AUDIO__
#define __CMANAGE__AUDIO__
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include "SoundUtil.h"
#include "Singleton.h"

enum TypeAudio;
//audio
#define AUDIO_PATH "..\\Resources\\Audio\\AudioPath.txt"

class ManageAudio : public CSingleton<ManageAudio>
{
	friend class CSingleton<ManageAudio>;
protected:
	CSoundManager* soundManage;
	std::hash_map<int, CSound*> listAudio;

public:
	bool _Music_Background;
	bool _Sound;

	ManageAudio(void);
	int init_DirectSound(HWND);
	void addSound(int key, bool loop, std::string fileName);
	CSound* loadSound(bool loop, std::string fileName);
	void playSound(TypeAudio _type);
	void loopSound(CSound *);
	void stopSound(TypeAudio _type);
	void readFileAudio();
	~ManageAudio(void);
};

#endif // !__CMANAGE__AUDIO__

#ifndef __TYPE__AUDIO__
#define __TYPE__AUDIO__

enum TypeAudio
{
	Boss_Battle_Poison_Mind = 3001,
	Game_Over = 3002,
	Game_Start_Prologue = 3003,
	Life_Lost = 3004,
	Stage_01_Vampire_Killer = 3005,
	Stage_04_Stalker = 3006,
	Stage_Clear = 3007,
	Title_Theme_Prelude = 3008,
	Collect_Item = 3051,
	CollectWeapon = 3052,
	Decrease_Weapon_Use_Point = 3053,
	Falling = 3054,
	Falling_Down_Water_Surface = 3055,
	Hit = 3056,
	Hit_Cannon = 3057,
	Holy_Cross = 3058,
	Holy_Water = 3059,
	Open_Door = 3060,
	Pause = 3061,
	Select = 3062,
	Splash_Water = 3063,
	Using_Whip = 3064
};

#endif // !__TYPE__AUDIO__
