#pragma once
#include "BasicUser.h"

using namespace std;

class Manager : public BasicUser
{
	void create_client();
	void edit_client();
	void reservation();
	void clients_menu();
	void search_client();

public:
	Manager(int _num, string _fnme, string _log, string _pass) {
		num = _num;
		full_name = _fnme;
		login = _log;
		password = _pass;
	}

	void menu();
};

