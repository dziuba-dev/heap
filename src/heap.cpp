#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "heap.h"
#include "minHeap.h"
#include "maxHeap.h"
using namespace std;

template<class ValueType> void getValidValue(ValueType& value);
template<class ValueType> void getValueFromRange(ValueType& value, int min, int max);

int chooseMode();
void chooseHeapProperties(int& heapType, int& valueType);
int showMenu();
template<class ValueType> void heapMode(int heapType);
template<class ValueType> void sortMode(int heapType);

template<class ValueType> void crateHeap(Heap<ValueType>** heap, int heapType);
template<class ValueType> void insertToHeap(Heap<ValueType>* heap);
template<class ValueType> void getFromHeap(Heap<ValueType>* heap);
template<class ValueType> void getArray(vector <ValueType>& newValues);


int main()
{
	int mode = chooseMode();
	int heapType, valueType;
	chooseHeapProperties(heapType, valueType);

	if (mode == 1) {
		switch (valueType) {
		case 3:
			heapMode<string>(heapType);
			break;
		case 2:
			heapMode<float>(heapType);
			break;
		default:
			heapMode<int>(heapType);
			break;
		}
	}
	else {
		switch (valueType) {
		case 3: 
			sortMode<string>(heapType);
			break;
		case 2:
			sortMode<float>(heapType);
			break;
		default: 
			sortMode<int>(heapType);
			break;
		}
	}
}


template<class ValueType>
void getValidValue(ValueType& value) {
	cin.clear();
	cin.sync();
	cin >> value;

	while (cin.fail()) {
		getchar();
		cin.clear();
		cin.sync();
		cout << "Niepoprawny wybor. Sprobuj jeszcze raz: ";
		cin >> value;
	}
}

template<class ValueType>
void getValueFromRange(ValueType& value, int min, int max) {
	getValidValue(value);
	while (value < min || value > max) {
		cout << "Niepoprawny wybor. Sprobuj jeszcze raz: ";
		getValidValue(value);
	}
}

int chooseMode() {
	int choice;
	cout << "--KOPIEC--" << endl;
	cout << "1. Dodawanie i usuwanie wartosci z kopca" << endl;
	cout << "2. Posortuj z uzyciem kopca" << endl;
	cout << "Wybierz opcje (1-2): ";
	getValueFromRange(choice, 1, 2);
	system("CLS");
	return choice;
}

void chooseHeapProperties(int& heapType, int& valueType) {
	cout << "Wybierz parametry dla nowego kopca" << endl;
	cout << "I Typ kopca: " << endl;
	cout << "1. Kopiec typu max" << endl;
	cout << "2. Kopiec typu min" << endl;
	cout << "Podaj typ (1-2): ";
	getValueFromRange(heapType, 1, 2);
	cout << endl;

	cout << "II Wartosci w kopcu: " << endl;
	cout << "1. Liczby calkowite" << endl;
	cout << "2. Liczby zmiennoprzecinkowe" << endl;
	cout << "3. Slowa" << endl;
	cout << "Podaj typ (1-3): ";
	getValueFromRange(valueType, 1, 3);
	system("CLS");
}

int showMenu() {
	int choice;
	cout << "--MENU--" << endl;
	cout << "1. Dodaj" << endl;
	cout << "2. Usun" << endl;
	cout << "3. Zwroc" << endl;
	cout << "4. Wyjdz" << endl;
	cout << "Wybierz opcje (1-4): ";
	getValueFromRange(choice, 1, 4);
	system("CLS");
	return choice;
}

template<class ValueType>
void crateHeap(Heap<ValueType>** heap, int heapType) {
	if (heapType == 1) {
		*heap = new MaxHeap<ValueType>;
	}
	else {
		*heap = new MinHeap<ValueType>;
	}
}

template<class ValueType>
void insertToHeap(Heap<ValueType>* heap) {
	ValueType newValue;

	cout << "DODAJ WARTOSC" << endl;
	cout << "Podaj nowa wartosc: ";
	getValidValue(newValue);
	heap->insertValue(newValue);
}

template<class ValueType>
void getFromHeap(Heap<ValueType>* heap) {
	cout << "ZWROC WARTOSC" << endl;
	cout << "Wartosc w korzeniu kopca to: ";
	//heap->get();
	Sleep(2000);
}

template<class ValueType>
void getArray(vector <ValueType>& newValues) {
	int number;
	ValueType newValue;

	cout << "PODAJ WARTOSCI DO SORTOWANIA" << endl;
	cout << "Ile wartosci chcesz dodac? ";
	getValidValue(number);
	system("CLS");
	cout << "PODAJ WARTOSCI DO SORTOWANIA" << endl;
	cout << "(Wpisz wartosc i kliknij Enter)" << endl;

	for (int i = 0; i < number; i++) {
		cout << "Wartosc nr " << i + 1 << ": ";
		getValidValue(newValue);
		newValues.push_back(newValue);
	}
	system("CLS");
}

template<class ValueType>
void heapMode(int heapType) {
	Heap<ValueType>* heap;
	int choice;

	cout << "--KOPIEC--" << endl;
	crateHeap(&heap, heapType);
	system("CLS");
	do {
		cout << "--KOPIEC--" << endl;
		heap->show();
		choice = showMenu();

		switch (choice)
		{
		case 1:
			insertToHeap(heap);
			break;
		case 2:
			heap->extract();
			break;
		case 3:
			getFromHeap(heap);
			break;
		default:
			break;
		}
		system("CLS");

	} while (choice != 4);
	delete heap;
}

template<class ValueType>
void sortMode(int heapType) {
	Heap<ValueType>* heap;
	vector <ValueType> values;

	cout << "--SORTOWANIE PRZEZ KOPCOWANIE--" << endl;
	crateHeap<ValueType>(&heap, heapType);
	getArray<ValueType>(values);
	cout << "Posortowane wartosci: ";
	//heap->sort(values);
	delete heap;
}