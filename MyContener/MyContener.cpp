#include <iostream>
#include <algorithm>

template <class T> class Node;
template <class T> class MyContr_iterator;


template<typename T>
class MyContr
{
public:

	MyContr();
	~MyContr();

	typedef MyContr_iterator<T> iterator;


	void push_back(T data); // Добовление в начало списка элемента 
	void push_front(T data);   // Добовление в конец списка элемента
	T Get_first_element();
	T Get_last_element();
	int GetSize();
	void print();
	iterator begin() const;
	iterator end() const;

private:

	Node<T>* head; // первый элемент
	int Size;      // размер списка
};

template<typename T>
class Node
{
public:

	T data; // поле данных
	Node* next; // указатель на следующий элемент
	Node* prev; // указатель на предыдущий элемент

	Node(T data = T(), Node* next = nullptr, Node* prev = nullptr)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};



template<typename T>
MyContr<T>::MyContr()
{
	Size = 0;
	head = nullptr;

}

template<typename T>
MyContr<T>::~MyContr()
{

}

template<typename T>
void MyContr<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>();
		head->data = data;
		head->next = head;
		head->prev = head;
		Size++;
	}
	else
	{
		Node<T>* temp, * p;
		temp = new Node<T>();
		p = head->next; // сохранение указателя на следующий узел
		head->next = temp; // предыдущий узел указывает на создаваемый
		temp->data = data; // сохранение поля данных добавляемого узла
		temp->next = p; // созданный узел указывает на следующий узел
		temp->prev = head; // созданный узел указывает на предыдущий узел
		p->prev = temp;
		Size++;
	}
}

template<typename T>
void MyContr<T>::push_front(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>();
		head->data = data;
		head->next = head;
		head->prev = head;
		Size++;
	}
	else
	{
		Node<T>* temp, * p;
		temp = new Node<T>();
		p = head->prev; // сохранение указателя на следующий узел
		head->prev = temp; // предыдущий узел указывает на создаваемый
		temp->data = data; // сохранение поля данных добавляемого узла
		temp->next = head; // созданный узел указывает на следующий узел
		temp->prev = p; // созданный узел указывает на предыдущий узел
		p->next = temp;
		Size++;
	}
}

template<typename T>
T MyContr<T>::Get_first_element()
{
	return head->data;
}

template<typename T>
T MyContr<T>::Get_last_element()
{
	Node<T>* temp;
	temp = new Node<T>();
	temp = head->prev;
	return temp->data;
}

template<typename T>
int MyContr<T>::GetSize()
{
	return Size;
}

template<typename T>
void MyContr<T>::print() // для Отладки
{

	Node<T>* p;
	p = head;

	do {
		printf("%d ", p->data); // вывод значения элемента p 
		p = p->next; // переход к следующему узлу
	} while (p != head); // условие окончания обхода
}

template <class T>
typename MyContr<T>::iterator MyContr<T>::begin() const
{
	return iterator(head);
}

template <class T>
typename MyContr<T>::iterator MyContr<T>::end() const
{
	Node<T>* temp;
	temp = new Node<T>();
	temp = head->prev;
	return iterator(temp);
}



template <class T> class MyContr_iterator
{
public:
	typedef MyContr_iterator<T> iterator;

	MyContr_iterator(Node<T>* source_link) : current_Node(source_link) { }
	MyContr_iterator() : current_Node(0) { }
	

	T& operator*();  // dereferencing operator
	bool operator==(const iterator& rhs) const;
	bool operator!=(const iterator& rhs) const;
	iterator& operator++();
	iterator operator++(int);
	iterator& operator--();
	

protected:
	Node<T>* current_Node;
	friend class Node<T>;
};

template<class T>
bool MyContr_iterator<T>::operator==(const iterator& rhs) const
{
	return (this->current_Node == rhs.current_Node);
}

template <class T>
bool MyContr_iterator<T>::operator!=(const iterator& rhs) const
{
	return !(*this == rhs);
}

template <class T>
T& MyContr_iterator<T>::operator*()
{
	return current_Node->data;
}

template <class T>
MyContr_iterator<T>& MyContr_iterator<T>::operator++()
{
	current_Node = current_Node->next;
	return *this;
}

template<class T>
MyContr_iterator<T> MyContr_iterator<T>::operator++(int)
{
	current_Node = current_Node->next;
	return current_Node;
}

template <class T>
MyContr_iterator<T>& MyContr_iterator<T>::operator--()
{
	current_Node = current_Node->prev;
	return *this;
}




int main()
{

	MyContr<int> cont;

	cont.push_back(5);
	cont.push_back(10);

	cont.push_front(200);
	cont.push_front(400);

	cont.push_back(15);
	cont.push_front(500);

	std::cout << "Get_first_elemen = " << cont.Get_first_element() << std::endl;
	std::cout << "Get_last_element = " << cont.Get_last_element() << std::endl;
	std::cout << "GetSize = " << cont.GetSize() << std::endl;

	std::cout << std::endl;


	MyContr<int>::iterator itr(cont.begin());
	 do {
		 
		std::cout << *itr << std::endl;
		itr++;

	 } while (itr != cont.begin());

	return 0;
};