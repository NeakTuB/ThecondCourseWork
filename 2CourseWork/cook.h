#pragma once

#include "BasicUser.h"
#include "List.h"
#include "client.h"

using namespace std;

class Cook : public BasicUser
{
	void search_client();
	void view_orders();
	void work_menu();

	int rnum;

public:

	string speciality;
	
	Cook(int _num, string _fnme, string _log, string _pass, string _spec) :
		speciality(_spec), rnum(0) {
		num = _num;
		full_name = _fnme;
		login = _log;
		password = _pass;
	}
	
	void menu();
};
