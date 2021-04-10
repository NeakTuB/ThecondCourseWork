#pragma once
#include <string>

using namespace std;

class Menu 
{
public:
	int num;
	string name;
	string main_product;
	string type;

public:
	Menu(int _num, string _type, string _name, string _mainp) {
		num = _num;
		name = _name;
		main_product = _mainp;
		type = _type;
	}

	void erase();
};