#pragma once
#include "al.h"

class AudioDescriptor;

class AudioSource
{
    friend class AudioEngine;
public:
    AudioSource(ALuint al_source);

    ~AudioSource();

    bool IsValid() const;

    void Reset();

    ALuint source_;
    AudioDescriptor* owner;
};
