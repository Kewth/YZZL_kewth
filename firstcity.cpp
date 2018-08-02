#include <bits/stdc++.h>
#include "h/city.h"
#include "h/city/firstcity.h"
static std::string infor = " press \'d\'";
int firstcity::xz0::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player*) P;
	pl->bag->coin_h(1000);
	say("","奖励1000金币!\n正在传送\n",69);
	P->Px = 1;
	P->Py += 2;
	return 0;
}
int firstcity::xz1::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player*) P;
	pl->bag->coin_h(100);
	say("","奖励100金币!\n正在传送\n",69);
	P->Py+=2;
	return 0;
}
int firstcity::xz2::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	say("","首先面向它\n然后按j向它的方向移动\n攻击花费200ms",89);
	return 0;
}
int firstcity::xz3::onein(people* P)
{
	if(P->m_typ == "player") 
		say("","不好,这有陷阱!\n",69);
	P->Px = 7;
	P->Py = 1;
	return 0;
}
int firstcity::xz4::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	extern FILE* information;
	fprintf(information,"多走走试试\n");
	static int jsq = 0;
	jsq ++;
	if(jsq == 10) P->Py += 3;
	P->c_hp(nullptr , -10 , 'r');
	return 0;
}
int firstcity::xz5::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player*) P;
	extern FILE* information;
	fprintf(information,"终于走出来了\n");
	static int jsq = 0;
	if(!jsq) pl->magic_h(100);
	jsq ++;
	if(jsq == 20) P->Px += 2;
	return 0;
}
int firstcity::xz6::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	say("向导","恭喜你总算是通过了新手城的考验,下次来我会将你带到主城,那里......\n",79);
	extern std::string filepl;
	system(("echo set notfirst >> " + filepl + "add.rc").c_str());
	return 3;
}
int firstcity::xz7::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player *) P;
	pl -> m_achi->c_get(pl , "first_find2");
	return 0;
}
int firstcity::xz8::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player *) P;
	pl -> m_achi->c_get(pl , "first_find1");
	return 0;
}
int firstcity::xz9::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	say("","你怎么走到这来了?",59);
	P->Px -= 2;
	P->Py = 4;
	return 0;
}
firstcity::firstcity()
{
	for(int i=1;i<maxn;i++)
		for(int j=1;j<maxn;j++)
			M->f(i,j) = new grass(' ');
	/* int mid = maxn >> 1; */
	M->m_name = "新手城firstcity";
	for(uint i=0;i<infor.size();i++)
		M->f(1,i+1) = new grass(infor[i] , "如你所见,按d可以向右移动"),
		M->f(2,i+1) = new wall(),
		M->f(3,i+1) = new grass(infor[i]=='d'?'a':infor[i] , "同样的按a可以左移"),
		M->f(4,i+1) = new wall(),
		M->f(5,i+1) = new grass('>'),
		M->f(6,i+1) = new wall();
	M->f(1,infor.size()+1) = new grass('!' , "再试试右移,你会发现你无法移动,因为你的右边显然是一堵墙,现在按s向下");
	for(uint i=1;i<=4;i++)
		M->f(i , infor.size()+2) = new wall();
	M->f(4 , infor.size()+1) = new wall();
	M->f(3 , infor.size()+1) = new grass('!' , "有没有发现你看不到上面的字却新看见下面的字了?\n事实上这是因为你的视线收到了墙的阻挡");
	M->f(4,1) = new grass('!' , "那么自己走走吧");
	for(uint i=1;i<=5;i++)
		M->f(i,infor.size()+3) = new grass(' '),
		M->f(i,infor.size()+4) = new wall();
	for(uint i=infor.size()+1;i<=infor.size()+4;i++)
		M->f(6,i) = new wall(); 
	M->f(5,infor.size()+3) = new grass('!' , "不用说你也能猜到,按w向上");
	M->f(2,infor.size()+3) = new grass('!' , "上去吧");
	M->f(1,infor.size()+3) = new xz0();
	uint sz = infor.size() + 4;
	for(uint i=1;i<=6;i++)
		M->f(i,sz+2) = new wall();
	M->f(6,sz+1) = new wall();
	M->f(3,sz+1) = new grass('!' , "你是否注意到你获得了金币?\n按B打开背包看看");
	M->f(5,sz+1) = new xz1();
	//
	sz += 2;
	for(uint i=1;i<=15;i++)
		M->f(i,sz+15) = new wall();
	for(uint i=sz+1;i<=sz+14;i++)
		M->f(6,i) = new wall();
	atree * T = new atree(3 , sz+3 , 0);
	T->apin(M);
	M->f(5,sz+2) = new grass('!' , "看见右上角那个\'T\'了吗?\n现在告诉你如何攻击它");
	M->f(3,sz+1) = new xz2();
	M->f(1,sz+14) = new xz3();
	M->f(1,sz+11) = new grass(';');
	M->f(2,sz+11) = new grass('^');
	M->f(3,sz+11) = new grass('~');
	M->f(4,sz+11) = new grass('`');
	M->f(5,sz+11) = new grass('#');
	//
	for(uint i=0;i<2;i++)
		M->f(6+i,sz+11) = new FakeWall();
	M->f(8,sz+11) = new wall();
	for(int i=sz+12;i<maxn-2;i++)
		M->f(7,i) = new FakeWall();
	for(int i=sz+10;i<maxn;i++)
		M->f(8,i) = new wall();
	M->f(7,sz+10) = new wall();
	//
	M->f(7,1) = new xz4();
	M->f(7,3) = new wall();
	for(uint i=1;i<=10;i++)
		M->f(8,i) = new wall();
	M->f(7,4) = new xz5();
	M->f(7,5) = new grass('!' , "现在受伤严重,按i使用治疗");
	M->f(7,9) = new xz6();
	M->f(9,3) = new grass('<');
	M->f(9,1) = new xz9();
	//彩蛋
	M->f(maxn-1 , 1) = new xz7();
	M->f(7,maxn-1) = new xz8();
}
