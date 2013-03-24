#pragma once
#include "AudioInput.h"

class AudioMemory : public AudioInput
{
public:
    AudioMemory(AudioInput* input);

    AudioMemory(const AudioMemory& audio_memory);
    AudioMemory& operator=(const AudioMemory& other_audio_memory);

    ~AudioMemory();

    bool Initialize();

    void Seek(uint32 sample_position);

    uint32 Read(uint8* buffer, uint32 size, bool& end);

private:
    uint8* _audio_data;

    uint32 _data_position;
};
