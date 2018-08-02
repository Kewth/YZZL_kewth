#include <bits/stdc++.h>
#include "h/more.h"
#include "h/bag.h"
#include "h/people.h"
int BAG::list()
{
	printf("金币:%d\n",coin);
	if(coin == max_coin) puts("(达到上限)");
	printf("元力:%d\n",yuanli);
	printf("木头:%d\n",wood);
	system("pause");
	return 0;
}
int BAG::coin_h(int oocoin)
{
	if(!oocoin) return coin;
	if((long long)coin + oocoin > max_coin) coin = max_coin;
	else if(coin + oocoin < 0)
	{
		printf("金币不足!!\n");
		return -1;
	}
	else coin += oocoin;
	if(oocoin > 0) messagebox(nullptr,("金币x"+number_str(oocoin)).c_str(),"获得：",MB_OK);
	return coin;
}
int BAG::yuanli_h(int ooyuanli)
{
	if(!ooyuanli) return yuanli;
	else if(yuanli + ooyuanli < 0)
	{
		printf("元力不足!!\n");
		return -1;
	}
	else yuanli += ooyuanli;
	if(ooyuanli > 0) messagebox(nullptr,("元力x"+number_str(ooyuanli)).c_str(),"获得：",MB_OK);
	return yuanli;
}
int BAG::wood_h(int oowood)
{
	if(!oowood) return wood;
	else if(wood + oowood < 0)
	{
		printf("木材不足!!\n");
		return -1;
	}
	else wood += oowood;
	if(oowood > 0) messagebox(NULL,("木头x"+number_str(oowood)).c_str(),"获得：",MB_OK);
	return wood;
}
BAG::BAG():coin(0),yuanli(0),wood(0),max_coin(1000000000) {}


void achievement::c_get(player * P , std::string name)
{
	if(m_achi.count(name))
	{
		messagebox(NULL,("--" + name + "--").c_str(),"已获得此成就:",MB_OK);
		return ;
	}
	else 
	{
		m_achi.insert(name);
		messagebox(NULL,("|-" + name + "-|").c_str(),"获得成就:",MB_OK);
		if(name == "first_find1") P->get_more_hpsx(500);
		else if(name == "first_find2") P->get_more_hpsx(500);
	}
}
void achievement::c_look(std::string name)
{
	system("cls");
	if(name == "first_find1") puts("解锁:在新手城中离开教程找到彩蛋1\n奖励:生命上限+500");
	else if(name == "first_find2") puts("解锁:在新手城中离开教程找到彩蛋2\n奖励:生命上限+500");
	else puts("未知成就..\n");
	system("pause");
}
void achievement::c_lookall()
{
	std::vector<std::string> acv;
	for(auto iter=m_achi.begin();iter!=m_achi.end();iter++)
		acv.push_back(*iter);
	for(uint begin=0 , page=1;;)
	{
		system("cls");
		printf("按对应数字查看详情\n按q退出,>下一页,<上一页\n");
		printf("第%d页:\n",page);
		for(uint i=begin;i<begin+10 && i<acv.size();i++)
			printf("%d.%s\n",i-begin,acv[i].c_str());
		int xz_num = getch();
		if(xz_num == 'q') break;
		if(xz_num == '>' && begin < acv.size()) { begin += 10; page ++; }
		else if(xz_num == '<' && begin >= 10) { begin -= 10; page --; }
		else xz_num -= '0';
		if(xz_num >= 0 && xz_num <= 9 && begin + xz_num < acv.size()) c_look(acv[begin + xz_num]);
	}
	system("pause");
}
