#include <bits/stdc++.h>
#include "h/people.h"
#include "h/shuju.h"
static void sj_Error()
{
	cgcolor("");
	debug_print("error:Get sj in error!");
	say("warning:","经反作弊系统检测,此账号的数据有被修改的嫌疑,是否能够恢复数据(y/n)?",79);
	if(csgetch())
	{
		say("warning:","请将数据恢复,否则此账号将面临作废的风险",79);
		system("pause");
		exit(0);
	}
	else 
	{
		say("warning:","很抱歉,你的账号因数据错误将被重置,确定重置(y/n)?",79);
		if(csgetch())
		{
			say("waning:","真的很抱歉,暂时没有自动重置,请运行fishrst.exe",79);
			system("pause");
			exit(0);
		}
		else
		{
			say("warning:","请将数据恢复,否则此账号将面临作废的风险",79);
			system("pause");
			exit(0);
		}
	}
}
int sjin(player * P ,std::string name)
{
	debug_print(name + " reading");
	extern std::string filepl;
	FILE * read = fopen((filepl+name+".dat").c_str() , "r");
	P->pet = new Dog(P->Px , P->Py-1 , 0);
	P->m_list = new list_jn();
	unsigned long long Hash_Number = P->Hash_Number();
	fscanf(read,"Hash_Number:%llu\n",&Hash_Number);
	fscanf(read,"LV:%d(EXP:%d)\n",&P->m_lv,&P->m_exp);
	fscanf(read,"HP:%d/%d\n",&P->m_hp,&P->m_hpsx);
	fscanf(read,"Magic:%d/%d\n",&P->m_magic,&P->m_magicsx);
	fscanf(read,"War:%d\n",&P->m_war);
	fscanf(read,"yuanli:%d\n",&P->bag->yuanli);
	fscanf(read,"coin:%d\n",&P->bag->coin);
	fscanf(read,"wood:%d\n",&P->bag->wood);
	fscanf(read,"jn_list:");
	std::vector<int> v;
	for(int i=0;i<list_jn::jnsl;i++)
	{
		int num = 0;
		fscanf(read," %d",&num);
		v.push_back(num);
	}
	fscanf(read,"\n");
	int num_achievement = 0;
	fscanf(read,"achievement_list(%d):\n",&num_achievement);
	for(int i=0;i<num_achievement;i++)
	{
		char s[20];
		fscanf(read,"%s\n",s);
		P->m_achi->m_achi.insert(s);
	}
	fscanf(read,"\n");
	fscanf(read,"PetEXP:%d\n",&P->pet->m_exp);
	P->pet->exp_h(0);
	
	P->m_list = new list_jn(v);
	P->m_I = P->m_list->jn[0];
	P->m_O = P->m_list->jn[1];
	P->m_U = P->m_list->jn[2];
	fclose(read);
	if(Hash_Number != P->Hash_Number())
		sj_Error();
	debug_print("read done");
	return 0;
}

int sjout(player * P,std::string name)
{
	debug_print(name + " writing");
	extern std::string filepl;
	FILE * write = fopen((filepl+name+".dat").c_str() , "w");
	fprintf(write,"Hash_Number:%llu\n",P->Hash_Number());
	fprintf(write,"LV:%d(EXP:%d)\n",P->m_lv,P->m_exp);
	fprintf(write,"HP:%d/%d\n",P->m_hp,P->m_hpsx);
	fprintf(write,"Magic:%d/%d\n",P->m_magic,P->m_magicsx);
	fprintf(write,"War:%d\n",P->m_war);
	fprintf(write,"yuanli:%d\n",P->bag->yuanli);
	fprintf(write,"coin:%d\n",P->bag->coin);
	fprintf(write,"wood:%d\n",P->bag->wood);
	fprintf(write,"jn_list:");
	for(int i=0;i<list_jn::jnsl;i++)
		fprintf(write," %d",P->m_list->jn[i]->m_lv);
	fprintf(write,"\n");
	fprintf(write,"achievement_list(%ld):\n",P->m_achi->m_achi.size());
	for(auto iter=P->m_achi->m_achi.begin();iter!=P->m_achi->m_achi.end();iter++)
		fprintf(write,"%s\n",iter->c_str());
	fprintf(write,"\n");
	fprintf(write,"PetEXP:%d\n",P->pet->m_exp);


	fclose(write);
	debug_print("write done");
	return 0;
}
