// ConsoleShooting2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ConsoleShooting2D.h"

//메모리 릭 체크
#define _CRTDBG_MAP_ALLOC;
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__);
#include <crtdbg.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, //IN 
                     _In_opt_ HINSTANCE hPrevInstance, //IN OPTIONAL
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //레거시 코드에서 넘어온 현재는 사용하지않는 파라미터들.
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //메모리 릭 체크



    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CONSOLESHOOTING2D, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance); //Window Class 등록 (중요~!!)

    // 애플리케이션 초기화를 수행합니다: (중요~!!)
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONSOLESHOOTING2D));
	//HACCEL : 단축키(Accelerator) 테이블 핸들
    //LoadAccelerators함수 : 단축키(Accelerator) 테이블을 로드
	//hInstance : 애플리케이션 인스턴스 핸들
	//MAKEINTRESOURCE : 정수를 리소스 식별자로 변환하는 매크로
	//IDC_CONSOLESHOOTING2D : 단축키 리소스 ID


    MSG msg;
	// MSG : 윈도우 메시지 구조체

	// 기본 메시지 루프입니다: (메시지 큐에 들어온 메시지를 처리하는 반복문) (중요~!!)
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) //단축키 메시지인지 확인
        {
			TranslateMessage(&msg); //키보드 메시지를 변환 (가상키코드를 문자메시지로 변환)
			DispatchMessage(&msg); //메시지를 해당 윈도우 프로시저로 전달
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; //WINDOW CLASS Extended 유니코드 버전(WIndow창 모양 등록용 구조체)

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; //윈도우 스타일
     //CS_HREDRAW : 수평 크기 변경시 전체를 다시 그린다.
	 //CS_VREDRAW : 수직 크기 변경시 전체를 다시 그린다.
	wcex.lpfnWndProc = WndProc; //윈도우 프로시저 함수 포인터
    wcex.cbClsExtra     = 0; //클래스별 추가 메모리 바이트 수
	//윈도우 클래스당 추가로 할당할 메모리의 바이트 수를 지정합니다.
	wcex.cbWndExtra = 0; //윈도우별 추가 메모리 바이트 수
    wcex.hInstance      = hInstance; //윈도우가 속한 인스턴스 핸들
	//인스턴스 핸들은 프로그램이 메모리에 적재될 때 운영체제가 부여하는 고유한 값입니다.
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CONSOLESHOOTING2D));  
	//윈도우 아이콘 핸들 (LoadIcon함수로 아이콘 리소스를 로드)
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	//윈도우 커서 핸들 (LoadCursor함수로 커서 리소스를 로드)
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	//윈도우 배경 브러시 핸들 (배경색 지정)
    wcex.lpszMenuName = nullptr; //메뉴는 날림.
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CONSOLESHOOTING2D);
	//윈도우 메뉴 이름 (메뉴 리소스 이름)
    wcex.lpszClassName  = szWindowClass; //윈도우 클래스 이름
	//CreateWindow, CreateWindowEx 함수에서 이 이름으로 윈도우 생성
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); 
    //작은 아이콘 핸들 (LoadIcon함수로 아이콘 리소스를 로드)
	 //작은 아이콘은 작업 표시줄과 창의 왼쪽 위 모서리에 표시됩니다.

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //윈도우콘솔 타이틀 수정
   SetConsoleTitle(L"Win Console Shooting 2D");

   //실제 윈도우 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,  //윈도우 스타일 (최대화 버튼 제거 연산, 테두리 크기 변경 제거 연산) 
       200, 100, //시작좌표(스크린 좌표계)
	   1280, 720, //윈도우 크기(너비, 높이)
       nullptr, nullptr, hInstance, nullptr);

  /* HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);  (DEFAULT) */
   //CreateWindowW함수
   //윈도우 클래스 이름, 윈도우 타이틀, 윈도우 스타일, x좌표, y좌표, 너비, 높이, 부모 윈도우 핸들, 메뉴 핸들, 인스턴스 핸들, 추가 매개변수

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow); //윈도우를 화면에 표시
   UpdateWindow(hWnd); //윈도우의 클라이언트 영역을 업데이트

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_COMMAND: // 메뉴, 버튼, 기타 컨트롤에서 전송된 명령 (잘 안씀)
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_PAINT: //윈도우의 클라이언트 영역을 그려야 할 때 (화면 갱신, 창 크기 변경 등)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_DESTROY: //윈도우가 파괴될 때 (종료)
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
