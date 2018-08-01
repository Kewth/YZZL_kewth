#ifndef BOSS_H
#define BOSS_H NULL
#include <bits/stdc++.h>
class people;
class player;
extern FILE* information;
class boss0
{
	protected:
		int m_lv;
		int m_war;
		int m_get;
		int m_spc;
		virtual void rc_hp(int&,char='o')=0;
		virtual void rc_war()=0;
		virtual void rspc(int)=0;
		virtual void rlose(int&,int&,int&,float)=0;
	public:
		std::string m_name;
		int m_hpsx;
		int m_hp;
		virtual bool c_hp(int,char='o');
		virtual int c_war();
		virtual bool spc(people*);
		virtual bool lose(player*);
};
class combs:public boss0
{
	private:
	protected:
		void rc_hp(int &,char='o');
		void rc_war();
		void rspc(int) {};
		void rlose(int&,int&,int&,float);
	public:
		combs(int);
};

class boss1:public boss0
{
	private:
		int m_jn1;
		bool m_jn2;
	protected:
		void rc_hp(int &,char='o');
		void rc_war();
		void rspc(int) {};
		void rlose(int&,int&,int&,float);
	public:
		boss1(int);
};
class plboss:public boss0
{
	private:
	protected:
		void rc_hp(int &,char='o');
		void rc_war();
		void rspc(int) {};
		void rlose(int&,int&,int&,float);
	public:
		bool c_hp(int,char='o');
		plboss(int,int=0,int=0);
		void lv_up();
	friend class player;
	friend int sjin(player*,std::string);
	friend int sjout(player*,std::string);
};
class treebs:public boss0
{
	private:
	protected:
		void rc_hp(int &,char='o');
		void rc_war();
		void rspc(int) {};
		void rlose(int&,int&,int&,float);
	public:
		treebs(int);
};
class dogbs : public boss0
{
private:
protected:
	void rc_hp(int &,char='o');
	void rc_war();
	void rspc(int) {};
	void rlose(int&,int&,int&,float);
public:
	dogbs(int);
};




#endif
