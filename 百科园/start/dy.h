#ifndef DY_H
#define DY_H
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
int isProcessRunning(const char* processName) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (strcmp(entry.szExeFile, processName) == 0) {
                CloseHandle(snapshot);
                return 1;
            }
        }
    }
    CloseHandle(snapshot);
    return 0;
}
#endif
