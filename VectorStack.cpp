#include "VectorStack.h"

// ����� ���������� �����������
void VectorStack::reserve(int newCapacity) {
    if (newCapacity <= capacity) return;      // ����� ����������� ������ ���� �� ������ �������
    Stack* newMass = new Stack[newCapacity];  // �������� ������ ������� � ����� ������������
    for (int i = 0; i < lenght; ++i) newMass[i] = data[i]; // �������� �������� �� ������� ������� � �����
    delete[] data;           // ����������� ������ ������� �������
    data = newMass;          // ��������� ��������� �� ����� ������
    capacity = newCapacity;  // ��������� �������� �����������
}

// ����������� �����������
VectorStack::VectorStack(const VectorStack& old) : data(nullptr), lenght(old.lenght), capacity(old.capacity) {
    if (capacity) {
        data = new Stack[capacity];
        for (int i = 0; i < lenght; ++i) data[i] = old.data[i]; // �������� ��������
    }
}

// �������� ������������
VectorStack& VectorStack::operator=(const VectorStack& old) {
    if (this == &old) return *this; // ��������� �� ����������������
    delete[] data;                  // ����������� ������� ������
    lenght = old.lenght;
    capacity = old.capacity;
    data = capacity ? new Stack[capacity] : nullptr;         // �������� ����� ������
    for (int i = 0; i < lenght; ++i) data[i] = old.data[i];  // �������� ��������
    return *this;
}

// ����������
VectorStack::~VectorStack() { delete[] data; }

// ������ �������:
int VectorStack::size() const { return lenght; }         // ���������� ������� ������
bool VectorStack::empty() const { return lenght == 0; }  // ��������� �� �������


// ��������� ������� � ������:
Stack& VectorStack::operator[](int i) { return data[i]; }              // ��� ���������
const Stack& VectorStack::operator[](int i) const { return data[i]; }  // ��� ������

// ���������� ����� � �����
void VectorStack::push_back(const Stack& add) {
    if (lenght == capacity) reserve(capacity ? capacity * 2 : 1);  // ����������� ����������� ��� �������������
    data[lenght++] = add;  // ��������� ������� � ����������� �����
}

// �������� ���������� �����
void VectorStack::pop_back() { if (lenght) --lenght; }
