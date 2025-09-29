#pragma once

#include "targetver.h"
//#define WIN32_LEAN_AND_MEAN       // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다. (GDI+를 사용하기 위해 제거)
// Windows 헤더 파일
#include <windows.h>
#include <gdiplus.h> // GDI+ 헤더 파일
#pragma comment (lib, "Gdiplus.lib") // Gdiplus.lib를 링커에 추가(정적 라이브러리)
//using namespace Gdiplus;
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
