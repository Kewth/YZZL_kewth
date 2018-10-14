#include "h/more.h"
#include "h/people.h"
std::vector<people*> Peo_will_do;
void Peo_all_do()
{
	debug_print("debug:Peo_all_do->");
	/* std::vector<std::vector<people*>::iterator> era; */
	for(auto i=Peo_will_do.begin();i!=Peo_will_do.end();i++)
	{
		debug_print("debug:Turn_to"+(*i)->m_name+"->");
		bool era = false;
		debug_print(std::string("debug:m_hp>0?")+
				((*i)->m_hp>0?"Y":"N"));
		if((*i)->m_hp <= 0 and (*i)->m_mut_leave.try_lock())
			(*i)->m_mut_leave.unlock(),
			(*i)->leave((*i)->m_inM);
		if((*i)->m_hp <= 0 or not (*i)->m_inM)
			era = true;
		else
			(*i)->Todo();
		debug_print("debug:Turn_to"+(*i)->m_name+"<-");
		if(era) (*i) = nullptr;
	}
	debug_print("debug:turn done");
	for(auto i=Peo_will_do.begin();i!=Peo_will_do.end();)
		if(not *i)
			i = Peo_will_do.erase(i);
		else 
			i ++;
	/* for(uint i=0;i<era.size();i++) */
	/* 	debug_print("debug:will erase "+(*era[i])->m_name), */
		/* *era[i] = nullptr, */
		/* Peo_will_do.erase(era[i]); */
	debug_print("debug:Peo_all_do<-");
}
