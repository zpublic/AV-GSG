#include "stdafx.h"
#include "AudioBuffer.h"

AudioBuffer::AudioBuffer()
{

}

AudioBuffer::~AudioBuffer()
{

}

void AudioBuffer::FillBuffer(
    uint8* data,
    ALenum format,
    uint32 size,
    uint32 frequency)
{
    alBufferData(buffer_, format, data, size, frequency);
}

bool AudioBuffer::IsValid() const
{
    return (alIsBuffer(buffer_) == AL_TRUE);
}
