#include "stdafx.h"
#include "AudioSource.h"

AudioSource::AudioSource( ALuint al_source )
    : source_(al_source)
    , owner(NULL)
{

}

AudioSource::~AudioSource()
{
    if (IsValid())
    {
        alSourceStop(source_);
        alDeleteSources(1, &source_);
    }
}

bool AudioSource::IsValid() const
{
    return (alIsSource(source_) == AL_TRUE);
}

void AudioSource::Reset()
{
    owner = NULL;
    if (IsValid() == false)
    {
        return;
    }
    alSourcei(source_, AL_LOOPING, AL_FALSE);
    alSourcef(source_, AL_GAIN, 1.0f);
    alSourcei(source_, AL_SAMPLE_OFFSET, 0);
    alSourcei(source_, AL_BUFFER, 0);
}
