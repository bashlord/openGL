#include "AudioManager.h"

#define SOUND_JOKER_LAUGH "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/Joker Laughing Sound Effect.mp3"
#define SOUND_RAIN "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/rainy short.wav"
#define SOUND_SH2 "/Users/JJK/Desktop/CSE167_3 4/CSE167_3/Ordinary Vanity (SH2).mp3"

using namespace std;
FMOD::System* fmodSystem;

FMOD::Sound* BGM;
FMOD::Sound* rain;
FMOD::Sound* jokerLaugh;

FMOD::Channel* musicChannel;
FMOD::Channel* rainChannel;
FMOD::Channel* SFXChannel;

AudioManager::AudioManager()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmodSystem);
	FmodErrorCheck(result);
	result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	FmodErrorCheck(result);

	result = fmodSystem->createSound(SOUND_JOKER_LAUGH, FMOD_DEFAULT, 0, &jokerLaugh);
	FmodErrorCheck(result);

	// BGM
	result = fmodSystem->createStream(SOUND_RAIN, FMOD_LOOP_NORMAL, 0, &rain);
	FmodErrorCheck(result);
	result = fmodSystem->playSound(rain, 0, false, &rainChannel);
	FmodErrorCheck(result);
	result = fmodSystem->createStream(SOUND_SH2, FMOD_LOOP_NORMAL, 0, &BGM);
	FmodErrorCheck(result);
	result = fmodSystem->playSound(BGM, 0, false, &musicChannel);
	musicChannel->setVolume(0.5f);
	FmodErrorCheck(result);
}

AudioManager::~AudioManager()
{}

AudioManager * AudioManager::Instance()
{
	if (!_instance)
		_instance = new AudioManager();
	
	return _instance;
}

void AudioManager::FmodErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void AudioManager::Update()
{
	fmodSystem->update();
}

void AudioManager::Laugh()
{
	cout << "I'M HONKING!" << endl;
	FMOD_RESULT result;
	result = fmodSystem->playSound(jokerLaugh, 0, false, &SFXChannel);
	SFXChannel->setVolume(0.75f);
	FmodErrorCheck(result);
}