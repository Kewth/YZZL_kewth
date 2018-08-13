#include <bits/stdc++.h>
#include "h/city.h"
#include "h/city/firstcity.h"
static std::string infor = " press \'d\'";
int firstcity::xz0::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player*) P;
	pl->bag->coin_h(100);
	say("","奖励100金币!\n正在传送\n",69);
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
	if(jsq >= 10) P->Py += 3;
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
	if(jsq >= 20) P->Px += 2;
	return 0;
}
int firstcity::xz6::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	say("向导","恭喜你总算是通过了新手城的考验,下次来我会将你带到主城,那里......\n咳咳,你学会的仅仅是基本操作,在主城找到我(Q),我会告诉你接下来该怎么做\n",79);
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
int firstcity::xz10::onein(people *P)
{
	P->Px = 9;
	P->Py = 5;
	return 0;
}
firstcity::firstcity()
{
	for(int i=1;i<maxn;i++)
		for(int j=1;j<maxn;j++)
			M->f(i,j) = new grass(' ');
	/* int mid = maxn >> 1; */
	M->m_name = "新手城firstcity";
	// 移动教程 {{{
	for(uint i=0;i<infor.size();i++)
		M->f(1,i+1) = new grass(infor[i] , "如你所见,按d可以向右移动\n那个移动的绿色的D是你的宠物,不会产生敌意"),
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
	M->f(4,1) = new grass('!' , "那么自己走走吧"); // }}}
	// 背包使用教程 {{{
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
	// }}}
	// 攻击教程 {{{
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
	M->f(5,sz+11) = new grass('#'); // }}}
	// 彩蛋 {{{
	for(uint i=0;i<2;i++)
		M->f(6+i,sz+11) = new FakeWall();
	M->f(8,sz+11) = new wall();
	for(int i=sz+12;i<maxn-2;i++)
		M->f(7,i) = new FakeWall();
	for(int i=sz+10;i<maxn;i++)
		M->f(8,i) = new wall();
	M->f(7,sz+10) = new wall(); // }}}
	// 技能教程 {{{
	M->f(7,1) = new xz4();
	M->f(7,3) = new wall();
	for(uint i=1;i<=10;i++)
		M->f(8,i) = new wall();
	M->f(7,4) = new xz5();
	M->f(7,5) = new grass('!' , "现在受伤严重,按i使用治疗");
	M->f(7,9) = new xz10();
	M->f(7,10) = new wall();
	M->f(9,3) = new grass('<');
	M->f(9,1) = new xz9(); // }}}
	// 宠物+状态栏教程 {{{
	M->f(9,4) = new wall();
	M->f(10,4) = new wall();
	sz = 17;
	for(uint i=0;i<sz;i++)
		M->f(11 , i+3) = new wall();
	M->f(9,6) = new grass('!' , "事实上你有一只宠物,嗯之前说过了,你也一定看见了");
	M->f(9,7) = new grass('!' , "但是你走的太快,它跟不上来了");
	M->f(9,8) = new grass('!' , "不要激动我的意思不是要你回去,事实上有更简单的办法");
	M->f(9,9) = new grass('!' , "很简单,按一下c(意思是call)\n而如果你想让它停下来,按两下c");
	M->f(9,10) = new grass('!' , "想详细了解你的宠物?朝它移动就行,试试\n!!!注意,是移动不是攻击!!!(肯定有熊孩子把这个当做一个提示的)");
	M->f(9,11) = new grass('!' , "事实上,朝任何生物移动,都会得到一个介绍");
	M->f(9,12) = new grass('!' , "怎么得到自己的详细信息?\n右上角不够你看的吗?");
	M->f(9,13) = new grass('!' , "如果真的觉得不够,那就按Z(大写,意思是Zhuangtai)吧");
	for(int i=6;i<=13;i++)
		M->f(10,i) = new grass(*((grass*)M->f(9,i)));
	/* M->f(9,sz+3) = new xz11(); */
	/* M->f(10,sz+3) = new xz11(); */
	// }}}
	// 门的使用教程 {{{
	for(int i=7;i<=13;i++)
		M->f(i,sz+4) = new wall();
	for(uint i=0;i<=sz+1;i++)
		M->f(14,i+4) = new wall();
	M->f(12,sz-3) = new Door("space");
	M->f(13,sz-3) = new Door("space");
	M->f(12,sz-4) = new grass('!' , "黄色的是什么?那是门");
	M->f(13,sz-5) = new grass('!' , "显然你已经轻松的掌握如何开门,和你想象的一样,撞一下,人过去门就自动关了");
	M->f(12,sz-6) = new grass('!' , "事实上之所以你能如此轻松的开门,是因为这个门的\"阵营\"与你一致");
	M->f(13,sz-7) = new grass('!' , "你右边这扇门就打不开了吧,原因你应该完全明白了");
	M->f(13,sz-6) = new Door("TEST");
	M->f(12,sz-8) = new grass('!' , " 这也意味着,与你敌对的势力无法通过与你同势力的门");
	M->f(12,5) = new xz6();
	M->f(13,5) = new xz6();
	// }}}
	//彩蛋位置 {{{
	M->f(maxn-1 , 1) = new xz7();
	M->f(7,maxn-1) = new xz8(); // }}}
}
