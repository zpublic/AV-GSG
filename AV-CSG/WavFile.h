#pragma once
#include "AudioInput.h"
#include <fstream>

class WavFile : public AudioInput
{
public:
    WavFile(const std::string& file_name);

    ~WavFile();

    bool Initialize();

    void Seek(uint32 sample_position);

    uint32 Read(uint8* buffer, uint32 size, bool& end);

private:
    std::ifstream _file_input;

    std::streampos _data_init;
};
