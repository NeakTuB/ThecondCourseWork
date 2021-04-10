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
		cout << "������������ �" << this->num + 1 << endl
			<< "������� ��������:" << endl
			<< "1. �������� ����������" << endl
			<< "2. ������������� ����������" << endl
			<< "3. ����" << endl
			<< "4. �������� c�����" << endl
			<< "0. �����" << endl;

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

			printf("| %-5s| %-16s| %-16s| %-16s|\n", "�����", "���������", "��������", "������� ����������");
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

	printf("| %-5s| %-16s| %-16s| %-16s|\n", "�����", "���������", "��������", "������� ����������");
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

	cout << "�� ������ ���-������ ��������?(0 - ��, 1 - ���)" << endl;
	char choice;
	cin >> choice;
	cout << endl;

	if (choice != '0' && choice != '1') {
		cout << "������������ ����";
		return;
	}

	if (choice == '0') {
		cout << endl;
		cout << "������� ����� �����" << endl;
		int number;

	}
	if (choice == '1') {
		system("cls");
	}
}*/

void Client::reservation() {
	cout << "����� �������." << endl;

	extern List<Order> orderList;

	int tnum;
	cout << "�������� ����� ������� (1 - ����� ����, ..., 20 - ����� �����)" << endl;
	cin >> tnum;
	if (!tnum || tnum > 20 || tnum < 0) {
		cout << "�������� �����." << endl;
		return;
	}

	size_t daynum;
	cout << "������� ����� ��� ������ (1 - ��, ..., 7 - ��)" << endl;
	cin >> daynum;
	if (!daynum || daynum > 7) {
		cout << "�������� �����." << endl;
		return;
	}

	cout << "������� ����� (��)." << endl;
	
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

	cout << endl << "�����: ";

	scanf_s("%d:%d", &hh, &mm);
	if (hh < 11 || hh > 24 || mm < 0 || mm > 59 || mm % 60) {
		cout << "�������� �����." << endl;
		return;
	}

	string _t = ((hh < 13) ? "0" : "") + to_string(hh) + ':' + ((mm < 10) ? "0" : "") + to_string(mm);

	for (size_t i = 0; i < time.size(); ++i) {
		if (_t == time[i].second && time[i].first == 0) {
			cout << "������������ �����.";
			return;
		}
	}

	orderList.push(new Order(orderList.size(), tnum, daynum,
		((hh < 10) ? "0" : "") + to_string(hh) + ':' + ((mm < 10) ? "0" : "") + to_string(mm),
		this->num));

	cout << "������ �������.";
	system("pause>>void");

	system("cls");

	Order * c = orderList[orderList.size() - 1];

	string dayArr[] = {"�����������", "�������", "�����", "�������", "�������", "�������", "�����������"};

	cout << "��� ����� �" << orderList.size() << endl;
	cout << "������ �" << tnum << "." << endl;
	cout << "����: " << dayArr[daynum - 1].c_str() << endl;
	cout << "�����: " << c->time.c_str() << "." << endl;
	cout << "�������: " << this->full_name.c_str() << endl;
}

void Client::data_edit() {
	cout << "������� ����:" << endl
		<< "1. �����" << endl
		<< "2. ���" << endl
		<< "3. ����� ��������" << endl
		<< "0. �����" << endl;

	bool ext = false;
	while (ext == false) {

		char variant;
		cin >> variant;


		switch (variant)
		{
		case '1':
			cout << endl << "������� ����� �����: " << endl;
			cin >> this->login;
			ext = true;
			cout << "�������������� ������ �������!";
			break;
		case '2':
			cout << endl << "������� ����� ���: " << endl;
			cin >> this->full_name;
			ext = true;
			cout << "�������������� ������ �������!";
			break;
		case '3':
			cout << endl << "������� ����� ����� ��������: " << endl;
			cin >> this->num_telephone;
			ext = true;
			cout << "�������������� ������ �������!";
			break;
		case '0':
			ext = true;
		}
	}
}

map<string, string> Client::get_data() {
	map<string, string> ans;
	ans["�����"] = std::to_string(this->num + 1);
	ans["���"] = full_name;
	ans["����� ��������"] = num_telephone;
	return ans;
}
