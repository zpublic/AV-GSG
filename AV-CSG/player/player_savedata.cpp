#include "stdafx.h"
#include "player_savedata.h"

#define Archive_File    "avgsg.af"

Player_SaveData::Player_SaveData()
{
    Unit::GetPath(m_strDataFile);
    m_strDataFile += Archive_File;
}

Player_SaveData::~Player_SaveData()
{

}

bool Player_SaveData::Save()
{
    SAVE_DATA data;
    data.content.nMaxScore = Player_->gamestatus_.GetMaxScore();
    Player_->gamestatus_.GetScoreList(data.content.scroeList);
    data.header.Calc(data.content);
    return SaveFile(data);
}

bool Player_SaveData::Load()
{
    SAVE_DATA data;
    if (LoadFile(data))
    {
        Player_->gamestatus_.SetMaxScore(data.content.nMaxScore);
        Player_->gamestatus_.SetScoreList(data.content.scroeList);
        return true;
    }
    return false;
}

bool Player_SaveData::LoadFile(SAVE_DATA& data)
{
    bool bRet = false;
    FILE* pFile = fopen(m_strDataFile.c_str(), "r");
    if (pFile)
    {
        if (fread(&(data.header), sizeof(data.header), 1, pFile) != 1)
        {
            goto _exit0;
        }
        if (data.header.dwSize == 0 || data.header.dwVersion != CurSaveDataVer)
        {
            goto _exit0;
        }
        if (fread(&(data.content), data.header.dwSize, 1, pFile) != 1)
        {
            goto _exit0;
        }
        if (data.header.dwCheckSum == zl::ExCRC32((BYTE*)&(data.content), data.header.dwSize))
        {
            bRet = true;
        }
    }
_exit0:
    if (pFile)
    {
        fclose(pFile);
    }
    return bRet;
}

bool Player_SaveData::SaveFile(const SAVE_DATA& data)
{
    bool bRet = false;
    FILE* pFile = fopen(m_strDataFile.c_str(), "w");
    if (pFile)
    {
        size_t sWrite = fwrite(&data, sizeof(data.header) + data.header.dwSize, 1, pFile);
        if (sWrite == 1)
        {
            bRet = true;
        }
        fclose(pFile);
    }
    return bRet;
}
