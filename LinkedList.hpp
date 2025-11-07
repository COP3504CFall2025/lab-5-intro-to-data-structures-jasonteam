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
	void PrintForward() const;
	void PrintReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const { return count; }
	Node* getHead() { return head; }
	const Node* getHead() const { return head; }
	Node* getTail() { return tail; }
	const Node* getTail() const { return tail; }

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	void Clear();

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
}

template <typename T>
LinkedList<T>::~LinkedList() {
	count = 0;
	Node* curr = head;
	while (curr && curr->next) {			// While the next pointer in the current node isn't null
											// Also make sure the curr ptr isnt null if the LL was already Cleared
		curr = curr->next;					// Set current pointer to the next node
		delete curr->prev;					// Delete the previous node of this node (i.e the og node)
	}
	delete curr;							// Delete the current pointer, should be the last one
	head = nullptr;							// Set head and tail pointers to nullptr
	tail = nullptr;							// No dangling pointers pls
}

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
	this->count = 0;				// Set count to 0
	Node* curr = other.head;				// Current node pointer for the other object
	while (curr) {
		this->AddTail(curr->data);			// Use AddTail to add nodes to THIS LL
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
		this->AddTail(curr->data);			// Use AddTail to add nodes to THIS LL
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
		this->AddTail(curr->data);			// Use AddTail to add nodes to THIS LL
		curr = curr->next;					// Also will create the head and tail automatically :D
		other.RemoveHead();					// Delete the last node from other
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
		this->AddTail(curr->data);			// Use AddTail to add nodes to THIS LL
		curr = curr->next;					// Also will create the head and tail automatically :D
		rhs.RemoveHead();					// Delete the last node from other
	}
	rhs.count = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;

	return *this;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data){
	if (count == 0) {						// If no nodes in LinkedList
		head = new Node();					// Create new node
		tail = head;						// Set tail to head because only one node
		head->data = data;					// Give node data
		// Node head and tail pointer are null because nothing to point
	} else {
		Node* tempPtr = new Node();			// Create new node
		tempPtr->data = data;				// Set the data into the node
		tempPtr->next = head;				// Set the next pointer node to the current head address
		head->prev = tempPtr;				// Set the previous pointer of the previous head to the new head
		head = tempPtr;						// Set the head pointer to new head pointer
	}
	count++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	if (count == 0) {						// If no nodes in LinkedList
		tail = new Node();					// Create new node
		head = tail;						// Set tail to head because only one node
		tail->data = data;					// Give node data
		// Node head and tail pointer are null because nothing to point
	} else {
		Node* tempPtr = new Node();			// Create new node
		tempPtr->data = data;				// Set the data into the node
		tempPtr->prev = tail;				// Set the prev pointer node to the current tail address
		tail->next = tempPtr;				// Set the next pointer of the previous tail to the new tail
		tail = tempPtr;						// Set the tail pointer to new tail pointer
	}
	count++;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (count == 0) {
		return false;						// If nothing in the LL
	} else if (count == 1) {
		delete head;						// Delete the head
		head = nullptr;						// Set head pointer to null
		tail = nullptr;						// But also set tail pointer to null
	} else {
		Node* tmpPtr = head;				// Store address of current head
		head = head->next;					// Set new head to next Node of head
		delete tmpPtr;						// Delete the previous head
	}
	count--;
	return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (count == 0) {
		return false;						// If nothing in the LL
	} else if (count == 1) {
		delete tail;						// Delete the tail
		head = nullptr;						// Set head pointer to null
		tail = nullptr;						// But also set tail pointer to null
	} else {
		Node* tmpPtr = tail;				// Store address of current tail
		tail = tail->prev;					// Set new tail to previous Node of tail
		delete tmpPtr;						// Delete the previous tail
	}
	count--;
	return true;
}

template <typename T>
void LinkedList<T>::Clear() {
	while (count > 0) {					// While head and tail pointer are real
		RemoveHead();						// Delete the head until nothing is left.
		count--;
	}
}

template <typename T>
void LinkedList<T>::PrintForward() const {
	Node* curr = head;
	while (curr) {
		std::cout << curr->data << " ";
		curr = curr->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	Node* curr = tail;
	while (curr) {
		std::cout << curr->data << " ";
		curr = curr->prev;
	}
}



