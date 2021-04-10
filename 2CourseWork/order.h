#pragma once
#include <iostream>

class Order /*:
	public Object*/
{
public:
	size_t table_num;
	size_t day_num;
	size_t num;
	string time;
	size_t client_num;

	Order(size_t num, size_t tnum, size_t daynum, string t, size_t cnum) :
		num(num), table_num(tnum), time(t), client_num(cnum), day_num(daynum) {}
};