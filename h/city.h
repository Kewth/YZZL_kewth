#ifndef CITY_H
#define CITY_H
#include <bits/stdc++.h>
#include "people.h"
#include "shuju.h"
extern std::string filepl;
/* extern FILE *information; */
class city
{
protected:
	class xz:public FLOOR
	{
	protected:
		virtual void rl_introduce()
		{
			print_inF Kuang(Pos(1,1) , Pos(4,30) , Pos(1,1));
			Kuang.clear();
			printf("???");
			Kuang.tonext();
			printf("过去看看是最高效的检验方式");
			Kuang.tonext();
			system("pause");
		}
	public:
		virtual int onein(people*) = 0;
		virtual bool cansee(people*) { return true; }
		xz() { face = 'O'; color = "01";  };
	};
public:
	MAP *M;
	const int maxn;
	virtual int move(people *P , char fg)
	{
		static int w_times = 0;
		w_times ++;
		player * PL = (player*) P;
		if(w_times == 30) sjout(PL , "common") , w_times = 0;
		return M->move(P,fg);
	}
	virtual void newmap(std::string files)
	{
		std::ifstream fin;
		fin.open((filepl+files).c_str());
		std::string s;
		getline(fin,s);
		for(int i=1;!s.empty() && i<=23;i++)
		{
			for(uint j=0;j<s.size() && j<23;j++)
				M->f(i,j+1) = new grass(s[j]);
			getline(fin,s);
		}
		for(uint i=1;i<=10;i++)
			M->f(maxn-6 , i) = new Door("space");
	}
	city():maxn(30) { M = new MAP(0,maxn); }
	virtual ~city() {}
};
class gotocity:public grass
{
	private:
		int returnid;
		int newx,newy;
	public:
		gotocity(int id,int newx,int newy,int fc):returnid(id + 100),newx(newx),newy(newy) { face = fc; }
		int onein(people* P) { if(P->m_typ != "player") return 0; P->Px = newx; P->Py = newy; return returnid; }
};
int xz_yangshen(people *);
#define xz_of_city(id)  class xz##id:public xz \
		{ \
			public: \
				static std::string name; \
				int onein(people *); \
				xz##id() {}; \
		}
#endif
