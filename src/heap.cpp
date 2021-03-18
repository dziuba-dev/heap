#include <iostream>
#include "heap.h"
#include "minHeap.h"
#include "maxHeap.h"
using namespace std;

int main()
{
	Heap<int>* testHeap = new MaxHeap<int>;
	delete testHeap;
}
