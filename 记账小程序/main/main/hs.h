#ifndef HS_H
#define HS_H
int js2()
{
	sprintf(yr2,"%d",yr1);
    sprintf(mh2,"%d",mh1);
    sprintf(dy2,"%d",dy1);
}
int btbg()
{
	bg2 = GetDC(hWnd);
	bt1 = (HBITMAP)LoadImage(NULL, TEXT("button1.dll"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    bt2 = (HBITMAP)LoadImage(NULL, TEXT("button2.dll"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    bt3 = (HBITMAP)LoadImage(NULL, TEXT("button3.dll"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ed1 = CreateFont(45,23,0,0,FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Candara")); 
	
}
int timeget ()
{
	time_t now = time(NULL);
	struct tm *ptm = localtime(&now);  
    yr1 = ptm->tm_year + 1900;
    mh1 = ptm->tm_mon + 1; 
    dy1 = ptm->tm_mday;
}
int show1()
{
	ShowWindow(rm, SW_SHOW);
	ShowWindow(we, SW_HIDE);
	ShowWindow(my, SW_SHOW);	
	ShowWindow(yr, SW_SHOW);
	ShowWindow(dy, SW_SHOW);
	ShowWindow(mh, SW_SHOW);
	ShowWindow(lk, SW_SHOW);
	if(we1==1)
	{
		whl=600;
		whl1=420; 
		while(whl>=400)
		{
			SetWindowPos(hWnd,NULL,0,0,420,whl,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
			whl=whl-4;
		} 
		while(whl1<=660)
		{
			SetWindowPos(hWnd,NULL,0,0,whl1,400,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
			whl1=whl1+4;
		} 
	} 
	else
	{
		whl=140;
		whl1=420;
		while(whl<=400)
		{
			whl1=whl1+4;
        	SetWindowPos(hWnd, NULL,0,0,whl1,whl,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);		
			whl=whl+4;
		}
	} 
	wzy=2; 
	lk1=1;
}
int show0()
{
	bg1=(HBITMAP)LoadImage(GetModuleHandle(0),TEXT("background.dll"),IMAGE_BITMAP,0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    GetObject(bg1,sizeof(BITMAP),(LPVOID)&bmp); 
	bg=CreateCompatibleDC(bg2);
    ReleaseDC(hWnd,bg2); 
	SendMessage(yr, WM_SETFONT , (WPARAM)ed1, TRUE);
	SendMessage(my, WM_SETFONT , (WPARAM)ed1, TRUE);
	SendMessage(mh, WM_SETFONT , (WPARAM)ed1, TRUE); 
	SendMessage(dy, WM_SETFONT , (WPARAM)ed1, TRUE);
	SendMessage(lk, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bt1);
	SendMessage(we, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bt2);
	SendMessage(rm, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bt3);
	ShowWindow(rm,SW_HIDE);
	ShowWindow(yr,SW_HIDE);
	ShowWindow(dy,SW_HIDE);
	ShowWindow(mh,SW_HIDE);
	ShowWindow(my,SW_HIDE);
}
int wjchack()
{
	if( (_access( "first.dll",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001943f。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
	}
	else if( (_access( "D:\\记账.ini",0 )) == -1) 
    {
    	if( (_access( "D:\\intjz.ini",0 )) == -1) 
   		 {
    		MessageBox(NULL,"检测到首次启动，需进行文件的创建。","首次启动",MB_TASKMODAL|MB_ICONINFORMATION); 
			system("start first.dll"); //要写一个first.dll 
			PostQuitMessage(0);
			return 0;
		}
		else
		{
			MessageBox(NULL,"文件丢失，请联系开发者予以解决！错误码：0x001548j。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
			PostQuitMessage(0);
			return 0;
		}
	}
	else if( (_access( "D:\\intjz.ini",0 )) == -1) 
   	{
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001541i。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
		return 0;
	}
	else if( (_access( "button1.dll",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001138b1。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
		return 0;
	}
	else if( (_access( "button2.dll",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001148b2。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
		return 0;
	}
	else if( (_access( "button3.dll",0 )) == -1) 
    {
    	MessageBox(NULL,"住文件丢失，请联系开发者予以解决！错误码：0x001148b3。","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
		return 0;
	}
    else if( (_access( "see.dll", 0 )) == -1 )
	{
		MessageBox(NULL,"主文件丢失，请联系开发者予以解决！错误码：0x001928s","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
		return 0;
	}
	else if( (_access( "background.dll", 0 )) == -1 )
	{
		MessageBox(NULL,"主文件丢失，请联系开发者予以解决！错误码：0x001929g","文件校验失败",MB_TASKMODAL|MB_ICONSTOP); 
		PostQuitMessage(0);
		return 0;
	} 
}  
int show2()
{
	system("start see.dll");
}
int showtxt()
{
    wd=BeginPaint(hWnd,&pt);
	SelectObject(bg,bg1); 
    BitBlt(wd,0,0,10000,10000,bg,30,0,SRCCOPY);
	SetBkMode(wd, TRANSPARENT);
	SelectObject(wd, ed1);
	TextOut(wd,125,123,"年",wzy);
	TextOut(wd,217,123,"月",wzy);
	TextOut(wd,310,123,"号",wzy);
	TextOut(wd,440,123,"记",wzy);
	TextOut(wd,590,123,"元",wzy); 
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	HICON hIcon = LoadIcon(hInstance, "项目1.ico");
    WNDCLASS WndClass;
    WndClass.style=CS_HREDRAW|CS_VREDRAW;
    WndClass.lpfnWndProc=WndProc;
    WndClass.cbClsExtra=0;
    WndClass.cbWndExtra=0;
    WndClass.hInstance=hInstance;
    WndClass.hIcon=hIcon;
    WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
    WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName=NULL;
    WndClass.lpszClassName="Hello Win";
    WndClass.cbWndExtra=sizeof(LONG_PTR);
    if(!RegisterClass(&WndClass))
    {
        MessageBox(NULL,"窗口注册失败!","Hello Win",0);
        return 0;
    }
    timeget(); 
   	flmcin();
    wjchack();
	hWnd=CreateWindow("Hello Win", "记账-Alice-Cratelet制作", WS_OVERLAPPEDWINDOW,20,20,420,140, NULL, NULL, hInstance, NULL);
   	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	GetLocalTime(&st);
	while(GetMessage(&Msg,NULL,0,0)) 
    {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
    }
    return Msg.wParam; 
} 
int numbercout()
{
	yr4=GetWindowText(yr,yr3,400);
	mh4=GetWindowText(mh,mh3,200);
	dy4=GetWindowText(dy,dy3,200);
	my4=GetWindowText(my,my3,400);
	if(yr4==0 || mh4==0 || dy4==0 || my4==0)
	{
		MessageBox(NULL,"存在未输入的数据，请检查！","提示",MB_TASKMODAL|MB_ICONSTOP|MB_ICONWARNING);
	}
	else
	{
		yr5=atoi(yr3);
		mh5=atoi(mh3);
		dy5=atoi(dy3);
		my5=atoi(my3);
		if(yr5<=2000 || mh5<=0 || mh5>12 || dy5<=0 || dy5>31 || yr5>=2100 || my5<=0)
		{
			MessageBox(NULL,"输入数据有误，请检查！","提示",MB_TASKMODAL|MB_ICONSTOP);
			return 0;
		}
		sprintf(ls,"是否将以下数据记录到文件: %d年%d月%d日 消费%d元 ?",yr5,mh5,dy5,my5);
		int ret=MessageBox(NULL,ls,"提示",MB_TASKMODAL|MB_YESNO|MB_ICONINFORMATION); 
    	if (ret==IDNO)
    	{ 
    	    return 0; 
    	}
		else if(ret==IDYES)
		{
			fn1=fn1+1;
			yro[fn1]=yr5;
			mho[fn1]=mh5;
			dyo[fn1]=dy5;
			myo[fn1]=my5;
			FILE *wj2 = fopen("D:\\记账.ini", "w");
			if(wj2 == NULL)
			{
				MessageBox(NULL,"文件打开失败！","提示",MB_TASKMODAL|MB_ICONSTOP);
				return 0; 
			}
			whl=0;
			while(whl<=212)
			{
				nw=rand()%1000;
				fprintf(wj2,"%d ",nw);
				whl++;
			}
			nw=rand()%1000;
			fprintf(wj2," %d ",nw*361);
			whl=0;
			while(whl<=nw)
			{
				lshs=rand()%200;
				if(lshs<=5)
				{
					lshs=rand()%8492;
					fprintf(wj2,"%d \n",lshs);
				}
				else
				{
					lshs=rand()%8492;
					fprintf(wj2,"%d ",lshs);
				}
				whl++;
			}
			fprintf(wj2," %d ",fn1*352);
			whl=1;
			while(whl<=fn1)
			{
				lshs=rand()%50;
				if(lshs<=5)
				{
					fprintf(wj2,"%d \n %d %d %d ",yro[whl]*824,mho[whl]*7612,dyo[whl]*162,myo[whl]*129);
				}
				else if(lshs<=10)
				{
					fprintf(wj2,"%d %d \n %d %d ",yro[whl]*824,mho[whl]*7612,dyo[whl]*162,myo[whl]*129);
				}
				else if(lshs<=15)
				{
					fprintf(wj2,"%d %d %d \n %d ",yro[whl]*824,mho[whl]*7612,dyo[whl]*162,myo[whl]*129);
				}
				else if(lshs<=20)
				{
					fprintf(wj2,"%d %d %d %d \n",yro[whl]*824,mho[whl]*7612,dyo[whl]*162,myo[whl]*129);
				}
				else
				{
					fprintf(wj2,"%d %d %d %d ",yro[whl]*824,mho[whl]*7612,dyo[whl]*162,myo[whl]*129);
				}
				whl++;
			} 
			whl=0;
			while(whl<=nw)
			{
				lshs=rand()%200;
				if(lshs<=5)
				{
					lshs=rand()%8492;
					fprintf(wj2,"%d \n",lshs);
				}
				else
				{
					lshs=rand()%8492;
					fprintf(wj2,"%d ",lshs);	
				}
				whl++;
			}
			whl=1;
			while(whl<=50)
			{
				whl++;	
				whl1=rand()%4096;
				whl2=1;
				while(whl2<=whl1)
				{
					whl2++;
					lshs=rand()%30;
					if(lshs<=1)
					{
						lshs=rand()%25031;
						fprintf(wj2,"%d",lshs);
					}
					else if(lshs<=3)
					{
						fprintf(wj2," ");
					}
					else
					{
						char w;
						w=rand()%260;
						fprintf(wj2,"%c",w); 
					}
				}
			}
			fclose(wj2);
			MessageBox(NULL,"已成功读入！","提示",MB_TASKMODAL|MB_ICONINFORMATION);
		} 
	} 
}
int flmcin()
{
	FILE *wj  = fopen("D:\\记账.ini", "r");
    if (wj == NULL) 
	{
    	MessageBox(NULL,"文件打开失败！","提示",MB_TASKMODAL|MB_ICONSTOP);
		return 0; 
	}
    whl=0; 
    fn1=100;
    while (whl<=212) 
	{
    	fscanf(wj, "%d", &nw);
    	whl++;
   	}
   	fscanf(wj,"%d", &fn1);
   	fn1=fn1/361; 
   	whl=1;
   	while(whl<=fn1+1)
	{
		fscanf(wj, "%d", &nw);
    	whl++;
	}
	fscanf(wj,"%d", &fn1);
	fn1=fn1/352;
	whl=1;
	while(whl<=fn1)
	{
		fscanf(wj, "%d%d%d%d",&yro[whl],&mho[whl],&dyo[whl],&myo[whl]);
		mho[whl]=mho[whl]/7612;
		yro[whl]=yro[whl]/824;
		dyo[whl]=dyo[whl]/162;
		myo[whl]=myo[whl]/129;
		whl++;
	}
}
#endif
