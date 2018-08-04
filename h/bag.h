#ifndef BAG_H
#define BAG_H
#include <bits/stdc++.h>
class player;
class BAG
{
private:
	bool print_mess;
	int coin;
	const int max_coin;
	int yuanli;
	int wood;
public:
	int list();
	int coin_h(int);
	int yuanli_h(int);
	int wood_h(int);
	friend int sjin(player * P,std::string name);
	friend int sjout(player * P,std::string name);
	BAG(bool=false);
};

class achievement 
{
private:
	std::set<std::string> m_achi;
	void c_look(std::string);
public:
	void c_get(player * , std::string);
	void c_lookall();
	friend int sjin(player * P,std::string name);
	friend int sjout(player * P,std::string name);
};
#endif
