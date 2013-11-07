
#pragma once

#include "NNConfig.h"
#include "NNSound.h"
#include "Library/FMOD/inc/fmod.hpp"
#include "Library/FMOD/inc/fmod_errors.h"

/* */
/* NNAudioSystem
/* ���� ����� ����ϴ� �̱��� Ŭ����/* */
/* Application
/* �����ӿ�ũ�� �ٽ� Ŭ����
/* �������� ������ �������� �����ϰ�
/* ���� ������ ���� ��Ȱ�� �Ѵ�.
/* */
/* */

class NNAudioSystem
{
public:
	static NNAudioSystem* GetInstance();
	static void ReleaseInstance();

	void Play( NNSound* sound );
	void Pause( NNSound* sound );
	void Stop( NNSound* sound );
	void Reset( NNSound* sound );

	void SetVolume( NNSound* sound, float volume );
	void SetPan( NNSound* sound, float pan );
	void SetFrequency( NNSound* sound, float frequency );

	bool IsPlay( NNSound* sound );

	FMOD::System* GetSystem() { return m_System; }

private:
	FMOD::System* m_System;
	FMOD::ChannelGroup* m_ChannelGroup;

	static NNAudioSystem* m_pInstance;

	NNAudioSystem();
	~NNAudioSystem();
};

// class NNAudioSystem
// {
// private:
// 	static NNAudioSystem* m_pInstance;
// 
// private:
// 	NNAudioSystem();
// 	~NNAudioSystem();
// 
// public:
// 	static NNAudioSystem* GetInstance();
// 	static void ReleaseInstance();
// 
// private:
// 	NNSound* m_BackgroundSound;
// 	std::map<std::string, NNSound*> m_EffectSoundTable;
// 
// public:
// 	/*		Background	*/
// 	void SetBackgroundSound( std::wstring path );
// 	void PlayBackgroundSound();
// 	void PauseBackgroundSound();
// 	void StopBackgroundSound();
// 
// 	/*		Effect		*/
// 	void AddEffectSound( std::string key, std::wstring path );
// 	void RemoveEffectSound( std::string key );
// 
// 	void PlayEffectSound( std::string key );
// 	void PauseEffectSound( std::string key );
// 	void StopEffectSound( std::string key );
// 
// 	void AllPlayEffectSound();
// 	void AllPauseEffectSound();
// 	void AllStopEffectSound();
// 
// public:
// 	inline NNSound* GetBackgroundSound() const { return m_BackgroundSound; }
// 	inline NNSound* GetEffectSound( std::string key ) /*const*/ { return m_EffectSoundTable[key]; }
// };


