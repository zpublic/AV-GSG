#include "stdafx.h"
#include "OggFile.h"

OggFile::OggFile( const std::string& file_name )
    : AudioInput()
    , _initialized(false)
    , _read_buffer_position(0)
    , _read_buffer_size(0)
{
    _filename = file_name;
}

OggFile::~OggFile()
{
    if (_initialized == true)
    {
        ov_clear(&_vorbis_file);
        _initialized = false;
    }
}

bool OggFile::Initialize()
{
    _initialized = false;
    // Windows requires a special loading method in order load ogg files
    // properly when dynamically linking vorbis libs. The workaround is
    // to use the ov_open_callbacks function
#ifdef WIN32
    // Callbacks struct defining the open, closing, seeking and location behaviors.
    ov_callbacks callbacks =  {
        (size_t (*)(void*, size_t, size_t, void*)) fread,
        (int (*)(void*, ogg_int64_t, int)) _FileSeekWrapper,
        (int (*)(void*)) fclose,
        (long (*)(void*)) ftell
    };

    FILE* file = fopen(_filename.c_str(), "rb");
    if (file == NULL)
    {
        return false;
    }

    if (ov_open_callbacks(file, &_vorbis_file, NULL, 0, callbacks) < 0)
    {
        fclose(file);
        return false;
    }

#else
    // File loading code for non Win32 platforms.  Much simpler.
    FILE* file = fopen(_filename.c_str(), "rb");
    if (file == NULL) {
        IF_PRINT_WARNING(AUDIO_DEBUG) << "failed to open file for reading: " << _filename << endl;
        return false;
    }

    if (ov_open(file, &_vorbis_file, NULL, 0) < 0) {
        fclose(file);
        IF_PRINT_WARNING(AUDIO_DEBUG) << "input file does not appear to be an Ogg bitstream: " << _filename << endl;
        return false;
    }
#endif

    _number_channels = _vorbis_file.vi->channels;
    _samples_per_second = _vorbis_file.vi->rate;
    _bits_per_sample = 16;
    _total_number_samples = static_cast<uint32>(ov_pcm_total(&_vorbis_file, -1));
    _play_time = static_cast<float>(ov_time_total(&_vorbis_file, -1));
    _sample_size = _number_channels * _bits_per_sample / 8;
    _data_size = _total_number_samples * _sample_size;

    _initialized = true;
    return true;
}

void OggFile::Seek(uint32 cursor)
{
    if (ov_seekable(&_vorbis_file) == 0)
    {
        return;
    }

    ov_pcm_seek(&_vorbis_file, cursor);

    // Reset the temporary buffer by setting the position to 0
    _read_buffer_position = 0;
    _read_buffer_size = 0;
}

uint32 OggFile::Read(uint8* buffer, uint32 size, bool& end)
{
    int current_section;
    uint32 read =0;
    end = false;

    // First get data from the temporary buffer if it holds any
    if (_read_buffer_size > 0)
    {
        if (_read_buffer_size > size*_sample_size)
        {
            read = size*_sample_size;
        }
        else
        {
            read = _read_buffer_size;
        }
        memcpy(buffer, _read_buffer + _read_buffer_position, read);
        _read_buffer_size -= read;
        _read_buffer_position += read;
    }

    while ((read < (size * _sample_size)) && !end)
    {
        _read_buffer_position = 0;
        int32 num_bytes_read = 0;

#ifdef __BIG_ENDIAN__
        num_bytes_read = ov_read(&_vorbis_file, (char*)_read_buffer, 4096, 1, _bits_per_sample/8, 1, &current_section);
#else
        num_bytes_read = ov_read(&_vorbis_file, (char*)_read_buffer, 4096, 0, _bits_per_sample/8, 1, &current_section);
#endif

        if (num_bytes_read == 0)
        { // Indicates EOF was reached
            end = true;
            break;
        }
        else if (num_bytes_read < 0)
        { // Indicates a read error occurred
            break;
        }
        else
        {
            //! \todo Take into account differences of sample rate when reading OGG
            _read_buffer_size = num_bytes_read;
            num_bytes_read = ((size * _sample_size) - read > static_cast<uint32>(num_bytes_read))
                ? num_bytes_read
                : (size * _sample_size) - read;
            memcpy(buffer + read, _read_buffer + _read_buffer_position, num_bytes_read);
            read += num_bytes_read;
            _read_buffer_size -= num_bytes_read;
            _read_buffer_position += num_bytes_read;
        }
    }

    return read / _sample_size;
}

int OggFile::_FileSeekWrapper(FILE* file, ogg_int64_t off, int whence)
{
    if (file == NULL)
    {
        return -1;
    }
    else
    {
        return fseek(file, static_cast<long>(off), whence);
    }
}
