#include <bits/stdc++.h>
#include "h/more.h"
#include "h/city.h"
#include "h/city/workcity.h"
int workcity::xz0::onein(people*)
{
	return 3;
}
int workcity::xz1::onein(people* P)
{
	if(P->m_typ != "player")
	{
		fprintf(information , "%s�������һЩ��ֵĶ���\n",P->m_name.c_str());
		return 0;
	}
	say("","�����������Ŀ¼...",69);
	system(("xdg-open " + filepl +" 2> /dev/null").c_str());
	return 0;
}
int workcity::xz2::onein(people *P)
{
	if(P->m_typ != "player")
	{
		fprintf(information , "%s�������һЩ��ֵĶ���\n",P->m_name.c_str());
		return 0;
	}
	extern std::string ftppl;
	say("","�����������Ŀ¼...",69);
	puts(ftppl.c_str());
	system(("xdg-open " + ftppl +" 2> /dev/null").c_str());
	return 0;
}
workcity::workcity()
{
	newmap("workcity.txt");
	int mid = maxn >> 1;
	M->m_name = "����workcity";
	M->f(mid,0) = new gotocity(0,mid,maxn,'<');
	M->f(mid,-1) = new wall();
	M->f(mid,1) = new grass('-');
	M->f(maxn-5,1) = new xz0();
	for(uint i=0;i<xz0::name.size();i++)
		M->f(maxn-5,i+2) = new grass(xz0::name[i],"�ɴ��˳�");
	M->f(maxn-4,1) = new xz1();
	for(uint i=0;i<xz1::name.size();i++)
		M->f(maxn-4,i+2) = new grass(xz1::name[i],"�ɴ˴�����Ŀ¼");
	M->f(maxn-3,1) = new xz2();
	for(uint i=0;i<xz2::name.size();i++)
		M->f(maxn-3,i+2) = new grass(xz2::name[i],"�ɴ˴򿪴˰汾������ƽ̨");
}
std::string workcity::xz0::name = "exit";
std::string workcity::xz1::name = "open_dir";//QwQ
std::string workcity::xz2::name = "open_ftp";//QwQ
