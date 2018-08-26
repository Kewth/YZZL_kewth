#include <bits/stdc++.h>
#include "h/city/skycity.h"

int skycity::xz0::onein(people *P)
{
	return xz_yangshen(P);
}

int skycity::xz1::onein(people *P)
{
	if(P -> m_hp <= P->c_hpmax() / 10)
	{
		P -> Px --;
		P -> m_hp += P->c_hpmax() / 1500;
		if(P->m_typ == "player")
			fprintf(information , "你没有足够的生命值复活!\n");
	}
	return 0;
}

skycity::skycity(int last_id,int last_x,int last_y)
{
	/* newmap("skycity.txt"); */
	const int Mlen = 8;
	M = new MAP(0,Mlen,"天堂skycity",2);
	int mid = Mlen >> 1;
	for(int i=3;i<Mlen-1;i++)
		M->f(i , mid) = new grass('|' , "向下走,迎来新生");
	M->f(Mlen-1,mid) = new xz1();
	M->f(Mlen,mid) = new gotocity(last_id,last_x,last_y,'v');
	M->f(Mlen+1,mid) = new wall();
	for(int i=2;i<Mlen-1;i++)
		M->f(2,i) = new xz0();
	for(uint i=0;i<xz0::name.size();i++)
		M->f(1,i+1) = new grass(xz0::name[i]);
	/* M->init(); */
}

std::string skycity::xz0::name = "You die";
