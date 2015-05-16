
#include <iostream>
using namespace std;

class int_queue {
private:
	//an array of queued integers
	int elements[20];
	//index of front element in the queue
	int front;
	//index of next available empty place at back
	int back;

public:
	int_queue() { //Constructor
	
		for (int i = 0; i < 20; i++) {
			elements[i] = 0;
			}
		front = 0;
		back = 0;
	}
	
	bool full() { return back == 20;}
	bool empty() { return front == back;}
	
	int get() { 
		if (empty()) {
			cout << "Queue is empty!";
			return 0;
		}
		else {
			int temp = 0;
			temp = elements[front];
			elements[front] = 0;
			front = front - 1;
			return temp;
		}
	}
	int put (int n) { 
		if (full()) {
			cout << "Queue is full!";
		}
		else {
			elements[back++] = n;
		}
	}
	
	void show_q() {
		cout << "Queue is ";
		for (int i = 0; i < 20; i++) {
			cout << elements[i] << " ";
		}
		cout << "\n";
	}
};
	

int main(void) {
	char ans = 'a';
	int_queue que;
	que.show_q();
	
	while(ans != 'e') {
		cout << "Enter get or put or exit [g/p/e] : ";
		cin >> ans;
	
		if (ans == 'p') {
			int a = 0;
			cout << "Enter integer (>0) : ";
			cin >> a;
			que.put(a);		
		}
		else if (ans == 'g');
		{
			cout << "Take from queue " << que.get();		
			cout << '\n';
		}
		
		que.show_q();
	}
	
	cout << "Goodbye";
}

