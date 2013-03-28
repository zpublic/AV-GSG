#include "stdafx.h"
#include "AudioMemory.h"

AudioMemory::AudioMemory(AudioInput* input) :
    AudioInput(),
    _audio_data(NULL),
    _data_position(0)
{
    _filename = input->GetFilename();
    _samples_per_second = input->GetSamplesPerSecond();
    _bits_per_sample = input->GetBitsPerSample();
    _number_channels = static_cast<uint8>(input->GetNumberChannels());
    _total_number_samples = input->GetTotalNumberSamples();
    _sample_size = input->GetSampleSize();
    _play_time = input->GetPlayTime();
    _data_size = input->GetDataSize();

    _audio_data = new uint8[input->GetDataSize()];
    bool all_data_read = false;
    input->Read(_audio_data, input->GetTotalNumberSamples(), all_data_read);
}

AudioMemory::AudioMemory(const AudioMemory& audio_memory) :
    AudioInput(),
    _audio_data(NULL),
    _data_position(0)
{
    _filename = audio_memory._filename;
    _samples_per_second = audio_memory.GetSamplesPerSecond();
    _bits_per_sample = audio_memory.GetBitsPerSample();
    _number_channels = static_cast<uint8>(audio_memory.GetNumberChannels());
    _total_number_samples = audio_memory.GetTotalNumberSamples();
    _sample_size = audio_memory.GetSampleSize();
    _play_time = audio_memory.GetPlayTime();
    _data_size = audio_memory.GetDataSize();

    _audio_data = new uint8[_data_size];
    memcpy(_audio_data, audio_memory._audio_data, _data_size);
}

AudioMemory& AudioMemory::operator=(const AudioMemory& audio_memory)
{
    if (_audio_data != NULL)
    {
        delete[] _audio_data;
        _audio_data = NULL;
    }
    _filename = audio_memory._filename;
    _samples_per_second = audio_memory.GetSamplesPerSecond();
    _bits_per_sample = audio_memory.GetBitsPerSample();
    _number_channels = static_cast<uint8>(audio_memory.GetNumberChannels());
    _total_number_samples = audio_memory.GetTotalNumberSamples();
    _sample_size = audio_memory.GetSampleSize();
    _play_time = audio_memory.GetPlayTime();
    _data_size = audio_memory.GetDataSize();

    _data_position = audio_memory._data_position;
    _audio_data = new uint8[_data_size];
    memcpy(_audio_data, audio_memory._audio_data, _data_size);

    return *this;
}

AudioMemory::~AudioMemory()
{
    if (_audio_data != NULL)
    {
        delete[] _audio_data;
        _audio_data = NULL;
    }
}


void AudioMemory::Seek(uint32 sample_position)
{
    if (_data_position >= _total_number_samples)
    {
        return;
    }

    _data_position = sample_position;
}

uint32 AudioMemory::Read(uint8* buffer, uint32 size, bool& end)
{
    // Clamp the number of samples to read in case there are not enough because of end of stream
    uint32 read = (_total_number_samples - _data_position >= size)
        ? size
        : (_total_number_samples - _data_position);

    // Copy the data in the buffer and move the read cursor
    memcpy(buffer, buffer + _data_position * _sample_size, read * _sample_size);
    _data_position += read;
    end = (_data_position == _total_number_samples);

    return read;
}

bool AudioMemory::Initialize()
{
    return true;
}
