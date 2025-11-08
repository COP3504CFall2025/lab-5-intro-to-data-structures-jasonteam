#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
public:

	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }
	Node* getTail() { return tail; }
	const Node* getTail() const { return tail; }

	// Insertion
	void addHead(const T& data);
	void addTail(const T& data);

	// Removal
	bool removeHead();
	bool removeTail();
	void clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};

template <typename T>
LinkedList<T>::LinkedList() {
	count = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	this->clear();
}

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
	this->count = 0;				// Set count to 0
	Node* curr = other.head;				// Current node pointer for the other object
	while (curr) {
		this->addTail(curr->data);			// Use addTail to add nodes to THIS LL
		curr = curr->next;					// Also will create the head and tail automatically :D
	}
}

// Copy Assignment Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	this->count = 0;				// Set count to 0
	Node* curr = rhs.head;				// Current node pointer for the other object
	while (curr) {
		this->addTail(curr->data);			// Use addTail to add nodes to THIS LL
		curr = curr->next;					// Also will create the head and tail automatically :D
	}
	return *this;
}

// Move Constructor
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
	this->count = 0;				// Set count to 0
	Node* curr = other.head;				// Current node pointer for the other object
	while (curr) {
		this->addTail(curr->data);			// Use addTail to add nodes to THIS LL
		curr = curr->next;					// Also will create the head and tail automatically :D
		other.removeHead();					// Delete the last node from other
	}
	other.count = 0;
	other.head = nullptr;
	other.tail = nullptr;
}

// Move Assignment Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& rhs) noexcept {
	if (this == &rhs) {
		return *this;
	}
	this->count = 0;				// Set count to 0
	Node* curr = rhs.head;				// Current node pointer for the other object
	while (curr) {
		this->addTail(curr->data);			// Use addTail to add nodes to THIS LL
		curr = curr->next;					// Also will create the head and tail automatically :D
		rhs.removeHead();					// Delete the last node from other
	}
	rhs.count = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;

	return *this;
}

template <typename T>
void LinkedList<T>::addHead(const T& data){
	if (count == 0) {						// If no nodes in LinkedList
		head = new Node();					// Create new node
		tail = head;						// Set tail to head because only one node
		head->data = data;					// Give node data
		head->next = nullptr;
		head->prev = nullptr;
		// Node head and tail pointer are null because nothing to point
	} else {
		Node* tempPtr = new Node();			// Create new node
		tempPtr->data = data;				// Set the data into the node
		tempPtr->next = head;				// Set the next pointer node to the current head address
		tempPtr->prev = nullptr;
		head->prev = tempPtr;				// Set the previous pointer of the previous head to the new head
		head = tempPtr;						// Set the head pointer to new head pointer
	}
	count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data) {
	if (count == 0) {						// If no nodes in LinkedList
		tail = new Node();					// Create new node
		head = tail;						// Set tail to head because only one node
		tail->data = data;					// Give node data
		tail->next = nullptr;
		tail->prev = nullptr;
		// Node head and tail pointer are null because nothing to point
	} else {
		Node* tempPtr = new Node();			// Create new node
		tempPtr->data = data;				// Set the data into the node
		tempPtr->next = nullptr;
		tempPtr->prev = tail;				// Set the prev pointer node to the current tail address
		tail->next = tempPtr;				// Set the next pointer of the previous tail to the new tail
		tail = tempPtr;						// Set the tail pointer to new tail pointer
	}
	count++;
}

template <typename T>
bool LinkedList<T>::removeHead() {
	if (count <= 0) {
		return false;						// If nothing in the LL
	} else if (count == 1) {
		delete head;						// Delete the head
		head = nullptr;						// Set head pointer to null
		tail = nullptr;						// But also set tail pointer to null
	} else {
		head = head->next;					// Set new head to next Node of head
		delete head->prev;					// Delete the previous head
		head->prev = nullptr;				// Set previous pointer to nullptr			
	}
	count--;
	return true;
}

template <typename T>
bool LinkedList<T>::removeTail() {
	if (count <= 0) {
		return false;						// If nothing in the LL
	} else if (count == 1) {
		delete tail;						// Delete the tail
		head = nullptr;						// Set head pointer to null
		tail = nullptr;						// But also set tail pointer to null
	} else {
		tail = tail->prev;					// Set new tail to previous Node of tail
		delete tail->next;					// Delete the next tail
		tail->next = nullptr;				// Set next pointer to nullptr				
	}
	count--;
	return true;
}

template <typename T>
void LinkedList<T>::clear() {
	while (head || tail) {					// While head and tail pointer are real
		removeHead();						// Delete the head until nothing is left.
		removeTail();						// Delete the tail until nothing is left.
		printForward();
	}
}

template <typename T>
void LinkedList<T>::printForward() const {
	Node* curr = head;
	while (curr) {
		std::cout << curr->data << " ";
		curr = curr->next;
	}
}

template <typename T>
void LinkedList<T>::printReverse() const {
	Node* curr = tail;
	while (curr) {
		std::cout << curr->data << " ";
		curr = curr->prev;
	}
}



