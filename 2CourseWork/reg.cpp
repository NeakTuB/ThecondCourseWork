#include "reg.h"
#include "List.h"
#include "client.h"
#include "manager.h"
#include "cook.h"
#include "admin.h"
#include "encryption.h"

#include <iostream>
#include <string>

using namespace std;
using encryption::encrypt;

int check_name(string& name) {

	if (name.size() < 1)
		return 1;

	for (int i = 0; i < name.size(); ++i) {
		if (!(('A' <= name[i] && name[i] <= 'z')
			|| ('А' <= name[i] && name[i] <= 'я')
			|| name[i] == 'Ё' || name[i] == 'ё'
			|| name[i] == ' ')) {
			return 1;
		}
		if (i && name[i - 1] == ' ' && name[i] != ' ')
			name[i] = toupper(name[i]);
	}

	name[0] = toupper(name[0]);

	return 0;
}

void reg::regNewClient() {
	string login;
	string pass, pass_chk, pass_encr;
	string num_telephone;
	string name;

	system("cls");

	extern List<Client> clientList;

	cout << "Регистрация." << endl;

	bool l_checked = true;
	do {
		if (!l_checked)
			cout << "Этот логин уже занят. Введите другой:\n";
		else
			cout << "Введите Ваш логин:\n";
		l_checked = true;

		cin >> login;

		for (int i = 0; i < clientList.size(); ++i) {
			if (clientList[i]->login == login) {
				l_checked = false;
				break;
			}
		}

		extern List<Cook> cookList;
		for (int i = 0; i < cookList.size(); ++i) {
			if (cookList[i]->login == login) {
				l_checked = false;
				break;
			}
		}

		extern List<Manager> managerList;
		for (int i = 0; i < managerList.size(); ++i) {
			if (managerList[i]->login == login) {
				l_checked = false;
				break;
			}
		}

		if (login == "admin")
			l_checked = false;

	} while (!l_checked);


	bool p_checked = true;
	do {
		if (!p_checked)
			cout << "Пароли не совпадают, повторите попытку!\n";
		p_checked = true;

		cout << "Введите Ваш пароль:\n";
		cin >> pass;
		cout << "Повторите Ваш пароль:\n";
		cin >> pass_chk;
		if (pass != pass_chk)
			p_checked = false;
	} while (!p_checked);

	pass_encr = encrypt(pass);

	bool n_checked = true;
	do {
		if (!n_checked)
			cout << "Недопустимые символы в имени!\n";
		n_checked = true;

		cout << "Введите Ваше имя:\n";
		getchar();
		getline(cin, name);
		if (check_name(name))
			n_checked = false;
	} while (!n_checked);

	cout << "Введите номер Вашего телефона:\n";
	cin >> num_telephone;

	clientList.push(new Client(clientList.size(), login, pass_encr, name, num_telephone));
	cout << "Регистрация прошла успешно!\n";
	system("pause>>void");
}

int reg::auth() {
	cout << "Авторизация." << endl;

	string login;
	cout << "Введите логин:\n";
	cin >> login;

	cout << "Введите пароль:\n";
	string password;
	while (true) {
		char c = _getch();
		if (c == 13)
			break;
		if (!c)
			continue;
		if (c == 8) {
			system("cls");
			cout << "Введите логин:\n"
				<< login << endl
				<< "Введите пароль:\n";
			for (size_t i = 0; i < password.size(); ++i)
				cout << '*';
			password = password.substr(0, password.size() - 1);
			continue;
		}
		password += c;
		cout << '*';
	}
	cout << endl;

	string pass_encr = encrypt(password);

	extern Admin admin;
	if (login == password && password == "admin") {
		admin.menu();
		return 0;
	}

	extern List<Client> clientList;
	for (int i = 0; i < clientList.size(); ++i) {
		if (clientList[i]->login == login && clientList[i]->password == pass_encr) {
			clientList[i]->menu();
			return 0;
		}
	}

	extern List<Cook> cookList;
	for (int i = 0; i < cookList.size(); ++i) {
		if (cookList[i]->login == login && cookList[i]->password == pass_encr) {
			cookList[i]->menu();
			return 0;
		}
	}

	extern List<Manager> managerList;
	for (int i = 0; i < managerList.size(); ++i) {
		if (managerList[i]->login == login && managerList[i]->password == pass_encr) {
			managerList[i]->menu();
			return 0;
		}
	}

	cout << "Неверный логин или пароль";
	system("pause>>void");

	return 1;

}

