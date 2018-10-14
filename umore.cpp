#include <bits/stdc++.h>
#include <sys/time.h>
#include <termios.h>  
#include <unistd.h>  
#include <fcntl.h>
#include <sys/ioctl.h>
#include "h/more.h"
#include "h/system.h"
#include "more.cpp"
void say(std::string name,std::string thing,int speed,int in)
{
	if(name!="")
	{
		system("cls");
		printf("%s:\n",name.c_str());
	}
	for(uint i=0;i<thing.size();i++)
	{
		if(kbhit() && getch()=='~') speed=0;
		if(thing[i]=='|')
		{
			i++;
			if(thing[i]=='d') printf("%d",in);
		}
		else
		{
			std::string str;
			str+=thing[i];
			fputs(str.c_str(),stderr);
		}
		Sleep(speed);
	}
	return ;
}
void cgcolor(std::string s)
{
	system__(("color "+s).c_str());
	return ;
}
int getch__()
{
     struct termios tm, tm_old;
     int fd = 0, ch;
 
     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
          return -1;
     }
 
     tm_old = tm;
     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
          return -1;
     }
 
     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
          return -1;
     }
     return ch;
}
int clock__()
{
	struct timeval    tv;
	struct timezone   tz;
    gettimeofday(&tv,&tz);
    return tv.tv_sec*1000+tv.tv_usec/1000;
}
void gotonow(int x,int y)//X表示行，Y表示列 
{
	if(x>0) printf("\033[%dB",x);
	else if(x<0) printf("\033[%dA",-x);
	if(y>0) printf("\033[%dC",y);
	else if(y<0) printf("\033[%dD",-y);
}
void gotoxy(int x,int y)//X表示行，Y表示列 
{
	printf("\033[%d;%dH",x,y);
}
int kbhit__(void)  
{  
	struct termios oldt, newt;  
	int ch;  
	int oldf;  
	tcgetattr(STDIN_FILENO, &oldt);  
	newt = oldt;  
	newt.c_lflag &= ~(ICANON | ECHO);  
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);  
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);  
	ch = getchar();  
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
	fcntl(STDIN_FILENO, F_SETFL, oldf);  
	if(ch != EOF)  
	{  
		ungetc(ch, stdin);  
		return 1;  
	}  
	return 0;  
} 
#undef system
int system__(const char *s)
{
	extern SET SET_of_ALL;
	std::string ifs = s;
	if(ifs=="cls") return system("clear");
	else if(ifs=="pause")
	{
		while(kbhit()) getch();
		printf("按任意键继续\n");
		getch();
		return 0;
	}
	else if(s[0]=='d' && s[1]=='e' && s[2]=='l' && s[3]==' ')
	{
		std::string ss = (s+4);
		return system(("rm "+ss).c_str());
	}
	else if(s[0]=='c' && s[1]=='o' && s[2]=='l' && s[3]=='o' && s[4]=='r')
	{
		if(not SET_of_ALL.has_color) return 0;
		std::string ss = ifs;
		if(ifs.size() != 8)
		{
			printf("\033[0m");
			return 0;
		}
		for(int i=6;i<=7;i++) //传入的参数先背景,再字体
		{
			int add;
			if(ss[i] >= 'a' && ss[i] <= 'f') ss[i] = ss[i] - 'a' + '0';
			if(ss[i] == '0') add = 0; //黑
			else if(ss[i] == '1') add = 4; //蓝
			else if(ss[i] == '2') add = 2; //绿
			else if(ss[i] == '3') add = 6; //青
			else if(ss[i] == '4') add = 1; //深红
			else if(ss[i] == '5') add = 5; //紫
			else if(ss[i] == '6') add = 3; //黄
			else if(ss[i] == '7') add = 7; //白
			else continue;
			if(i == 6) printf("\e[%dm",40+add);
			else if(i == 7) printf("\e[%dm",30+add);
		}
		return 0;
	}
	else if(ifs.substr(0,4) == "copy")
		return system(("cp" + ifs.substr(4,ifs.size())).c_str());
	else return system(s);
}
int Sleep__(int time)
{
	return usleep(time*1000);
}
int messagebox(void*,const char* text__,const char* title__,int y)
{
	std::string empty_line = "\n                                                                ";
	std::string text = text__ , title = title__;
	if(y == 1)
		return system__(("zenity --info --title=\"" + title + "\" --text=\"" + text + empty_line + "\" 2> /dev/null").c_str());
	if(y == 2)
		return system__(("zenity --question --title=\"" + title + "\" --text=\"" + text + empty_line + "\" 2> /dev/null").c_str());
	return -1;
	/*
	while(kbhit()) getch();
	printf("\n-----%s-----\n",title__);
	int nl = 0;
	for(unsigned int i=0;i<strlen(text__);i++)
		if(text__[i] == '\n')
			nl++;
	printf("%s\n",text__);
	for(unsigned int i=0;i<strlen(title__);i++) putchar('-');
	puts("----------");
	Sleep(999);
	while(kbhit()) getch();
	system__("pause");
	gotonow(-4-nl,0);
	for(int i=0;i<4+nl;i++)
	{
		for(int j=0;j<40;j++)
			putchar(' ');
		puts("");
	}
	gotonow(-5-nl,0);
	*/
}
bool debug_open = 0;
bool debug_to_print = 0;
void debug_print(std::string f)
{
	static std::string tab = "";
	if(f.substr(0,5) != "debug" || debug_open)
	{
		System sys(1);
		FILE *for_debug = fopen(("/home/" + sys.Name() + "/.yzzl/debug.txt").c_str() , "a");
		if(f.substr(f.size()-2 , 2) == "<-") tab = tab.size()<=1 ? "" : tab.substr(0 , tab.size()-1);
		fputs((tab + f + '\n').c_str(),for_debug);
		if(f.substr(f.size()-2 , 2) == "->") tab += '\t';
		fclose(for_debug);
	}
	if(debug_to_print && f.substr(0,5) != "debug")
		puts(f.c_str());
}
int ver_new;
//0:cloning
//1:have cloned but player doesn't know
//2:player know that
int version_check() // for linux
{
	ver_new = 0;
	system("git clone https://github.com/Kewth/YZZL_help.git 2>/dev/null");
	std::ifstream fin("YZZL_help/version.txt");
	std::string v_y , v_m , v_d;
	extern std::string up_y , up_m , up_d;
	fin >> v_y >> v_m >>v_d;
	debug_print(("get version:"+v_y+v_m+v_d).c_str());
	ver_new = 1;
	if(v_y > up_y || v_m > up_m || v_d > up_d)
	{
		debug_print("find new version");
		while(ver_new != 2);
		int mres = messagebox(NULL,(
					"最新版本:"+v_y+"."+v_m+"."+v_d+"\n"
					"当前版本:"+up_y+"."+up_m+"."+up_d+"\n"
					"是否进行更新?\n"
					"更新将下载程序,源码请自行获取").c_str(),"发现新版本",MB_YESNO);
		if(mres == 0)
		{
			system(("mv YZZL_help/Y"+v_y+"_"+v_m+"_"+v_d+" ./").c_str());
			/* system(("mv YZZL_help/Y ./Y"+v_y+"_"+v_m+"_"+v_d+"_").c_str()); */ 
			system("rm -r YZZL_help/");
			system(("chmod +x Y"+v_y+"_"+v_m+"_"+v_d).c_str());
			messagebox(NULL,"消息框后进入新版本","提示:",MB_OK);
			system(("./Y"+v_y+"_"+v_m+"_"+v_d).c_str());
			ver_new = 3;
			return 1;
		}
		else
			system("rm -r YZZL_help/");
	}
	else debug_print("this is already the latest version");
	return 0;
}
bool CG_guangbiao()
{
	static bool open = true;
	if(open) printf("\033[?25l");
	else printf("\033[?25h");
	return true;
}
void make_new_user(std::string name)
{
	System sys(1);
	std::string FP = "/home/"+sys.Name()+"/.yzzl/" + name + "/";
	debug_print("create new user at " + FP);
	system(("mkdir "+FP).c_str());
	for(int i=1;i<=10;i++)
		sys.make_file(FP+"informa"+number_str(i)+".txt");
	sys.make_file(FP+"maincity.txt");
	sys.make_file(FP+"cutcity.txt");
	sys.make_file(FP+"funcity.txt");
	sys.make_file(FP+"workcity.txt");
	sys.make_file(FP+"add.rc");
	sys.make_file(FP+"common.dat");
	sys.make_file(FP+"runlist.txt");
}
