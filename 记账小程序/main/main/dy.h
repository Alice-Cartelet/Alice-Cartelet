#ifndef DY_H
#define DY_H
#include<windows.h>
#include<tchar.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
HBITMAP bg1;
BITMAP bmp; 
HDC bg,wd;
PAINTSTRUCT pt;
int lk1=0;
int yr1;
int lshs;
char yr2[];
char ls[];
FILE *wj;
char mh2[];
char dy2[];
int mh1;
int wzy=0;
int dy1=1;
int we1=0;
int whl=0;
char p=10;
SYSTEMTIME st;
int whl1=0;
int whl2=0;
int yr4=0;
int mh4=0;
int dy4=0;
int my4=0;
int yr5=0;
int mh5=0;
int dy5=0;
int my5=0;
int nw=0;
int fn1=0;
static HWND lk,we,yr,mh,dy,my,rm;
HDC bg2;
HWND hWnd;
MSG Msg;
char yr3[10000],dy3[10000],mh3[10000],my3[10000];
int  yro[10000],dyo[10000],mho[10000],myo[10000];
HBITMAP bt1;
HBITMAP bt2;
HBITMAP bt3;
HBITMAP mve;
HFONT   ed1;
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
#endif
