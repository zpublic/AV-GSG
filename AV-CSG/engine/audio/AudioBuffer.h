#pragma once
#include "al.h"

class AudioBuffer
{
public:
    AudioBuffer();
    ~AudioBuffer();

    void FillBuffer(uint8* data, ALenum format, uint32 size, uint32 frequency);

    bool IsValid() const;

    ALuint buffer_;
};
