#include <bits/stdc++.h>
#include "h/more.h"
#include "h/bag.h"
#include "h/people.h"
int BAG::list()
{
	printf("���:%d\n",coin);
	if(coin == max_coin) puts("(�ﵽ����)");
	printf("Ԫ��:%d\n",yuanli);
	printf("ľͷ:%d\n",wood);
	system("pause");
	return 0;
}
int BAG::coin_h(int oocoin)
{
	if(!oocoin) return coin;
	if((long long)coin + oocoin > max_coin) coin = max_coin;
	else if(coin + oocoin < 0)
	{
		printf("��Ҳ���!!\n");
		return -1;
	}
	else coin += oocoin;
	if(oocoin > 0) messagebox(nullptr,("���x"+number_str(oocoin)).c_str(),"��ã�",MB_OK);
	return coin;
}
int BAG::yuanli_h(int ooyuanli)
{
	if(!ooyuanli) return yuanli;
	else if(yuanli + ooyuanli < 0)
	{
		printf("Ԫ������!!\n");
		return -1;
	}
	else yuanli += ooyuanli;
	if(ooyuanli > 0) messagebox(nullptr,("Ԫ��x"+number_str(ooyuanli)).c_str(),"��ã�",MB_OK);
	return yuanli;
}
int BAG::wood_h(int oowood)
{
	if(!oowood) return wood;
	else if(wood + oowood < 0)
	{
		printf("ľ�Ĳ���!!\n");
		return -1;
	}
	else wood += oowood;
	if(oowood > 0) messagebox(NULL,("ľͷx"+number_str(oowood)).c_str(),"��ã�",MB_OK);
	return wood;
}
BAG::BAG():coin(0),yuanli(0),wood(0),max_coin(1000000000) {}


void achievement::c_get(player * P , std::string name)
{
	if(m_achi.count(name))
	{
		messagebox(NULL,("--" + name + "--").c_str(),"�ѻ�ô˳ɾ�:",MB_OK);
		return ;
	}
	else 
	{
		m_achi.insert(name);
		messagebox(NULL,("|-" + name + "-|").c_str(),"��óɾ�:",MB_OK);
		if(name == "first_find1") P->get_more_hpsx(500);
		else if(name == "first_find2") P->get_more_hpsx(500);
	}
}
void achievement::c_look(std::string name)
{
	system("cls");
	if(name == "first_find1") puts("����:�����ֳ����뿪�̳��ҵ��ʵ�1\n����:��������+500");
	else if(name == "first_find2") puts("����:�����ֳ����뿪�̳��ҵ��ʵ�2\n����:��������+500");
	else puts("δ֪�ɾ�..\n");
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
		printf("����Ӧ���ֲ鿴����\n��q�˳�,>��һҳ,<��һҳ\n");
		printf("��%dҳ:\n",page);
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
