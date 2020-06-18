// MyArray.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class MyArray
{
protected:
	//сколько памяти выделено
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//конструкторы и деструктор
	MyArray(int Dimension = 100)
	{
		cout << "\nMyArray constructor";
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}

	//конструктор принимает существующий массив
	MyArray(double* arr, int len)
	{
		cout << "\MyArray constructor";
		capacity = len;
		count = len;
		ptr = new double[len];
		for (int i = 0; i < len; i++)
			ptr[i] = arr[i];
	}
	//деструктор
	~MyArray()
	{
		cout << "\nMyArray destructor";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

	//обращение к полям
	int Capacity() { return capacity; }

	int Size() { return count; }

	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		//сгенерировать исключение, если индекс неправильный
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		else
			throw "Wrong Index";
		//сгенерировать исключение, если индекс неправильный
	}

	//добавление в конец нового значения
	void AddValue(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
		else 
			throw "Array is filled";
		//что делаем, если массив заполнен?
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count >= 0)
			count--;
		else
			throw "There is no elements in array";
		//что делаем, если пуст?
	}

	double& operator[](int index)
	{
		//перегрузка оператора []
		if (index < 0 || index >= count)
			throw "Wrong Index";
		return ptr[index];
	}

	MyArray& operator=(const MyArray& V)
	{
		cout << "\noperator = ";
		if (capacity != V.capacity)
		{
			capacity = V.capacity;
			count = V.count;
			ptr = new double[count];
				for (int i = 0; i < count; i++)
					ptr[i] = V.ptr[i];
	
		}
		else 
		{
			count = V.count;
			for (int i = 0; i < V.count; i++)
				ptr[i] = V.ptr[i];
		}
		return *this;
	}

	MyArray(const MyArray& V)
	{
		cout << "\nCopy constructor";
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
		capacity = V.capacity;
		count = V.count;
		ptr = new double[count];
		for (int i = 0; i < count; i++)
			ptr[i] = V.ptr[i];
	}

	virtual void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}



};

class MySortedArray : public MyArray
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MySortedArray(int Dimension = 100) : MyArray(Dimension) { cout << "\nMySortedArray constructor"; }

	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

	MySortedArray(const MySortedArray& V)
	{
		cout << "\nCopy constructor";
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
		capacity = V.capacity;
		count = V.count;
		ptr = new double[count];
		for (int i = 0; i < count; i++)
			ptr[i] = V.ptr[i];
		sort(ptr);
	}

	void print()
	{
		cout << "\nMyArrChild, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

	void sort(double* arr) { // Сортировка массива пузырьком O(n^2) - максимум
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					// меняем элементы местами
					double temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

	//добавление в конец нового значения
	void AddValue(double value) // Добавление файла. Сначала ищется ближайший элемент, больший чем добавляемый.
		//Потом массив сдвигается на один элемент до найденного индекса и в этот индекс вставляется новое значение
	{
		if (count < capacity)
		{
			int index = 0;
			for (int i = 0; i < count; i++) {
				if (ptr[i] < value) {
					index = i;
					break;
				}
			}

			for (int i = count; i > index; i++) 
				ptr[i] = ptr[i - 1];

			ptr[index] = value;

			count++;
		}
		else
			throw "Array is filled";
		//что делаем, если массив заполнен?
	}

	int indexOf(double value) { // Нахождение индекса заданного файла через бинарный поиск. О(log(n))  - максимум

		int left = 0; 
		int right = count;
		int index = -1; // найденный индекс элемента равен -1 (элемент не найден)
		while (left <= right) // пока левая граница не "перескочит" правую
		{
			int mid = (left + right) / 2; // ищем середину отрезка
			if (value == ptr[mid]) {  // если ключевое поле равно искомому
				index = mid;     // мы нашли требуемый элемент,
				break;            // выходим из цикла
			}
			if (value < ptr[mid])     // если искомое ключевое поле меньше найденной середины
				right = mid - 1;  // смещаем правую границу, продолжим поиск в левой части
			else                  // иначе
				left = mid + 1;   // смещаем левую границу, продолжим поиск в правой части
		}
		return index;
	}

	double quantile(double prob) { // Подсчет квантиля для заданной вероятности, О(1)  - максимум
		int index = ceil(count * prob);
		return index;
	}

	//выделение подпоследовательности
	//MySortedArray SubSequence(int StartIndex = 0, int Length = -1)

};

int main()
{
	
		//MyArray arr;
		MySortedArray arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			//функция AddValue() принадлежит родителю класса MySortedArray
			//Но пользоваться открытыми функциями родителя можно
			arr.AddValue(i + 1);
		}
		//MyArray p1;
		//p1 = arr;
		arr.print();
		cout << "\n";
		cout << arr.quantile(0.65);

	char c; 
	cin >> c;
	return 0;
}
