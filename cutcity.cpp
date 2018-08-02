#include <bits/stdc++.h>
#include "h/more.h"
#include "h/city.h"
#include "h/city/cutcity.h"
#include "h/war.h"
static int warres;
static int allreturn;
static bool allstop;
static void * Emain(people *E , MAP *M)
{
	/*
	std::pair<people *,MAP *> *Pr = ( std::pair<people *,MAP *>*)NU;
	people * E = Pr->first;
	MAP * M = Pr->second;
	*/
	while(!warres)
	{
		while(allstop);
		E->m_sta["dikang"] = std::make_pair(clock() + 1000 , 1000000);
		E->look(M);
		int mres = M->move(E , ' ');
		if(mres == 1) warres = 2;
		else Sleep(399);
		if(E->m_hp <= 0)
			break;
	}
	if(warres) E->leave(M);
	allreturn ++;
	return NULL;
}

static void Emain2(people *E , MAP *M)
{
	E->apin(M);
	while(!warres)
	{
		while(allstop);
		E->look(M);
		int mres = M->move(E , ' ');
		if(mres == 1) warres = 1 ;
		else Sleep(399);
		if(E->m_hp <= 0)
			break;
	}
	if(warres) E->leave(M);
	allreturn ++;
}

int cutcity::xz0::onein(people*)
{
	return 3;
}

int cutcity::xz1::onein(people* P)
{
	if(P->m_typ != "player")
	{
		fprintf(information , "%s似乎想去森林\n",P->m_name.c_str());
		return 0;
	}
	int bf_x = P->Px , bf_y = P->Py;
	int diff = warres = allreturn = 0;
	allstop = 0;
	player * PL = (player *) P;
	P->Px = P->Py = 1;
	atree * T = new atree(3,3,0);
	MAP * M = new MAP(0,6,"小树林");
#define Esl 3
	people * E[Esl];
	/* pthread_t tids[Esl]; */
	std::thread *th[Esl];
	/* std::pair<people* , MAP*> Pr[Esl]; */
	int E_lv = PL->bag->wood_h(0) / 100;
	for(int i=0;i<Esl;i++)
	{
		if(i) E[i] = new pig(5,i+1,E_lv);
		else E[i] = new snake(5,i+1,E_lv);
		E[i]->apin(M);
		/* Pr[i] = std::make_pair(E[i] , M); */
		/* pthread_create(&tids[i] , NULL , Emain , (void*)&Pr[i]); */
		th[i] = new std::thread(Emain , E[i] , M);
	}
	T->apin(M);
	P->apin(M);
	int endci = clock() + 30000;
	std::string end_str = "错误退出(我也很无奈)";
	while(!warres)
	{
		P->look(M);
		printf("此树剩余生命:%d\n",T->m_hp);
		printf("剩余时间:%ds\n",(endci - clock())/1000);
		puts("按Q退出");
		readinforma();
		/* int c = ifgetch(199); */
		int c = getch();
		if(c == 'Q') warres = 3;
		int mres = M->move(P , c);
		if(mres == 1)
		{
			T->leave(M); // 强行离开
			allstop = 1;
			messagebox(NULL,"你砍倒了这棵树!!!","恭喜:",MB_OK);
			/* PL->bag->wood_h(diff*10); */
			diff += 3;
			/* delete T; */
			T = new atree(3,3,diff);
			T->apin(M);
			endci += 10000;
			allstop = 0;
		}
		if(clock() >= endci) warres = 1;
	}
	if(warres == 1) end_str = "时间已到";
	else if(warres == 2) end_str = "死于树林";
	else if(warres == 3) end_str = "主动退出";
	messagebox(NULL,end_str.c_str(),"砍树结束:",MB_OK);
	P->Px = bf_x , P->Py = bf_y;
	printf("返回%d\n",warres);
	//while(allreturn < Esl) printf("%d\n",allreturn);
	for(int i=0;i<Esl;i++)
		th[i] -> join() ,
		delete th[i];
	delete M;
#undef Esl
	return 0;
}

int cutcity::xz2::onein(people * P)
{
	return xz_yangshen(P);
}

int cutcity::xz3::onein(people *P)
{
	if(P->m_typ != "player")
	{
		fprintf(information , "%s似乎想去森林\n",P->m_name.c_str());
		return 0;
	}
	int bf_x = P->Px , bf_y = P->Py;
	warres = allreturn = 0;
	const int map_size = 20 , Esl = 10;
	allstop = 1;
	/* player * PL = (player *) P; */
	P->Px = P->Py = 1;
	atree * T = new atree(1,map_size>>1,0);
	MAP * M = new MAP(0,map_size+1,"森林");
	people * E[Esl];
	std::thread *th[Esl];
	for(int i=0;i<Esl;i++)
	{
		E[i] = new snake(3+i,1+rand()%(map_size-1),0);
		//E[i]->apin(M);
		th[i] = new std::thread(Emain2 , E[i] , M);
	}
	T->apin(M);
	P->apin(M);
	debug_print("debug:all people is ready"); //debug
	allstop = 0;
	while(!warres)
	{
		P->look(M);
		printf("击杀敌人:%d/%d\n",allreturn,Esl);
		readinforma();
		int c = ifgetch(199);
		if(c == 'Q') warres = 2;
		M->move(P , c);
		if(allreturn == Esl)
			warres = 3;
	}
	P->Px = bf_x , P->Py = bf_y;
	for(int i=0;i<Esl;i++)
		th[i] -> join() ,
		delete th[i];
	return 0;
}

cutcity::cutcity()
{
	newmap("cutcity.txt");
	int mid = maxn >> 1;
	M->m_name = "樵夫城cutcity";
	M->f(maxn,mid) = new gotocity(0,0,mid,'v');
	M->f(maxn+1,mid) = new wall();
	M->f(maxn-1,mid) = new grass('|');
	M->f(maxn-5,1) = new xz0();
	for(unsigned int i=0;i<xz0::name.size();i++)
		M->f(maxn-5,i+2) = new grass(xz0::name[i],"由此退出");
	M->f(maxn-4,1) = new xz1();
	for(unsigned int i=0;i<xz1::name.size();i++)
		M->f(maxn-4,i+2) = new grass(xz1::name[i],"由此砍树");
	M->f(maxn-3,1) = new xz2();
	for(unsigned int i=0;i<xz2::name.size();i++)
		M->f(maxn-3,i+2) = new grass(xz2::name[i],"由此养神");
	M->f(maxn-2,1) = new xz3();
	for(unsigned int i=0;i<xz3::name.size();i++)
		M->f(maxn-2,i+2) = new grass(xz3::name[i],"由此进入森林");
}

std::string cutcity::xz0::name = "exit";
std::string cutcity::xz1::name = "cut_tree";
std::string cutcity::xz2::name = "relax";
std::string cutcity::xz3::name = "tree_more";
