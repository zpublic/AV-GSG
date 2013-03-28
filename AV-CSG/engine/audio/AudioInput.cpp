#include "stdafx.h"
#include "AudioInput.h"

AudioInput::AudioInput()
    : _filename("")
    , _samples_per_second(0)
    , _bits_per_sample(0)
    , _number_channels(0)
    , _total_number_samples(0)
    , _data_size(0)
    , _sample_size(0)
    , _play_time(0.0f)

{
}

AudioInput::~AudioInput()
{

}

const std::string& AudioInput::GetFilename() const
{
    return _filename;
}

uint32 AudioInput::GetSamplesPerSecond() const
{
    return _samples_per_second;
}

uint16 AudioInput::GetBitsPerSample() const
{
    return _bits_per_sample;
}

uint16 AudioInput::GetNumberChannels() const
{
    return _number_channels;
}

uint32 AudioInput::GetTotalNumberSamples() const
{
    return _total_number_samples;
}

uint32 AudioInput::GetDataSize() const
{
    return _data_size;
}

float AudioInput::GetPlayTime() const
{
    return _play_time;
}

uint16 AudioInput::GetSampleSize() const
{
    return _sample_size;
}
