#include <bits/stdc++.h>
#include "h/city.h"
#include "h/city/firstcity.h"
static std::string infor = " press \'d\'";
int firstcity::xz0::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player*) P;
	pl->bag->coin_h(1000);
	say("","����1000���!\n���ڴ���\n",69);
	P->Px = 1;
	P->Py += 2;
	return 0;
}
int firstcity::xz1::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	player *pl = (player*) P;
	pl->bag->coin_h(100);
	say("","����100���!\n���ڴ���\n",69);
	P->Py+=2;
	return 0;
}
int firstcity::xz2::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	say("","����������\nȻ��j�����ķ����ƶ�\n��������200ms",89);
	return 0;
}
int firstcity::xz3::onein(people* P)
{
	if(P->m_typ == "player") 
		say("","����,��������!\n",69);
	P->Px = 7;
	P->Py = 1;
	return 0;
}
int firstcity::xz4::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	extern FILE* information;
	fprintf(information,"����������\n");
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
	fprintf(information,"�����߳�����\n");
	static int jsq = 0;
	if(!jsq) pl->magic_h(100);
	jsq ++;
	if(jsq == 20) P->Px += 2;
	return 0;
}
int firstcity::xz6::onein(people *P)
{
	if(P->m_typ != "player") return 0;
	say("��","��ϲ��������ͨ�������ֳǵĿ���,�´����һὫ���������,����......\n",79);
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
	say("","����ô�ߵ�������?",59);
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
	M->m_name = "���ֳ�firstcity";
	for(uint i=0;i<infor.size();i++)
		M->f(1,i+1) = new grass(infor[i] , "��������,��d���������ƶ�"),
		M->f(2,i+1) = new wall(),
		M->f(3,i+1) = new grass(infor[i]=='d'?'a':infor[i] , "ͬ���İ�a��������"),
		M->f(4,i+1) = new wall(),
		M->f(5,i+1) = new grass('>'),
		M->f(6,i+1) = new wall();
	M->f(1,infor.size()+1) = new grass('!' , "����������,��ᷢ�����޷��ƶ�,��Ϊ����ұ���Ȼ��һ��ǽ,���ڰ�s����");
	for(uint i=1;i<=4;i++)
		M->f(i , infor.size()+2) = new wall();
	M->f(4 , infor.size()+1) = new wall();
	M->f(3 , infor.size()+1) = new grass('!' , "��û�з����㿴�����������ȴ�¿������������?\n��ʵ��������Ϊ��������յ���ǽ���赲");
	M->f(4,1) = new grass('!' , "��ô�Լ����߰�");
	for(uint i=1;i<=5;i++)
		M->f(i,infor.size()+3) = new grass(' '),
		M->f(i,infor.size()+4) = new wall();
	for(uint i=infor.size()+1;i<=infor.size()+4;i++)
		M->f(6,i) = new wall(); 
	M->f(5,infor.size()+3) = new grass('!' , "����˵��Ҳ�ܲµ�,��w����");
	M->f(2,infor.size()+3) = new grass('!' , "��ȥ��");
	M->f(1,infor.size()+3) = new xz0();
	uint sz = infor.size() + 4;
	for(uint i=1;i<=6;i++)
		M->f(i,sz+2) = new wall();
	M->f(6,sz+1) = new wall();
	M->f(3,sz+1) = new grass('!' , "���Ƿ�ע�⵽�����˽��?\n��B�򿪱�������");
	M->f(5,sz+1) = new xz1();
	//
	sz += 2;
	for(uint i=1;i<=15;i++)
		M->f(i,sz+15) = new wall();
	for(uint i=sz+1;i<=sz+14;i++)
		M->f(6,i) = new wall();
	atree * T = new atree(3 , sz+3 , 0);
	T->apin(M);
	M->f(5,sz+2) = new grass('!' , "�������Ͻ��Ǹ�\'T\'����?\n���ڸ�������ι�����");
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
	M->f(7,5) = new grass('!' , "������������,��iʹ������");
	M->f(7,9) = new xz6();
	M->f(9,3) = new grass('<');
	M->f(9,1) = new xz9();
	//�ʵ�
	M->f(maxn-1 , 1) = new xz7();
	M->f(7,maxn-1) = new xz8();
}
