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
				next = NULL;
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
	Node<T> temp;

	while (front != null) {
		temp = front;
		front = 
	}
}