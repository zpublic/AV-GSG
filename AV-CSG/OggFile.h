#pragma once
#include "AudioInput.h"

class OggFile : public AudioInput
{
public:
	OggFile(const std::string& file_name);

	~OggFile();

	bool Initialize();

	void Seek(uint32 sample_position);

	uint32 Read(uint8* data_buffer, uint32 number_samples, bool& end);

private:
	bool _initialized;

	OggVorbis_File _vorbis_file;

	unsigned char _read_buffer[4096];

	uint16 _read_buffer_position;

	uint16 _read_buffer_size;

	static int _FileSeekWrapper(FILE* file, ogg_int64_t off, int whence);
};
