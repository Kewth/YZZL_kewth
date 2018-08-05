#include <bits/stdc++.h>
#include "h/more.h"
#include "h/people.h"
FILE* information;

// Pos {{{
Pos::Pos(int x,int y):x(x),y(y) {}
Pos Pos::move(int fg)
{
	Pos res = *this;
	if(fg == 0 || fg == 'w') res.x --;
	else if(fg == 1 || fg == 's') res.x ++;
	else if(fg == 2 || fg == 'a') res.y --;
	else if(fg == 3 || fg == 'd') res.y ++;
	return res;
}
/* Pos Pos::move(char fg) */
/* { */
/* 	Pos res = *this; */
/* 	if(fg == 'w') res.x --; */
/* 	else if(fg == 's') res.x ++; */
/* 	else if(fg == 'a') res.y --; */
/* 	else if(fg == 'd') res.y ++; */
/* 	return res; */
/* } */
// }}}
// print_inF {{{
print_inF::print_inF(Pos U , Pos D , Pos B):U(U),D(D),B(B),now_pox(U.x)
{
#ifdef windows
	auto print_hang = []() -> void { printf("-"); } ;
	auto print_lie = []() -> void { printf("|"); } ;
	auto print_lu = []() -> void { printf("/"); } ;
	auto print_ld = []() -> void { printf("\\"); } ;
	auto print_ru = []() -> void { printf("\\"); } ;
	auto print_rd = []() -> void { printf("/"); } ;
#else
	auto print_hang = []() -> void { printf("─"); } ;
	auto print_lie = []() -> void { printf("│"); } ;
	auto print_lu = []() -> void { printf("┌"); } ;
	auto print_ld = []() -> void { printf("└"); } ;
	auto print_ru = []() -> void { printf("┐"); } ;
	auto print_rd = []() -> void { printf("┘"); } ;
#endif
	P_gotoxy(U.move('d'));
	for(int i=U.y+1;i<D.y;i++)
		print_hang();
	gotoxy(D.x , U.y + 1);
	for(int i=U.y+1;i<D.y;i++)
		print_hang();
	Pos now = U.move('s');
	while(now.x < D.x)
		P_gotoxy(now) ,
		print_lie() ,
		now = now.move('s');
	now = D.move('w');
	while(now.x > U.x)
		P_gotoxy(now) ,
		print_lie() ,
		now = now.move('w') ;
	P_gotoxy(U);
	print_lu();
	P_gotoxy(D);
	print_rd();
	gotoxy(U.x , D.y);
	print_ru();
	gotoxy(D.x , U.y);
	print_ld();
	gotoxy(U.x , U.y + 5);
}
print_inF::~print_inF()
{
	P_gotoxy(B);
}
void print_inF::clear()
{
	for(int i=U.x+1;i<D.x;i++)
	{
		gotoxy(i , U.y + 1);
		for(int j=U.y+1;j<D.y;j++)
			putchar(' ');
	}
	gotoxy(now_pox = U.x , U.y + 5);
}
void print_inF::tonext(int times)
{
	gotoxy(now_pox = std::min(D.x-1 , now_pox + times) , U.y + 1);
}
void print_inF::tolast(int times)
{
	gotoxy(now_pox = std::max(U.x , now_pox - times) , U.y + 1);
	if(now_pox == U.x) gotoxy(now_pox , U.y + 5);
}
// }}}

bool csgetch()
{
	int c = getch();
	while(c != 'y' && c != 'n') c = getch();
	return c == 'y';
}
int intgetch()
{
	int c=getch();
	int res=0;
	while(c>='0' && c<='9') putchar(c) , res = res*10+c-'0' , c = getch();
	puts("");
	return res;
}
int ifgetch(int time)
{
	long long ci = clock__();
	while(clock__() - ci <= time)
		if(kbhit())
			return getch();
	return -1;
}
int tlgetch(int time)
{
	long long ci = clock__();
	int res = -1;
	while(clock__() - ci <= time)
	{
		if(kbhit() && res == -1)
			res = getch();
	}
	return res;
}
std::string split(std::string& s)
{
	std::string res;
	bool done = 0;
	for(uint i=0;i<s.size();i++)
	{
		if(s[i]!=' ')
			res += s[i] , done = 1;
		else if(done)
		{
			s = s.substr(i,s.size()-i);
			return res;
		}
	}
	s.clear();
	return res;	std::ifstream fin;
}
unsigned long myrand(void) {//period 2^96-1
	static unsigned long randx=123456789, randy=362436069, randz=521288629;
	unsigned long &x=randx,&y=randy,&z=randz;
	unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
 
   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;
 
  return (z+clock());
}
void cpinfors(int times)
{
	extern std::string filepl;
	if(!times) return ;
	std::ifstream fin;
	fin.open((filepl + "informa" + (char)('0'+times) + ".txt").c_str());
	while(1)
	{
		std::string s;
		getline(fin , s);
		if(s.empty()) break;
		puts(s.c_str());
	}
	if(times > 1)
		system(("copy " + filepl + "informa" + (char)('0'+times-1) + ".txt " + filepl + "informa" + (char)('0'+times) + ".txt > just_now.txt").c_str());
	fin.close();
	cpinfors(times - 1);
}
void readinforma()
{
	extern std::string filepl;
	std::ifstream fin;
	if(!information) puts("ERROR");
	else fclose(information);
	cpinfors(8);
	information = fopen((filepl + "informa1.txt").c_str() , "w");
}
float power11(int x)
{
	float res = 1;
	for(;x>0;x--)
	{
		res *= 1.1;
	}
	return res;
}
std::string number_str(int num)
{
	if(!num) return "";
	if(num < 0) return '-' + number_str(-num);
	return number_str(num/10) + (char)('0' + num % 10);
}
void P_gotoxy(Pos pos)
{
	gotoxy(pos.x , pos.y);
}
std::vector<people*> Peo_will_do;
void Peo_all_do()
{
	std::vector<std::vector<people*>::iterator> era;
	for(auto i=Peo_will_do.begin();i!=Peo_will_do.end();i++)
	{
		if((*i)->m_hp <= 0)
			era.push_back(i);
		else
			(*i)->Todo();
	}
	for(uint i=0;i<era.size();i++)
		Peo_will_do.erase(era[i]);
}
