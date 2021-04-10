#pragma once
#include "User.h"

class Admin :
	public User {
	void cook_menu();
	void client_menu();
	void manager_menu();
public:
	void menu();
};
