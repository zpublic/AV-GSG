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

#include "PictureDef.h"
#include "GameDef.h"
#include "Unit.h"

///> 引擎部分，全局访问
#include "InputEngine.h"
#include "SceneEngine.h"
#include "AudioEngine.h"

extern InputEngine* InputEngine_;
extern SceneEngine* SceneEngine_;
extern AudioEngine* AudioEngine_;
extern bool AUDIO_ENABLE;

extern HDC  g_hMemDC;
extern HDC  g_hWndDC;

///> 音频相关的第三方库
#include "al.h"
#include "alc.h"
#include "vorbis/vorbisfile.h"
