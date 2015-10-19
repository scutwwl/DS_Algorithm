#ifndef __QUENE_H__
#define __QUENE_H__

#include "list.h"

template <typename T>
class Quene : public List  // List头作为队头
{
public:
	void en_quene(T data);
	void de_quene();
	int size();
	bool is_empty();
};

template <typename T>
void Quene<T>::en_quene(T data)
{
	insert_last(data);
}

template <typename T>
void Quene<T>::de_quene()
{
	remove_first();
}

template <typename T>
int Quene<T>::size()
{
	return amount;
}

template <typename T>
bool Quene<T>::is_empty()
{
	return ( amount == 0 );
}

#endif
