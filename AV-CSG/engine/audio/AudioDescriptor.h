#pragma once
#include "al.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioInput.h"
#include "AudioStream.h"

enum AUDIO_STATE
{
    AUDIO_STATE_UNLOADED   = 0,
    AUDIO_STATE_STOPPED    = 1,
    AUDIO_STATE_PLAYING    = 2,
    AUDIO_STATE_PAUSED     = 3,
};

enum AUDIO_LOAD
{
    AUDIO_LOAD_STATIC         = 0,
    AUDIO_LOAD_STREAM_FILE    = 1,
    AUDIO_LOAD_STREAM_MEMORY  = 2,
};

const uint32 DEFAULT_BUFFER_SIZE = 8192;
const uint32 NUMBER_STREAMING_BUFFERS = 4;

class AudioDescriptor
{
    friend class AudioEngine;
public:
    AudioDescriptor();

    virtual ~AudioDescriptor()
    { FreeAudio(); }

    AudioDescriptor(const AudioDescriptor& copy);

    virtual bool LoadAudio(
        const std::string& filename,
        AUDIO_LOAD load_type = AUDIO_LOAD_STATIC,
        uint32 stream_buffer_size = DEFAULT_BUFFER_SIZE
        );

    void FreeAudio();

    const std::string GetFilename() const
    {
        if (_input == NULL)
            return "";
        else
            return _input->GetFilename();
    }

    virtual bool IsSound() const = 0;

    AUDIO_STATE GetState();

    virtual void Play();
    virtual void Stop();
    virtual void Pause();
    virtual void Resume();

    bool IsLooping() const
    { return _looping; }
    void SetLooping(bool loop);

protected:
    void _AcquireSource();
    void _SetSourceProperties();
    void _PrepareStreamingBuffers();

    AUDIO_STATE _state;

    AudioBuffer* _buffer;

    AudioSource* _source;

    AudioInput* _input;

    AudioStream* _stream;

    //! \brief A pointer to where the data is streamed to
    uint8* _data;

    //! \brief The format of the audio (mono/stereo, 8/16 bits per second).
    ALenum _format;

    //! \brief Flag for indicating if the audio should loop or not
    bool _looping;

    //! \brief The audio position that was last seeked, in samples.
    uint32 _offset;

    //! \brief Size of the streaming buffer, if the audio was loaded for streaming
    uint32 _stream_buffer_size;
};
