#include <windows.h>
int ilt=1;
PAINTSTRUCT ps;
HBITMAP a;
BITMAP bm;
char *filename="back.dll";
HDC memdc;
#pragma comment(linker, "/subsystem:windows /entry:WinMainCRTStartup")
#if(_MSC_VER == 1200) 
#define WS_EX_LAYERED 0x00080000
#define LWA_COLORKEY 1
#define LWA_ALPHA 2

int SetLayeredWindowAttributes(HWND hwnd, COLORREF crKey,BYTE bAlpha, DWORD dwFlags)
{
    typedef int (WINAPI *Func)( HWND hwnd, COLORREF crKey,BYTE bAlpha, DWORD dwFlags);
    Func func;
    if(func = (Func)GetProcAddress(GetModuleHandle(TEXT("user32.dll")),TEXT("SetLayeredWindowAttributes")))
    return func(hwnd, crKey, bAlpha, dwFlags);
    return 0;
}
#endif

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int alpha = 0;
	HDC hDC;
    PAINTSTRUCT Ps,ps;
    switch(message)
    {
    	case WM_TIMER:
        if(ilt==1)
		{
			alpha += 20;
			if (alpha>=255) 
			{
				ilt=2;
				alpha=255;
			}
		} 
        else
        {
        	if(ilt>=50)
        	{
        		alpha-=20;
        		if(alpha<=0)
        		{
        			alpha=0;
        			
        			PostQuitMessage(0);
				}
			}
			else
			{
				alpha=255;
				ilt++;
			}
		}
        SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA);
        return 0;
    	case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        case WM_CREATE:  
      		a=(HBITMAP)LoadImage(GetModuleHandle(0),filename,IMAGE_BITMAP,0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
            GetObject(a,sizeof(BITMAP),(LPVOID)&bm);
            HDC hdc=GetDC(hwnd); 
            memdc=CreateCompatibleDC(hdc); 
            ReleaseDC(hwnd,hdc);
    	case WM_PAINT:
            hDC=BeginPaint(hwnd,&Ps);
       	    SelectObject(memdc,a);
            BitBlt(hDC,0,0,bm.bmWidth,bm.bmHeight,memdc,0,0,SRCCOPY);
            EndPaint(hwnd,&Ps);
        	break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance,
                                   HINSTANCE hPrevInstance,
                                   PSTR pCmdLine,
                                   int nCmdShow)
{

    static TCHAR szAppName[] = TEXT("HelloWin");
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.lpszClassName = szAppName;
    wndclass.hInstance     = hInstance;
    wndclass.lpfnWndProc   = WndProc;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName  = NULL;
    RegisterClass(&wndclass);
    hwnd = CreateWindowEx(WS_EX_LAYERED,
                          szAppName,
                          TEXT("Title"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "back.dll", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap == NULL) {
        MessageBox(NULL, "主文件缺失，错误码 0x00198bg2！", "错误", MB_ICONERROR | MB_OK);
        return 1;
    }
    if( (_access( "main.exe",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001987m。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
	}
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    int imageWidth = bmp.bmWidth;
    int imageHeight = bmp.bmHeight;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth - imageWidth) / 2;
    int y = (screenHeight - imageHeight) / 2;
    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, imageWidth, imageHeight, SWP_SHOWWINDOW);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
	SetTimer(hwnd, 1, 30, NULL);
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    ShellExecuteA(NULL, "open", "main.exe", NULL, NULL, SW_SHOW);
    return msg.wParam;
}

