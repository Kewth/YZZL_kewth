#ifndef BAG_H
#define BAG_H
#include <bits/stdc++.h>
class player;
class BAG
{
private:
	bool print_mess;
	int coin;
	int yuanli;
	int wood;
	const int max_coin;
public:
	int list();
	void clear();
	void add_an(BAG *);
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
