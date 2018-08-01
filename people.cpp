#include <bits/stdc++.h>
#include "h/const.h"
#include "h/more.h"
#include "h/people.h"
#include "h/shuju.h"

// MAP {{{
char& MAP::operator () (int x,int y) { return p(x,y)->face; }
int MAP::move(people *P,char flag)
//1:kill someone
//2:cannot move or do not move
//3:exit
{
	debug_print("debug:people"+P->m_name+"move in"+m_name+"->");
	int leave_res = P->leave(this);
	int Px = P->Px,Py = P->Py , res=0 , now = clock();
	int mres;
	if(leave_res == 1) mres = 2;
	else if(now < P->m_sta["back"].first) mres = P->move(P->m_sta["back"].second);
	else if(now >= P->m_sta["stop"].first) mres = P->move(flag);
	else mres = 2;
	/* debug_print("debug:move1");//debug */
	if(mres == 2)
	{
		P->apin(this);
		debug_print("debug:people"+P->m_name+"move in"+m_name+" and do nothing<-");
		return 2;
	}
	if(P->m_typ == "player")
	{
		player *pl = (player *) P;
		if(pl->pet->m_inM == this)
			this ->move(pl->pet , ' ');
	}
	bool back = 0;
	/* debug_print("debug:move2");//debug */
	people *meet_p = p(P->Px , P->Py);
	if(meet_p && meet_p != P)
	{
		if(meet_p -> m_mut_leave . try_lock())
		{
			if(now < meet_p->m_sta["tishen"].first)
			{
				meet_p -> m_mut_leave . unlock();
				this->move(meet_p , meet_p->m_sta["tishen"].second);
				this->move(meet_p , meet_p->m_sta["tishen"].second);
			}
			else if(meet_p == p(P->Px , P->Py))
			{
				back = 1;
				/* debug_print("debug:meet1");//debug */
				int pres = P->meet(meet_p);
				/* debug_print("debug:meet2");//debug */
				if(pres == 1)
				{
					res = 1;
					if(!p(P->Px , P->Py)) debug_print("error:map中没有要离开的位置,位置" + number_str(P->Px) + "," + number_str(P->Py));
					else
						/* debug_print("debug:p_leave"), */
						meet_p -> m_mut_leave . unlock(),
						meet_p -> leave(this);
				}
				meet_p -> m_mut_leave . unlock();
			}
			else meet_p -> m_mut_leave . unlock();
		}
		else fprintf(information , "%s精准闪避!\n",meet_p->m_name.c_str());
	}
	/* debug_print("debug:meet3");//debug */
	if(!f(P->Px,P->Py))
	{
		debug_print("error:没有地面,发生在"+this->m_name+number_str(P->Px)+","+number_str(P->Py));
		return -1;
	}
	if(!back)
	{
		int fres = f(P->Px,P->Py)->onein(P);
		if(fres == 1) back = 1;
		else if(fres == 3) res = 3;
		else if(fres >= 100 && fres <= 200) res = fres;
	}
	if(back) P->Px = Px , P->Py = Py;
	P->apin(this);
	debug_print("debug:people"+P->m_name+"move in"+m_name+"<-");
	return res;
}
int MAP::newfloor(int x,int y)
{
	int rd = rand()%1000;
	if(rd <100) f(x,y) = new wall();
	else if(rd <1000) f(x,y) = new grass();
	return 0;
}
static int linked(MAP *M,_map2<bool> *vis,int x,int y)
{
	if(M->f(x,y)->face == '#') return 0;
	int res = M->f(x,y)->face=='.';
	(*vis)(x,y) = 1;
	for(int i=0;i<4;i++)
	{
		int tx = x + movex[i] , ty = y + movey[i];
		if(!(*vis)(tx,ty)) res +=  linked(M,vis,tx,ty);
	}
	return res;
}
MAP::MAP(int mins,int _maxn,std::string name):_min(mins),maxn(_maxn),m_name(name)
{
	while(1)
	{
		int floorsl = 0;
		for(int i=mins;i<=maxn;i++)
			for(int j=mins;j<=maxn;j++)
			{
				if(i == mins || j == mins || i==maxn || j==maxn) f(i,j) = new wall();
				else newfloor(i,j);
				floorsl += f(i,j)->face == '.';
			}
		_map2<bool> *vis = new _map2<bool>;
		int lres = linked(this,vis,mins+1,mins+1);
		if(lres == floorsl) break;
		else
		{
			printf("MAP make error:%d(ex%d)\n",lres,floorsl);
			debug_print("warning:地图死角,联通大小"+number_str(lres)+"期待"+number_str(floorsl));
			if(maxn-mins == 4)
			{
				for(int i=mins;i<=maxn;i++,puts(""))
					for(int j=mins;j<=maxn;j++)
						putchar(f(i,j)->face);
				for(int i=mins;i<=maxn;i++,puts(""))
					for(int j=mins;j<=maxn;j++)
						printf("%d",(*vis)(i,j));
			}
		}
		delete vis;
	}
}
// }}}

// FLOOR {{{
void FLOOR::introduce()
{
	rl_introduce();
}
// }}}

// wall {{{
wall::wall()
{
	face = '#';
	color = "70";
}
int wall::onein(people* P) { P->move(P->reflag(P->flag)); return 0; }
bool wall::cansee(people*) { return false; }
void wall::rl_introduce()
{
	print_inF Kuang(Pos(1,1) , Pos(6,30) , Pos(1,1));
	Kuang.clear();
	printf("WALL:");
	Kuang.tonext();
	printf("显而易见,这是一堵墙");
	Kuang.tonext();
	printf("它不仅无法经过");
	printf("而且会挡住你的视野");
	Kuang.tonext();
	system("pause");
}
// }}}

// grass {{{
int grass::onein(people* P)
{
	if(P->m_typ != "player") return 0;
	extern FILE* information;
	if(!infor.empty()) fprintf(information,"%s\n",infor.c_str());
	return 0;
}
bool grass::cansee(people *) { return true; }
void grass::rl_introduce()
{
	print_inF Kuang(Pos(1,1) , Pos(5,30) , Pos(1,1));
	Kuang.clear();
	printf("Grass:");
	Kuang.tonext();
	printf("这里是一块标有%c的草地",this->face);
	if(!this->infor.empty())
	{
		Kuang.tonext();
		printf("而且这上面似乎有什么信息...");
	}
	Kuang.tonext();
	system("pause");
}
// }}}

// Door {{{
Door::Door(std::string bl):isopen(false),belong(bl)
{
	face = '+';
	color = "60";
}
int Door::onein(people *P)
{
	if(not isopen)
		P->move(P->reflag(P->flag));
	if(P->belong == belong)
		open_change();
	return 0;
}
void Door::open_change()
{
	if(isopen)
		isopen = false ,
		color = "60";
	else
		isopen = true ,
		color = "06";
}
bool Door::cansee(people *) { return isopen; }
void Door::rl_introduce()
{
	print_inF Kuang(Pos(1,1) , Pos(5,30) , Pos(1,1));
	Kuang.clear();
	printf("Door:");
	Kuang.tonext();
	printf("这是一扇正%s着的门",this->isopen?"开":"关");
	Kuang.tonext();
	printf("它是由%s阵营创造的",this->belong.c_str());
	Kuang.tonext();
	system("pause");
}
// }}}

// FakeWall {{{
FakeWall::FakeWall()
{
	face = '#';
	color = "70";
}
int FakeWall::onein(people *) { return 0; }
bool FakeWall::cansee(people*) { return false; }
void FakeWall::rl_introduce()
{
	if(rand() % 2)
	{
		wall duce_wall;
		duce_wall.introduce();
		return;
	}
	print_inF Kuang(Pos(1,1) , Pos(5,30) , Pos(1,1));
	Kuang.clear();
	printf("FakeWall!");
	Kuang.tonext();
	printf("Ops!!!震惊!!!");
	Kuang.tonext();
	printf("这玩意长得和墙一模一样");
	Kuang.tonext();
	printf("而且也能阻挡视线");
	Kuang.tonext();
	printf("但是它竟然可以随意通过!!!");
}
// }}}

// people {{{
// people 构造 {{{
people::people():flag('w')
{
	const int stasl = 4;
	int now = clock();
	std::string s[stasl] = {"dikang" , "back" , "stop", "tishen"};
	for(int i=0;i<stasl;i++)
		m_sta[s[i]].first = now;
} // }}}
void people::upd() // {{{
{
	return ;
	int now = clock()-1;
	const int stasl = 3;
	std::string s[stasl] = {"dikang","back","stop"};
	for(int i=0;i<stasl;i++)
		m_sta[s[i]] = std::make_pair(std::max(m_sta[s[i]].first , now) , m_sta[s[i]].second);
} // }}}
int people::move(char fg) // {{{
//2:not move
{
	//if(m_sta["stop"].first > clock()) return 2;
	//else upd();
	int res = 0;
	if(fg==' ') fg = this->flag , res = 1;
	if(fg == 'w') Px--;
	else if(fg == 's') Px++;
	else if(fg == 'd') Py++;
	else if(fg == 'a') Py--;
	else return 2;
	flag = fg;
	return res;
} // }}}
void people::introduce() // {{{
{
	print_inF Kuang(Pos(1,1) , Pos(7,34) , Pos(1,1));
	Kuang.clear();
	printf("%s:",m_name.c_str());
	Kuang.tonext();
	printf("所属阵营:%s",belong.c_str());
	Kuang.tonext();
	printf("生命值:%d/%d",m_hp,c_hpmax());
	Kuang.tonext();
	printf("伤害值:%d",c_war());
	Kuang.tonext();
	system("pause");
} // }}}
int people::apin(MAP* M) // {{{
{
	debug_print("debug:people"+m_name+"出现"+M->m_name+"("+number_str(Px)+","+number_str(Py)+")->");
	m_inM = M;
	people *t_p = M->p(Px , Py);
	int res = 0;
	if(t_p)
	{
		debug_print("warning:重复出现:"+t_p->m_name);
		/* m_mut_leave.unlock(); */
		res = 1;
	}
	else M->p(Px,Py) = this;
	if(!M->f(Px,Py))
	{
		debug_print("warning:出生无地面");
		M->f(Px,Py) = new grass();
		/* m_mut_leave.unlock(); */
		res = 1;
	}
	m_mut_leave.unlock();
	debug_print("debug:people"+m_name+"出现"+M->m_name+"<-");
	return res;
} // }}}
int people::leave(MAP *M) // {{{
//1: 无法离开
{
	debug_print("debug:people"+m_name+"离开"+M->m_name+"("+number_str(Px)+","+number_str(Py)+")->");
	if(!M)
		return -1;
	int res = 0;
	if(m_mut_leave.try_lock())
	{
		if(!M->p(Px,Py))
		{
			debug_print("error:在此之前提前离开,发生在"+number_str(Px)+","+number_str(Py));
			return -1;
		}
		else if(M->p(Px , Py) != this)
		{
			debug_print("error:离开位置已被抢占,发生在"+number_str(Px)+","+number_str(Py));
			res = -1;
		}
		else
			M->p(Px, Py) = nullptr;
	}
	else fprintf(information , "%s被牵制无法移动!\n",m_name.c_str()) , res = 1;
	/* m_inM = nullptr; */
	debug_print("debug:"+m_name+"离开"+M->m_name+"<-");
	return res;
} // }}}
bool people::c_hp(people *from_p,int val,int typ) // {{{
{
	int now = clock();
	if(now < m_sta["dikang"].first && typ != 'r' && val < 0)
		val = std::min(0 , val + m_sta["dikang"].second);
	rc_hp(from_p , val , typ);
	m_hp += val;
	if(m_hp <= 0)
	{
		rc_die(from_p);
		m_hp = 0;
		return true;
	}
	if(m_hp > c_hpmax())
		m_hp = c_hpmax();
	return false;
} // }}}
void people::get_more_war(int cg) // {{{
{
	m_war += cg;
	if(m_typ == "player") messagebox(NULL,("伤害提高"+number_str(cg)).c_str(),"能力增强:",MB_OK);
} // }}}
void people::get_more_hpsx(int cg) // {{{
{
	m_hpsx += cg;
	if(m_typ == "player") messagebox(NULL,("生命上限"+number_str(cg)).c_str(),"能力增强:",MB_OK);
} // }}}
int people::c_hpmax() // {{{
{
	return m_hpsx;
} // }}}
int people::c_war() // {{{
{
	return m_war;
} // }}}
char people::reflag(char c) // {{{
{
	if(c == 'w') return 's';
	if(c == 's') return 'w';
	if(c == 'a') return 'd';
	if(c == 'd') return 'a';
	else return ' ';
} // }}}
// }}}

// player {{{
int player::meet(people* P) // {{{
//1:kill
{
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"->");
	//std::lock_guard<std::mutex> lock(P->m_mut_leave);
	int res = 0;
	if(ready_fight)
	{
		m_lianji ++;
		int bres;
		if(m_lianji == 3)
			bres = P->c_hp(this , -m_war*2.5) ,
			fprintf(information , "%s对%s打出了重伤!\n",m_name.c_str(),P->m_name.c_str()) ;
		else if(m_lianji >= 34)
			bres = P->c_hp(this , -m_war*0.04);
		else if(m_lianji >= 25)
			bres = P->c_hp(this , -m_war*0.1) ,
				fprintf(information , "%s开始对频繁的攻击感到乏力...\n",m_name.c_str());
		else if(m_lianji >= 15)
			bres = P->c_hp(this , -m_war*0.2);
		else if(m_lianji >= 8)
			bres = P->c_hp(this , -m_war*0.4);
		else if(m_lianji >= 5)
			bres = P->c_hp(this , -m_war*0.66);
		else
			bres = P->c_hp(this , -m_war);
		if(m_lianji == 2 || m_lianji == 4)
			P->m_sta["back"] = std::make_pair(clock()+300 , flag) ,
			fprintf(information , "%s对%s打出了击退!!!\n",m_name.c_str(),P->m_name.c_str());
		if(bres == 1)
		{
			debug_print("debug:"+m_name+"击杀people"+P->m_name+"->");
			res = 1;
			debug_print("debug:"+m_name+"击杀people"+P->m_name+"<-");
		}
	}
	else P->introduce() , m_lianji = 0;
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"<-");
	return res;
} // }}}
int player::move(char fg) // {{{
//1:press move with flag
//2:not move
{
	//if(m_sta["stop"].first > clock()) return 2;
	//else upd();
	/* pet->m_inM->move(pet , ' '); */
	int res = 0;
	if(fg == 'i') m_I->doit(this) , res = 2;
	else if(fg == 'o') m_O->doit(this) , res = 2;
	else if(fg == 'k' && ~bag->wood_h(-10)) m_sta["tishen"] = std::make_pair(clock()+600 , flag) , res = 2;
	else if(fg == 'L')
	{
		Pos l_pos(0 , 0);
		printf("输入其坐标x:");
		l_pos.x = intgetch();
		printf("输入其坐标y:");
		l_pos.y = intgetch();
		if(!m_inM) debug_print("error:no map in people");
		else if(m_inM->p(l_pos)) m_inM->p(l_pos)->introduce();
		else if(m_inM->f(l_pos)) m_inM->f(l_pos)->introduce();
		else fprintf(information , "指定位置此时为空!\n");
	}
	else if(fg == 'B') bag->list();
	else if(fg == 'Z') this->introduce();
	if(fg == ' ') fg = this->flag , res = 1;
	if(fg == 'j')
	{
		fg = this->flag;
		ready_fight = 2;
		res = 1;
	}
	else 
	{
		m_lianji = 0;
		if(ready_fight) ready_fight --;
	}
	if(fg == 'w') Px--;
	else if(fg == 's') Px++;
	else if(fg == 'd') Py++;
	else if(fg == 'a') Py--;
	else return 2;
	flag = fg;
	return res;
} // }}}
bool player::_cans(MAP *M,int x,int y,bool cansee) { if(!M->f(x,y)) M->newfloor(x,y); return cansee && M->f(x,y)->cansee(this); }
// player构造 {{{
player::player(int x,int y,std::string name):m_lianji(0),m_achi(new achievement),IO_name(name) 
{
	belong = "space";
	m_typ = "player";
	m_name = "你";
	m_hpsx = m_hp = FIR_hp;
	m_war = FIR_war;
	m_magic = m_magicsx = FIR_magic;
	Px=x; Py=y; face='P';
	/* B = new plboss(0); */
	pet = new Dog(x , y+1 , 0 , belong);
	m_list = new list_jn();
	bag = new BAG();
	sjin(this , name);
	debug_print("made a player");
} // }}}
// player 析构 {{{
player::~player()
{
	sjout(this , IO_name);
} // }}}
char player::pface(char c) // {{{
{
	if(c == 'w') return '^';
	if(c == 's') return 'v';
	if(c == 'a') return '<';
	if(c == 'd') return '>';
	else return 'P';
} // }}}
int player::look(MAP *M) // {{{
{
	pet->look(pet->m_inM);
	system("cls");
	_map2<bool> cansee;
	cansee(Px,Py) = 1;
	const int maxl = 8 , liest = 20 , lieen = 50 , hang = 11;
	// 判断视野 {{{
	#define cans(x,y) _cans(M,x,y,cansee(x,y))
	for(int len=1;len<=maxl+1;len++)
	{
		for(int i=Py-len+1;i<Py+len;i++)
			cansee(Px-len,i) = cans(Px-len+1,i);
		for(int i=Px-len+1;i<Px+len;i++)
			cansee(i,Py+len) = cans(i,Py+len-1);
		for(int i=Py-len+1;i<Py+len;i++)
			cansee(Px+len,i) = cans(Px+len-1,i);
		for(int i=Px-len+1;i<Px+len;i++)
			cansee(i,Py-len) = cans(i,Py-len+1);
		cansee(Px-len,Py-len) = (cans(Px-len+1,Py-len) || cans(Px-len,Py-len+1));
		cansee(Px-len,Py+len) = (cans(Px-len+1,Py+len) || cans(Px-len,Py+len-1));
		cansee(Px+len,Py-len) = (cans(Px+len-1,Py-len) || cans(Px+len,Py-len+1));
		cansee(Px+len,Py+len) = (cans(Px+len-1,Py+len) || cans(Px+len,Py+len-1));
	}
	#undef cans
	// }}}
	//  进行打印 {{{
	for(int i=Px-maxl;i<=Px+maxl;i++)
	{
		for(int j=Py-maxl;j<=Py+maxl;j++)
		{
			if(!cansee(i,j)) cgcolor("") , putchar(' ');
			else if(i == Px && j == Py)
			{
				cgcolor("05");
				putchar(pface(flag));
			}
			else if(M->p(i,j))
			{
				cgcolor(M->p(i,j)->color);
				putchar(M->p(i,j)->face);
			}
			else if(!M->f(i,j)) { printf("error:%d,%d\n",i-Px,j-Py); return -1; }
			else
			{
				cgcolor(M->f(i,j)->color);
				putchar(M->f(i,j)->face);
			}
		}
		puts("");
	}
	// 打印状态栏 {{{
	cgcolor(std::string("0") + (char)('0'+rand()%7));
	print_inF Kuang(Pos(1 , liest) , Pos(hang , lieen) , Pos(maxl * 2 + 2 , 1));
	// 提示 {{{
	cgcolor("");
	printf("Your imformation:");
	// }}}
	// 位置 {{{
	Kuang.tonext();
	cgcolor("");
	printf("place:%d %d(in %s)",Px,Py,M->m_name.c_str());
	// }}}
	// 等级 {{{
	Kuang.tonext();
	cgcolor("");
	printf("LV:%d/%d(EXP:%d/%d)",m_lv,lvmax,m_exp,lvup[m_lv]);
	// }}}
	// 生命值 {{{
	Kuang.tonext();
	cgcolor("");
	printf("Your HP:");
	if(m_hp < m_hpsx*0.3) cgcolor("04");
	else if(m_hp < m_hpsx*0.5) cgcolor("06");
	else if(m_hp < m_hpsx*0.8) cgcolor("01");
	else cgcolor("02");
	printf("%d/%d",m_hp,m_hpsx);
	if(!m_hpinfor.empty())
	{
		int f = m_hpinfor.front();
		m_hpinfor.pop();
		if(f > 0) cgcolor("02") ,printf("(+%d)",f);
		else cgcolor("04") , printf("(%d)",f);
	}
	cgcolor("");
	printf("(Pet's:");
	if(pet->m_hp < pet->c_hpmax()*0.3) cgcolor("04");
	else if(pet->m_hp < pet->c_hpmax()*0.5) cgcolor("06");
	else if(pet->m_hp < pet->c_hpmax()*0.8) cgcolor("01");
	else cgcolor("02");
	printf("%d",pet->m_hp);
	cgcolor("");
	putchar(')');
	// }}}
	// 魔法值 + 伤害 {{{
	Kuang.tonext();
	cgcolor("");
	printf("Your Magic:");
	if(m_magic < m_magicsx*0.3) cgcolor("04");
	else if(m_magic < m_magicsx*0.5) cgcolor("06");
	else if(m_magic < m_magicsx*0.8) cgcolor("01");
	else cgcolor("02");
	printf("%d/%d",m_magic,m_magicsx);
	cgcolor("");
	printf("  |  ");
	printf("ATK:%d",c_war());
	// }}}
	// 技能I {{{
	Kuang.tonext();
	cgcolor("");
	printf("-I-:%s(%d级)",m_I->m_name.c_str(),m_I->m_lv);
	// }}}
	// 技能O {{{
	Kuang.tonext();
	cgcolor("");
	printf("-O-:%s(%d级)",m_O->m_name.c_str(),m_O->m_lv);
	// }}}
	// 所处状态 {{{
	Kuang.tonext();
	cgcolor("");
	int now = clock();
	printf("状态:");
	for(auto iter = m_sta.begin();iter != m_sta.end();iter++)
		if(now < iter->second.first)
			printf("-%s",iter->first.c_str());
	// }}}
	// 连击数 {{{
	Kuang.tonext();
	cgcolor("");
	if(m_lianji) printf("%d连击!!!\n",m_lianji);
	// }}}
	// }}}
	cgcolor(""); // }}}
	return 0;
} // }}}
void player::introduce() // {{{
{
	print_inF Kuang(Pos(1,1) , Pos(7,38) , Pos(1,1));
	Kuang.clear();
	printf("勇士%s:",IO_name.c_str());
	Kuang.tonext();
	printf("基础生命上限:%5d  基础伤害:%dn",m_hpsx,m_war);
	Kuang.tonext();
	printf("实际生命上限:%5d  实际伤害:%d",c_hpmax(),c_war());
	Kuang.tonext();
	printf("基础魔法上限:%d",m_magicsx);
	Kuang.tonext();
	printf("作为一个勇士,你还是太菜了");
	Kuang.tonext();
	system("pause");
} // }}}
void player::exp_h(int ooexp) // {{{
{
	/* extern int lvup[]; */
	m_exp += ooexp;
	while(m_lv < lvmax && m_exp >= lvup[m_lv])
	{
		m_hpsx += FIR_hp * power11(m_lv);
		m_hp = m_hpsx;
		m_war += FIR_war * power11(m_lv);
		m_magicsx += FIR_magic * power11(m_lv);
		m_lv ++;
		messagebox(NULL,"升级了！！！\n","恭喜：",MB_OK);
	}
} // }}}
int player::magic_h(int oomagic) // {{{
{
	if(!oomagic) return m_magic;
	if(m_magic + oomagic < 0) return -1;
	else m_magic += oomagic;
	if(m_magic > m_magicsx) m_magic = m_magicsx;
	return m_magic;
} // }}}
void player::rc_hp(people *,int& val,int typ) // {{{
{
	extern FILE* information;
	int now = clock();
	if(now < m_sta["dikang"].first && typ != 'r' && val < 0)
		val = std::min(0 , val + m_sta["dikang"].second) ,
		fprintf(information,"抵抗生效!\n") ;
	m_hpinfor.push(val);
} // }}}
void player::rc_die(people *kill_p) // {{{
{
	fprintf(information , "%s杀死了你!\n",kill_p->m_name.c_str());
	kill_p->exp_h(100*power11(m_lv));
} // }}}
int player::call_pet(MAP *M) // {{{
{
	debug_print("debug:you call pet->");
	if(pet->m_mut_leave . try_lock())
	{
		debug_print("debug:call su");
		pet->m_mut_leave . unlock();
		pet->leave(pet->m_inM);
		int fg = myrand() % 4;
		pet->Px = Px + movex[fg];
		pet->Py = Py + movey[fg];
		pet->apin(M);
	}
	else fprintf(information , "召唤!!──────────失败......\n");
	debug_print("debug:you call pet<-");
	return 0;
} // }}}
// }}}

// Dog {{{
Dog::Dog(int x,int y,int lv,std::string bl)
{
	m_typ = "Dog";
	m_name = "Doge";
	color = "02";
	belong = bl;
	Px = x;
	Py = y;
	/* B = bs; */
	m_lv = lv;
	m_exp = lv ? lvup[lv - 1] : 0;
	m_war = FIR_war*10*power11(lv);
	m_hpsx = m_hp = FIR_hp*10*power11(lv);
	face = 'D';
	debug_print("made a Dog");
}
void Dog::rc_hp(people * , int& , int) {}
void Dog::rc_die(people *kill_p)
{
	kill_p->c_hp(this , -1000 , 'r');
}
int Dog::look(MAP *M)
//1 : MAP 为空
{
	if(!M) return -1;
	for(int i=0;i<4;i++)
	{
		auto p = M->p(Px + movex[i] , Py + movey[i]);
		if(p && p->belong != belong)
		{
			flag = MOVE[i];
			return 0;
		}
	}
	for(int i=0;i<4;i++)
	{
		auto p = M->p(Px + movex[i] * 2 , Py + movey[i] * 2);
		if(p && p->belong == belong)
		{
			flag = MOVE[i];
			return 0;
		}
	}
	flag = MOVE[rand()%4];
	return 0;
}
int Dog::meet(people* P)
{
	debug_print("debug:Dog"+m_name+"遭遇"+P->m_name+"->");
	int res = 0;
	//std::lock_guard<std::mutex> lock(P->m_mut_leave);
	if(P->belong == belong) res = 0;
	else if(P->c_hp(this,-c_war()) == 1) res = 1;
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"<-");
	return res;
}
void Dog::exp_h(int ooexp)
{
	m_exp += ooexp;
	while(m_exp >= lvup[m_lv])
	{
		m_war += FIR_war*power11(m_lv);
		m_hpsx += FIR_hp*power11(m_lv);
		m_hp = m_hpsx;
		m_lv ++;
	}
}
// }}}

// pig {{{
pig::pig(int x,int y,int lv,std::string bl)
{
	m_typ = "pig";
	m_name = "流浪者";
	color = "04";
	belong = bl;
	Px = x;
	Py = y;
	/* B = bs; */
	m_exp = lv ? lvup[lv - 1] : 0;
	m_war = FIR_war*10*power11(lv);
	m_hpsx = m_hp = FIR_hp*10*power11(lv);
	m_lv = lv;
	face = 'x';
	debug_print("made a pig");
}
void pig::rc_hp(people *,int&,int) {};
void pig::rc_die(people* kill_p)
{
	kill_p->bag->coin_h(800 * power11(m_lv));
	kill_p->bag->yuanli_h(6 * power11(m_lv));
	kill_p->exp_h(6 * power11(m_lv));
}
int pig::look(MAP *M)
{
	for(int i=0;i<4;i++)
	{
		auto p = M->p(Px+movex[i] , Py+movey[i]);
		if(p && p->belong != belong)
		{
			flag = MOVE[i];
			return 0;
		}
	}
	flag = MOVE[rand()%4];
	return 0;
}
int pig::meet(people* P)
{
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"->");
	int res = 0;
	//std::lock_guard<std::mutex> lock(P->m_mut_leave);
	if(P->belong == belong) res = 0;
	else if(P->c_hp(this,-c_war()) == 1) res = 1;
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"<-");
	return res;
}
void pig::exp_h(int ooexp)
{
	m_exp += ooexp;
	while(m_exp >= lvup[m_lv])
	{
		m_war += FIR_war*power11(m_lv);
		m_hpsx += FIR_hp*power11(m_lv);
		m_hp = m_hpsx;
		m_lv ++;
	}
}
// }}}

// snake {{{
snake::snake(int x,int y,int lv,std::string bl)
{
	m_typ = "snake";
	m_name = "杀戮者";
	color = "04";
	belong = bl;
	Px = x;
	Py = y;
	/* B = bs; */
	m_exp = lv ? lvup[lv - 1] : 0;
	m_war = FIR_war*10*power11(lv);
	m_hpsx = m_hp = FIR_hp*10*power11(lv);
	m_lv = lv;
	face = 's';
	debug_print("made a snake");
}
void snake::rc_hp(people * , int& , int) {};
void snake::rc_die(people *kill_p)
{
	kill_p->bag->coin_h(900 * power11(m_lv));
	kill_p->bag->yuanli_h(5 * power11(m_lv));
	kill_p->exp_h(8 * power11(m_lv));
}
bool snake::_cans(MAP *M,int x,int y,bool cansee) { if(!M->f(x,y)) return 0; return cansee && M->f(x,y)->cansee(this); }
int snake::look(MAP *M)
{
	_map2<bool> cansee;
	cansee(Px,Py) = 1;
	int maxl = 6;
	int gl = myrand() % 1000;
	#define cans(x,y) _cans(M,x,y,cansee(x,y))
	if(gl < 550)
		for(int len=1;len<=maxl+1;len++)
		{
			for(int i=Py-len+1;i<Py+len;i++)
			{
				cansee(Px-len,i) = cans(Px-len+1,i);
				if(cansee(Px-len,i) && M->p(Px-len,i) && M->p(Px-len,i)->belong != belong)
				{ flag = 'w'; return 0;}
			}
			for(int i=Px-len+1;i<Px+len;i++)
			{
				cansee(i,Py+len) = cans(i,Py+len-1);
				if(cansee(i,Py+len) && M->p(i,Py+len) && M->p(i,Py+len)->belong != belong)
				{ flag = 'd'; return 0;}
			}
			for(int i=Py-len+1;i<Py+len;i++)
			{
				cansee(Px+len,i) = cans(Px+len-1,i);
				if(cansee(Px+len,i) && M->p(Px+len,i) && M->p(Px+len,i)->belong != belong)
				{ flag = 's'; return 0;}
			}
			for(int i=Px-len+1;i<Px+len;i++)
			{
				cansee(i,Py-len) = cans(i,Py-len+1);
				if(cansee(i,Py-len) && M->p(i,Py-len) && M->p(i,Py-len)->belong != belong)
				{ flag = 'a'; return 0;}
			}
			cansee(Px-len,Py-len) = (cans(Px-len+1,Py-len) || cans(Px-len,Py-len+1));
			cansee(Px-len,Py+len) = (cans(Px-len+1,Py+len) || cans(Px-len,Py+len-1));
			cansee(Px+len,Py-len) = (cans(Px+len-1,Py-len) || cans(Px+len,Py-len+1));
			cansee(Px+len,Py+len) = (cans(Px+len-1,Py+len) || cans(Px+len,Py+len-1));
		}
	#undef cans
	flag = MOVE[rand()%4];
	return 0;
}
int snake::meet(people* P)
{
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"->");
	int res = 0;
	//std::lock_guard<std::mutex> lock(P->m_mut_leave);
	if(P->belong == belong) res = 0;
	else if(P->c_hp(this,-c_war()) == 1) res = 1;
	debug_print("debug:"+m_name+"遭遇"+P->m_name+"<-");
	return res;
}
void snake::exp_h(int ooexp)
{
	m_exp += ooexp;
	while(m_exp >= lvup[m_lv])
	{
		m_war += FIR_war*power11(m_lv);
		m_hpsx += FIR_hp*power11(m_lv);
		m_hp = m_hpsx;
		m_lv ++;
	}
}
// }}}

//atree {{{
atree::atree(int x,int y,int lv,std::string bl)
{
	m_typ = "tree";
	m_name = "灵树";
	belong = bl;
	/* B = bs; */
	m_exp = lv ? lvup[lv - 1] : 0;
	m_war = FIR_war*10*power11(lv);
	m_hpsx = m_hp = FIR_hp*10*power11(lv);
	m_lv = lv;
	face = 'T';
	color = "36";
	Px = x;
	Py = y;
}
void atree::rc_hp(people* , int& , int) {};
void atree::rc_die(people* kill_p)
{
	kill_p->bag->coin_h(800*power11(m_lv));
	kill_p->bag->wood_h(30*power11(m_lv));
	kill_p->exp_h(8*power11(m_lv));
}
int atree::look(MAP *)
{
	return 0;
}
int atree::meet(people*)
{
	debug_print("error:atree意外地遭遇");
	return -1;
}
void atree::exp_h(int ooexp)
{
	m_exp += ooexp;
	while(m_exp >= lvup[m_lv])
	{
		m_war += FIR_war*power11(m_lv);
		m_hpsx += FIR_hp*power11(m_lv);
		m_hp = m_hpsx;
		m_lv ++;
	}
}
// }}}


