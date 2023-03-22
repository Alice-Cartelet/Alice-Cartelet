#include<windows.h>
#include<tchar.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include"dy.h"
#include"hs.h"
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	btbg();
	switch(message)
	{
		case WM_SYSCOMMAND:
			if (wParam == SC_CLOSE)
			{
				PostQuitMessage(0);
			}  
		case WM_CREATE:
			js2();
			lk=CreateWindow("button","查看账本",WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_FLAT,30 ,20 ,160,54 ,hWnd,NULL,NULL,NULL);
	   		we=CreateWindow("button","添加账本",WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_FLAT,210,20 ,160,54 ,hWnd,NULL,NULL,NULL);
	   		rm=CreateWindow("button","添    加",WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_FLAT,250,220,160,54 ,hWnd,NULL,NULL,NULL); 
			yr=CreateWindow("edit"  ,yr2       ,WS_CHILD|WS_VISIBLE|WS_BORDER, 20,120,100, 50,hWnd,NULL,NULL,NULL);
        	mh=CreateWindow("edit"  ,mh2       ,WS_CHILD|WS_VISIBLE|WS_BORDER,170,120, 45, 50,hWnd,NULL,NULL,NULL);
			dy=CreateWindow("edit"  ,dy2       ,WS_CHILD|WS_VISIBLE|WS_BORDER,260,120, 50, 50,hWnd,NULL,NULL,NULL);
			my=CreateWindow("edit"  ,"1"       ,WS_CHILD|WS_VISIBLE|WS_BORDER,490,120,100, 50,hWnd,NULL,NULL,NULL); 
			show0();
			break;
	    case WM_COMMAND:
	    	if(((HWND)lParam==lk)&&(HIWORD(wParam)==BN_CLICKED))
	    	{
	    		show2(); 
			}
			if(((HWND)lParam==we)&&(HIWORD(wParam)==BN_CLICKED))
	    	{
	    		show1();	 
			}
			if(((HWND)lParam==rm)&&(HIWORD(wParam)==BN_CLICKED))
			{
				numbercout();
			} 
			break;
        case WM_PAINT:
			showtxt(); 
           	break; 
	} 
	return DefWindowProc(hWnd,message,wParam,lParam);
} 
