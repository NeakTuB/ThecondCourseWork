#pragma once

#include "BasicUser.h"

#include <map>

using namespace std;

class Client : public BasicUser
{

protected:
	string num_telephone;

public:

	map<string, string> get_data();

	Client(int _num, string _log, string _pass,
		string _fnme, string _tnum) :
		num_telephone(_tnum) {
		num = _num;
		login = _log;
		password = _pass;
		full_name = _fnme;
	};

	void menu();

	friend void writing();

	void reservation();
	void data_edit();
	//void order_menu();
};