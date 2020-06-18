// LinkedList.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
// LinkedList.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>

using namespace std;

class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	double field;
public:
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field

	virtual double getValue() { return field; }
	virtual void setValue(double value) { field = value; }
};

class LinkedList
{
protected:
	//достаточно хранить только начало
	Element* begin;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }

	virtual Element* getBegin() { return begin; }

	LinkedList()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		begin = NULL;
		num = 0;
	}

	virtual Element* push(double a)
	{
		//положить элемент в конец
		Element* cur = begin;
		if (begin == NULL)
		{
			//ничего в списке нет
			num = 1;
			begin = new Element;
			begin->setValue(a);
			begin->setNext(NULL);
			return begin;
		}
		//ищем последний элемент - добавить аналогичную рекурсивную процедуру
		while (cur->getNext() != NULL)
		{
			cur = cur->getNext();
		}
		num++;
		//вставка элемента
		cur->setNext(new Element);
		cur->getNext()->setValue(a);
		cur->getNext()->setNext(NULL);

		return cur->getNext();
	}

	virtual Element* push_r(double a, Element* current = NULL)
	{
		//положить элемент в конец - рекурсивная версия

		//в списке нет элементов - цепляем в начало добавляемый элемент
		if (begin == NULL)
		{
			//ничего в списке нет
			num = 1;
			begin = new Element;
			begin->setValue(a);
			begin->setNext(NULL);
			return begin;
		}
		//ничего не передано в функцию - по умолчанию начинаем поиск свободного места с начала списка
		if (current == NULL)
			current = begin;


		//мы находимся где-то в списке - ищем последний элемент рекурсивно
		if (current->getNext() != NULL)
			return push_r(a, current->getNext());
		//указатель на следующий элемент свободен - цепляем туда новый. Здесь рекурсия закончится 
		if (current->getNext() == NULL)
		{
			current->setNext(new Element);
			current->getNext()->setValue(a);
			current->getNext()->setNext(NULL);
			num++;
			return current->getNext();
		}
	}
	virtual double pop()
	{
		//вытащить элемент с конца
		Element* cur = begin;
		Element* prev = NULL;
		//отдельно рассмотрим случай 0/1 элементов
		if (begin == NULL)
		{
			return -1;
		}
		if (num == 1)
		{
			double res = begin->getValue();
			num--;
			return res;
		}
		//ищем последний и предпоследний элемент
		while (cur->getNext() != NULL)
		{
			prev = cur;
			cur = cur->getNext();
		}
		//сохраняем результат
		double res = cur->getValue();
		//предпоследний стал последним
		prev->setNext(NULL);
		//последнего стёрли
		delete cur;
		//число элементов снизилось на 1	
		num--;
		//возвращаем удаленный элемент
		return res;
	}


	~LinkedList()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element* cur = begin;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	virtual void print()
	{
		//итеративная версия вывода списка - стандартный цикл перебора всех элементов
		Element* cur = begin;
		while (cur != NULL)
		{
			cout << cur->getValue() << "\n";
			cur = cur->getNext();
		}
	}

	virtual void print_r(Element* current = NULL)
	{
		//рекурсивная версия вывода списка 
		if (current == NULL)
			current = begin;
		if (current != NULL)
		{
			cout << current->getValue() << "\n";
			//применяем функцию к следующему элементу
			if (current->getNext() != NULL)
				print_r(current->getNext());
		}

	}

	LinkedList& operator=(const LinkedList& list)
	{
		begin = list.begin;
		num = list.num;
	}

	LinkedList(const LinkedList& list) {
		begin = NULL;
		Element* listBegin = list.begin;

		push(listBegin->getValue());

		Element* nextElem = listBegin->getNext();

		for (int i = 1; i < list.num; i++) {
			push(nextElem->getValue());
			nextElem->getNext();
		}
	}

	friend ostream& operator<< (ostream& ustream, LinkedList& obj);
	friend istream& operator>> (istream& ustream, LinkedList& obj);
};

ostream& operator << (ostream& ustream, LinkedList& obj)
{
	cout << "\n" << typeid(ustream).name() << "\n";
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

istream& operator >> (istream& ustream, LinkedList& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

class LinkedListChild : public LinkedList
{
public:
	LinkedListChild() : LinkedList() { cout << "\nChild constructor"; }

	~LinkedListChild() { cout << "\nChild destructor"; }

	virtual Element* insert(Element* current, double value)
	{
		//вставка элемента со значением value в список сразу за элементом current
		//используем другую версию insert()
		Element* newElem = new Element;
		newElem->setNext(NULL);
		newElem->setValue(value);

		return insert(current, newElem);
	}

	virtual Element* insert(Element* current, Element* newElem)
	{
		//вставка элемента newElem в список сразу за элементом current
		if (current == NULL)
		{
			//ищем последний, если список не пуст

			return push(newElem->getValue());

		}

		newElem->setNext(current->getNext());
		current->setNext(newElem);
		num++;


		//список не пустой, current!=NULL

		return current->getNext();
	}

	void remove(Element* current)
	{
		//удаление элемента
		if (current != NULL)
		{
			Element* previous = begin;
			//условие для последнего элемента
			while (previous->getNext() != current)
			{
				previous = previous->getNext();
			}
			//previous - предыдущий элемент для удаляемого
			//current->getNext()
			previous->setNext(current->getNext());
			num--;

			//освобождение памяти
			delete current;
		}
	}

	virtual Element* find(double value_to_find)
	{

		//поиск в списке. value_to_find - значение, которое мы сравниваем при поиске с полем find в элементе списка
		//если нашли, - возвращаем указатель на элемент списка

		//1.  список закончился current==NULL
		//2.  current->getValue() == value_to_find
		Element* current = begin;
		while (current != NULL)
		{
			//нашли элемент
			if (current->getValue() == value_to_find)
				return current;
			current = current->getNext();
		}
		return NULL;
	}

	LinkedListChild& operator=(const LinkedListChild& list)
	{
		begin = list.begin;
		num = list.num;
	}

	LinkedListChild(const LinkedListChild& list) {
		begin = NULL;
		Element* listBegin = list.begin;

		push(listBegin->getValue());

		Element* nextElem = listBegin->getNext();

		for (int i = 1; i < list.num; i++) {
			push(nextElem->getValue());
			nextElem->getNext();
		}
	}
};


class DoubleSidedLinkedList : public LinkedListChild
{
protected:
	//указатель на конец списка
	Element* end;
public:
	DoubleSidedLinkedList() : LinkedListChild() { cout << "\nDoubleSidedLinkedList constructor"; end = NULL; }
	~DoubleSidedLinkedList() { cout << "\nDoubleSidedLinkedList destructor"; }

	virtual Element* getEnd() { return end; }

	virtual Element* push(double value)
	{
		//O(n)

		Element* added_element = new Element;

		added_element->setValue(value);

		if (end != NULL)
		{
			//O(1)
			//Element* added_element = LinkedListChild::insert(end, value);
			//много элементов
			end->setNext(added_element);
			added_element->setPrevious(end);
			end = added_element;
		}
		else
		{
			begin = added_element;
			//добавляем первый элемент
			end = added_element;
		}
		return end;
	}

	virtual double pop() {
		double value = end->getValue();
		remove(end);
		return value;
	}

	virtual Element* insert(Element* current, double value)
	{
		Element* inserted_element;
		if (current == NULL)
		{
			inserted_element = push(value);
			return inserted_element;
		}
		else
		{
			//известно, за каким элементом вставка
			inserted_element = LinkedListChild::insert(current, value);
			if (inserted_element->getNext() != NULL)
				inserted_element->getNext()->setPrevious(inserted_element);
			inserted_element->setPrevious(current);
		}

		return inserted_element;
	}

	void remove(Element* current)
	{
		//удаление элемента
		if (current != NULL)
		{
			Element* next = current->getNext();
			Element* previous = current->getPrevious();
			
			if (num == 1) {
				begin = end = NULL;
			}else if (current == end) {
				end = previous;
				previous->setNext(NULL);
			} else if (current == begin) {
				begin = next;
				previous->setPrevious(NULL);
			}
			else {
				next->setPrevious(previous);
				previous->setNext(next);
			}

			num--;

			//освобождение памяти
			delete current;
		}
	}

	virtual Element* find(double value_to_find)
	{

		//поиск в списке. value_to_find - значение, которое мы сравниваем при поиске с полем find в элементе списка
		//если нашли, - возвращаем указатель на элемент списка

		//1.  список закончился current==NULL
		//2.  current->getValue() == value_to_find
		Element* current = begin;
		while (current != NULL)
		{
			//нашли элемент
			if (current->getValue() == value_to_find)
				return current;
			current = current->getNext();
		}
		return NULL;
	}

	void split(Element* delimetr, DoubleSidedLinkedList& list1, DoubleSidedLinkedList& list2) {
		Element* element = begin;

		while (element != delimetr) {
			list1.push(element->getValue());
			element = element->getNext();
		}
		
		list2.push(element->getValue());

		while (element != NULL) {
			list2.push(element->getValue());
			element = element->getNext();
		}
		
	};

};

DoubleSidedLinkedList* merge(DoubleSidedLinkedList& list1, DoubleSidedLinkedList& list2) {

	DoubleSidedLinkedList list(list1);

	Element* element = list2.getBegin();

	while(element != NULL) {
		list.push(element->getValue());
		element = element->getNext();
	}

	return &list;
};


int main()
{
	DoubleSidedLinkedList list;
	list.push(1.);
	list.push(2.);
	list.push(3.);
	list.push(4.);
	list.print();

	cout << endl << endl;

	cout << list.find(1) << endl;

	cout << endl << endl;

	list.insert(list.getBegin(), 12);

	list.print();

	cout << endl << endl;

	list.remove(list.find(3.));

	list.print();



	char c; cin >> c;
	return 0;
}

