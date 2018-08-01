#ifndef JN_H
#define JN_H NULL
#include <bits/stdc++.h>
class player;
class JN
{
	private:
	static const int lvmax = 7;
	protected:
	virtual void rlcheck(bool) = 0;
	public:
	int m_need[lvmax+1];
	int m_val[lvmax+1];
	int m_tuse[lvmax+1];
	int m_pay[lvmax];
	int m_lvmax;
	int m_lv;
	std::string m_name;
	virtual int doit(player *);
	virtual int rldo(player *) = 0;
	virtual int lvup();
	virtual void check(bool = 0);
};
class jn_hp:public JN
{
	protected:
	void rlcheck(bool);
	public:
	int rldo(player *);
	jn_hp(int=0);
};
class jn_dikang:public JN
{
	protected:
	int m_val2[8];
	void rlcheck(bool);
	public:
	int rldo(player *);
	jn_dikang(int=0);
};
class list_jn
{
	private:
	public:
	static const int jnsl = 2;
	JN* jn[jnsl];
	list_jn();
	list_jn(std::vector<int>);
};
#endif
