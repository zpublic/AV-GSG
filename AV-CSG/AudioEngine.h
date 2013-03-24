#pragma once
#include "Singleton.h"
#include "AudioSource.h"
#include <vector>

#ifdef __BIG_ENDIAN__
#define SWAP_U32_FROM_LITTLE(x) { x = SDL_Swap32(x); }
#define SWAP_U16_FROM_LITTLE(x) { x = SDL_Swap16(x); }
#else
// not a big-endian system - no byte swapping needed
#define SWAP_U32_FROM_LITTLE(x) { }
#define SWAP_U16_FROM_LITTLE(x) { }
#endif

class AudioEngine : public Singleton<AudioEngine>
{
    friend class Singleton<AudioEngine>;

public:
    virtual ~AudioEngine();

    virtual bool Initialize();

    void PauseAudio();
    void ResumeAudio();
    void StopAudio();

    ///> 背景音乐部分
    bool LoadMusic(const std::string& filename);
    void StopMusic();
    void PlayMusic();
    void PauseMusic();
    void ResumeMusic();

    ///> 音效部分
    bool LoadSound(const std::string& filename);
    void PlaySound(const std::string& filename);
    void StopSound(const std::string& filename);
    void PauseSound(const std::string& filename);
    void ResumeSound(const std::string& filename);
    void PauseAllSounds();
    void ResumeAllSounds();
    void StopAllSounds();

    AudioSource* _AcquireAudioSource();

private:
    AudioEngine();

    std::vector<AudioSource*> _audio_sources;
};
