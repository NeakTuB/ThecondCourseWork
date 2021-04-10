#include "cook.h"
#include "order.h"
#include "menu.h"

#include <string>
#include <vector>

void Cook::menu() {
	bool ext = false;
	while (!ext) {
		system("cls");
		cout << "����� �"<< this->num+1 << endl
			<< "������� ��������:" << endl
			<< "1. ������� " << endl
			<< "2. �������� ������" << endl
			<< "3. ������ � ����" << endl
			<< "0. �����" << endl;

		switch (_getch()) {
		case '1': {
			system("cls");

			extern List<Client> clientList;

			printf("| %-5s| %-32s| %-16s|\n",
				"�����", "���", "� ��������");
			for (int i = 0; i < 60; ++i)
				cout << '*';
			cout << endl;
			for (size_t i = 0; i < clientList.size(); ++i) {
				map<string, string> data = clientList[i]->get_data();
				printf("| %-5s| %-32s| %-16s|\n",
					data["�����"].c_str(), data["���"].c_str(), data["����� ��������"].c_str());
				for (int i = 0; i < 60; ++i)
					cout << '*';
				cout << endl;
			}
			break;
		}
		case '2':
			system("cls");
			this->view_orders();
			break;
		case '3':
			system("cls");
			this->work_menu();
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

void Cook::search_client() {
	int variant;
	cout << "����� ������� �� ������ (0) ��� �� ����� (1)." << endl;
	cin >> variant;
	if (!variant && variant != 1) {
		cout << "������������ ����";
		return;
	}

	extern List<Client> clientList;

	if (variant == 0) {
		int num;
		cout << "������� �����: " << endl;
		cin >> num;

		if (num >= clientList.size()) {
			cout << "������ ������� ���" << endl;
			return;
		}

		map<string, string> data = clientList[num]->get_data();
		for (auto it = data.begin(); it != data.end(); ++it)
			cout << it->first << ": " << it->second << endl;

	}
	else {
		string name;
		cout << "������� ���: " << endl;
		getline(cin, name);
		if (name == "")
			getline(cin, name);

		int num = clientList.find(name);
		if (num == -1) {
			cout << "������ ������� ���." << endl;
			return;
		}

		map<string, string> data = clientList[num]->get_data();
		for (auto it = data.begin(); it != data.end(); ++it)
			cout << it->first << ": " << it->second << endl;
	}
}

void Cook::view_orders() {
	extern List<Order> orderList;
	cout << "������ �� ������: " << endl;
	if (!orderList.size()) {
		cout << "������� ���." << endl;
	}
	
	extern List<Client> clientList;

	string dayArr[] = { "�����������", "�������", "�����", "�������", "�������", "�������", "�����������" };

	for (auto c : orderList) {
		cout << dayArr[c->day_num-1] << " " << c->time << ": " << " ������ - " << c->table_num << endl;
	}

}

void Cook::work_menu() {
	extern List<Menu> menuList;

	string name;

	while (true) {
		system("cls");
		cout << "������� ��������:" << endl
			<< "1. �������� ����\n"
			<< "2. �������� ����� �����\n"
			<< "3. ������� �����\n"
			<< "0. �����\n";

		switch (_getch()) {
		case '1':
			system("cls");

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
		case '2': {
			system("cls");
			
			string name, main_pr, type;
			cout << "������� ���������: " << endl;
			cin >> type;
			cout << "������� ��������: " << endl;
			cin >> name;
			cout << "������� ������� ����������: " << endl;
			cin >> main_pr;

			menuList.push(new Menu(menuList.size(), type, name, main_pr));
			cout << "����� ������� ��������� � ����.";

			break;
		}
		case '3': {
			system("cls");

			size_t num;
			cout << "������� ����� �����:" << endl;
			cin >> num;
			num--;
			if (num >= menuList.size()) {
				cout << "������ ����� ���.";
				break;
			}
			menuList.erase(num);
			cout << "�������� ������ �������."; 

			break;
		}
		case '0':
			return;
		}
		system("pause>>void");
	}

	for (size_t i = 0; i < menuList.size(); ++i) {
		cout << menuList[i]->num << ". " << menuList[i]->name << endl;
	}
}