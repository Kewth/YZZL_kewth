#include <bits/stdc++.h>
#include <stdlib.h>
#include "h/more.h"
#include "h/city.h"
#include "h/allcity.h"
#include "h/shuju.h"
#include "h/const.h"
#include "h/system.h"
#ifdef windows
std::string filepl = "C:";
std::string ftppl = "C:\\yzzlrc\\";
#else
/* std::string filepl = "/home/user/.yzzl/"; */
std::string filepl = "/home/";
std::string ftppl = "/run/user/1001/gvfs/ftp:host=172.16.14.3/g2018/Kewth/more/a/b/c/d/";
#endif
extern FILE *information;
std::string color;
std::string release = "2.0" , up_y = "2018" , up_m = "09" , up_d = "08";
SET SET_of_ALL;
void flash(bool nocolor , bool quick)
{
	printf("Flashing\n");
	char xz;
	int times = quick ? 14 : 20;
	for(int i=1;i<=times;i++)
	{
		system("cls");
		if(!nocolor)
		{
			if(i==1) system((color="color fa").c_str());
			if(i==2) system((color="color fb").c_str());
			if(i==3) system((color="color ec").c_str());
			if(i==4) system((color="color fd").c_str());
			if(i==5) system((color="color bf").c_str());
			if(i==6) system((color="color a0").c_str());
			if(i==7) system((color="color 31").c_str());
			if(i==8) system((color="color 82").c_str());
			if(i==9) system((color="color 73").c_str());
			if(i==10) system((color="color 64").c_str());
			if(i==11) system((color="color 55").c_str());
			if(i==12) system((color="color 46").c_str());
			if(i==13) system((color="color 37").c_str());
			if(i==14) system((color="color 28").c_str());
			if(i==15) system((color="color 19").c_str());
			if(i==16) system((color="color 0a").c_str());
			if(i==17) system((color="color 3b").c_str());
			if(i==18) system((color="color 4d").c_str());
			if(i==19) system((color="color 5e").c_str());
			if(i==20) system((color="color 0f").c_str());
		}
		float s=(times + 1 - i)*0.2;
		printf("欢迎玩本游戏\nPowerby 万大师 copyright <c> 2018 版权所有\n按~停止颜色变化并进入主城\n约%.1f秒后自动跳转\n",s);
		printf("release:V%s(%s.%s.%s更新)\n",release.c_str(),up_y.c_str(),up_m.c_str(),up_d.c_str());
		printf("K        W          W     TTTTTTTTT      H      H         \n");
		printf(" e        W        W          T          H      H         \n");
		printf("           W  W   W           T          HHHHHHHH     出品\n");
		printf("           W W W W            T          H      H         \n");
		printf("            W   W             T          H      H         \n");
		printf("                                                          \n");
		Sleep(159);
		if(kbhit())
		{
			xz=getch();
			if(xz=='~') break;
		}
	}
}
void maptest()
{
	puts("Testing a map with 4×4");
	MAP *M = new MAP(0,4);
	puts("Done.");
	delete M;
	system("pause");
}
unsigned long long readrc()
{
	unsigned long long res = 0;
	static std::map<std::string , bool> rc_set;
	std::ifstream fin;
	fin.open((filepl+"add.rc").c_str());
	puts("Read .rc ...");
	while(1)
	{
		std::string s;
		if(!getline(fin , s)) break;
		std::string ns = split(s);
		if(ns == "set") rc_set[split(s)] = 1;
	}
	flash(rc_set["noflashcolor"] , rc_set["quickflash"]);
	if(rc_set["maptest"]) maptest();
	if(!rc_set["notfirst"]) res |= 1;
	puts("Rced");
	return res;
}
static int last_id;
city* allcity(int id)
{
	last_id = id;
	static city *CITYS[5];
	if(CITYS[id]) return CITYS[id];
	city *res;
	if(id == 0) res = new maincity();
	if(id == 1) res = new cutcity();
	if(id == 2) res = new funcity();
	if(id == 3) res = new workcity();
	if(id == 4) res = new firstcity();
	return CITYS[id] = res;
	return NULL;
}
int main(int args,char *argv[])
{
	NOTHING {
#ifdef windows
		System sys(0);
#else
		System sys(1);
#endif
		sys.make_file(filepl + sys.Name() + "/.yzzl/");
		sys.make_file(filepl + sys.Name() + "/.yzzl/debug.txt");
	}
	debug_print("\ngame start:");
	puts("check version...");
	std::thread to_ck_ver(version_check);
	puts("done");
	for(int i=1;i<args;i++)
	{
		if(strcmp(argv[i] , "--debug") == 0 || strcmp(argv[i] , "-d") == 0)
		{
			extern bool debug_open;
			debug_open = 1;
		}
		else if(strcmp(argv[i] , "--deprint") == 0 || strcmp(argv[i] , "-p") == 0)
		{
			extern bool debug_to_print;
			debug_to_print = 1;
		}
		else if(strcmp(argv[i] , "--nocolor") == 0 || strcmp(argv[i] , "-c") == 0)
		{
			SET_of_ALL.has_color = false;
		}
		else 
			printf("warning:无效参数:%s\n",argv[i]);
	}
	messagebox(NULL,"请输入用户名:\n或输入_null来注册","Welcome to the game",MB_OK);
	printf("Your username(or \'_null\'):");
	std::cin >> filepl;
	if(filepl == "_null") filepl = new_user();
	debug_print("get username:"+filepl);
	if(CG_guangbiao())
		puts("SetConsoleCursorInfo:Done");
	else
		puts("SetConsoleCursorInfo:Fail");
	extern int ver_new;
	if(ver_new == 1)
		ver_new = 2 ,
		to_ck_ver.join();
	if(ver_new == 3)
		return 0;
#ifdef windows
	filepl = "C:\\yzzlrc\\" + filepl + "\\";
#else 
	NOTHING {
		System sys(1);
		filepl = "/home/" + sys.Name() + "/.yzzl/" + filepl + '/';
	}
#endif
	information = fopen((filepl + "informa1.txt").c_str() , "w");
	//debug_start
	puts("Loading...");
	unsigned long long rres = readrc();
	city *c = (rres & 1) ? allcity(4) : allcity(0);
	puts("Made a city");
	player *P = new player(1 , 2 , "common");
	/* sjin(P , "common"); */
	puts("a player");
	P->apin(c->M);
	P->pet->apin(c->M);
	extern std::vector<people*> Peo_will_do;
	Peo_will_do.push_back(P->pet);
	std::thread th_of_chprint([=]() { P->check_print(); });
	puts("Made a player");
	while(1)
	{
		if(ver_new == 1)
			ver_new = 2 ,
			to_ck_ver.join();
		if(ver_new == 3)
			return 0;
		P->look(c->M);
		readinforma();
		P->check_print_open = 1;
		int ch = ifgetch(69);
		P->check_print_open = 0;
		if(ch == 'c') P->call_pet(c->M);
		int mres = c->move(P,ch);
		if(mres == 3) break;
		if(mres >=100 && mres <=200)
		{
			P->leave(c->M);
			c = allcity(mres-100);
			messagebox(NULL,"前往另一个城市","正在路途中...",MB_OK);
			P->apin(c->M);
		}
		Peo_all_do();
		if(P->m_hp <= 0 and c->M->m_name != "天堂skycity")
		{
			P->leave(c->M);
			c = new skycity(last_id , P->Px , P->Py);
			P->Px = P->Py = 1;
			P->apin(c->M);
		}
	}
	printf("EXIT\n");
	P->check_print_open = -1;
	th_of_chprint.join();
	/* sjout(P , "common"); */
	debug_print("game end successfully");
}
