#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> L;

	for (int i = 0; i < 10; i++) { // Добавление 10 элементов в список
		L.push_back(i);
	}


	list<int>::iterator p = L.begin(); // Получение итератора
	
	while (p != L.end()) // Вывод элементов списка
	{
		cout << *p << " ";
		p++;
	}


	cout << endl << endl;

	p = L.begin();

	for (int i = 0; i < 5; i++) {
		p++;
	}

	L.insert(p, 12); // Вставка элемента в позицию, заданную итератором


	cout << endl << endl;

	p = L.begin();


	while (p != L.end())
	{
		cout << *p << " ";
		p++;
	}

	L.remove(6); // Удаление элемента


	cout << endl << endl;

	p = L.begin();

	while (p != L.end())
	{
		cout << *p << " ";
		p++;
	}

	cout << "Search element = 7, index = ";

	p = L.begin();

	int index = 0;
	while (p != L.end()) // Линейный поиск через итератор
	{
		if (*p == 7) {
			cout << index;
			break;
		}
		index++;
		p++;
	}

	char c; cin >> c;
	return 0;
}
