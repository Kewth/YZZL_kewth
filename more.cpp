#include <bits/stdc++.h>
#include "h/more.h"
#include "h/people.h"
FILE* information;
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
unsigned long myrand(void)
//period 2^96-1
{
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
 
  return (z ^ clock());
}
int new_read_info = 0;
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
	if(times > 1 && not new_read_info)
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
	if(not new_read_info)
	{
		information = fopen((filepl + "informa1.txt").c_str() , "w");
		new_read_info = 7;
	}
	else
	{
		information = fopen((filepl + "informa1.txt").c_str() , "ab");
		new_read_info --;
	}
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
	debug_print("debug:Peo_all_do->");
	/* std::vector<std::vector<people*>::iterator> era; */
	for(auto i=Peo_will_do.begin();i!=Peo_will_do.end();i++)
	{
		debug_print("debug:Turn_to"+(*i)->m_name+"->");
		bool era = false;
		debug_print(std::string("debug:m_hp>0?")+
				((*i)->m_hp>0?"Y":"N"));
		if((*i)->m_hp <= 0 and (*i)->m_mut_leave.try_lock())
			(*i)->m_mut_leave.unlock(),
			(*i)->leave((*i)->m_inM);
		if((*i)->m_hp <= 0 or not (*i)->m_inM)
			era = true;
		else
			(*i)->Todo();
		debug_print("debug:Turn_to"+(*i)->m_name+"<-");
		if(era) (*i) = nullptr;
	}
	debug_print("debug:turn done");
	for(auto i=Peo_will_do.begin();i!=Peo_will_do.end();)
		if(not *i)
			i = Peo_will_do.erase(i);
		else 
			i ++;
	/* for(uint i=0;i<era.size();i++) */
	/* 	debug_print("debug:will erase "+(*era[i])->m_name), */
		/* *era[i] = nullptr, */
		/* Peo_will_do.erase(era[i]); */
	debug_print("debug:Peo_all_do<-");
}
void SJ_inline(std::string text,int now,int tot)
{
	cgcolor("");
	printf("%s",text.c_str());
	const double add = tot/100;
	auto f = [=](std::string st,std::string en,int ist)
	{
		bool isgreen = true;
		cgcolor(st);
		for(int i=ist;i<ist+25;i++)
		{
			if(isgreen && add*i >= now)
				cgcolor(en),
				isgreen = false;
			print_hang();
		}
	};
	if(now < add*25)
		f("-4" , "-7" , 0);
	else if(now < add*50)
		f("-6" , "-4" , 25);
	else if(now < add*75)
		f("-3" , "-6" , 50);
	else
		f("-2" , "-3" , 75);
	puts("");
	cgcolor("");
}
std::string new_user()
{
	while(kbhit()) getch();
	std::string name;
	const int line = 8;
	system("cls");
	puts("请输入一个合法用户名:(按ctrl-c退出)");
	puts("");
	puts("以下的用户名被认为是非法的:");
	puts("1.以下划线开头");
	puts("2.空用户名");
	puts("3.包含字母、下划线、数字以外的字符");
	puts("4.名字长度超过10");
	gotoxy(2,0);
	while(1)
	{
		puts("----------");
		gotonow(-1 , 0);
		printf("%s",name.c_str());
		int ch = getch();
		if(ch == '')  {
			name = "_public";
			break;
		}
		else if(ch == '_' && name.empty())
			gotoxy(line,0),
			puts("违反规则1!"),
			gotoxy(2,0);
		else if((ch == '\n' || ch == '\r') && name.empty())
			gotoxy(line,0),
			puts("违反规则2!"),
			gotoxy(2,0);
		else if(ch == '\n' || ch == '\r')
			break;
		else if(ch == '') {
			gotoxy(line,0);
			if(name.empty()) 
				puts("名字已为空.");
			else
				puts("未违反规则.");
			gotoxy(2,0);
			name = name.substr(0 , name.size() - 1);
		}
		else if((ch<'a'||ch>'z') && (ch<'A'||ch>'Z') && ch!='_' && (ch<'0'||ch>'9')) {
			gotoxy(line,0);
			puts("违反规则3!");
			gotoxy(2,0);
		}
		else if(name.size() >= 10) {
			gotoxy(line,0);
			puts("违反规则4!");
			gotoxy(2,0);
		}
		else {
			gotoxy(line,0);
			puts("未违反规则.");
			gotoxy(2,0);
			name += ch;
		}
	}
	make_new_user(name);
	return name;
}
