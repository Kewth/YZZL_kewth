#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <tchar.h>
#include "h/more.h"
#include "more.cpp"
void gotoxy(int x,int y)
{
	HANDLE app;
	COORD  pos;
	pos.X=y-1;
	pos.Y=x-1;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}
void GetCurrentCursorPosition(int &x,int &y)
{
    HANDLE   hStdout;
    CONSOLE_SCREEN_BUFFER_INFO   pBuffer;
    hStdout   =   GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout,   &pBuffer);
    x=pBuffer.dwCursorPosition.X;
    y=pBuffer.dwCursorPosition.Y;
}
void gotonow(int fy,int fx)
{
	int x,y;
	GetCurrentCursorPosition(x,y);
	HANDLE app;
	COORD  pos;
	pos.X=x+fx;
	pos.Y=y+fy;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}
void say(std::string name,std::string thing,int speed,int in)
{
	if(name!="")
	{
		system("cls");
		printf("%s:\n",name.c_str());
	}
	for(int i=0;i<thing.size();i++)
	{
		if(kbhit() && getch()=='~') speed=0;
		if(thing[i]=='|')
		{
			i++;
			if(thing[i]=='d') printf("%d",in);
		}
		else
		{
			printf("%c",thing[i]);
		}
		Sleep(speed);
	}
	return ;
}
void cgcolor(std::string cr) // Linux
{
#define setc(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|x)
#define fred FOREGROUND_RED
#define fblu FOREGROUND_BLUE
#define fgre FOREGROUND_GREEN
#define bred BACKGROUND_RED
#define bblu BACKGROUND_BLUE
#define bgre BACKGROUND_GREEN
	static int b[] = {0,bred,bgre|bblu,bred|bgre,bblu,bred|bblu,bgre,bred|bblu|bgre};
	static int f[] = {0,fred,fgre|fblu,fred|fgre,fblu,fred|fblu,fgre,fred|fblu|fgre};
	if(cr.empty()) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),b[0]|f[7]); return; }
	else if(cr.size() != 2) { puts("colorERROR"); return; }
	setc(b[cr[0]-'0'] | f[cr[1]-'0']);
#undef setc
#undef fred
#undef fblu
#undef fgre
#undef bred
#undef bblu
#undef bgre
}
#undef getch
int getch__()
{
	return getch();
}
#undef clock
int clock__()
{
	return clock();
}
#undef kbhit
int kbhit__()
{
	return kbhit();
}
#undef system
int system__(const char * s)
{
	return system(s);
}
#undef Sleep
int Sleep__(int x)
{
	Sleep(x);
	return 0;
}
int messagebox(void *null,const char * s1,const char *s2,int x)
{
	if(x == 1) return MessageBox(NULL,_T(s1),_T(s2),__MSABI_LONG(0x00000000)); // MB_OK
	else if(x == 2) return MessageBox(NULL,_T(s1),_T(s2),__MSABI_LONG(0x0000000000000001)); // MB_YESNO
}
bool debug_open;
bool debug_to_print;
void debug_print(std::string f)
{
	FILE *for_debug = fopen("C:/yzzlrc/debug.txt" , "a");
	fputs((f + '\n').c_str(),for_debug);
	fclose(for_debug);
}
int ver_new;
int version_check()
{
	ver_new = 0;
}
//中文
