// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "Common.h"
#include "Resource.h"
#include "framework.h"

//메모리 릭 체크
#include <crtdbg.h> //C 런타임 디버그 헤더
#define _CRTDBG_MAP_ALLOC //CRT의 메모리할당함수(malloc, calloc, realloc, free)를 디버그 버전으로 매핑
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) //new연산자를 디버그용으로 재정의. 누수된 메몰블록의 파일명, 라인번호까지 출력

#endif //PCH_H
