#include "stdafx.h"
#include "AudioDescriptor.h"
#include "WavFile.h"
#include "OggFile.h"
#include "AudioMemory.h"

AudioDescriptor::AudioDescriptor()
    : _state(AUDIO_STATE_UNLOADED)
    , _buffer(NULL)
    , _source(NULL)
    , _input(NULL)
    , _stream(NULL)
    , _data(NULL)
    , _looping(false)
    , _offset(0)
    , _stream_buffer_size(0)
{
}

AudioDescriptor::AudioDescriptor(const AudioDescriptor& copy)
    : _state(AUDIO_STATE_UNLOADED)
    , _buffer(NULL)
    , _source(NULL)
    , _input(NULL)
    , _stream(NULL)
    , _data(NULL)
    , _looping(copy._looping)
    , _offset(0)
    , _stream_buffer_size(0)
{
}

bool AudioDescriptor::LoadAudio(
    const std::string& filename,
    AUDIO_LOAD load_type,
    uint32 stream_buffer_size)
{
    if (!AUDIO_ENABLE)
        return true;

    // Clean out any audio resources being used before trying to set new ones
    FreeAudio();

    // Load the input file for the audio
    if (filename.size() <= 3)
    {
        return false;
    }
    // Convert the file extension to uppercase and use it to create the proper input type
    std::string file_extension = filename.substr(filename.size() - 3, 3);
    for (std::string::iterator i = file_extension.begin(); i != file_extension.end(); i++)
        *i = toupper(*i);

    // Based on the extension of the file, load properly one
    if (file_extension.compare("WAV") == 0)
    {
        _input = new WavFile(filename);
    }
    else if (file_extension.compare("OGG") == 0)
    {
        _input = new OggFile(filename);
    }
    else
    {
        return false;
    }

    if (_input->Initialize() == false)
    {
        return false;
    }

    // Retreive audio data properties from the newly initialized input
    if (_input->GetBitsPerSample() == 8)
    {
        if (_input->GetNumberChannels() == 1)
        {
            _format = AL_FORMAT_MONO8;
        }
        else
        {
            _format = AL_FORMAT_STEREO8;
        }
    }
    else
    { // 16 bits per sample
        if (_input->GetNumberChannels() == 1)
        {
            _format = AL_FORMAT_MONO16;
        }
        else
        {
            _format = AL_FORMAT_STEREO16;
        }
    }

    // Load the audio data depending upon the load type requested
    if (load_type == AUDIO_LOAD_STATIC)
    {
        // For static sounds just 1 buffer is needed. We create it as an array here, so that
        // later we can delete it with a call of delete[], similar to the streaming cases
        _buffer = new AudioBuffer[1];

        // Create space in memory for the audio data to be read and passed to the OpenAL buffer
        _data = new uint8[_input->GetDataSize()];
        bool all_data_read = false;
        if (_input->Read(_data, _input->GetTotalNumberSamples(), all_data_read) != _input->GetTotalNumberSamples())
        {
            return false;
        }

        // Pass the buffer data to the OpenAL buffer
        _buffer->FillBuffer(_data, _format, _input->GetDataSize(), _input->GetSamplesPerSecond());
        delete[] _data;
        _data = NULL;

        // Attempt to acquire a source for the new audio to use
        _AcquireSource();
    }

    // Stream the audio from the file data
    else if (load_type == AUDIO_LOAD_STREAM_FILE)
    {
        _buffer = new AudioBuffer[NUMBER_STREAMING_BUFFERS]; // For streaming we need to use multiple buffers
        _stream = new AudioStream(_input, _looping);
        _stream_buffer_size = stream_buffer_size;

        _data = new uint8[_stream_buffer_size * _input->GetSampleSize()];

        // Attempt to acquire a source for the new audio to use
        _AcquireSource();
    }

    // Allocate memory for the audio data to remain in and stream it from that location
    else if (load_type == AUDIO_LOAD_STREAM_MEMORY)
    {
        _buffer = new AudioBuffer[NUMBER_STREAMING_BUFFERS]; // For streaming we need to use multiple buffers
        _stream = new AudioStream(_input, _looping);
        _stream_buffer_size = stream_buffer_size;

        _data = new uint8[_stream_buffer_size * _input->GetSampleSize()];

        // We need to replace the _input member with a AudioMemory class object
        AudioInput* temp_input = _input;
        _input = new AudioMemory(temp_input);
        delete temp_input;

        // Attempt to acquire a source for the new audio to use
        _AcquireSource();
    }
    else
    {
        return false;
    }

    _state = AUDIO_STATE_STOPPED;
    return true;
}

void AudioDescriptor::FreeAudio()
{
    if (_source != NULL)
        Stop();

    _state = AUDIO_STATE_UNLOADED;
    _offset = 0;

    // If the source is still attached to a sound, reset to the default parameters the source
    if (_source != NULL)
    {
        _source->Reset();
        _source = NULL;
    }

    if (_buffer != NULL)
    {
        delete[] _buffer;
        _buffer = NULL;
    }

    if (_input != NULL)
    {
        delete _input;
        _input = NULL;
    }

    if (_stream != NULL)
    {
        delete _stream;
        _stream = NULL;
    }

    if (_data != NULL)
    {
        delete[] _data;
        _data = NULL;
    }
}

AUDIO_STATE AudioDescriptor::GetState()
{
    // If the last set state was the playing state, we have to double check
    // with the OpenAL source to make sure that the audio is still playing.
    if (_state == AUDIO_STATE_PLAYING)
    {
        // If the descriptor no longe
        if (_source == NULL || _data == NULL)
        {
            _state = AUDIO_STATE_STOPPED;
        }
        else {
            ALint source_state;
            alGetSourcei(_source->source_, AL_SOURCE_STATE, &source_state);
            if (source_state != AL_PLAYING)
            {
                _state = AUDIO_STATE_STOPPED;
            }
        }
    }

    return _state;
}

void AudioDescriptor::Play()
{
    if (!AUDIO_ENABLE)
        return;

    if (_source == NULL)
    {
        _AcquireSource();
        if (_source == NULL)
        {
            return;
        }
        _SetSourceProperties();
    }

    if (_stream && _stream->GetEndOfStream())
    {
        _stream->Seek(_offset);
        _PrepareStreamingBuffers();
    }

    alSourcePlay(_source->source_);
    _state = AUDIO_STATE_PLAYING;
}

void AudioDescriptor::Stop()
{
    if (_state == AUDIO_STATE_STOPPED || _state == AUDIO_STATE_UNLOADED)
        return;

    if (_source == NULL)
    {
        return;
    }

    alSourceStop(_source->source_);
    _state = AUDIO_STATE_STOPPED;
}

void AudioDescriptor::Pause()
{
    if (_state == AUDIO_STATE_PAUSED || _state == AUDIO_STATE_UNLOADED)
        return;

    if (_source == NULL)
    {
        return;
    }

    alSourcePause(_source->source_);
    _state = AUDIO_STATE_PAUSED;
}

void AudioDescriptor::Resume()
{
    if (_state != AUDIO_STATE_PAUSED)
        return;

    Play();
}

void AudioDescriptor::SetLooping(bool loop)
{
    if (_looping == loop)
        return;

    _looping = loop;
    if (_stream != NULL)
    {
        _stream->SetLooping(_looping);
    }
    else if (_source != NULL)
    {
        if (_looping)
            alSourcei(_source->source_, AL_LOOPING, AL_TRUE);
        else
            alSourcei(_source->source_, AL_LOOPING, AL_FALSE);
    }
}

void AudioDescriptor::_AcquireSource()
{
    if (_source != NULL)
    {
        return;
    }

    if (_buffer == NULL)
    {
        return;
    }

    _source = AudioEngine_->_AcquireAudioSource();
    if (_source == NULL)
    {
        return;
    }

    _source->owner = this;
    _SetSourceProperties();
    if (_stream == NULL)
        alSourcei(_source->source_, AL_BUFFER, _buffer->buffer_);
    else
        _PrepareStreamingBuffers();
}

void AudioDescriptor::_SetSourceProperties()
{
    if (_source == NULL)
    {
        return;
    }

    // Set volume (gain)
    float volume_multiplier = 0.0f;
//     if (IsSound())
//         volume_multiplier = AudioManager->GetSoundVolume();
//     else
//         volume_multiplier = AudioManager->GetMusicVolume();
    ///> 先不管音量
    alSourcef(_source->source_, AL_GAIN, 1/*_volume * volume_multiplier*/);

    // Set looping (source has looping disabled by default, so only need to check the true case)
    if (_stream != NULL)
    {
        _stream->SetLooping(_looping);
    }
    else if (_source != NULL)
    {
        if (_looping)
        {
            alSourcei(_source->source_, AL_LOOPING, AL_TRUE);
        }
    }
}

void AudioDescriptor::_PrepareStreamingBuffers()
{
    if (_stream == NULL)
    {
        return;
    }

    if (_source == NULL)
    {
        return;
    }

    bool was_playing = false;

    // Stop the audio if it is playing and detatch the buffer from the source
    if (_state == AUDIO_STATE_PLAYING)
    {
        was_playing = true;
        Stop();
    }
    alSourcei(_source->source_, AL_BUFFER, 0);

    // Fill each buffer with audio data
    for (uint32 i = 0; i < NUMBER_STREAMING_BUFFERS; i++)
    {
        uint32 read = _stream->FillBuffer(_data, _stream_buffer_size);
        if (read > 0)
        {
            _buffer[i].FillBuffer(
                _data,
                _format,
                read * _input->GetSampleSize(),
                _input->GetSamplesPerSecond());
            if (_source != NULL)
                alSourceQueueBuffers(_source->source_, 1, &_buffer[i].buffer_);
        }
    }

    if (was_playing)
    {
        Play();
    }
}
