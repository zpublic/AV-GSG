#pragma once

class AudioInput
{
public:
    AudioInput();
    virtual ~AudioInput ();

    virtual bool Initialize() = 0;
    virtual void Seek(uint32 sample_position) = 0;
    virtual uint32 Read(uint8* data_buffer, uint32 number_samples, bool& end) = 0;

    const std::string& GetFilename() const;

    uint32 GetSamplesPerSecond() const;

    uint16 GetBitsPerSample() const;

    uint16 GetNumberChannels() const;

    uint32 GetTotalNumberSamples() const;

    uint32 GetDataSize() const;

    float GetPlayTime() const;

    uint16 GetSampleSize() const;

protected:
    std::string _filename;

    //! \brief The number of samples per second (typically 11025, 22050, 44100)
    uint32 _samples_per_second;

    //! \brief The number of bits per sample (typically 8 or 16)
    uint16 _bits_per_sample;

    //! \brief Channels of the sound (1 = mono, 2 = stereo)
    uint16 _number_channels;

    //! \brief The total number of samples of the audio piece
    uint32 _total_number_samples;

    //! \brief The size of the audio data in bytes
    uint32 _data_size;

    //! \brief The size of an individual sample in bytes (_bits_per_sample * _channels / 8)
    uint16 _sample_size;

    //! \brief The total play ime of the audio piece in seconds (_samples / _samples_per_second)
    float _play_time;
};
