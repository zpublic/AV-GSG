#include "stdafx.h"
#include "AudioEngine.h"

template<> AudioEngine* Singleton<AudioEngine>::m_pInst = NULL;

AudioEngine::~AudioEngine()
{

}

AudioEngine::AudioEngine()
{

}

bool AudioEngine::Initialize()
{
    return true;
}

void AudioEngine::PauseAudio()
{
    PauseAllSounds();
    PauseMusic();
}

void AudioEngine::ResumeAudio()
{
    ResumeAllSounds();
    ResumeMusic();
}

void AudioEngine::StopAudio()
{
    StopAllSounds();
    StopMusic();
}

bool AudioEngine::LoadMusic( const std::string& filename )
{
    return true;
}

void AudioEngine::StopMusic()
{

}

void AudioEngine::PlayMusic()
{

}

void AudioEngine::PauseMusic()
{

}

void AudioEngine::ResumeMusic()
{

}

bool AudioEngine::LoadSound( const std::string& filename )
{
    return true;
}

void AudioEngine::PlaySound( const std::string& filename )
{

}

void AudioEngine::StopSound( const std::string& filename )
{

}

void AudioEngine::PauseSound( const std::string& filename )
{

}

void AudioEngine::ResumeSound( const std::string& filename )
{

}

void AudioEngine::PauseAllSounds()
{

}

void AudioEngine::ResumeAllSounds()
{

}

void AudioEngine::StopAllSounds()
{

}

