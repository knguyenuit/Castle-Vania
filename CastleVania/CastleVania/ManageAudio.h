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
	Select = 3062
};

#endif // !__TYPE__AUDIO__
