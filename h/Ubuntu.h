#ifndef Ubuntu_h
#define Ubuntu_h NULL
#include <sys/time.h>
#include <termios.h>  
#include <unistd.h>  
#include <fcntl.h>
#include <sys/ioctl.h>
int getch();
int clock__();
void gotonow(int,int);
void gotoxy(int,int);
int kbhit();
int system__(const char *);
int Sleep(int);
void MessageBox(void*,const char*,const char*,int);
const int MB_OK = 0;
#define clock clock__
#define system system__
#endif
