#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>
#include "dy.h" 
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR pCmdLine,int nCmdShow)
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
    hwnd=CreateWindowEx(WS_EX_LAYERED,szAppName,TEXT("Title"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
    SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "back.dll", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap == NULL) {
        MessageBox(NULL, "主文件缺失，错误码 0x00198bg2！", "错误", MB_ICONERROR | MB_OK);
        return 1;
    }
    const char* processName = "ExamClient.exe";
    int isRunning = isProcessRunning(processName);
    if (isRunning) {
    } else {
        MessageBox(NULL, "请在开始考试后打开本文件。", "提示", MB_ICONERROR | MB_OK);
    	return 0; 
	}
    if( (_access( "main.dll",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001987m。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		return 0;
		PostQuitMessage(0);
	}
	if( (_access( "~dp0",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001987~。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		return 0;
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
    system("start Examchack.exe");
    system("start main.dll");
    return msg.wParam;
}

