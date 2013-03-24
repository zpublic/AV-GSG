#include "stdafx.h"
#include "WavFile.h"

WavFile::WavFile( const std::string& file_name )
    : AudioInput()
{
    _filename = file_name;
}

WavFile::~WavFile()
{
    if (_file_input.is_open() == true)
        _file_input.close();
}

bool WavFile::Initialize()
{
    uint32 size;
    char buffer[4];

    _file_input.open(_filename.c_str(), std::ios::binary);
    if (_file_input.fail())
    {
        _file_input.clear();
        return false;
    }

    // Check that the initial chunk ID is "RIFF" -- 4 bytes
    _file_input.read(buffer, 4);
    if (buffer[0] != 'R' || buffer[1] != 'I' || buffer[2] != 'F' || buffer[3] != 'F')
    {
        return false;
    }

    // Get chunk size (file size - 8) -- 4 bytes
    _file_input.read(buffer, 4);
    memcpy(&size, buffer, 4);
    SWAP_U32_FROM_LITTLE(size);

    // Check format to be "WAVE" -- 4 bytes
    _file_input.read(buffer, 4);
    if (buffer[0] != 'W' || buffer[1] != 'A' || buffer[2] != 'V' || buffer[3] != 'E')
    {
        return false;
    }

    // Check SubChunk ID to be "fmt " -- 4 bytes
    _file_input.read(buffer, 4);
    if (buffer[0] != 'f' || buffer[1] != 'm' || buffer[2] != 't' || buffer[3] != ' ')
    {
        return false;
    }

    // Check subchunk size (to be 16) -- 4 bytes
    _file_input.read(buffer, 4);
    memcpy(&size, buffer, 4);
    SWAP_U32_FROM_LITTLE(size);
    if (size != 16)
    {
        return false;
    }

    // Check audio format (only PCM supported currently) -- 2 bytes
    _file_input.read(buffer, 2);
    size = 0;
    memcpy(&size, buffer, 2);
    SWAP_U32_FROM_LITTLE(size);
    if (size != 1)
    {
        return false;
    }

    // Get the number of channels (only mono and stereo supported) -- 2 bytes
    _file_input.read(buffer, 2);
    memcpy(&_number_channels, buffer, 2);
    SWAP_U16_FROM_LITTLE(_number_channels);
    if (_number_channels != 1 && _number_channels != 2)
    {
        return false;
    }

    // Get sample rate (usually 11025, 22050, or 44100 Hz) -- 4 bytes
    _file_input.read(buffer, 4);
    memcpy(&_samples_per_second, buffer, 4);
    SWAP_U32_FROM_LITTLE(_samples_per_second);

    // Get byte rate -- 4 bytes
    uint32 byte_rate;
    _file_input.read(buffer, 4);
    memcpy(&byte_rate, buffer, 4);
    SWAP_U32_FROM_LITTLE(byte_rate);

    // Get block alignment (channels * bits_per_sample / 8) -- 2 bytes
    _file_input.read(buffer, 2);
    memcpy(&_sample_size, buffer, 2);
    SWAP_U16_FROM_LITTLE(_sample_size);

    // Get bits per sample -- 2 bytes
    _file_input.read(buffer, 2);
    memcpy(&_bits_per_sample, buffer, 2);
    SWAP_U16_FROM_LITTLE(_bits_per_sample);
    if (_sample_size != (_number_channels * _bits_per_sample)/8)
    {
        return false;
    }

    // Check subchunk 2 ID (to be "data") -- 4 bytes
    _file_input.read(buffer, 4);
    if (buffer[0] != 'd' || buffer[1] != 'a' || buffer[2] != 't' || buffer[3] != 'a')
    {
        return false;
    }

    // Check subchunk 2 size -- 4 bytes
    _file_input.read(buffer, 4);
    memcpy(&_data_size, buffer, 4);
    SWAP_U32_FROM_LITTLE(_data_size);

    _data_init = _file_input.tellg();
    _total_number_samples = _data_size / _sample_size;
    _play_time = static_cast<float>(_total_number_samples) / static_cast<float>(_samples_per_second);
    return true;
}

void WavFile::Seek( uint32 sample_position )
{
    uint32 sample = sample_position * _sample_size;

    if (sample >= _data_size)
    {
        return;
    }

    _file_input.clear();
    _file_input.seekg(static_cast<std::streamoff>(sample + _data_init), std::ios_base::beg);
}

uint32 WavFile::Read(uint8* buffer, uint32 size, bool& end)
{
    _file_input.read(reinterpret_cast<char*>(buffer), size * _sample_size);

    uint32 read = (uint32)(_file_input.gcount() / _sample_size);
    end = (read != size);

#ifdef __BIG_ENDIAN__
    if (_bits_per_sample == 16)
    {
        uint8 tmp;
        // iterate through
        for (uint32 i = 0; i < read * _sample_size; i += 2)
        {
            tmp = buffer[i];
            buffer[i] = buffer[i + 1];
            buffer[i + 1] = tmp;
        }
    }
#endif

    return read;
}
