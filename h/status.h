#ifndef STATUS_H
#define STATUS_H
#include <bits/stdc++.h>
class people;
class status
{
	protected:
	people *P;
	virtual void rldo(people *) = 0;
	public:
	virtual void doit(people *) = 0;
};
class sta_fight : public status
{
	protected:
	virtual void rldo(people *) = 0;
	public:
	void doit(people *);
};
class sta_move : public status
{
	protected:
	virtual void rldo(people *) = 0;
	public:
	void doit(people *);
};
class sta_hp : public status
{
	protected:
	virtual void rldo(people *) = 0;
	public:
	void doit(people *);
};
class sta_shouxian : public sta_move
{
	public:
	static const std::string m_name;
};
#endif
