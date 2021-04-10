#include "admin.h"
#include "cook.h"
#include "client.h"
#include "manager.h"
#include "List.h"
#include "reg.h"
#include "encryption.h"

#include <iostream>
#include <string>

using namespace std;

void Admin::menu() {

	bool ext = false;
	while (!ext) {
		system("cls");

		cout << "АДМИН" << endl
			<< "Введите действие:" << endl
			<< "1. Работники кухни" << endl
			<< "2. Клиенты" << endl
			<< "3. Работники зала" << endl
			<< "0. Выйти" << endl;

		switch (_getch()) {
		case '1': {
			system("cls");
			this->cook_menu();
			break;
		}
		case '2': {
			system("cls");
			this->client_menu();
			break;
		}
		case '3': {
			system("cls");
			this->manager_menu();
			break;
		}
		case '0':
			system("cls");
			ext = true;
		}
		if (!ext) {
			system("pause>>void");
		}
	}
}

void Admin::cook_menu() {
	extern List<Cook> cookList;

	string name;

	while (true) {
		system("cls");
		cout << "Введите действие:" << endl
			<< "1. Показать список\n"
			<< "2. Сортировка поваров\n"
			<< "3. Зарегистировать повара\n"
			<< "4. Удалить повара\n"
			<< "5. Фильтрация докторов по специализации\n"
			<< "0. Выход\n";

		switch (_getch()) {
		case '1':
			system("cls");

			printf("| %-5s| %-32s| %-16s|\n", "Номер", "Имя", "Специализация");
			for (int i = 0; i < 60; ++i)
				cout << '*';
			cout << endl;
			for (size_t i = 0; i < cookList.size(); ++i) {
				printf("| %-5d| %-32s| %-16s|\n", cookList[i]->num + 1,
					cookList[i]->full_name.c_str(), cookList[i]->speciality.c_str());
				for (int i = 0; i < 60; ++i)
					cout << '*';
				cout << endl;
			}
			break;
		case '2': {
			system("cls");
			cout << "0 - по возрастанию номеров, 1 - по убыванию номеров\n";
			char variant;
			cin >> variant;

			if (variant != '0' && variant != '1') {
				cout << "Некорректный ввод";
				break;
			}

			for (size_t i = 0; i < cookList.size(); ++i)
				for (size_t j = i + 1; j < cookList.size(); ++j) {
					bool cond = (cookList[i]->num > cookList[j]->num) ^ variant;
					if (cookList[i]->num > cookList[j]->num && variant == '1') {
						break;
					}
					if (cond) {
						Cook * tmp = cookList[i];
						cookList[i] = cookList[j];
						cookList[j] = tmp;
					}
				}

			for (size_t i = 0; i < cookList.size(); ++i) {
				cout << cookList[i]->num+1 << ". " << cookList[i]->full_name << endl;
			}

			break;
		}
		case '3': {
			system("cls");

			cout << "Регистрация" << endl;

			string login, pass, name;
			cout << "Введите логин: " << endl;
			cin >> login;
			cout << "Введите пароль: " << endl;
			cin >> pass;
			cout << "Введите имя: " << endl;
			getline(cin, name);
			if (name == "")
				getline(cin, name);

			string spec;
			cout << "Введите специализацию: " << endl;
			cin >> spec;

			cookList.push(new Cook(cookList.size(), name, login, encryption::encrypt(pass), spec));
			cout << "Повар зарегистирован успешно.";

			break;
		}
		case '4' : {
			system("cls");

			size_t num;
			cout << "Введите номер повара:" << endl;
			cin >> num;
			num--;
			if (num >= cookList.size()) {
				cout << "Такого повара нет.";
				break;
			}
			cookList.erase(num);
			cout << "Удалено успешно.";

			break;
		}
		case '5': {
			system("cls");
			cout << "Введите специализацию: ";
			string spec; cin >> spec;
			cout << endl;
			bool f = false;
			for (int i = 0; i < 60; ++i)
				cout << '*';
			cout << endl;
			printf("| %-5s| %-32s| %-16s|\n", "Номер", "Имя", "Специализация");
			for (int i = 0; i < 60; ++i)
				cout << '*';
			for (auto doc : cookList) {
				if (doc->speciality == spec) {
					f = true;
					printf("\n| %-5d| %-32s| %-16s|\n", doc->num + 1,
						doc->full_name.c_str(), doc->speciality.c_str());
					for (int i = 0; i < 60; ++i)
						cout << '*';
				}
			}
			if (!f) {
				system("cls");
				cout << "Ничего не найдено";
			}
			break;
		}
		case '0':
			return;
		}
		system("pause>>void");
	}
}

void Admin::client_menu() {
	extern List<Client> clientList;

	string name;

	while (true) {
		system("cls");
		cout << "Введите действие:" << endl
			<< "1. Показать список\n"
			<< "2. Сортировка клиентов\n"
			<< "3. Редактировать клиента\n"
			<< "4. Регистрация клиента\n"
			<< "5. Удалить клиента\n"
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
			cout << "0 - по возрастанию номеров, 1 - по убыванию номеров\n";
			char variant;
			cin >> variant;

			if (variant != '0' && variant != '1') {
				cout << "Некорректный ввод";
				break;
			}

			for (size_t i = 0; i < clientList.size(); ++i)
				for (size_t j = i + 1; j < clientList.size(); ++j) {
					bool cond = (clientList[i]->num > clientList[j]->num) ^ variant;
					if (clientList[i]->num > clientList[j]->num && variant == '1') {
						break;
					}
					if (cond) {
						Client * tmp = clientList[i];
						clientList[i] = clientList[j];
						clientList[j] = tmp;
					}
				}

			for (size_t i = 0; i < clientList.size(); ++i) {
				cout << clientList[i]->num+1 << ". " << clientList[i]->full_name << endl;
			}
			break;
		}
		case '3': {
			system("cls");

			size_t num;
			cout << "Введите номер клиента:" << endl;
			cin >> num;
			num--;

			if (num >= clientList.size()) {
				cout << "Такого клиента нет.";
				break;
			}

			cout << endl;

			clientList[num]->data_edit();

			break;
		}
		case '4':
			system("cls");
			extern reg rna;
			rna.regNewClient();
			break;
		case '5': {
			system("cls");
			size_t num;
			cout << "Введите номер клиента:" << endl;
			cin >> num;
			num--;
			if (num >= clientList.size()) {
				cout << "Такого клиента нет.";
				break;
			}
			clientList.erase(num);
			cout << "Удалено успешно.";
			break;
		}
		case '0':
			return;
		}
		system("pause>>void");
	}

}

void Admin::manager_menu() {
	extern List<Manager> managerList;

	string name;

	while (true) {
		system("cls");
		cout << "Введите действие:" << endl
			<< "1. Показать список\n"
			<< "2. Сортировка менеджера\n"
			<< "3. Зарегистрировать менеджера\n"
			<< "4. Удалить менеджера\n"
			<< "0. Выход\n";

		switch (_getch()) {
		case '1':
			system("cls");

			printf("| %-5s| %-32s|\n", "Номер", "Имя");
			for (int i = 0; i < 42; ++i)
				cout << '*';
			cout << endl;
			for (size_t i = 0; i < managerList.size(); ++i) {
				printf("| %-5d| %-32s|\n", managerList[i]->num + 1, managerList[i]->full_name.c_str());
				for (int i = 0; i < 42; ++i)
					cout << '*';
				cout << endl;
			}
			break;
		case '2': {
			system("cls");
			cout << "0 - по возрастанию номеров, 1 - по убыванию номеров\n";
			char variant;
			cin >> variant;

			if (variant != '0' && variant != '1') {
				cout << "Некорректный ввод";
				break;
			}

			for (size_t i = 0; i < managerList.size(); ++i)
				for (size_t j = i + 1; j < managerList.size(); ++j) {
					bool cond = (managerList[i]->num > managerList[j]->num) ^ variant;
					if (managerList[i]->num > managerList[j]->num && variant == '1') {
						break;
					}
					if (cond) {
						Manager * tmp = managerList[i];
						managerList[i] = managerList[j];
						managerList[j] = tmp;
					}
				}
			for (size_t i = 0; i < managerList.size(); ++i) {
				cout << managerList[i]->num + 1 << ". " << managerList[i]->full_name << endl;
			}

			break;
		}
		case '3': {
			system("cls");

			cout << "Регистрация" << endl;

			string login, pass, name;
			cout << "Введите логин: " << endl;
			cin >> login;
			cout << "Введите пароль: " << endl;
			cin >> pass;
			cout << "Введите имя: " << endl;
			getline(cin, name);
			getline(cin, name);

			managerList.push(new Manager(managerList.size(), name, login, encryption::encrypt(pass)));
			cout << "Менеджер зарегистрирован успешно.";
			break;
		}
		case '4': {
			system("cls");
			size_t num;
			cout << "Введите номер менеджера:" << endl;
			cin >> num;
			num--;
			if (num >= managerList.size()) {
				cout << "Такого менеджера нет.";
				break;
			}
			managerList.erase(num);
			cout << "Удалено успешно.";
			break;
		}
		case '0':
			return;
		}
		system("pause>>void");
	}
}
