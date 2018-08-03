#include <bits/stdc++.h>
#include "h/more.h"
#include "h/people.h"
#include "h/war.h"
/* static volatile int warres; */
/* static void* Emain(people *E , MAP *M) */
/* { */
/* 	while(Sleep(399) == 0 && warres == 0) */
/* 	{ */
/* 		E->look(M); */
/* 		//printf("Pig's flag = %c\n",E->flag); */
/* 		int mres = M->move(E , ' '); */
/* 		if(mres == 1) warres = 1; */
/* 	} */
/* 	return NULL; */
/* } */
int war(people *P , people *G)
//1:lose
//2:spc
//3:win
{
	int warres = 0;
	MAP *M = new MAP(0,6);
	P->Px = 1;P->Py = 1;
	P->apin(M);
	G->apin(M);
	/* std::thread *th = new std::thread(Emain , G , M); */
	int turn_to_G = clock();
	while(!warres)
	{
		P->look(M);
		printf("Its hp:%d\n",G->m_hp);
		readinforma();
		int c = ifgetch(P->speed());
		if(clock() < P->m_sta["stop"].first && c == 'Q') warres = 2;
		M->move(P , c);
		if(G->m_hp <= 0) warres = 3;
		else while(clock() >= turn_to_G)
		{
			turn_to_G += G->speed();
			G->look(M);
			M->move(G , ' ');
			if(P->m_hp <= 0) warres = 1;
		}
	}
	P->look(M);
	puts("War done.");
	/* th->join(); */
	delete M;
	return warres;
}
