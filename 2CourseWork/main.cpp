#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "user.h"
#include "manager.h"
#include "client.h"
#include "List.h"
#include "cook.h"
#include "admin.h"
#include "reg.h"
#include "order.h"
#include "menu.h"

using namespace std;

List<Cook> cookList;
List<Client> clientList;
List<Manager> managerList;
List<Order> orderList;
List<Menu> menuList;

Admin admin;
reg R;

void reading() {
	ifstream c_in("clients.txt");
	if (!c_in.fail()) {
		while (!c_in.eof()) {
			string login; getline(c_in, login);
			string pass; getline(c_in, pass);
			string name; getline(c_in, name);
			string num_telephone; getline(c_in, num_telephone);
			clientList.push(new Client(clientList.size(), login, pass, name, num_telephone));
		}
	}
	c_in.close();

	ifstream co_in("cooks.txt");
	if (!co_in.fail()) {
		while (!co_in.eof()) {
			string login; getline(co_in, login);
			string pass; getline(co_in, pass);
			string name; getline(co_in, name);
			string spec; getline(co_in, spec);
			cookList.push(new Cook(cookList.size(), name, login, pass, spec));
		}
	}
	co_in.close();

	ifstream m_in("managers.txt");
	if (!m_in.fail()) {
		while (!m_in.eof()) {
			string login; getline(m_in, login);
			string pass; getline(m_in, pass);
			string name; getline(m_in, name);
			managerList.push(new Manager(managerList.size(), name, login, pass));
		}
	}
	m_in.close();

	ifstream o_in("orders.txt");
	if (!o_in.fail()) {
		while (!o_in.eof()) {
			string table_num; getline(o_in, table_num);
			string day_num; getline(o_in, day_num);
			string time; getline(o_in, time);
			string client_num; getline(o_in, client_num);

			size_t t; sscanf(table_num.c_str(), "%zu", &t);
			size_t d; sscanf(day_num.c_str(), "%zu", &d);
			size_t c; sscanf(client_num.c_str(), "%zu", &c);

			orderList.push(new Order(orderList.size(), t, d, time, c));
		}
	}
	o_in.close();

	ifstream me_in("menu.txt");
	if (!me_in.fail()) {
		while (!me_in.eof()) {
			string type; getline(me_in, type);
			string name; getline(me_in, name);
			string main_product; getline(me_in, main_product);
			menuList.push(new Menu(menuList.size(), type, name, main_product));
		}
	}
	me_in.close();
}

void writing() {
	ofstream c_out("clients.txt");
	if (!c_out.fail()) {
		for (size_t i = 0; i < clientList.size(); ++i) {
			c_out << clientList[i]->login << endl
				<< clientList[i]->password << endl
				<< clientList[i]->full_name << endl
				<< clientList[i]->num_telephone;

			if (i < clientList.size() - 1)
				c_out << endl;
		}
	}
	c_out.close();

	ofstream co_out("cooks.txt");
	if (!co_out.fail()) {
		for (size_t i = 0; i < cookList.size(); ++i) {
			co_out << cookList[i]->login << endl
				<< cookList[i]->password << endl
				<< cookList[i]->full_name << endl
				<< cookList[i]->speciality;

			if (i < cookList.size() - 1)
				co_out << endl;
		}
	}
	co_out.close();

	ofstream m_out("managers.txt");
	if (!m_out.fail()) {
		for (size_t i = 0; i < managerList.size(); ++i) {
			m_out << managerList[i]->login << endl
				<< managerList[i]->password << endl
				<< managerList[i]->full_name;

			if (i < managerList.size() - 1)
				m_out << endl;
		}
	}
	m_out.close();

	ofstream o_out("orders.txt");
	if (!o_out.fail()) {
		for (size_t i = 0; i < orderList.size(); ++i) {
			o_out << orderList[i]->table_num << endl
				<< orderList[i]->day_num << endl
				<< orderList[i]->time << endl
				<< orderList[i]->client_num;

			if (i < orderList.size() - 1)
				o_out << endl;
		}
	}
	o_out.close();

	ofstream me_out("menu.txt");
	if (!me_out.fail()) {
		for (size_t i = 0; i < menuList.size(); ++i) {
			me_out << menuList[i]->type << endl
				<< menuList[i]->name << endl
				<< menuList[i]->main_product;

			if (i < menuList.size() - 1)
				me_out << endl;
		}
	}
	me_out.close();
}

void startMenu() {
	while (true) {
		system("cls");

		cout << "Выберите номер действия:\n";
		cout << "1. Авторизация\n";
		cout << "2. Регистрация\n";
		cout << "0. Выход\n";
		switch (_getch()) {
		case '1':
			system("cls");

			R.auth();

			break;
		case '2':
			system("cls");

			R.regNewClient();

			break;
		case '0':
			return;
			break;
		}
	}
}



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	reading();

	startMenu();

	writing();

	return 0;
}
