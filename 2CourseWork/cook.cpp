#include "cook.h"
#include "order.h"
#include "menu.h"

#include <string>
#include <vector>

void Cook::menu() {
	bool ext = false;
	while (!ext) {
		system("cls");
		cout << "Повар №"<< this->num+1 << endl
			<< "Введите действие:" << endl
			<< "1. Клиенты " << endl
			<< "2. Показать заказы" << endl
			<< "3. Работа с меню" << endl
			<< "0. Выйти" << endl;

		switch (_getch()) {
		case '1': {
			system("cls");

			extern List<Client> clientList;

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
	cout << "Поиск клиента по номеру (0) или по имени (1)." << endl;
	cin >> variant;
	if (!variant && variant != 1) {
		cout << "Некорректный ввод";
		return;
	}

	extern List<Client> clientList;

	if (variant == 0) {
		int num;
		cout << "Введите номер: " << endl;
		cin >> num;

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
		if (name == "")
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

void Cook::view_orders() {
	extern List<Order> orderList;
	cout << "Заказы на неделю: " << endl;
	if (!orderList.size()) {
		cout << "Заказов нет." << endl;
	}
	
	extern List<Client> clientList;

	string dayArr[] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };

	for (auto c : orderList) {
		cout << dayArr[c->day_num-1] << " " << c->time << ": " << " Столик - " << c->table_num << endl;
	}

}

void Cook::work_menu() {
	extern List<Menu> menuList;

	string name;

	while (true) {
		system("cls");
		cout << "Введите действие:" << endl
			<< "1. Показать меню\n"
			<< "2. Добавить новое блюдо\n"
			<< "3. Удалить блюдо\n"
			<< "0. Выход\n";

		switch (_getch()) {
		case '1':
			system("cls");

			printf("| %-5s| %-16s| %-16s| %-16s|\n", "Номер", "Категория", "Название", "Главный ингредиент");
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
			cout << "Введите категорию: " << endl;
			cin >> type;
			cout << "Введите название: " << endl;
			cin >> name;
			cout << "Введите главный ингредиент: " << endl;
			cin >> main_pr;

			menuList.push(new Menu(menuList.size(), type, name, main_pr));
			cout << "Блюдо успешно добавлено в меню.";

			break;
		}
		case '3': {
			system("cls");

			size_t num;
			cout << "Введите номер блюда:" << endl;
			cin >> num;
			num--;
			if (num >= menuList.size()) {
				cout << "Такого блюда нет.";
				break;
			}
			menuList.erase(num);
			cout << "Удаление прошло успешно."; 

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