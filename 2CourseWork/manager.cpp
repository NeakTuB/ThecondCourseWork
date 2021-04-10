#include "manager.h"
#include "List.h"
#include "client.h"
#include "reg.h"
#include "cook.h"
#include "order.h"

#include <string>
#include <vector>

extern reg rna;

void Manager::create_client() {
	extern List<Client> clientList;
	rna.regNewClient();
}

void Manager::edit_client() {
	
	int num;
	cout << "������� ����� �������:" << endl;
	cin >> num;

	extern List<Client> clientList;

	if (num >= clientList.size()) {
		cout << "������ ������� ���.";
		return;
	}

	clientList[num]->data_edit();

}

void Manager::reservation() {
	int num;
	cout << "������� ����� ������� ��� �������� ����� �������������� ����� �������:" << endl;
	cin >> num;

	extern List<Client> clientList;

	clientList[num]->reservation();

}

void Manager::search_client() {
	int variant;
	cout << "0. �� ������\n1. �� �����\n";
	cin >> variant;
	if (variant && variant != 1) {
		cout << "������������ ����";
		return;
	}

	extern List<Client> clientList;


	if (!variant) {
		int num;
		cout << "������� �����: " << endl;
		cin >> num;
		num--;

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

void Manager::clients_menu() {
	extern List<Client> clientList;

	string name;

	while (true) {
		system("cls");
		cout << "������� ��������:" << endl
			<< "1. �������� ������\n"
			<< "2. ����� �������\n"
			<< "3. ���������� ��������\n"
			<< "4. ������������� �������\n"
			<< "5. ����������� �������\n"
			<< "0. �����\n";

		switch (_getch()) {
		case '1':
			system("cls");
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
		case '2': {
			system("cls");
			this->search_client();
			break;
		}
		case '3': {
			system("cls");
			cout << "�� ����������� ������� (0) ��� �� �������� (1)?\n";
			bool variant;
			cin >> variant;

			for (size_t i = 0; i < clientList.size(); ++i)
				for (size_t j = i + 1; j < clientList.size(); ++j) {
					bool cond = (clientList[i]->num > clientList[j]->num) ^ variant;
					if (cond) {
						Client * tmp = clientList[i];
						clientList[i] = clientList[j];
						clientList[j] = tmp;
					}
				}
			for (size_t i = 0; i < clientList.size(); ++i) {
				cout << clientList[i]->num << ". " << clientList[i]->full_name << endl;
			}
			break;
		}
		case '4': {
			system("cls");
			this->edit_client();
			break;
		}
		case '5':
			system("cls");
			rna.regNewClient();
			break;
		case '0':
			return;
		}
		system("pause>>void");
	}

}

void Manager::menu() {
	bool ext = false;
	int num, s, sum;
	while (!ext) {
		system("cls");

		cout << "�������� �" << this->num + 1 << endl
			<< "������� ��������:" << endl
			<< "1. �������" << endl
			<< "2. �������� ������" << endl
			<< "3. ������� �����" << endl
			<< "4. �����" << endl
			<< "0. �����" << endl;

		switch (_getch()) {
		case '1': {
			system("cls");
			this->clients_menu();
			break;
		}
		case '2': {
			system("cls");

			extern List<Order> orderList;
			extern List<Client> clientList;
			extern List<Cook> cookList;

			if (!orderList.size()) {
				cout << "������� ���.";
				break;
			}

			string dayArr[] = { "�����������", "�������", "�����", "�������", "�������", "�������", "�����������" };

			printf("%5s | %15s | %15s |\n", "�����", "����", "����� �������");
			for (int i = 0; i < 43; i++) {
				cout << "*";
			}
			cout << endl;
			for (auto c : orderList) {
				int num = c->day_num;
				string time = c->time;
				int tnum = c->table_num;
				printf("%5s | %15s | %15d |\n",
					time.c_str(), dayArr[num-1].c_str(), tnum); 
				for (int i = 0; i < 43; i++) {
					cout << "*";
				}
				cout << endl;
			}	
			break;
		}
		case '3':
			system("cls");
			
			extern List<Order> orderList;


			size_t num;
			cout << "������� ����� ������:" << endl;
			cin >> num;
			num--;
			if (num >= orderList.size()) {
				cout << "������ ������ ���.";
				break;
			}
			orderList.erase(num);
			cout << "������� �������.";

			break;
		case '4':
			system("cls");

			num = rand() % 20;
			s = num * 300;
			sum = rand() % s;
			cout << "���������� �������� - " << num << endl;
			cout << "����������� ����� - " << sum << endl;

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