#ifndef MORE_H
#define MORE_H
#include <bits/stdc++.h>
/* #define windows nullptr */
// class {{{
class Pos
{
public :
	int x;
	int y;
	Pos move(int);
	/* Pos move(char); */
	Pos(int,int);
};
template <class T>
struct _map2
{
	std::map<std::pair<int,int>,T> mps;
	T& operator () (int x,int y) { return mps[std::pair<int,int>(x,y)]; }
	T& operator () (Pos P) { return mps[std::pair<int,int>(P.x , P.y)]; }
	int clear() { mps.clear(); return 0; }
};
class print_inF
{
private:
	Pos U ; Pos D; Pos B;
	int now_pox;
public:
	print_inF(Pos , Pos , Pos);
	~print_inF();
	void tonext(int=1);
	void tolast(int=1);
	void clear();
};
struct SET
{
	bool has_color;
	SET():has_color(true) {}
};
// }}}
// function {{{
std::string split(std::string&);
unsigned long myrand();
void cpinfor(int);
void readinforma();
float power11(int);
std::string number_str(int);
int version_check();
void debug_print(std::string);
void say(std::string,std::string,int,int=0);
void cgcolor(std::string);
void Peo_all_do();
bool csgetch();
int intgetch();
int ifgetch(int);
int tlgetch(int);
int getch__();
#define getch() getch__()
int messagebox(void*,const char*,const char*,int);
int Sleep__(int);
#define Sleep Sleep__ 
int kbhit__(void);
#define kbhit kbhit__ 
int system__(const char*);
#define system system__
int clock__();
#define clock clock__
void gotoxy(int , int);
void P_gotoxy(Pos);
void gotonow(int , int);
#define rand() myrand()
// }}}
// const {{{
#undef MB_OK
#undef MB_YESNO
const int MB_OK = 1 , MB_YESNO = 2;
//#define MB_OK mes_MB_OK
//FILE* information , *for_debug;
extern FILE *information;
// }}}
typedef unsigned int uint;
#ifdef windows
const auto print_hang = []() -> void { printf("-"); } ;
const auto print_lie = []() -> void { printf("|"); } ;
const auto print_lu = []() -> void { printf("/"); } ;
const auto print_ld = []() -> void { printf("\\"); } ;
const auto print_ru = []() -> void { printf("\\"); } ;
const auto print_rd = []() -> void { printf("/"); } ;
#else
const auto print_hang = []() -> void { printf("─"); } ;
const auto print_lie = []() -> void { printf("│"); } ;
const auto print_lu = []() -> void { printf("┌"); } ;
const auto print_ld = []() -> void { printf("└"); } ;
const auto print_ru = []() -> void { printf("┐"); } ;
const auto print_rd = []() -> void { printf("┘"); } ;
#endif

#endif
