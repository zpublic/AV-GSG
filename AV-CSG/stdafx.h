// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdint.h>

#include <atlbase.h>
#include <atlconv.h>

#include <time.h>
#include <math.h>
#include <map>
#include <string>

#include "tinyxml.h"

#include "unit\PictureDef.h"
#include "unit\GameDef.h"
#include "unit\Unit.h"

///> ���沿�֣�ȫ�ַ���
#include "engine\input\InputEngine.h"
#include "engine\scene\SceneEngine.h"
#include "engine\audio\AudioEngine.h"

extern InputEngine* InputEngine_;
extern SceneEngine* SceneEngine_;
extern AudioEngine* AudioEngine_;
extern bool AUDIO_ENABLE;

extern HDC  g_hMemDC;
extern HDC  g_hWndDC;

///> ��Ƶ��صĵ�������
#include "al.h"
#include "alc.h"
#include "vorbis/vorbisfile.h"
