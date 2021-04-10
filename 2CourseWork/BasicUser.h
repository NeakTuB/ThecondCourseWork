#pragma once
#include <iostream>
#include <conio.h>
#include "User.h"

using namespace std;

class BasicUser :
	public User {
public:
	int num;
	string login, password, full_name;
};
