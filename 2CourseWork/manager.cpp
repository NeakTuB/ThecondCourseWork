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
	cout << "Введите номер клиента:" << endl;
	cin >> num;

	extern List<Client> clientList;

	if (num >= clientList.size()) {
		cout << "Такого клиента нет.";
		return;
	}

	clientList[num]->data_edit();

}

void Manager::reservation() {
	int num;
	cout << "Введите номер клиента для которого будет осуществляться заказ столика:" << endl;
	cin >> num;

	extern List<Client> clientList;

	clientList[num]->reservation();

}

void Manager::search_client() {
	int variant;
	cout << "0. По номеру\n1. По имени\n";
	cin >> variant;
	if (variant && variant != 1) {
		cout << "Некорректный ввод";
		return;
	}

	extern List<Client> clientList;


	if (!variant) {
		int num;
		cout << "Введите номер: " << endl;
		cin >> num;
		num--;

		if (num >= clientList.size()) {
			cout << "Такого клиента нет" << endl;
			return;
		}

		map<string, string> data = clientList[num]->get_data();
		for (auto it = data.begin(); it != data.end(); ++it)
			cout << it->first << ": " << it->second << endl;

	}
	else {
		string name;
		cout << "Введите имя: " << endl;
		getline(cin, name);
		getline(cin, name);

		int num = clientList.find(name);
		if (num == -1) {
			cout << "Такого клиента нет." << endl;
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
		cout << "Введите действие:" << endl
			<< "1. Показать список\n"
			<< "2. Поиск клиента\n"
			<< "3. Сортировка клиентов\n"
			<< "4. Редактировать клиента\n"
			<< "5. Регистрация клиента\n"
			<< "0. Выход\n";

		switch (_getch()) {
		case '1':
			system("cls");
			printf("| %-5s| %-32s| %-16s|\n",
				"Номер", "Имя", "№ телефона");
			for (int i = 0; i < 60; ++i)
				cout << '*';
			cout << endl;
			for (size_t i = 0; i < clientList.size(); ++i) {
				map<string, string> data = clientList[i]->get_data();
				printf("| %-5s| %-32s| %-16s|\n",
					data["Номер"].c_str(), data["Имя"].c_str(), data["Номер телефона"].c_str());
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
			cout << "По возрастанию номеров (0) или по убыванию (1)?\n";
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

		cout << "Менеджер №" << this->num + 1 << endl
			<< "Введите действие:" << endl
			<< "1. Клиенты" << endl
			<< "2. Показать заказы" << endl
			<< "3. Удалить заказ" << endl
			<< "4. Отчет" << endl
			<< "0. Выйти" << endl;

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
				cout << "Заказов нет.";
				break;
			}

			string dayArr[] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };

			printf("%5s | %15s | %15s |\n", "Время", "День", "Номер столика");
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
			cout << "Введите номер заказа:" << endl;
			cin >> num;
			num--;
			if (num >= orderList.size()) {
				cout << "Такого заказа нет.";
				break;
			}
			orderList.erase(num);
			cout << "Удалено успешно.";

			break;
		case '4':
			system("cls");

			num = rand() % 20;
			s = num * 300;
			sum = rand() % s;
			cout << "Количество клиентов - " << num << endl;
			cout << "Потраченная сумма - " << sum << endl;

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