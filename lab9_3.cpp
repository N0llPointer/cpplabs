#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> L;

	for (int i = 0; i < 10; i++) {
		L.push_back(i);
	}

	cout << endl << endl;

	list<int>::iterator p = L.begin(); // Итератор
	
	while (p != L.end())
	{
		cout << *p << " ";
		p++;
	}


	char c; cin >> c;
	return 0;
}
