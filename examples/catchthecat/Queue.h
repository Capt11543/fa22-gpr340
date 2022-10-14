#pragma once

template<typename T>
class Queue {
	private:
		template<typename R>
		struct Node {
			R data;
			Node<R>* next;

			Node() {
				data = R();
				next = NULL;
			}
			
			Node(R data) {
				this->data = data;
				next = nullptr;
			}
		};
		
		int count;
		Node<T>* front, rear;
	public:
		void clear();
		T dequeue();
		void enqueue(T data);
		bool exists(T key);
		int getCount();
		bool isEmpty();
		Queue();
		~Queue();
};

template<typename T>
void Queue<T>::clear() {
	Node<T>* temp;

	while (front != nullptr) {
		temp = front;
		front = front->next;
		temp->next = nullptr;
		delete temp;
	}

	rear = nullptr;
	count = 0;
}

template<typename T>
T Queue<T>::dequeue() {
	Node<T>* temp;
	T data = T();

	if (front != nullptr) {
		temp = front;
		front = front->next;

		data = temp->data;
		temp->next = null;
		delete temp;

		count--;
	}

	return data;
}

template<typename T>
void Queue<T>::enqueue(T data) {
	Node<T>* newNode;

	newNode = new Node<T>(data);
}