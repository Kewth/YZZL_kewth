#include <bits/stdc++.h>
#include "more.h"
#include "bag.h"
#include "jn.h"
class people;
class FLOOR;
class MAP;

class MAP // {{{
{
	private:
		const int _min,maxn;
	public:
		std::string m_name;
		_map2<people* > p;
		_map2<FLOOR* > f;
		char& operator () (int,int);
		int newfloor(int,int);
		int move(people*,char);
	MAP(int,int,std::string="荒野");//峳栰
	~MAP();
//	friend int player::look(MAP *M);
}; // }}}

class people // {{{
{
protected:
	int m_exp;
	int m_war ;
	int m_hpsx ;
	int turn_to_self;
	virtual void rc_hp(people*,int&,int) = 0;
	virtual void rc_introduce(print_inF&) = 0;
	virtual void rc_chat_with(player *) = 0;
	virtual void rc_die(people*) = 0;
public:
	int m_hp;
	int m_lv;
	BAG * bag;
	std::mutex m_mut_leave;
	/* std::mutex m_mut_move; */
	std::map<std::string , std::pair<int,int> > m_sta;
	std::string belong;
	std::string m_typ;
	std::string m_name;
	/* boss0 *B; */
	MAP *m_inM;
	std::string color;
	int Px,Py;
	char face , flag;
	virtual int meet(people*) = 0;
	virtual int move(char=' ');
	int apin(MAP*);
	int leave(MAP*);
	virtual int look(MAP*) = 0;
	virtual void introduce(player * = nullptr);
	void get_more_war(int);
	void get_more_hpsx(int);
	void upd();
	bool c_hp(people *,int,int='o');
	int c_hpmax();
	int c_war();
	virtual void exp_h(int) = 0;
	virtual int speed() = 0;
	int Todo();
	char reflag(char);
	people();
	friend int sjin(player * P,std::string name);
	friend int sjout(player * P,std::string name);
	/* people(int,int); */
}; // }}}

class FLOOR // {{{
{
	private:
		virtual void rl_introduce() = 0;
	public:
		int Px,Py;
		char face;
		std::string color;
		virtual int onein(people*) = 0;
		virtual bool cansee(people*) = 0;
		void introduce();
	FLOOR() {}
	FLOOR(int Px,int Py):Px(Px),Py(Py) {}
}; // }}}

class wall:public FLOOR
{
private:
	void rl_introduce();
public:
	int onein(people*);
	bool cansee(people*);
	wall();
};

class grass:public FLOOR
{
private:
	void rl_introduce();
	std::string infor;
public:
	bool cansee(people*);
	int onein(people*);
	grass(char c='.',std::string inm="") { face=c; infor = inm; color = "02"; }
};

class Door : public FLOOR
{
protected:
	void rl_introduce();
	bool isopen;
	std::string belong;
	void open_change();
public:
	bool cansee(people*);
	int onein(people*);
	Door(std::string);
};

class FakeWall : public FLOOR
{
private:
	void rl_introduce();
public:
	int onein(people*);
	bool cansee(people*);
	FakeWall();
};

// player {{{
class player:public people
{
private:
	std::string IO_name;
	std::queue<int> m_hpinfor;
	int m_lianji;
	std::mutex m_look_mut;
	/* bool will_check; */
	_map2<int> cansee;
	int m_magic;
	/* bool m_looked; */
	bool _cans(MAP*,int,int,bool);
	void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	void rc_die(people*);
	char pface(char);
public:
	static const int FIR_war = 10;
	static const int FIR_hp = 200;
	static const int FIR_magic = 20;
	people *pet;
	achievement *m_achi;
	int ready_fight;
	int check_print_open;
	JN *m_I , *m_O , *m_U;
	list_jn * m_list;
	int m_magicsx;
	int meet(people*);
	int look(MAP *);
	void introduce(player * = nullptr);
	void check_print();
	void exp_h(int);
	int call_pet(MAP *);
	virtual int move(char=' ');
	int magic_h(int);
	int speed();
	/* bool c_hp(people*,int,int='o'); */
	player(int,int,std::string);
	~player();
	friend int sjin(player * P,std::string name);
	friend int sjout(player * P,std::string name);
};
// }}}

// Dog {{{
class Dog : public people
{
protected:
	virtual void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	virtual void rc_die(people*);
public:
	static const int FIR_war = 13;
	static const int FIR_hp = 140;
	int meet(people*);
	int look(MAP *);
	void exp_h(int);
	int speed();
	Dog(int,int,int,std::string="space");
};
// }}}

// pig {{{
class pig:public people
{
private:
	virtual void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	virtual void rc_die(people*);
public:
	static const int FIR_war = 12;
	static const int FIR_hp = 200;
	int meet(people*);
	int look(MAP *);
	void exp_h(int);
	int speed();
	pig(int,int,int,std::string="fight");
};
// }}}

// snake {{{
class snake:public people
{
private:
	virtual void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	virtual void rc_die(people*);
	bool _cans(MAP*,int,int,bool);
public:
	static const int FIR_war = 15;
	static const int FIR_hp = 180;
	int meet(people*);
	int look(MAP *);
	void exp_h(int);
	int speed();
	snake(int,int,int,std::string="fight");
};
// }}}

// Tree_guard {{{
class Tree_guard:public people
{
private:
	virtual void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	virtual void rc_die(people*);
	bool _cans(MAP*,int,int,bool);
public:
	static const int FIR_war = 15;
	static const int FIR_hp = 10;
	int meet(people*);
	int look(MAP *);
	void exp_h(int);
	int speed();
	Tree_guard(int,int,int,std::string="tree");
};
// }}}

// atree {{{
class atree:public people
{
private:
	virtual void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	virtual void rc_die(people*);
public:
	static const int FIR_war = 0;
	static const int FIR_hp = 400;
	int meet(people*);
	int look(MAP *);
	void exp_h(int);
	int speed();
	atree(int,int,int,std::string="tree");
	~atree() {}
};
// }}}

// Zi_dan {{{
class Zi_dan : public people
{
protected:
	people *host;
	void rc_hp(people*,int&,int);
	void rc_introduce(print_inF&);
	void rc_chat_with(player *);
	void rc_die(people*);
	virtual void rc_meet(people*) = 0;
public:
	int meet(people*);
	virtual int look(MAP*) = 0;
	void exp_h(int);
	virtual int speed() = 0;
	Zi_dan();
}; // }}}

// Stone {{{
class Stone : public Zi_dan
{
private:
	void rc_meet(people*);
	int dist;
public:
	static const int FIR_war = 100;
	int look(MAP*);
	int speed();
	Stone(people*,int);
}; // }}}

//const int psl = 5;
//static FLOOR* ALLP[psl] = {new wall(),new grass(),new grass(),new grass(),new grass(),};
const char MOVE[4] = {'w' , 's' , 'a' , 'd'}; 
const int movex[4] = {-1 , 1 , 0 , 0};
const int movey[4] = {0 , 0 , -1 , 1};
