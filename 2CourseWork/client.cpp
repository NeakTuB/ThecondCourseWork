#include "client.h"
#include "List.h"
#include "cook.h"
#include "order.h"
#include "menu.h"

#include <string>
#include <iostream>
#include <vector>

void Client::menu() {
	bool ext = false;
	while (!ext) {
		system("cls");
		cout << "Пользователь №" << this->num + 1 << endl
			<< "Введите действие:" << endl
			<< "1. Показать информацию" << endl
			<< "2. Редактировать информацию" << endl
			<< "3. Меню" << endl
			<< "4. Заказать cтолик" << endl
			<< "0. Выйти" << endl;

		char var = _getch();
		if (var < '0' || var > '5')
			var = _getch();

		switch (var) {
		case '1': {
			system("cls");
			map<string, string> dat = this->get_data();
			for (map<string, string>::iterator it = dat.begin(); it != dat.end(); ++it)
				cout << it->first << " : " << it->second << endl;
			break;
		}
		case '2':
			system("cls");
			data_edit();
			break;
		case '3':
			system("cls");
			extern List<Menu> menuList;

			printf("| %-5s| %-16s| %-16s| %-16s|\n", "Номер", "Категория", "Название", "Главный ингридиент");
			for (int i = 0; i < 64; ++i)
				cout << '*';
			cout << endl;
			for (size_t i = 0; i < menuList.size(); ++i) {
				printf("| %-5d| %-16s| %-16s| %-18s|\n", menuList[i]->num + 1, menuList[i]->type.c_str(),
					menuList[i]->name.c_str(), menuList[i]->main_product.c_str());
				for (int i = 0; i < 64; ++i)
					cout << '*';
				cout << endl;
			}
			break;
		case '4':
			system("cls");
			this->reservation();
			break;
		case '0':
			system("cls");
			ext = true;
		}
		if (!ext) {
			system("pause>>void");
		}
	}
}

/*void Client::order_menu() {
	extern List<Menu> menuList;
	extern List<Menu> order_menuList;

	printf("| %-5s| %-16s| %-16s| %-16s|\n", "Номер", "Категория", "Название", "Главный ингридиент");
	for (int i = 0; i < 64; ++i)
		cout << '*';
	cout << endl;
	for (size_t i = 0; i < menuList.size(); ++i) {
		printf("| %-5d| %-16s| %-16s| %-18s|\n", menuList[i]->num + 1, menuList[i]->type.c_str(),
			menuList[i]->name.c_str(), menuList[i]->main_product.c_str());
		for (int i = 0; i < 64; ++i)
			cout << '*';
		cout << endl;
	}

	cout << "Вы хотите что-нибудь заказать?(0 - да, 1 - нет)" << endl;
	char choice;
	cin >> choice;
	cout << endl;

	if (choice != '0' && choice != '1') {
		cout << "Некорректный ввод";
		return;
	}

	if (choice == '0') {
		cout << endl;
		cout << "Введите номер блюда" << endl;
		int number;

	}
	if (choice == '1') {
		system("cls");
	}
}*/

void Client::reservation() {
	cout << "Заказ столика." << endl;

	extern List<Order> orderList;

	int tnum;
	cout << "Ввведите номер столика (1 - возле окна, ..., 20 - возле стены)" << endl;
	cin >> tnum;
	if (!tnum || tnum > 20 || tnum < 0) {
		cout << "Неверный номер." << endl;
		return;
	}

	size_t daynum;
	cout << "Введите номер дня недели (1 - Пн, ..., 7 - Вс)" << endl;
	cin >> daynum;
	if (!daynum || daynum > 7) {
		cout << "Неверный номер." << endl;
		return;
	}

	cout << "Введите время (чч)." << endl;
	
	int hh, mm = 0;
	vector<pair<bool, string>> time;
	for (hh = 11; hh < 24; ) {
		time.push_back({ 1, ((hh < 10) ? "0" : "") + to_string(hh) + ':' + ((mm < 10) ? "0" : "") + to_string(mm) });
		mm += 60;
		if (mm == 60) {
			mm = 0;
			hh++;
		}
	}

	for (Order * c : orderList) {
		if (c->table_num != tnum || c->day_num != daynum)
			continue;
		for (size_t i = 0; i < time.size(); ++i) {
			if (c->time == time[i].second) {
				time[i].first = 0;
				break;
			}
		}
	}

	for (auto t : time) {
		if (t.first)
			cout << t.second << ' ';
	}

	cout << endl << "Время: ";

	scanf_s("%d:%d", &hh, &mm);
	if (hh < 11 || hh > 24 || mm < 0 || mm > 59 || mm % 60) {
		cout << "Неверное время." << endl;
		return;
	}

	string _t = ((hh < 13) ? "0" : "") + to_string(hh) + ':' + ((mm < 10) ? "0" : "") + to_string(mm);

	for (size_t i = 0; i < time.size(); ++i) {
		if (_t == time[i].second && time[i].first == 0) {
			cout << "Некорректное время.";
			return;
		}
	}

	orderList.push(new Order(orderList.size(), tnum, daynum,
		((hh < 10) ? "0" : "") + to_string(hh) + ':' + ((mm < 10) ? "0" : "") + to_string(mm),
		this->num));

	cout << "Столик заказан.";
	system("pause>>void");

	system("cls");

	Order * c = orderList[orderList.size() - 1];

	string dayArr[] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};

	cout << "Ваш заказ №" << orderList.size() << endl;
	cout << "Столик №" << tnum << "." << endl;
	cout << "Дата: " << dayArr[daynum - 1].c_str() << endl;
	cout << "Время: " << c->time.c_str() << "." << endl;
	cout << "Заказан: " << this->full_name.c_str() << endl;
}

void Client::data_edit() {
	cout << "Введите поле:" << endl
		<< "1. Логин" << endl
		<< "2. Имя" << endl
		<< "3. Номер телефона" << endl
		<< "0. Назад" << endl;

	bool ext = false;
	while (ext == false) {

		char variant;
		cin >> variant;


		switch (variant)
		{
		case '1':
			cout << endl << "Введите новый логин: " << endl;
			cin >> this->login;
			ext = true;
			cout << "Редактирование прошло успешно!";
			break;
		case '2':
			cout << endl << "Введите новое имя: " << endl;
			cin >> this->full_name;
			ext = true;
			cout << "Редактирование прошло успешно!";
			break;
		case '3':
			cout << endl << "Введите новый номер телефона: " << endl;
			cin >> this->num_telephone;
			ext = true;
			cout << "Редактирование прошло успешно!";
			break;
		case '0':
			ext = true;
		}
	}
}

map<string, string> Client::get_data() {
	map<string, string> ans;
	ans["Номер"] = std::to_string(this->num + 1);
	ans["Имя"] = full_name;
	ans["Номер телефона"] = num_telephone;
	return ans;
}
