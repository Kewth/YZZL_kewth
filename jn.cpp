#include <bits/stdc++.h>
#include "h/more.h"
#include "h/jn.h"
#include "h/people.h"

// JN {{{ 
int JN::lvup()
{
	if(m_lv == m_lvmax)
	{
		messagebox(NULL,(m_name+"等级已满就不要瞎逼逼了,年轻人").c_str(),"技能",MB_OK);
		return -1;
	}
	m_lv ++;
	messagebox(NULL,(m_name+"升级").c_str(),"技能:",MB_OK);
	return 0;
}
int JN::doit(player * P)
{
	if(P->magic_h(-m_need[m_lv]) == -1)
	{
		fprintf(information,"魔法值不足!");
		return -1;
	}
	fprintf(information,"正在使用%s\n",m_name.c_str());
	P->upd();
	P->m_sta["stop"].first = clock() + m_tuse[m_lv];
	return rldo(P);
}
void JN::check(bool more)
{
	printf("%d级%s:",m_lv,m_name.c_str());
	if(m_lv == m_lvmax) printf("已满级") , more = 0;
	puts("");
	rlcheck(more);
	printf("准备时间:%d",m_tuse[m_lv]);
	if(more) printf("(下一级:%d)",m_tuse[m_lv+1]);
	puts("");
	printf("魔法值消耗:%d",m_need[m_lv]);
	if(more) printf("(下一级:%d)",m_need[m_lv+1]);
	puts("");
} // }}}

jn_hp::jn_hp(int lv) // {{{
{
	m_lvmax = 7;
	//const int val[]={45,100,200,400,800,1600,};
	//const int need[]={10,17,28,48,80,140,};
	//const int use[]={999,900,800,700,600,500,};
	//const int pay[]={2000,5000,12000,26000,60000,};
	const int val[]={90,205,500,510,910,950,1800,2100,};
	const int need[]={10,20,40,40,60,60,90,90,};
	const int use[]={1500,2200,4000,2000,2800,1400,2000,1100,};
	const int pay[]={3000,7000,20000,40000,70000,120000,180000,};
	memcpy(m_val,val,sizeof(val));
	memcpy(m_need,need,sizeof(need));
	memcpy(m_tuse,use,sizeof(use));
	memcpy(m_pay,pay,sizeof(pay));
	m_lv = lv;
	m_name = "治疗";
}
int jn_hp::rldo(player * P)
{
	P->c_hp(nullptr , m_val[m_lv]);
	return 0;
}
void jn_hp::rlcheck(bool more)
{
	printf("回复%d",m_val[m_lv]);
	if(more) printf("(下一级:%d)",m_val[m_lv+1]);
	puts("点生命");
} // }}}

list_jn::list_jn(std::vector<int> v) // {{{
{
	jn[0] = new jn_hp(v[0]);
	jn[1] = new jn_dikang(v[1]);
	jn[2] = new jn_throw_Stone(v[2]);
}
list_jn::list_jn()
{
	jn[0] = new jn_hp(0);
	jn[1] = new jn_dikang(0);
	jn[2] = new jn_throw_Stone(0);
} // }}}

jn_dikang::jn_dikang(int lv) // {{{
{
	m_lvmax = 7;
	/*
	const int val[]={45,85,165,320,620,1200,};
	const int val2[]={1800,2000,2200,2400,2600,2800,};
	const int need[]={10,17,28,48,80,140,};
	const int use[]={999,900,800,700,600,500,};
	const int pay[]={2000,5000,12000,26000,60000,};
	*/
	const int val[]={80,80,120,200,200,200,200,220,};
	const int val2[]={3000,6000,6000,7200,10500,10800,13400,14100,};
	const int need[]={10,20,30,50,70,70,70,70,};
	const int use[]={2000,1800,1200,1800,2100,1000,1000,1000,};
	const int pay[]={3000,7000,20000,40000,70000,120000,180000,};
	memcpy(m_val,val,sizeof(val));
	memcpy(m_val2,val2,sizeof(val2));
	memcpy(m_need,need,sizeof(need));
	memcpy(m_tuse,use,sizeof(use));
	memcpy(m_pay,pay,sizeof(pay));
	m_lv = lv;
	m_name = "抵抗";
}
int jn_dikang::rldo(player * P)
{
	P->m_sta["dikang"] = std::make_pair(clock() + m_val2[m_lv] , m_val[m_lv]);
	return 0;
}
void jn_dikang::rlcheck(bool more)
{
	printf("%d",m_val2[m_lv]);
	if(more) printf("(下一级:%d)",m_val2[m_lv+1]);
	printf("ms内抵抗%d",m_val[m_lv]);
	if(more) printf("(下一级:%d)",m_val[m_lv+1]);
	puts("点伤害");
} // }}}

jn_throw_Stone::jn_throw_Stone(int lv) // {{{
{
	m_lvmax = 7;
	//const int val[]={45,100,200,400,800,1600,};
	//const int need[]={10,17,28,48,80,140,};
	//const int use[]={999,900,800,700,600,500,};
	//const int pay[]={2000,5000,12000,26000,60000,};
	const int val[]={135,305,750,755,1365,1425,2700,3150,};
	const int need[]={10,20,40,40,60,60,90,90,};
	const int use[]={750,1100,2000,1000,1400,700,1000,550,};
	const int pay[]={3000,7000,20000,40000,70000,120000,180000,};
	memcpy(m_val,val,sizeof(val));
	memcpy(m_need,need,sizeof(need));
	memcpy(m_tuse,use,sizeof(use));
	memcpy(m_pay,pay,sizeof(pay));
	m_lv = lv;
	m_name = "投掷";
}
int jn_throw_Stone::rldo(player * P)
{
	extern std::vector<people*> Peo_will_do;
	people* st = new Stone(P,m_val[m_lv]);
	st->apin(P->m_inM);
	Peo_will_do.push_back(st);
	return 0;
}
void jn_throw_Stone::rlcheck(bool more)
{
	printf("投掷%d",m_val[m_lv]);
	if(more) printf("(下一级:%d)",m_val[m_lv+1]);
	puts("点伤害的石头");
} // }}}
