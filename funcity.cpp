#include <bits/stdc++.h>
#include "h/more.h"
#include "h/city/funcity.h"
extern std::string filepl;
namespace RUN
{
	using std::string;
	const string MAP[] ={ 
	"-#         #####" ,//0
	"-#        ######" ,//1
	"-#          ####" ,//2
	"-#      #  #####" ,//3
	"-#   #  #  #####" ,//4
	"-#       #######" ,//5
	"-#           ###" ,//6
	"-#         #####" ,//7
	"-###############" ,//8
	"-########      #" ,//9
	"-#        @    #" ,//10
	"-#             #" ,//11
	};
	const string clMAP[] ={ 
	"-#    $    #####" ,//0
	"-#       $######" ,//1
	"-#          ####" ,//2
	"-#      #$ #####" ,//3
	"-#   # $#  #####" ,//4
	"-#     $ #######" ,//5
	"-#         $ ###" ,//6
	"-#        $    #" ,//7
	"-# # # #$# # # #" ,//8
	"-########    $ #" ,//9
	"-#       #@#   #" ,//10
	"-#             #" ,//11
	};
	const int difc[] ={
	1300,//0
	400,//1
	400,//2
	100,//3
	70,//4
	170,//5
	180,//6
	140,//7
	40,//8
	70,//9
	200,//10
	180,//11
	};
	struct note
	{
		string map;
		int pos , high , insky , go , mon;
		note():pos(5),high(6),insky(0),go(0),mon(0) {};
	};
	string newmap(int x)
	{
		string s;
		s+=(char)0;
		for(int i=1;i<=x;i++)
		{
			int tot = 12 , sum = 0;
			s+=(char)0;
			for(int j=0;j<tot;j++)
				sum += difc[j];
			int rd = rand()%sum;
			for(int j=0;j<tot;j++)
				if(rd < difc[j])
				{
					s[i] = j;
					break;
				}
				else
					rd -= difc[j];
		}
		return s;
	}
	note his;
	int look(note &p)
	{
		static int laspos;
		static std::map<int,bool> getmon;
		if(p.pos < laspos) getmon.clear();
		laspos = p.pos;
		int res = 0;
		/* int ci = clock(); */
		if(p.high>15) return -1;
		char see[20][20];
		for(int i=p.pos-5;i<=p.pos+9;i++)
		{
			int k = i-p.pos+6;
			if(k<=8)
				for(int j=1;j<=15;j++)
					see[j][k] = clMAP[(int)p.map[i]][j];
			else
				for(int j=1;j<=15;j++)
					see[j][k] = MAP[(int)p.map[i]][j];
		}
		if(see[16-p.high][6] == '#') res = -1;
		else if(see[17-p.high][6] != '#' && p.go != 2) p.high--;
		else if(see[17-p.high][6] == '#') p.insky = 0;
		int h = 16 - p.high;
		if(see[h][6] == '$') res = 1 , getmon[p.pos] = 100	>1;
		else if(see[h][6] == '@') his = p , his.go = 2 , getmon[p.pos] = 1;
		see[h][6] = p.insky ? '0' : 'O' ;
		if(p.go == 1)
			see[h][5] = see[h][4] = '-';
		p.go = 0;
		for(int i=1;i<=15;i++)
		{
			for(int j=1;j<=15;j++)
			{
				if(see[i][j] == '#') cgcolor("04");
				else if(see[i][j] == '$' && !getmon[p.pos-6+j]) cgcolor("06");
				else if(see[i][j] == '@' && !getmon[p.pos-6+j]) cgcolor("01");
				else if(see[i][j] == 'O' || see[i][j] == '0') res == -1 ? cgcolor("41") : cgcolor("01");
				else if(see[i][j] == '-') cgcolor("06");
				putchar(see[i][j]);
				cgcolor("");
			}
			puts("");
		}
		printf("Jump\n");
		return res;
	}
	void jump(note &p , int jp)
	{
		if(p.insky >= 2) return ;
		else p.insky ++;
		while(clMAP[(int)p.map[p.pos]][16-p.high] != '#' && jp)
			p.high ++ , jp--;
		p.go = 2;
	}
	void update(note &p);
	int eaymain(int speed,string file="")
	{
		if(his.map.empty())
		{
			string map;
			if(file.empty())
			{
				for(int i=1;i<=10;i++) map += (char)0;
				map += newmap(20);
			}
			else
			{
				std::ifstream fin(file.c_str());
				int num;
				while(fin >> num)
					map += (char)num;
			}
			his.map = map;
		}
		system("clear");
		look(his);
		string news = "Good luck for you...";
		for(uint i=0;i<news.size();i++)
			fprintf(stderr,"%c",news[i]) , Sleep(29);
		for(note p(his);;p.pos++)
		{
			system("clear");
			printf("pos:%d($:%d),marks:%d\n",p.pos,p.mon,p.pos+p.mon*5);
			int lres = look(p);
			if(lres == -1)
			{
				puts("LOSE!!!");
				his.map = p.map;
				update(p);
				break;
			} else if(lres == 1) p.mon ++;
			gotonow(-1 , 0);
			cgcolor("02");
			puts("Jump");
			int ch = tlgetch(speed);
			gotonow(-1 , 0);
			cgcolor("");
			puts("Jump");
			if(ch == ' ')
				jump(p,2);
			else if(ch == '\n')
				p.pos += 2 , p.go = 1;
			else if(ch == 'w')
				jump(p,1);
			if(file.empty())
				p.map += newmap(1);
			else if(p.pos + 9 == (int)p.map.size())
			{
				puts("Win!!");
				update(p);
				break;
			}
		}
		puts("Try again?");
		if(csgetch()) return 1;
		else return 0;
	}
	void update(note &p)
	{
		FILE *fin = std::fopen((filepl + "runlist.txt").c_str(),"r");
		const int sl = 5;
		int num[sl+1] , mark = p.pos + p.mon*5;
		memset(num,0,sizeof(num));
		//std::string s[sl+1];
		for(int i=1;i<=sl;i++)
		{
			fscanf(fin,"%d",&num[i]);
			/*
			char ch;
			for(int j=0;j<num[i];j++)
				fscanf(fin,"%c",&ch) , s[i] += ch;
				*/
		}
		int getn = sl;
		for(;getn;getn--)
			if(mark > num[getn])
				printf("(以%d)打破第%d名的分数(%d)记录!!!\n",mark,getn,num[getn]);
			else break;
		getn ++;
		for(int i=sl;i>getn;i--)
			num[i] = num[i-1]; // , s[i] = s[i-1];
		num[getn] = mark;
		//s[getn] = p.map;
		std::ofstream fout;
		fout.open((filepl + "runlist.txt").c_str());
		for(int i=1;i<=sl;i++)
			fout << num[i] << '\n'; // << s[i] << '\n' ;
	}
};
int funcity::xz0::onein(people *)
{
	return 3;
}
int funcity::xz1::onein(people *P)
{
	if(P->m_typ != "player")
		printf("%s把你带进了跑酷!!\n",P->m_name.c_str()) ,
		Sleep(999);
	RUN::note his;
	RUN::his = his;
	srand(time(0));
	say("开发者","跑酷正在测试阶段,接下来的询问回答y,玩法在update.html中有提到...\n",69);
	printf("no ending?\n");
	if(csgetch())
	{
		while(1)
		{
			int rres;
			rres = RUN::eaymain(199);
			if(rres == 0) break;
		}
	}
	else
	{
		printf("the file:");
		while(kbhit()) getch();
		std::string file;
		while(file.empty())
		{
			std::cin >> file;
			std::cout << file << std::endl;
		}
		while(1)
		{
			int rres;
			rres = RUN::eaymain(199,file);
			if(rres == 0) break;
		}
	}
	say("开发者","想要奖励吗?\n不存在的!\n(仅供娱乐)\n",69);
	return 0;
}
funcity::funcity()
{
	newmap("funcity.txt");
	int mid = maxn >> 1;
	M->m_name = "娱乐圣地funcity";
	M->f(0,mid) = new gotocity(0,maxn,mid,'^');
	M->f(-1,mid) = new wall();
	M->f(1,mid) = new grass('|');
	M->f(maxn-5,1) = new xz0();
	for(uint i=0;i<xz0::name.size();i++)
		M->f(maxn-5,i+2) = new grass(xz0::name[i],"由此退出");
	M->f(maxn-4,1) = new xz1();
	for(uint i=0;i<xz1::name.size();i++)
		M->f(maxn-4,i+2) = new grass(xz1::name[i],"由此跑酷");
}
std::string funcity::xz0::name = "exit";
std::string funcity::xz1::name = "parkour";

