#include <iostream>
#include "heap.h"
#include "minHeap.h"
#include "maxHeap.h"
using namespace std;

int main()
{
	Heap<int>* testHeap = new MaxHeap<int>;
	testHeap->insertValue(1);
	testHeap->insertValue(2);
	testHeap->insertValue(3);
	testHeap->insertValue(4);
	testHeap->insertValue(5);
	testHeap->insertValue(6);
	testHeap->insertValue(7);
	testHeap->insertValue(8);
	testHeap->insertValue(9);
	testHeap->insertValue(10);

	for (int i = 0; i < 12; i++) {
		cout << testHeap->extract() << endl;
	}
	cout << endl;

	delete testHeap;

	Heap<string>* testHeap1 = new MinHeap<string>;
	testHeap1->insertValue("lorem");
	testHeap1->insertValue("ipsum");
	testHeap1->insertValue("dolor");
	testHeap1->insertValue("sit");
	testHeap1->insertValue("amet");
	testHeap1->insertValue("consectetur");
	
	for (int i = 0; i < 8; i++) {
		cout << testHeap1->extract() << endl;
	}
	cout << endl;
	delete testHeap1;
}
