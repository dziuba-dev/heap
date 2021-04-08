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
	testHeap->show();
	delete testHeap;

	Heap<int>* testHeap1 = new MinHeap<int>;
	testHeap1->insertValue(10);
	testHeap1->insertValue(9);
	testHeap1->insertValue(8);
	testHeap1->insertValue(7);
	testHeap1->insertValue(6);
	testHeap1->insertValue(5);
	testHeap1->insertValue(4);
	testHeap1->insertValue(3);
	testHeap1->insertValue(2);
	testHeap1->insertValue(1);
	testHeap->show();
	delete testHeap1;
}
