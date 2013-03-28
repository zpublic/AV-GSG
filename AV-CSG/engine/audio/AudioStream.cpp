#include "stdafx.h"
#include "AudioStream.h"

AudioStream::AudioStream(AudioInput* input, bool loop)
    : _audio_input(input)
    , _looping(loop)
    , _loop_start_position(0)
    , _loop_end_position(0)
    , _read_position(0)
    , _end_of_stream(false)
{
    if (_audio_input == NULL)
    {
        exit(1);
    }

    // Loop end is initially set to the final sample
    _loop_end_position = _audio_input->GetTotalNumberSamples();
}

uint32 AudioStream::FillBuffer(uint8* buffer, uint32 size)
{
    uint32 num_samples_read = 0; // The number of samples which have been read
    uint32 read_samples; // The number of samples to request the audio input to read

    while (num_samples_read < size)
    {
        // If looping is enabled and the end of the stream has been reached, seek to the starting position
        if (_looping == true && (_read_position == _loop_end_position || _read_position == _audio_input->GetTotalNumberSamples())) {
            _audio_input->Seek(_loop_start_position);
            _read_position = _loop_start_position;
        }

        // Determine the number of samples we should request for the input to read
        uint32 remaining_data = (_looping == true) ? _loop_end_position : _audio_input->GetTotalNumberSamples();
        remaining_data -= _read_position;
        read_samples = (size - num_samples_read < remaining_data) ? size - num_samples_read : remaining_data;
        num_samples_read += _audio_input->Read(buffer + num_samples_read * _audio_input->GetSampleSize(), read_samples, _end_of_stream);
        _read_position += num_samples_read;

        // Detect early exit condition
        if (_looping == false && _end_of_stream == true)
        {
            return num_samples_read;
        }
    }

    return num_samples_read;
}

void AudioStream::Seek(uint32 sample)
{
    _audio_input->Seek(sample);
    _read_position = sample;
    _end_of_stream = false;
}

void AudioStream::SetLoopStart(uint32 sample)
{
    if (sample >= _audio_input->GetTotalNumberSamples())
    {
        return;
    }

    _loop_start_position = sample;
}

void AudioStream::SetLoopEnd(uint32 sample)
{
    if (sample >= _audio_input->GetTotalNumberSamples())
    {
        return;
    }

    _loop_end_position = sample;
}
