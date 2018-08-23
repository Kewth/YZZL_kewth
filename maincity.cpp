#include <bits/stdc++.h>
#include "h/more.h"
#include "h/city.h"
#include "h/city/maincity.h"
#include "h/war.h"
int maincity::xz0::onein(people*)
{
	//allexit(P);
	return 3;
}
int maincity::xz1::onein(people* P)
{
	fprintf(information , "%s开始了磨练\n",P->m_name.c_str());
	if(P->m_typ != "player")
	{
		P->m_sta["stop"] = std::make_pair(clock() + 3999,0);
		P->c_hp(nullptr , -100 , 'r');
		return 0;
	}
	player * PP = (player *) P;
	int lv = PP->m_lv;
	system("cls");
	std::cout<<"请选择难度：\n";
	std::cout<<"1、简单\n";
	std::cout<<"2、普通";
	if(lv<2) printf("（未解锁）\n");else printf("\n");
	std::cout<<"3、困难";
	if(lv<6) printf("（未解锁）\n");else printf("\n");
	std::cout<<"4、挑战";
	if(lv<10) printf("（未解锁）\n");else printf("\n");
	std::cout<<"5，地狱";
	if(lv<16) printf("（未解锁）\n");else printf("\n");
	std::cout<<"6，次高试炼";
	if(lv<22) printf("（未解锁）\n");else printf("\n");
	std::cout<<"7，最高试炼";
	if(lv<28) printf("（未解锁）\n");else printf("\n");
	std::cout<<"注：逃跑、失败不能获得奖励.\n";
	std::cout<<"请输入难度编号\n";
	char c;
	c=getch();
	if((c=='2'&&lv<2)||(c=='3'&&lv<6)||(c=='4'&&lv<10)||(c=='5'&&lv<16)||(c=='6'&&lv<22)||(c=='7'&&lv<28))
	{
		printf("未解锁此难度!\n");
		system("pause");
		return 0;
	}
	else
	{
		/* if(PP->pet->m_mut_leave . try_lock()) */
			/* PP->pet->m_mut_leave . unlock(); */
		/* else puts("ERROR") , Sleep(999); */
		int res;
		if(c=='1')
		{
			int rd = myrand()%3;
			res=war(PP , new pig(5 , 5 , rd));
		}
		else if(c=='2')
		{
			int rd = 4 + myrand()%4;
			res=war(PP , new pig(5 , 5 ,rd));
		}
		else if(c=='3')
		{
			int rd = 7 + myrand()%4;
			if(rd < 9) res = war(PP , new pig(5 , 5 , rd));
			else res=war(PP , new snake(5 , 5 , rd));
		}
		else if(c=='4')
		{
			int rd = 12 + myrand()%5;
			if(rd < 14) res = war(PP , new pig(5 , 5 , rd));
			else res=war(PP , new snake(5 , 5 , rd));
		}
		else if(c=='5')
		{
			int rd = 18 + myrand()%6;
			if(rd < 20) res = war(PP , new pig(5 , 5 , rd));
			else res=war(PP , new snake(5 , 5 , rd));
		}
		else if(c=='6')
		{
			int rd = 25 + myrand()%10;
			if(rd < 27) res = war(PP , new pig(5 , 5 , rd));
			else res=war(PP , new snake(5 , 5 , rd));
		}
		else if(c=='7')
		{ 
			int rd = 32 + myrand()%20;
			if(rd < 35) res = war(PP , new pig(5 , 5 , rd));
			else res=war(PP , new snake(5 , 5 , rd));
		}
		else return 0;
		printf("\n\n\n");
		if(res==1)
		{
			printf("敌人杀死了你!!\n");
			printf("        结局：战死沙场\n");
		}
		if(res==2)
		{
			printf("        结局：走为上策\n");
		}
		if(res==3)
		{
			printf("敌人剩余0HP！！\n");
			printf("你杀死了敌人！！\n");
			printf("        结局：大获全胜\n");
		}
		system("pause");
		Sleep(999);
		return 1;
	}
	return 0;
}
int xz_yangshen(people * P)
{
	if(P->m_typ != "player")
	{
		fprintf(information , "%s开始了养神\n",P->m_name.c_str());
		P->c_hp(nullptr , 100);
		return 0;
	}
	player * pl = (player*) P;
	int lv = pl->m_lv;
	int yuanli = pl->bag->yuanli_h(0);
	int oohp = 400*power11(lv);
	int oomagic = 70*power11(lv);
	printf("你目前有元力：%d\n",yuanli);
	printf("是否花费%d点元力来恢复",lv);
	cgcolor("02");
	printf("%d",oohp);
	system("color");
	printf("点HP和");
	cgcolor("02");
	printf("%d",oomagic);
	system("color");
	printf("点魔法值？\n1,是        其余，否\n");
	char xzxz;
	xzxz=getch();
	if(xzxz=='1')
	{
		if(pl->bag->yuanli_h(-lv) != -1)
		{
			printf("养神成功!\n");
			pl->c_hp(nullptr , oohp);
			pl->magic_h(oomagic);
		}
	}
	system("pause");
	return 0;
}
int maincity::xz2::onein(people * P)
{
	return xz_yangshen(P);
}
int maincity::xz3::onein(people * P)
{
	if(P->m_typ != "player")
	{
		fprintf(information , "%s尝试学习,似乎大有所悟\n",P->m_name.c_str());
		P->m_sta["stop"] = std::make_pair(clock() + 999,0);
		P->exp_h(P->m_lv*2+3);
		return 0;
	}
	player * pl = (player *) P;
	printf("选择你要学习的技能:\n");
	int l=0,r=2;
#define jns(x) pl->m_list->jn[x]
	for(int i=l;i<=r;i++)
	{
		if(jns(i)->m_lv == jns(i)->m_lvmax) printf("%d. %s(满级)\n",i,jns(i)->m_name.c_str());
		else printf("%d. %s(金币:%d)\n",i,pl->m_list->jn[i]->m_name.c_str(),pl->m_list->jn[i]->m_pay[pl->m_list->jn[i]->m_lv]);
	}
	printf("%d. 退出\n\n",r+1);
	int xzs = getch() - '0';
	while(xzs<l || xzs>r+1) xzs = getch() - '0';
	if(xzs == r+1) return 0;
	if(!pl || !pl->bag || !pl->m_list || !pl->m_list->jn[xzs]) puts("ERROR");
	jns(xzs)->check(1);
	printf("确定升级?(y/n)\n");
	if(!csgetch()) return 0;
	if(pl->bag->coin_h(-pl->m_list->jn[xzs]->m_pay[pl->m_list->jn[xzs]->m_lv]) == -1)
	{
		puts("金币不足!");
		Sleep(999);
	}
	else
		pl->m_list->jn[xzs]->lvup();
	return 0;
#undef jns
}
int maincity::xz4::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	player * pl = (player *) P;
	pl->m_achi->c_lookall();
	return 0;
}
maincity::maincity()
{
	newmap("maincity.txt");
	int mid = maxn >> 1;
	M->m_name = "主城maincity";
	M->f(0,mid) = new gotocity(1,maxn,mid,'^');
	M->f(-1,mid) = new wall();
	M->f(1,mid) = new grass('|');
	M->f(maxn,mid) = new gotocity(2,0,mid,'v');
	M->f(maxn+1,mid) = new wall();
	M->f(maxn-1,mid) = new grass('|');
	M->f(mid,maxn) = new gotocity(3,mid,0,'>');
	M->f(mid,maxn+1) = new wall();
	M->f(mid,maxn-1) = new grass('-');
	M->f(maxn-5,1) = new xz0();
	for(uint i=0;i<xz0::name.size();i++)
		M->f(maxn-5,i+2) = new grass(xz0::name[i],"由此退出");
	M->f(maxn-4,1) = new xz1();
	for(uint i=0;i<xz1::name.size();i++)
		M->f(maxn-4,i+2) = new grass(xz1::name[i],"由此磨炼");
	M->f(maxn-3,1) = new xz2();
	for(uint i=0;i<xz2::name.size();i++)
		M->f(maxn-3,i+2) = new grass(xz2::name[i],"由此养神");
	M->f(maxn-2,1) = new xz3();
	for(uint i=0;i<xz3::name.size();i++)
		M->f(maxn-2,i+2) = new grass(xz3::name[i],"由此学习");
	M->f(maxn-1,1) = new xz4();
	for(uint i=0;i<xz4::name.size();i++)
		M->f(maxn-1,i+2) = new grass(xz4::name[i],"由此查看成就");
}
std::string maincity::xz0::name = "exit";
std::string maincity::xz1::name = "fight";
std::string maincity::xz2::name = "relax";
std::string maincity::xz3::name = "study";
std::string maincity::xz4::name = "achievement";

