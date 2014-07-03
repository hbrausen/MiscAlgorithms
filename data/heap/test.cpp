#include "heap.cpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv)
{
	Heap<int> H;
	srand(time(NULL));
	
	for (int i = 0; i < 20; ++i) H.Insert(rand());
	while (H.Size() > 0) {
		cout << H.Top() << endl;
		H.Pop();
	}
	
	cout << endl;
	
	vector<int> toHeap;
	for (int i = 0; i < 20; ++i) toHeap.push_back(rand());
	H.Heapify(toHeap);
	while (H.Size() > 0) {
		cout << H.Top() << endl;
		H.Pop();
	}
	
	return 0;
}
