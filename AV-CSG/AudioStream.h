#pragma once
#include "AudioInput.h"

class AudioStream
{
public:
    AudioStream (AudioInput* input, bool loop);

    ~AudioStream()
    {}

    uint32 FillBuffer(uint8* buffer, uint32 size);

    void Seek(uint32 sample);

    bool IsLooping() const
    { return _looping; }

    void SetLooping(bool loop)
    { _looping = loop; if (loop) _end_of_stream = false; }

    void SetLoopStart(uint32 sample);

    void SetLoopEnd(uint32 sample);

    bool GetEndOfStream() const
    { return _end_of_stream; }

    private:
    //! \brief Pointer to an AudioInput object that holds the audio data
    AudioInput* _audio_input;

    //! \brief Set to true when the stream should loop
    bool _looping;

    //! \brief The sample that represents the start position of the loop
    uint32 _loop_start_position;

    //! \brief The sample that represents the end position of the loop
    uint32 _loop_end_position;

    //! \brief The sample position from where the next read operation will be performed
    uint32 _read_position;

    //! \brief True if the end of the stream was reached, false otherwise
    bool _end_of_stream;
};
