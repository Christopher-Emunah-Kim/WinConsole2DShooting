// ConsoleShooting2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

#define KHS_USE_PACKMAN 1
#include "Objects/Player.h"

#if KHS_USE_PACKMAN
#ifndef KHS_PACKMAN
#define KHS_PACKMAN
#endif
#endif

//Back Buffer
Gdiplus::Bitmap* g_backBuffer = nullptr; //백버퍼용 GDI+ 비트맵 객체 포인터
Gdiplus::Graphics* g_backGraphics = nullptr; //백버퍼용 GDI+ 그래픽 객체 포인터

#ifdef KHS_PACKMAN
////250929 KHS PackMan 객체 포인터 생성
////250930 Player 클래스로 변경
AirPlayer* k_AirPlayer = nullptr;
constexpr int PLAYER_IMAGE_SIZE = 64;
#endif
constexpr int DEFAULT_PLAYER_IMAGE_SIZE = 64;

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

     //메모리 릭 체크
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//CRT디버그 플래그 설정. 디버그 힙 기능활성, 메모리 릭 체크 활성화, 프로그램 종료 시 메모리 누수보고서 출력

	//GDI+ 초기화
	ULONG_PTR dwGdiplusToken; //GDI+ 토큰
	Gdiplus::GdiplusStartupInput gdiplusStartupInput; //GDI+ 시작 구조체
	Gdiplus::GdiplusStartup(&dwGdiplusToken, &gdiplusStartupInput, nullptr); //GDI+ 시작snsk qn



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


	//GDI+ 종료
	Gdiplus::GdiplusShutdown(dwGdiplusToken);

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

   //클라이언트 영역 크기 조정
   RECT myRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }; //클라이언트 영역 크기 설정
   AdjustWindowRectEx(&myRect, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, FALSE, 0);
   //윈도우 스타일 (최대화 버튼 제거 연산, 테두리 크기 변경 제거 비트 연산) 
   //AdjustWindowRect함수 : 윈도우 스타일에 맞게 클라이언트 영역 크기를 조정
   //myRect : 조정할 RECT 구조체 포인터

   //실제 윈도우 생성
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,  
       APP_POSITION_X, APP_POSITION_Y, //시작좌표(스크린 좌표계)
	   myRect.right - myRect.left, myRect.bottom - myRect.top, //윈도우 스타일에 맞춰 조정된 너비와 높이
       nullptr, nullptr, hInstance, nullptr);

  /* HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);  (DEFAULT) */
   //CreateWindowW함수
   //윈도우 클래스 이름, 윈도우 타이틀, 윈도우 스타일, x좌표, y좌표, 너비, 높이, 부모 윈도우 핸들, 메뉴 핸들, 인스턴스 핸들, 추가 매개변수

   if (!hWnd)
   {
      return FALSE;
   }

#ifdef KHS_PACKMAN
   if (!k_AirPlayer)
   {
	   std::wstring imagePath = L"./Images\\player.png";
       k_AirPlayer = new AirPlayer(DEFAULT_PLAYER_IMAGE_SIZE, DEFAULT_PLAYER_IMAGE_SIZE, 20, imagePath); //AirPlayer 객체 생성
   }
#endif

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
//UINT gActiveKey = 0; //현재 눌린 키 저장용 전역변수

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: //윈도우가 생성될 때
    {
        //백버퍼용 GDI+ 비트맵 객체 생성
        if (g_backBuffer == nullptr)
        {
            g_backBuffer = new Gdiplus::Bitmap(WINDOW_WIDTH, WINDOW_HEIGHT, PixelFormat32bppARGB );
        }
        //백버퍼용 GDI+ 그래픽 객체 생성
        if (g_backGraphics == nullptr && g_backBuffer != nullptr)
        {
            g_backGraphics = Gdiplus::Graphics::FromImage(g_backBuffer);
		}
        
		if (!g_backGraphics) //백버퍼용 그래픽 객체 생성 실패시
        {
            MessageBox(hWnd, L"Back Buffer Graphics Create Failed!", L"Error", MB_OK | MB_ICONERROR);
			PostQuitMessage(0); //프로그램 종료
        }
    }
    break;
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

            if (!g_backGraphics)
            {
                EndPaint(hWnd, &ps);
				break;
            }

            g_backGraphics->Clear(Gdiplus::Color(255, 255, 255, 255)); //백버퍼를 흰색으로 지우기

			Gdiplus::SolidBrush  redBrush(Gdiplus::Color(255, 255, 0, 0)); //붉은색 브러시 객체 생성 (불투명도, R, G, B)
			Gdiplus::SolidBrush  blueBrush(Gdiplus::Color(255, 0, 0, 255)); //파란색 브러시 객체 생성 (불투명도, R, G, B)
			Gdiplus::SolidBrush  yellowBrush(Gdiplus::Color(255, 255, 255, 0)); //노란색 브러시 객체 생성 (불투명도, R, G, B)
			Gdiplus::Pen greenPen(Gdiplus::Color(255, 0, 255, 0), 5); //초록색 펜 객체 생성 (색상, 두께)
			Gdiplus::Pen blackPen(Gdiplus::Color(255, 0, 0, 0), 3); //검은색 펜 객체 생성 (색상, 두께)
			

            for (int y = 0; y < 2; ++y)
            {
                for (int x = 0; x < 10; ++x)
                {
					g_backGraphics->FillRectangle(&blueBrush, x * 50 + 50, y * 50 + 50, 40, 40);
                }
            }

#ifdef KHS_PACKMAN
            if (k_AirPlayer)
                k_AirPlayer->Draw(*g_backGraphics); //AirPlayer 그리기
#endif


            Gdiplus::Graphics graphicInstance(hdc); //GDI+ 그래픽 객체 생성

            graphicInstance.DrawImage(g_backBuffer, 0, 0); //백버퍼의 내용을 실제 윈도우에 그리기

            EndPaint(hWnd, &ps);

            //graphicInstance.FillEllipse(&redBrush, 100, 100, 200, 200); //타원 채우기 (브러시, x좌표, y좌표, 너비, 높이)
            //graphicInstance.FillRectangle(&blueBrush, 400, 100, 200, 200); //사각형 채우기 (브러시, x좌표, y좌표, 너비, 높이)
			//graphicInstance.DrawLine(&greenPen, 700, 100, 900, 300);
			//Gdiplus::Point points[4] = { Gdiplus::Point(1000,100), Gdiplus::Point(1200,100), Gdiplus::Point(1100,300), Gdiplus::Point(900,300) };
			//graphicInstance.FillPolygon(&blueBrush, points, 4); //다각형 그리기 (펜, 점 배열, 점 개수)

   //         Gdiplus::Point housePoints[5] = {
   //             Gdiplus::Point(100, 500), //왼쪽 아래
   //             Gdiplus::Point(300, 500), //오른쪽 아래
   //             Gdiplus::Point(300, 300), //오른쪽 위
   //             Gdiplus::Point(200, 200), //꼭대기
   //             Gdiplus::Point(100, 300)  //왼쪽 위
   //         }; //집모양그리기
            
			//graphicInstance.DrawPolygon(&blackPen, housePoints, 5); //다각형 채우기 (브러시, 점 배열, 점 개수)

            //Packman 모양 노란색 그리기 위쪽에
			//graphicInstance.FillPie(&yellowBrush, 400, 200, 200, 200, 30, 300); //타원 채우기 (브러시, x좌표, y좌표, 너비, 높이, 시작각도, 호의 각도)

        }
        break;
    case WM_ERASEBKGND: //윈도우 배경을 지울 때 (WM_PAINT 메시지 전에 발생, 배경을 지우지 않도록 처리)
    {
        return 1; //0이 아닌 값을 반환하면 배경 지우기를 하지 않음
	}
    break;
    case WM_KEYDOWN:
    {
		//bool bIsInitialKeyPress = ((lParam & (1 << 30)) == 0); //키가 처음 눌렸는지 여부 (자동반복 방지)

        //if (bIsInitialKeyPress)
       // {
           //gActiveKey = (UINT)wParam; //현재 눌린 키 저장

            switch (wParam) //눌린 키의 가상키코드
            {
            case 'A':
            case VK_LEFT: //왼쪽 방향키
                OutputDebugStringW(L"Left Key Pressed\n");
#ifdef KHS_PACKMAN
				if (k_AirPlayer)
                    k_AirPlayer->MoveLeft(); 
#endif
                InvalidateRect(hWnd, nullptr, FALSE); //윈도우 전체를 무효화(다시 그리기 요청)
                break;
            case 'D':
            case VK_RIGHT: //오른쪽 방향키
                OutputDebugStringW(L"Right Key Pressed\n");
#ifdef KHS_PACKMAN
                if (k_AirPlayer)
                    k_AirPlayer->MoveRight(); 
#endif
                InvalidateRect(hWnd, nullptr, FALSE); //윈도우 전체를 무효화(다시 그리기 요청)
                break;
            case 'W':
            case VK_UP: //위쪽 방향키
                OutputDebugStringW(L"Up Key Pressed\n");
#ifdef KHS_PACKMAN
                if (k_AirPlayer)
                    k_AirPlayer->MoveUp(); 
#endif
                InvalidateRect(hWnd, nullptr, FALSE); //윈도우 전체를 무효화(다시 그리기 요청)
                break;
            case 'S':
            case VK_DOWN: //아래쪽 방향키
                OutputDebugStringW(L"Down Key Pressed\n");
#ifdef KHS_PACKMAN
                if (k_AirPlayer)
                    k_AirPlayer->MoveDown();
#endif
                InvalidateRect(hWnd, nullptr, FALSE); //윈도우 전체를 무효화(다시 그리기 요청)
                break;
            case VK_SPACE: //스페이스바
                OutputDebugStringW(L"Space Key Pressed\n");
                InvalidateRect(hWnd, nullptr, FALSE); //윈도우 전체를 무효화(다시 그리기 요청)
                break;
            case VK_ESCAPE: //ESC키
                DestroyWindow(hWnd); //윈도우 종료
                break;

            default:
                break;
            }
        //}
    }
        break;
    case WM_KEYUP:
    {
  //      if ((UINT)wParam == gActiveKey) //떼어진 키가 현재 눌린 키인지 확인
  //      {
  //          gActiveKey = 0; //현재 눌린 키 초기화
		//}
    }
        break;
    case WM_DESTROY: //윈도우가 파괴될 때 (종료)
    {
#ifdef KHS_PACKMAN
        if (k_AirPlayer)
        {
            delete k_AirPlayer; //AirPlayer 객체 삭제
            k_AirPlayer = nullptr;
        }
#endif
        		
        //백버퍼용 GDI+ 그래픽 객체 삭제
        if (g_backGraphics)
        {
            delete g_backGraphics;
            g_backGraphics = nullptr;
        }
        //백버퍼용 GDI+ 비트맵 객체 삭제
        if (g_backBuffer)
        {
            delete g_backBuffer;
            g_backBuffer = nullptr;
        }
        PostQuitMessage(0);
    }
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
