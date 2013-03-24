#include "stdafx.h"
#include "AudioEngine.h"
#include "AudioDescriptor.h"

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

AudioSource* AudioEngine::_AcquireAudioSource()
{
    // (1) Find and return the first source that does not have an owner
    for (std::vector<AudioSource*>::iterator i = _audio_sources.begin(); i != _audio_sources.end(); i++)
    {
        if ((*i)->owner == NULL)
        {
            return *i;
        }
    }

    // (2) If all sources are owned, find one that is in the initial or stopped state and change its ownership
    for (std::vector<AudioSource*>::iterator i = _audio_sources.begin(); i != _audio_sources.end(); i++)
    {
        ALint state;
        alGetSourcei((*i)->source_, AL_SOURCE_STATE, &state);
        if (state == AL_INITIAL || state == AL_STOPPED)
        {
            (*i)->owner->_source = NULL;
            (*i)->Reset(); // this call sets the source owner pointer to NULL
            return *i;
        }
    }

    // (3) Return NULL in the (extremely rare) case that all sources are owned and actively playing or paused
    return NULL;
}

