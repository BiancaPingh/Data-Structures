#include <iostream>
#include <tuple>
#include <list>
#include <fstream>


//ex1

struct List {
	struct Node {
		int info;
		Node* urm, * prev;
	};

	int size = 0;
	Node* head=nullptr, * tail=nullptr;

	void print() {
		if (size == 0)
			std::cout << "Lista e goala";
		for (Node* nod = head;nod != nullptr;nod = nod->urm) {
			std::cout << nod->info << " ";
		}
	}

	void push_front(int key) {
		if (size == 0) {
			Node* nou = new Node{ key,nullptr,nullptr };
			head = nou;
			tail = nou;
			size++;
			return;
		}

		Node* nou = new Node{ key,head,nullptr };
		head->prev = nou;
		head = nou;
		size++;

	}

	void pop_front() {
		if (size == 0) {
			std::cout << "Nu este nimic in lista";
			return;
		}
		if (size == 1) {
			tail = nullptr;
			head = nullptr;
			size = 0;
			return;
		}
		Node* temp = head;
		head = head->urm;
		head->prev = nullptr;
		delete temp;
		size--;
	}

	void pop_back() {
		if (size == 0) {
			std::cout << "Nu este nimic in lista";
			return;
		}
		if (size == 1) {
			tail = nullptr;
			head = nullptr;
			size = 0;
			return;
		}
		Node* temp = tail;
		tail = tail->prev;
		tail->urm = nullptr;
		delete temp;
		size--;
	}

	void push_back(int key) {
		if (size == 0) {
			Node* nou = new Node{ key,nullptr,nullptr };
			head = nou;
			tail = nou;
			size++;
			return;
		}
		Node* nou = new Node{ key,nullptr,tail };
		tail->urm = nou;
		tail = nou;
		size++;
	}

	Node* find(int key) {
		for (Node* nod = head;nod != nullptr;nod = nod->urm) {
			if (nod->info == key)
				return nod;
		}
		return nullptr;
	}

	void insert_before(int key1, int key2) {
		Node* nou = find(key1);
		if (nou == nullptr) {
			push_back(key2);
			return;
		}
		if (nou == head) {
			push_front(key2);
			return;
		}
		Node* aux = new Node{ key2,nou,nou->prev };
		nou->prev->urm = aux;
		nou->prev = aux;
		size++;

	}
	void erase(Node * nod) {
		
		if (nod == nullptr) 
			return;

		if (nod == head) {
			pop_front();
			return;
		}

		if (nod == tail) {
			pop_back();
			return;
		}

		if (nod->prev == nullptr || nod->urm == nullptr) 
			return;

		nod->prev->urm = nod->urm;
		nod->urm->prev = nod->prev;
		size--;
		delete nod;
	}

	void remove(int key) {
		Node* nod = head;
		while (nod != nullptr) {
			if (nod->info == key) {
				Node* toDelete = nod;
				nod = nod->urm;  
				erase(toDelete);
			}
			else {
				nod = nod->urm;
			}
		}
	}

	int sizeOfList() {
		return size;
	}

	bool empty() {
		if (tail == head && head == nullptr)
			return true;
		return false;
	}
	
	void clear() {
		if (empty()) {
			std::cout << "Lista e goala";
			return;
		}
		Node* nod = tail;
		while (nod != nullptr) {
			Node* toDelete = nod;
			nod = nod->prev;  
			erase(toDelete);
		}
	}
	void copy(List& temp) {
		temp.head = temp.tail = nullptr;
		temp.size = 0;

		for (Node* current = head; current != nullptr; current = current->urm) {
			temp.push_back(current->info);
		}
	}
};

bool palindrom(List lista) {
	List temp;
	lista.copy(temp);
	
	int size = temp.size;
	for (int i = 0; i < size / 2 && !temp.empty(); i++) {
		if (temp.head->info != temp.tail->info)
			return false;
		temp.pop_back();
		temp.pop_front();
	}
	return true;
}

bool compare(List l1, List l2) {
	if (l1.sizeOfList() != l2.sizeOfList())
		return false;
	
	List aux1, aux2;
	l1.copy(aux1), l2.copy(aux2);
	while (!aux1.empty() && !aux2.empty()) {
		if (aux1.head->info != aux2.head->info)
			return false;
		aux1.pop_front();
		aux2.pop_front();
	}
	return true;
}



int main() {
	//ex1
	List myList;
	int choice, value, key1, key2;
	bool running = true;

	while (running) {
		std::cout << "\nMenu:\n";
		std::cout << "1. Add element to front\n";
		std::cout << "2. Add element to back\n";
		std::cout << "3. Remove element from front\n";
		std::cout << "4. Remove element from back\n";
		std::cout << "5. Find element\n";
		std::cout << "6. Insert before element\n";
		std::cout << "7. Remove element by key\n";
		std::cout << "8. Check if list is palindrome\n";
		std::cout << "9. Compare with another list\n";
		std::cout << "10. Print list\n";
		std::cout << "11. Clear list\n";
		std::cout << "12. Exit\n";
		std::cout << "Alege optiunea: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "Valoare pe care o adaugi in fata: ";
			std::cin >> value;
			myList.push_front(value);
			break;
		case 2:
			std::cout << "Valoare pe care o adaugi la final: ";
			std::cin >> value;
			myList.push_back(value);
			break;
		case 3:
			myList.pop_front();
			break;
		case 4:
			myList.pop_back();
			break;
		case 5:
			std::cout << "Elementul pe care vrei sa l gasesti: ";
			std::cin >> value;
			if (myList.find(value)) {
				std::cout << "A fost gasit.\n";
			}
			else {
				std::cout << "Nu a fost gasit.\n";
			}
			break;
		case 6:
			std::cout << "Element inainte de care vrei sa adaugi: ";
			std::cin >> key1;
			std::cout << "Valoarea pe care vrei sa o iserezi: ";
			std::cin >> key2;
			myList.insert_before(key1, key2);
			break;
		case 7:
			std::cout << "Ce valoare vrei sa stergi: ";
			std::cin >> value;
			myList.remove(value);
			break;
		case 8:
			if (palindrom(myList)) {
				std::cout << "Lista e palindrom.\n";
			}
			else {
				std::cout << "Lista nu e palindrom.\n";
			}
			break;
		case 9: {
			List anotherList;
			std::cout << "Ce elemente ai in lista? (se termina la -1): ";
			std::cin >> value;
			while (true && value!=-1) {
				anotherList.push_back(value);
				std::cin >> value;
			}
			if (compare(myList, anotherList)) {
				std::cout << "Listele sunt identice.\n";
			}
			else {
				std::cout << "Listele nu sunt identice.\n";
			}
			break;
		}
		case 10:
			myList.print();
			break;
		case 11:
			myList.clear();
			break;
		case 12:
			running = false;
			break;
		default:
			std::cout << "Aceasta nu e o optiune valida. \n";
			break;
		}
	}

	
	return 0;
}